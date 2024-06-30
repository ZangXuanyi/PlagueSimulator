#ifndef START_H
#define START_H

#include <QPushButton>
#include <QWidget>

class pre;

namespace Ui {
class start;
}

class start : public QWidget {
    Q_OBJECT

public:

    void paintEvent(QPaintEvent* event);
    explicit start(QWidget *parent = nullptr);
    ~start();

signals:
    void loadgame();

public:
    Ui::start *ui;
};

#endif // START_H
