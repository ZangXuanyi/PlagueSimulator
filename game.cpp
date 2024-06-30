#include "game.h"
#include "ui_game.h"
#include<QPainter>
#include<QPixmap>
#include <QString>
#include <QDebug>
#include <QLabel>
#include"dialog.h"
#include"MainWidget.h"
#include <QHBoxLayout>


std::string country_name[26]={" ","Ngadiepia","Meshia","Muiloiko","Dourupia","Ikania","Amoia",
                            "Ereshna","Dashnia","Heungdongia","Hatia","Yayadyurt","Fanwangon"
                            ,"Hokshan","Shinu","Kanda","Argia","Nekalia","Tachia","Shigawa",
                            "Khuria","Shaga","Gawrarē",
                            "Chulandor","Haguria","Kidshu"};


game::game(QWidget *parent,Ethene::CWorld*worlds,Ethene::CDisease*diseases) :
    QWidget(parent),
    ui(new Ui::game)
{
    stay=0;
    if_first_infected=false;
    if_first_dead=false;
    if_first_unordered=false;
    if_first_none=false;
    antidote_progress=0;
    all_infected=false;
    world=worlds;
    disease=diseases;
    ui->setupUi(this);
    country_selected=0;
    area1 = QRect(173,0,217,108);      // Ngadiepia
    area2 = QRect(227, 140, 87, 98);  // Meshia
    area3 = QRect(109,167,100,118);   //Muiloiko
    area4 = QRect(500, 121, 46, 85);   // Dourupia
    area5 = QRect(584, 90, 64, 86);  // Ikania
    area6 = QRect(651, 154, 101, 97);  // Amoia
    area7 = QRect(757, 186, 30, 41);    // Ereshna
    area8 = QRect(741, 259, 49, 68);  // Dashnia
    area9 = QRect(201, 275, 96, 63);  // Heungdongia
    area10 = QRect(529, 235, 52, 41); // Hatia
    area11 = QRect(312, 234, 65, 106); // Yayadyurt
    area12 = QRect(135, 297, 55, 24);  // Fanwangon
    area13 = QRect(155, 326, 35, 39); // Hokshan
    area14 = QRect(199, 345, 61, 57);  // Shinu
    area15 = QRect(273, 399, 175, 100); // Kanda
    area16 = QRect(628, 262, 46, 74); // Argia
    area17 = QRect(691, 284, 40, 43); // Nekalia
    area18 = QRect(371, 345,71, 54); // Tachia
    area19 = QRect(451, 341, 77, 87); // Shigawa
    area20 = QRect(399, 228, 61, 104); //Khuria
    area21 = QRect(678, 335, 81, 165);//Shaga
    area22 = QRect(326, 120, 154, 81);//Gawvave
    area23 = QRect(470, 209, 48, 88);//Chulandor
    area24 = QRect(553, 288, 62, 185);//Haguria
    area25 = QRect(554, 127, 29, 67);//Kidshu


    connect(ui->pause,&QPushButton::clicked, this, &game::paus);

    // 设置底部布局
    setupBottomLayout();

}

game::~game()
{
    delete ui;
}

void game::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap pixmap(":/pic3.png");
    QRect targetRect(10, 5, 860, 484);//改变背景大小
    QPixmap scaledPixmap = pixmap.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    painter.drawPixmap(targetRect, scaledPixmap);

    QWidget::paintEvent(event);
}



