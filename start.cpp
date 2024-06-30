#include "start.h"
#include "ui_start.h"
#include<QVBoxLayout>
#include<QPainter>
#include<QPixmap>





 start::start(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::start) {
    ui->setupUi(this);
     ui->startbutton->setStyleSheet("background-color: rgba(0, 0, 0, 0);"
                                    "border: 2px solid #ffffff;"  // 设置边框颜色和宽度
                                    "border-radius: 10px;"  // 设置圆角边框
                                    "color: black;"  // 设置字体颜色
                                    "font-size: 18px;"  // 设置字体大小
                                    "font-family: Georgia;"  // 设置字体类型
                                    "font-weight: bold;"  // 设置字体加粗
                                    "text-align: center;");  // 设置文本对齐

    connect(ui->startbutton, &QPushButton::clicked, this, &start::loadgame);

}

start::~start() {
    delete ui;
}
void start::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap pixmap(":/pic1.png");

    QPixmap scaledPixmap = pixmap.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    painter.drawPixmap(this->rect(), scaledPixmap);

    QWidget::paintEvent(event);
}
