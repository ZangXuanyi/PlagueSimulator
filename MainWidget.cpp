#include "MainWidget.h"
#include "QVBoxLayout"
#include <QTimer>
#include "dialog.h"

MainWidget::MainWidget(QWidget *parent, Ethene::CWorld* worlds, Ethene::CDisease* diseases, FHistoryScreen* h) : QWidget(parent) {
    stackedWidget = new QStackedWidget(this);
    startWidget = new start(this);
    preWidget = new pre(this);
    reswidget = new res(this, worlds, diseases);
    world = worlds;
    disease = diseases;
    history = h;
    gameWidget = new game(this, worlds, diseases);
    stackedWidget->addWidget(startWidget);
    stackedWidget->addWidget(preWidget);
    stackedWidget->addWidget(gameWidget);
    stackedWidget->addWidget(reswidget);
    setFixedSize(900, 600);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(stackedWidget);

    connect(startWidget, &start::loadgame, this, &MainWidget::switchToPre);
    connect(preWidget, &pre::intogame, this, &MainWidget::switchToGame);
    connect(preWidget, &pre::intogame, this, &MainWidget::startSimulation);
    connect(preWidget, &pre::nameset, this, &MainWidget::updatename);

    // 连接参数改变的信号
    connect(preWidget, &pre::parameterChanged, this, &MainWidget::handleParameterChanged);

    connect(reswidget, &res::sig, this, &MainWidget::g16);
    connect(reswidget, &res::sign, this, &MainWidget::g15);

    setLayout(mainLayout);
    setupConnections();
}

void MainWidget::switchToPre() {
    stackedWidget->setCurrentWidget(preWidget);
}

void MainWidget::switchToGame() {
    stackedWidget->setCurrentWidget(gameWidget);
}

void MainWidget::updatename(const QString &text) {
    disease->name = text.toStdString();
}

void MainWidget::handleParameterChanged(int index, double value) {
    switch (index) {
    case 0: disease->infectivity = value; break;
    case 1: disease->severity = value; break;
    case 2: disease->lethality = value; break;
    case 3: disease->wealthyResistance = value; break;
    case 4: disease->povertyResistance = value; break;
    case 5: disease->urbanResistance = value; break;
    case 6: disease->ruralResistance = value; break;
    case 7: disease->hotResistance = value; break;
    case 8: disease->coldResistance = value; break;
    case 9: disease->humidResistance = value; break;
    case 10: disease->aridResistance = value; break;
    case 11: disease->corpseTransmission = value; break;
    case 12: disease->cureRequirement = value; break;
    case 13: disease->landTransmission = value; break;
    default: break;
    }
    qDebug() << "Parameter" << index << "changed to" << value;
}

void MainWidget::g15() {
    this->close();
}

void MainWidget::g16() {
    history->show();
    history->ShowHisory(*world);
}

void MainWidget::setupConnections() {
    connect(gameWidget, &game::showChildDialog, this, &MainWidget::showChildDialog);
    connect(gameWidget, &game::paus, this, &MainWidget::pause);
}

void MainWidget::showChildDialog() {
    qDebug() << "called";
    emit pauseSimulation();

    // 创建子窗口
    dialog childDialog(this, world, disease, gameWidget->country_selected);

    // 显示子窗口
    childDialog.exec();

    // 子窗口关闭后，发射继续信号
    emit resumeSimulation();
}

void MainWidget::pause() {
    emit pauseSimulation();

    // 创建子窗口
    dialog childDialog(this, world, disease, -1);

    // 显示子窗口
    childDialog.exec();

    // 子窗口关闭后，发射继续信号
    emit resumeSimulation();
}
