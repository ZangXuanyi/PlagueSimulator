#ifndef GAME_H
#define GAME_H
#include <QMouseEvent>
#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "PlagueSimulatorLib.hpp"

namespace Ui {
class game;
}

class game : public QWidget
{
    Q_OBJECT

signals:
 void areaClicked(int area);
 void showChildDialog();
 void paus();
 public slots:


public:

    void mousePressEvent(QMouseEvent *event) override;

    explicit game(QWidget *parent = nullptr,Ethene::CWorld *world=nullptr,Ethene::CDisease*disease=nullptr);
    void paintEvent(QPaintEvent* event) override;
    ~game();

public:
    int country_selected;
    Ui::game *ui;
    QHBoxLayout *mainLayout;
    QVBoxLayout *leftLayout;
    QVBoxLayout *rightLayout;
    QLabel *infoLabel;
    QPushButton *actionButton1;
    QPushButton *actionButton2;
    QRect area1;
    QRect area2;
    QRect area3;
    QRect area4;
    QRect area5;
    QRect area6;
    QRect area7;
    QRect area8;
    QRect area9;
    QRect area10;
    QRect area11;
    QRect area12;
    QRect area13;
    QRect area14;
    QRect area15;
    QRect area16;
    QRect area17;
    QRect area18;
    QRect area19;
    QRect area20;
    QRect area21;
    QRect area22;
    QRect area23;
    QRect area24;
    QRect area25;

    void specialinfo(int x);
    int stay;
    bool if_first_infected;
    bool if_first_dead;
    bool if_first_unordered;
    bool if_first_none;
    bool all_infected;
    int antidote_progress;
    Ethene::CWorld*world;
    Ethene::CDisease*disease;
    void setupBottomLayout();
    void updateBottomLayout(int area);

    void updatetext(int y,int x);
};

#endif // GAME_H
