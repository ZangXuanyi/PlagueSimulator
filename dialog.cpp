#include "dialog.h"
#include "ui_dialog.h"
#include <QPainter>
#include <QDialog>
#include <QCheckBox>
#include "PlagueSimulatorLib.hpp"
#include <set>
#include <QDebug>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QPalette>

QString country_name[26]={" ","Ngadiepia","Meshia","Muiloiko","Dourupia","Ikania","Amoia",
                            "Ereshna","Dashnia","Heungdongia","Hatia","Yayadyurt","Fanwangon"
                            ,"Hokshan","Shinu","Kanda","Argia","Nekalia","Tachia","Shigawa",
                            "Khuria","Shaga","Gawrarē",
                            "Chulandor","Haguria","Kidshu"};


dialog::dialog(QWidget *parent,Ethene::CWorld*worlds,Ethene::CDisease*diseases,int x) :
    QDialog(parent),
    ui(new Ui::dialog)
{   num=x;
    isExpanded=false;
    world=worlds;
    disease=diseases;


    ui->setupUi(this);




    if(x>0){
        ui->textEdit1->setText(QString("国家名称: %1").arg(country_name[x]));
        scrollLayout = new QVBoxLayout(ui->scrollAreaWidgetContents);
        connect(ui->unfold, &QPushButton::clicked, this, &dialog::toggleExpand);
        ui->scrollArea->setVisible(isExpanded);
        auto it=world->countries.begin();
        for(;it!=world->countries.end();it++){
            if(it->name==country_name[num].toStdString()) break;
        }

        ui->listWidget->setWindowTitle("已经执行过的政策");
        int len = world->policiesAll.size();
        for (int i = 0; i < len; i++)
        {
            Ethene::CPolicy& policy = world->policiesAll[i];

            if ( !Ethene::IsInset(it->policyExecuted, policy.name))
            {
                addcheckbox(policy);
            }
            else
            {
                ui->listWidget->addItem(QString::fromStdString(policy.name));
            }
        }

        QPieSeries *pie = new QPieSeries();
        pie->append("感染者", it->infectedPopulation)->setColor(Qt::darkRed);
        pie->append("健康者", it->healthyPopulation)->setColor(Qt::darkCyan);
        pie->append("病逝者", it->deadPopulation)->setColor(Qt::darkGray);

        QChart *chart = new QChart();
        chart->addSeries(pie);
        chart->setTitle("人口比例");
        chart->palette();

        QVBoxLayout *layout = new QVBoxLayout(ui->widget);
        QChartView *chartView = new QChartView(chart);
        layout->addWidget(chartView);
        ui->widget->setLayout(layout);


       }
    if(x==0){
        ui->scrollArea->setVisible(false);
        ui->unfold->setVisible(false);
        ui->textEdit1->setText("世界概况");

        QPieSeries *pie = new QPieSeries();
        pie->append("感染者", world->infectedPopulation)->setColor(Qt::darkRed);
        pie->append("健康者", world->healthyPopulation)->setColor(Qt::darkCyan);
        pie->append("病逝者", world->deadPopulation)->setColor(Qt::darkGray);

        QChart *chart = new QChart();
        chart->addSeries(pie);
        chart->setTitle("人口比例");

        QVBoxLayout *layout = new QVBoxLayout(ui->widget);
        QChartView *chartView = new QChartView(chart);
        layout->addWidget(chartView);
        ui->widget->setLayout(layout);
    }
      if(x==-1) {
        ui->scrollArea->setVisible(false);
        ui->unfold->setVisible(false);
        ui->textEdit1->setText("您暂停了模拟进程");
    }
}

dialog::~dialog()
{
    delete ui;
}
void dialog::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap pixmap(":/pic4.jpg");

    QPixmap scaledPixmap = pixmap.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    painter.drawPixmap(this->rect(), scaledPixmap);

    QWidget::paintEvent(event);
}


void dialog::toggleExpand() {
    isExpanded = !isExpanded;
    ui->
        scrollArea->setVisible(isExpanded);
    ui->unfold->setText(isExpanded ? "收起可执行政策列表" : "展开可执行政策列表");
}

void dialog::addcheckbox(Ethene::CPolicy& policy){
    QCheckBox* p = new QCheckBox(ui->scrollAreaWidgetContents);
    p->setChecked(false);
    p->setText(QString::fromStdString(policy.name));
    scrollLayout->addWidget(p);
    connect(p, &QCheckBox::clicked, [=](){alter((p->text()));});
}

void dialog::alter(QString x){
    auto it=world->countries.begin();
    for(;it!=world->countries.end();it++){
        if(it->name==country_name[num].toStdString()) break;
    }
    Ethene::CCountry& instance = it->GetThis();
    Ethene::CPolicy& policy=world->policiesAll[0];

    int len = world->policiesAll.size();
    for (int i = 0; i < len; i++){
        if(world->policiesAll[i].name==x.toStdString()) policy = world->policiesAll[i];
    }

    policy.Execute(instance);
    it->policyExecuted.insert(policy.name);

}


