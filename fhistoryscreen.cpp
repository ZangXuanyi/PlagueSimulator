#include "fhistoryscreen.h"
#include "ui_fhistoryscreen.h"
#include "PlagueSimulatorLib.hpp"

#include <QApplication>
#include <QtCharts/qchart.h>
#include <QtCharts/qchartview.h>
#include <QtCharts/qlineseries.h>
#include <QtCharts/qvalueaxis.h>
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qwidget.h>
#include <QPen>
#include <QTabWidget>
#include <iostream>
//修改完成2024.05.31
QChartView* FHistoryScreen::GetPopHistoryChart(const Ethene::CWorld& world)
{
    QChart* chartPopulationHistory = new QChart;
    chartPopulationHistory->setTitle("Population History");
    chartPopulationHistory->setAnimationOptions(QChart::AllAnimations);

    QValueAxis* axisX = new QValueAxis;
    QValueAxis* axisY = new QValueAxis;

    axisX->setTitleText("Time");
    axisY->setTitleText("Population");

    axisX->setMin(0);
    axisY->setMin(0);
    axisY->setMax(world.originalPopulation);

    QPen penDarkCyan;
    penDarkCyan.setWidth(3);
    penDarkCyan.setColor(Qt::darkCyan);

    QPen penDarkRed;
    penDarkRed.setWidth(3);
    penDarkRed.setColor(Qt::darkRed);

    QPen penDarkGray;
    penDarkGray.setWidth(3);
    penDarkGray.setColor(Qt::darkGray);

    QLineSeries* healthy = new QLineSeries;
    healthy->setName("Healthy");
    healthy->setColor(Qt::darkCyan);
    healthy->setMarkerSize(25);
    healthy->setPen(penDarkCyan);

    QLineSeries* infected = new QLineSeries;
    infected->setName("Infected");
    infected->setColor(Qt::darkRed);
    infected->setMarkerSize(25);
    infected->setPen(penDarkRed);

    QLineSeries* dead = new QLineSeries;
    dead->setName("Dead");
    dead->setColor(Qt::darkGray);
    dead->setMarkerSize(25);
    dead->setPen(penDarkGray);

    int days = world.worldHistory.size();
    int i =0;
    for(i = 0;i<days;i++)
    {
        std::tuple<long,long,long>& t = world.worldHistory[i];
        healthy->append(i,std::get<0>(t));
        infected->append(i,std::get<1>(t));
        dead->append(i,std::get<2>(t));
    }

    chartPopulationHistory->addSeries(healthy);
    chartPopulationHistory->addSeries(infected);
    chartPopulationHistory->addSeries(dead);
    chartPopulationHistory->addAxis(axisX,Qt::AlignBottom);
    chartPopulationHistory->addAxis(axisY,Qt::AlignLeft);
    healthy->attachAxis(axisX);
    infected->attachAxis(axisX);
    dead->attachAxis(axisX);
    healthy->attachAxis(axisY);
    infected->attachAxis(axisY);
    dead->attachAxis(axisY);
    axisX->setLabelFormat("%d");
    axisY->setLabelFormat("%d");

    chartPopulationHistory->setAnimationDuration(2500);

    QChartView *pChartPopHistory = new QChartView(chartPopulationHistory);
    pChartPopHistory->setRenderHint(QPainter::Antialiasing);

    std::cout<<"Sucessfully add series to pop History"<<std::endl;
    return pChartPopHistory;
}

QChartView* FHistoryScreen::GetResHistoryChart(const Ethene::CWorld& world)
{
    QChart* chartMedicHistory = new QChart;
    chartMedicHistory->setTitle("Research History");
    chartMedicHistory->setAnimationOptions(QChart::AllAnimations);

    QValueAxis* axisX = new QValueAxis;
    QValueAxis* axisY = new QValueAxis;
    QValueAxis* axisY2 = new QValueAxis;

    axisX->setTitleText("Time");
    axisY->setTitleText("Investment");
    axisY2->setTitleText("Today's Total Investment");

    axisX->setMin(0);
    axisY->setMin(0);
    axisY2->setMin(0);


    QPen pen1;
    pen1.setWidth(3);
    pen1.setColor(Qt::cyan);

    QPen pen2;
    pen2.setWidth(3);
    pen2.setColor(Qt::darkRed);

    QPen pen3;
    pen3.setWidth(3);
    pen3.setColor(Qt::blue);

    QLineSeries* ttr = new QLineSeries;
    ttr->setName("Total Research");
    ttr->setColor(Qt::cyan);
    ttr->setMarkerSize(25);
    ttr->setPen(pen1);

    QLineSeries* rsr = new QLineSeries;
    rsr->setName("Research Requirement");
    rsr->setColor(Qt::darkRed);
    rsr->setMarkerSize(25);
    rsr->setPen(pen2);

    QLineSeries* todayttr = new QLineSeries;
    todayttr->setName("Today's Total research");
    todayttr->setColor(Qt::blue);
    todayttr->setMarkerSize(25);
    todayttr->setPen(pen3);

    int days = world.researchHistory.size();

    axisY->setMax(std::get<0>(world.researchHistory.at(days-1))*1.1);
    axisY2->setMax(std::get<2>(world.researchHistory.at(int(days/1.4)))*1.5);

    int i = 0;
    for(i = 0;i<days;i++)
    {
        std::tuple<long,long,long>& t = world.researchHistory[i];
        rsr->append(i,std::get<0>(t));
        ttr->append(i,std::get<1>(t));
        todayttr->append(i,std::get<2>(t));
    }

    chartMedicHistory->addSeries(ttr);
    chartMedicHistory->addSeries(rsr);
    chartMedicHistory->addSeries(todayttr);

    chartMedicHistory->addAxis(axisX,Qt::AlignBottom);
    chartMedicHistory->addAxis(axisY,Qt::AlignLeft);
    chartMedicHistory->addAxis(axisY2,Qt::AlignRight);

    ttr->attachAxis(axisX);
    ttr->attachAxis(axisY);

    rsr->attachAxis(axisX);
    rsr->attachAxis(axisY);

    todayttr->attachAxis(axisX);
    todayttr->attachAxis(axisY2);

    axisX->setLabelFormat("%d");
    axisY->setLabelFormat("%d");

    chartMedicHistory->setAnimationDuration(2500);

    QChartView *chartView = new QChartView(chartMedicHistory);
    chartView->setRenderHint(QPainter::Antialiasing);
    std::cout<<"Sucessfully add series to medic History"<<std::endl;
    return chartView;
}