void game::mousePressEvent(QMouseEvent *event)
{
//鼠标点到的地方为国家，当然是有瑕疵的，很粗糙的手动拟合
        QPoint clickPos = event->pos();
        if (area1.contains(clickPos)) {
            emit areaClicked(1);
            updateBottomLayout(1);
            country_selected = 1;
        } else if (area2.contains(clickPos)) {
            emit areaClicked(2);
            updateBottomLayout(2);
            country_selected = 2;
        } else if (area3.contains(clickPos)) {
            emit areaClicked(3);
            updateBottomLayout(3);
            country_selected = 3;
        } else if (area4.contains(clickPos)) {
            emit areaClicked(4);
            updateBottomLayout(4);
            country_selected = 4;
        } else if (area5.contains(clickPos)) {
            emit areaClicked(5);
            updateBottomLayout(5);
            country_selected = 5;
        } else if (area6.contains(clickPos)) {
            emit areaClicked(6);
            updateBottomLayout(6);
            country_selected = 6;
        } else if (area7.contains(clickPos)) {
            emit areaClicked(7);
            updateBottomLayout(7);
            country_selected = 7;
        } else if (area8.contains(clickPos)) {
            emit areaClicked(8);
            updateBottomLayout(8);
            country_selected = 8;
        } else if (area9.contains(clickPos)) {
            emit areaClicked(9);
            updateBottomLayout(9);
            country_selected = 9;
        } else if (area10.contains(clickPos)) {
            emit areaClicked(10);
            updateBottomLayout(10);
            country_selected = 10;
        } else if (area11.contains(clickPos)) {
            emit areaClicked(11);
            updateBottomLayout(11);
            country_selected = 11;
        } else if (area12.contains(clickPos)) {
            emit areaClicked(12);
            updateBottomLayout(12);
            country_selected = 12;
        } else if (area13.contains(clickPos)) {
            emit areaClicked(13);
            updateBottomLayout(13);
            country_selected = 13;
        } else if (area14.contains(clickPos)) {
            emit areaClicked(14);
            updateBottomLayout(14);
            country_selected = 14;
        } else if (area15.contains(clickPos)) {
            emit areaClicked(15);
            updateBottomLayout(15);
            country_selected = 15;
        } else if (area16.contains(clickPos)) {
            emit areaClicked(16);
            updateBottomLayout(16);
            country_selected = 16;
        } else if (area17.contains(clickPos)) {
            emit areaClicked(17);
            updateBottomLayout(17);
            country_selected = 17;
        } else if (area18.contains(clickPos)) {
            emit areaClicked(18);
            updateBottomLayout(18);
            country_selected = 18;
        } else if (area19.contains(clickPos)) {
            emit areaClicked(19);
            updateBottomLayout(19);
            country_selected = 19;
        }
        else if (area20.contains(clickPos)) {
            emit areaClicked(20);
            updateBottomLayout(20);
            country_selected = 20;
        }
        else if (area21.contains(clickPos)) {
            emit areaClicked(21);
            updateBottomLayout(21);
            country_selected = 21;
        }
        else if (area22.contains(clickPos)) {
            emit areaClicked(22);
            updateBottomLayout(22);
            country_selected = 22;
        }
        else if (area23.contains(clickPos)) {
            emit areaClicked(23);
            updateBottomLayout(23);
            country_selected = 23;
        }
        else if (area24.contains(clickPos)) {
            emit areaClicked(24);
            updateBottomLayout(24);
            country_selected = 24;
        }
        else if (area25.contains(clickPos)) {
            emit areaClicked(25);
            updateBottomLayout(25);
            country_selected = 25;
        }
        else{
            emit areaClicked(26);
            updateBottomLayout(26);
            country_selected = 0;
        }
    }


void game::setupBottomLayout()
{
    // 创建主水平布局
    mainLayout = new QHBoxLayout(this);

    // 创建左侧垂直布局并添加infoLabel
    leftLayout = new QVBoxLayout();
    infoLabel = new QLabel("点击不同区域显示不同信息", this);
    leftLayout->addWidget(infoLabel);
    leftLayout->setAlignment(infoLabel, Qt::AlignLeft);

    // 获取infoLabel的宽度
    int labelWidth = infoLabel->sizeHint().width();

    // 创建右侧垂直布局并添加按钮
   rightLayout = new QVBoxLayout();
    actionButton1 = new QPushButton("按钮1", this);
    actionButton2 = new QPushButton("按钮2", this);

    // 设置按钮最小宽度等于infoLabel的宽度
    actionButton1->setMinimumWidth(labelWidth);
    actionButton2->setMinimumWidth(labelWidth);

    rightLayout->addWidget(actionButton1);
    rightLayout->addWidget(actionButton2);
    rightLayout->setAlignment(actionButton1, Qt::AlignRight);
    rightLayout->setAlignment(actionButton2, Qt::AlignRight);

    // 将左右布局添加到主布局中
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    mainLayout->setAlignment(Qt::AlignBottom);

    QFrame *frame = new QFrame(this);
    frame->setLayout(mainLayout);
    frame->setFrameStyle(QFrame::Box | QFrame::Plain);
    frame->setLineWidth(2);

    // 创建底部布局并添加frame
    QVBoxLayout *bottomLayout = new QVBoxLayout();
    bottomLayout->addWidget(frame);
    bottomLayout->setAlignment(frame, Qt::AlignBottom);

    // 设置窗口布局
    setLayout(bottomLayout);
    // 连接信号和槽
    connect(actionButton1, &QPushButton::clicked, this, &game::showChildDialog);
}

