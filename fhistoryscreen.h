#ifndef FHISTORYSCREEN_H
#define FHISTORYSCREEN_H

#include <QDialog>
#include <QWidget>
#include <qchartview.h>
#include "PlagueSimulatorLib.hpp"

namespace Ui {
class FHistoryScreen;
}

class FHistoryScreen : public QDialog
{
    Q_OBJECT

public:
    explicit FHistoryScreen(QWidget *parent = nullptr);
    ~FHistoryScreen();
    void ShowHisory(const Ethene::CWorld& world);


private:
    Ui::FHistoryScreen *ui;
    QChartView* GetPopHistoryChart(const Ethene::CWorld& world);
    QChartView* GetResHistoryChart(const Ethene::CWorld& world);
    QChartView* GetDisHistoryChart(const Ethene::CWorld& world);
    void LayOut(QChartView* pChart, QWidget* pPage);
};

#endif // FHISTORYSCREEN_H