QChartView* FHistoryScreen::GetDisHistoryChart(const Ethene::CWorld& world)
{
    QChart* chartDiseaseHistory = new QChart;
    chartDiseaseHistory->setTitle("Disease History");
    chartDiseaseHistory->setAnimationOptions(QChart::AllAnimations);

    QValueAxis* axisX = new QValueAxis;
    QValueAxis* axisY = new QValueAxis;

    axisX->setTitleText("Time");
    axisY->setTitleText("Risk");

    axisX->setMin(0);
    axisY->setMin(0);
    axisY->setMax(200.0);

    QPen penDarkCyan;
    penDarkCyan.setWidth(3);
    penDarkCyan.setColor(Qt::darkCyan);

    QPen penDarkRed;
    penDarkRed.setWidth(3);
    penDarkRed.setColor(Qt::darkRed);

    QPen penDarkMagenta;
    penDarkMagenta.setWidth(3);
    penDarkMagenta.setColor(Qt::darkMagenta);

    QLineSeries* inf = new QLineSeries;
    inf->setName("Infectivity");
    inf->setColor(Qt::darkCyan);
    inf->setMarkerSize(25);
    inf->setPen(penDarkCyan);

    QLineSeries* sev = new QLineSeries;
    sev->setName("Severity");
    sev->setColor(Qt::darkRed);
    sev->setMarkerSize(25);
    sev->setPen(penDarkRed);

    QLineSeries* lth = new QLineSeries;
    lth->setName("Lethality");
    lth->setColor(Qt::darkMagenta);
    lth->setMarkerSize(25);
    lth->setPen(penDarkMagenta);

    int days = world.diseaseHistory.size();
    int i =0;
    for(i = 0;i<days;i++)
    {
        std::tuple<double,double,double>& t = world.diseaseHistory[i];
        inf->append(i,std::get<0>(t));
        sev->append(i,std::get<1>(t));
        lth->append(i,std::get<2>(t));
    }

    chartDiseaseHistory->addSeries(inf);
    chartDiseaseHistory->addSeries(sev);
    chartDiseaseHistory->addSeries(lth);
    chartDiseaseHistory->addAxis(axisX,Qt::AlignBottom);
    chartDiseaseHistory->addAxis(axisY,Qt::AlignLeft);
    inf->attachAxis(axisX);
    sev->attachAxis(axisX);
    lth->attachAxis(axisX);
    inf->attachAxis(axisY);
    sev->attachAxis(axisY);
    lth->attachAxis(axisY);

    chartDiseaseHistory->setAnimationDuration(2500);

    QChartView *pChartPopHistory = new QChartView(chartDiseaseHistory);
    pChartPopHistory->setRenderHint(QPainter::Antialiasing);
    std::cout<<"Sucessfully add series to disease History"<<std::endl;
    return pChartPopHistory;
}

inline void FHistoryScreen::LayOut(QChartView* pChart, QWidget* pPage)
{
    QHBoxLayout *layout = new QHBoxLayout(pPage);
    layout->addWidget(pChart);
    pPage->setLayout(layout);
}

void FHistoryScreen::ShowHisory(const Ethene::CWorld& world)
{
    QChartView* pPHC = GetPopHistoryChart(world);
    LayOut(pPHC, ui->tabWorldHistory);

    QChartView* pRHC = GetResHistoryChart(world);
    LayOut(pRHC, ui->tabMedicHistory);

    QChartView* pDHC = GetDisHistoryChart(world);
    LayOut(pDHC, ui->tabDiseaseHistory);
}

FHistoryScreen::FHistoryScreen(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FHistoryScreen)
{
    ui->setupUi(this);
}



FHistoryScreen::~FHistoryScreen()
{
    delete ui;
}