void game::updateBottomLayout(int area)
{
    switch (area) {
    case 1:
         //   updatetext(area);
            actionButton1->setText("Specific Info");
            actionButton2->setText("Ngadiepia");
            break;
    case 2:
        //    updatetext(area);
            actionButton1->setText("Specific Info");
            actionButton2->setText("Meshia");
            break;
    case 3:
         //  updatetext(area);
            actionButton1->setText("Specific Info");
            actionButton2->setText("Muiloiko");
            break;
    case 4:
        //   updatetext(area);
            actionButton1->setText("Specific Info");
            actionButton2->setText("Dourupia");
            break;
    case 5:
        //  updatetext(area);
            actionButton1->setText("Specific Info");
            actionButton2->setText("Ikania");
            break;
    case 6:
          // updatetext(area);
            actionButton1->setText("Specific Info");
            actionButton2->setText("Amoia");
            break;
    case 7:
         //   updatetext(area);
            actionButton1->setText("Specific Info");
            actionButton2->setText("Ereshna");
            break;
    case 8:
         //   updatetext(area);
            actionButton1->setText("Specific Info");
            actionButton2->setText("Dashnia");
            break;
    case 9:
        //   updatetext(area);
            actionButton1->setText("Specific Info");
            actionButton2->setText("Heungdongia");
            break;
    case 10:
          //updatetext(area);
            actionButton1->setText("Specific Info");
            actionButton2->setText("Hatia");
            break;
    case 11:
          // updatetext(area);
            actionButton1->setText("Specific Info");
            actionButton2->setText("Yayadyurt");
            break;
    case 12:
         //updatetext(area);
            actionButton1->setText("Specific Info");
            actionButton2->setText("Fanwangon");
            break;
    case 13:
          //updatetext(area);
            actionButton1->setText("Specific Info");
            actionButton2->setText("Hokshan");
            break;
    case 14:
            //updatetext(area);
            actionButton1->setText("Specific Info");
            actionButton2->setText("Shinu");
            break;
    case 15:
           // updatetext(area);
            actionButton1->setText("Specific Info");
            actionButton2->setText("Kanda");
            break;
    case 16:
          // updatetext(area);
            actionButton1->setText("Specific Info");
            actionButton2->setText("Argia");
            break;
    case 17:
          // updatetext(area);
            actionButton1->setText("Specific Info");
            actionButton2->setText("Nekalia");
            break;
    case 18:
          //  updatetext(area);
            actionButton1->setText("Specific Info");
            actionButton2->setText("Tachia");
            break;
    case 19:
//updatetext(area);
            actionButton1->setText("Specific Info");
            actionButton2->setText("Shigawa");
            break;
    case 20:
      //  updatetext(area);
        actionButton1->setText("Specific Info");
        actionButton2->setText("Khuria");
        break;
    case 21:
       // updatetext(area);
        actionButton1->setText("Specific Info");
        actionButton2->setText("Shaga");
        break;
    case 22:
       //updatetext(area);
        actionButton1->setText("Specific Info");
        actionButton2->setText("Gawrarē");
        break;
    case 23:
      // updatetext(area);
        actionButton1->setText("Specific Info");
        actionButton2->setText("Chulandor");
        break;
    case 24:
        //updatetext(area);
        actionButton1->setText("Specific Info");
        actionButton2->setText("Haguria");
        break;
    case 25:
        //updatetext(area);
        actionButton1->setText("Specific Info");
        actionButton2->setText("Kidshu");
        break;
    default:
        actionButton1->setText("Specific Info");
        actionButton2->setText(QString::fromStdString(world->name));
            break;
    }
}
void game::updatetext(int y,int x){
    if(x==0){
            QString deadnum=QString::number(world->deadPopulation);
            QString infected=QString::number(world->infectedPopulation);
            QString live=QString::number(world->healthyPopulation);
            QString text=QString("疾病传播天数 :%1 \t健康人数: %2 \t携带人数: %3 \t病逝人数: %4").arg(y).arg(live).arg(infected).arg(deadnum);
            infoLabel->setText(text);
    }
    else{
    auto it=Ethene::CWorld::countries.begin();
    for(;it!=Ethene::CWorld::countries.end();it++){
            if(it->name==country_name[x])
                break;
    }
    QString deadnum=QString::number(it->deadPopulation);
    QString infected=QString::number(it->infectedPopulation);
    QString live=QString::number(it->healthyPopulation);
    QString text=QString("疾病传播天数 :%1 \t健康人数: %2 \t携带人数: %3 \t病逝人数: %4").arg(y).arg(live).arg(infected).arg(deadnum);
    infoLabel->setText(text);
    }

}



