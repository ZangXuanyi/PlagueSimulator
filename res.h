#ifndef RES_H
#define RES_H

#include <QWidget>
#include "PlagueSimulatorLib.hpp"
namespace Ui {
class res;
}

class res : public QWidget
{
    Q_OBJECT

signals:
    void sig();
    void sign();
public:
    int k;
    Ethene::CWorld*world;
    Ethene::CDisease*disease;
    explicit res(QWidget *parent = nullptr,Ethene::CWorld *world=nullptr,Ethene::CDisease*disease=nullptr);
    ~res();
    void paintEvent(QPaintEvent* event);

public:
    Ui::res *ui;
};

#endif // RES_H
