#include <start.h>
#include <pre.h>
#include <QStackedWidget>
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QLineEdit>
#include <QObject>
#include <QDebug>
#include <QString>
#include "MainWidget.h"
#include "PlagueSimulatorLib.hpp"
#include <QTimer>
#include "fhistoryscreen.h"

#pragma region
std::vector<Ethene::CCountry> Ethene::CWorld::countries = {};
std::vector<Ethene::CPolicy> Ethene::CWorld::policiesAll = {};
std::vector<std::tuple<long, long, long>> Ethene::CWorld::worldHistory = {};
std::vector<std::tuple<double, double, double>> Ethene::CWorld::diseaseHistory = {};
std::vector<std::tuple<long, long, long>> Ethene::CWorld::researchHistory = {};
Ethene::CDisease Ethene::CDisease::disease = *new Ethene::CDisease();
Ethene::CWorld Ethene::CWorld::world = *new Ethene::CWorld();
#pragma endregion

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "cshw_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    FHistoryScreen FHS;

    Ethene::CWorld& world = Ethene::CWorld::GetWorld();
    Ethene::CDisease& disease = Ethene::CDisease::GetDisease();
    world.Initialize();
    disease.Initialize();

    world.countries[0].infectedPopulation = 1;
    world.countries[0].healthyPopulation -= 1;

    MainWidget mainWidget(nullptr, &world, &disease, &FHS);
    mainWidget.show();
    QEventLoop loop;

    // 连接信号和事件循环的退出槽
    QObject::connect(&mainWidget, &MainWidget::startSimulation, &loop, &QEventLoop::quit);
    loop.exec();

    QTimer timer;
    int i = 0;
    QObject::connect(&mainWidget, &MainWidget::pauseSimulation, &timer, &QTimer::stop);
    QObject::connect(&mainWidget, &MainWidget::resumeSimulation, [&timer]() {
        timer.start(500); // 继续循环时，重新启动定时器
    });
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        if (world.healthyPopulation + world.infectedPopulation < 100 ||
            world.worldTotalResearch > disease.cureRequirement || i >= 1000)
        {
            timer.stop(); // 停止定时器
            qDebug() << "Simulation finished";

            QTimer::singleShot(5000, [&]() {
                mainWidget.stackedWidget->setCurrentWidget(mainWidget.reswidget);
            });
            return;
        }

        world.Update(disease);
        mainWidget.gameWidget->specialinfo(i);
        i++;
        mainWidget.gameWidget->updatetext(i, mainWidget.gameWidget->country_selected);

        qDebug() << "Iteration:" << i;
    });

    // 启动定时器，每0.5秒触发一次
    timer.start(500);

    return a.exec();
}