void game::specialinfo(int x){
    if(world->infectedPopulation>=1&&if_first_infected==false){
            ui->special->setText(
                QString("第一例 %1 病患出现了！科学家们尚不知道它对人类有何影响。").arg(QString::fromStdString(disease->name)));
            if_first_infected=true;
            stay=x;
    }
    if(world->deadPopulation>=1&&if_first_dead==false){
            ui->special->setText(
                QString("第一个 %1 导致的死亡病例出现了！这究竟是巧合还是不祥的征兆？").arg(QString::fromStdString(disease->name)));
            if_first_dead=true;
            stay=x;
    }
    if(if_first_unordered==false){
    bool res=false;
    auto it=Ethene::CWorld::countries.begin();
    for(;it!=Ethene::CWorld::countries.end();it++){
            if(it->areaOrder==0.0)
                {res=true;break;}
    }
    if(res)
    { ui->special->setText(
                QString("%1 地区的政府已经垮台，一切解药研究陷入停滞。").arg(QString::fromStdString(it->name)));
            if_first_unordered=true;
            stay=x;}

    }

    if(if_first_none==false){
    bool res=false;
    auto it=Ethene::CWorld::countries.begin();
    for(;it!=Ethene::CWorld::countries.end();it++){
            if(it->deadRatio==1.0)
            {res=true;break;}
    }
    if(res)
    { ui->special->setText(
                QString("%1 的所有人全部死于 %2 了。多么悲伤的一件事！").arg(QString::fromStdString(it->name)).arg(QString::fromStdString(disease->name)));
            if_first_none=true;
            stay=x;}

    }


    if(antidote_progress==0&&world->worldTotalResearch>=0.25*disease->cureRequirement){
    antidote_progress=25;
    ui->special->setText(
        QString("%1 的解药已经研发了25%！").arg(QString::fromStdString(disease->name)));
    stay=x;
    }

    if(antidote_progress==25&&world->worldTotalResearch>=0.5*disease->cureRequirement){
    antidote_progress=50;
    ui->special->setText(
        QString("%1 的解药已经研发了50%！").arg(QString::fromStdString(disease->name)));
    stay=x;
    }

    if(antidote_progress==50&&world->worldTotalResearch>=0.75*disease->cureRequirement){
    antidote_progress=75;
    ui->special->setText(
        QString("%1 的解药已经研发了75%！").arg(QString::fromStdString(disease->name)));
    stay=x;
    }

    if(antidote_progress==75&&world->worldTotalResearch>=disease->cureRequirement){
    antidote_progress=100;
    ui->special->setText(
        QString("%1 的解药已经彻底研发完成了！").arg(QString::fromStdString(disease->name)));
    stay=x;
    }

    if(antidote_progress==100&&x-stay>=5){
    antidote_progress=125;
    stay=x;
    ui->special->setText(
        QString("%1 的解药正在被发放到全世界去！").arg(QString::fromStdString(disease->name)));
    }


    if(world->healthyPopulation==0&&all_infected==false){
    stay=x;
    all_infected=true;
    ui->special->setText(
        QString("最后一个健康的人也感染了%1。").arg(QString::fromStdString(disease->name)));
    }

    if(x-stay>=5){
    ui->special->setText(" ");
    }
}
