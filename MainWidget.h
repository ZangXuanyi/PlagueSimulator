#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include "PlagueSimulatorLib.hpp"
#include <QWidget>
#include <QStackedWidget>
#include "start.h"
#include "QVBoxLayout"
#include "fhistoryscreen.h"
#include "res.h"
#include "pre.h"
#include "game.h"


class MainWidget : public QWidget {
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr, Ethene::CWorld* worlds = nullptr, Ethene::CDisease* diseases = nullptr, FHistoryScreen* h = nullptr);
    game *gameWidget;
    QStackedWidget *stackedWidget;
    start *startWidget;
    pre *preWidget;
    res *reswidget;
private:

    Ethene::CWorld *world;
    Ethene::CDisease *disease;
    FHistoryScreen *history;

    void setupConnections();

private slots:
    void switchToPre();
    void switchToGame();
    void updatename(const QString &text);
    void handleParameterChanged(int index, double value);
    void g15();
    void g16();
    void showChildDialog();
    void pause();

signals:
    void pauseSimulation();
    void resumeSimulation();
    void startSimulation();
};

#endif // MAINWIDGET_H

