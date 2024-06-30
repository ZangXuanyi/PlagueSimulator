#include "res.h"
#include "ui_res.h"
#include<QWidget>
#include<QPainter>
#include<QPixmap>
#include <QString>

res::res(QWidget *parent,Ethene::CWorld*worlds,Ethene::CDisease*diseases) :
    QWidget(parent),
    ui(new Ui::res)
{
    world=worlds;
    disease=diseases;
    k=0;
    ui->setupUi(this);

    ui->textEdit->setStyleSheet(
        "QTextEdit {"
        "    font-size: 18px;"  // 设置字体大小
        "    text-align: center;"  // 设置文本居中对齐
        "    background: qlineargradient("
        "        spread:pad, x1:0, y1:0, x2:0, y2:1,"
        "        stop:0 #003366, stop:1 #000033"
        "    );"
        "    color: #FFFFFF;"
        "}"
        );

    connect(ui->pushButton, &QPushButton::clicked, this,&res::sig);
    connect(ui->pushButton_2, &QPushButton::clicked, this,&res::sign);

    if(world->infectedPopulation+world->healthyPopulation<=100){
        ui->textEdit->setText(QString("尽管人们尽了全力，%2 依然完成了它的使命。风吹过空荡荡的房屋，昭示着文明历史的终结。")
                                  .arg(QString::fromStdString(worlds->name)).arg(QString::fromStdString(disease->name)));
        k=1;
    }


    else if(1.0-world->deadRatio<1e-2){
        ui->textEdit->setText(QString("在夺去了无数生命之后，%1 被永远消灭了。尽管如此，幸存人类只能在废墟中喘息，重建文明将会难过登天。")
                                 .arg(QString::fromStdString(disease->name)));
        k=2;
    }

    else if(world->worldTotalResearch<disease->cureRequirement){
        ui->textEdit->setText(QString("科学家们没能研制出 %1 的解药。但是好消息是，在政府的通力合作之下，疾病在大范围传播之前就被扑灭了。")
                                  .arg(QString::fromStdString(disease->name)));
        k=3;
    }


    else if(world->worldTotalResearch>=disease->cureRequirement){
        ui->textEdit->setText(QString("科学家们成功研制出了 %1 的解药。人类再一次运用了他们的聪明才智抵挡了病魔的侵袭。")
                                  .arg(QString::fromStdString(disease->name)));
        k=4;
    }

}

res::~res()
{
    delete ui;
}
void res::paintEvent(QPaintEvent *event) {
    if(k==1){
    QPainter painter(this);
    QPixmap pixmap(":/pic5.png");
    QPixmap scaledPixmap = pixmap.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    painter.drawPixmap(this->rect(), scaledPixmap);
    QWidget::paintEvent(event);
    }
    if(k==2){
    QPainter painter(this);
    QPixmap pixmap(":/pic6.png");
    QPixmap scaledPixmap = pixmap.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    painter.drawPixmap(this->rect(), scaledPixmap);
    QWidget::paintEvent(event);
    }
    if(k==3){
    QPainter painter(this);
    QPixmap pixmap(":/pic7.png");
    QPixmap scaledPixmap = pixmap.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    painter.drawPixmap(this->rect(), scaledPixmap);
    QWidget::paintEvent(event);
    }
    if(k==4){
    QPainter painter(this);
    QPixmap pixmap(":/pic8.png");
    QPixmap scaledPixmap = pixmap.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    painter.drawPixmap(this->rect(), scaledPixmap);
    QWidget::paintEvent(event);
    }
}
