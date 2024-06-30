#include "pre.h"
#include "ui_pre.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QHBoxLayout>

pre::pre(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pre) {
    name = "default";
    ui->setupUi(this);
    ui->label->setWordWrap(true);
    connect(ui->nexti, &QPushButton::clicked, this, &pre::intogame);
    connect(ui->name_input, &QLineEdit::textChanged, this, &pre::nameset);
    isExpanded = false;
    inputcount = 0;

    scrollLayout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    connect(ui->unfold, &QPushButton::clicked, this, &pre::toggleExpand);

    ui->scrollArea->setVisible(isExpanded);

    ui->nexti->setStyleSheet("background-color: rgba(0, 0, 0, 0);"
                             "border: 2px solid #ffffff;"  // 设置边框颜色和宽度
                             "border-radius: 10px;"  // 设置圆角边框
                             "color: white;"  // 设置字体颜色
                             "font-size: 18px;"  // 设置字体大小
                             "font-family: Georgia;"  // 设置字体类型
                             "font-weight: bold;"  // 设置字体加粗
                             "text-align: center;");  // 设置文本对齐
    ui->unfold->setStyleSheet("background-color: rgba(0, 0, 0, 0);"
                              "border: 2px solid #ffffff;"  // 设置边框颜色和宽度
                              "border-radius: 10px;"  // 设置圆角边框
                              "color: white;"  // 设置字体颜色
                              "font-size: 16px;"  // 设置字体大小
                              "font-family: Georgia;"  // 设置字体类型
                              "font-weight: bold;"  // 设置字体加粗
                              "text-align: center;");  // 设置文本对齐);
    ui->name_input->setStyleSheet("background-color: rgba(0, 0, 0, 0);"
                                  "border: 2px solid #ffffff;"  // 设置边框颜色和宽度
                                  "border-radius: 10px;"  // 设置圆角边框
                                  "color: white;"  // 设置字体颜色
                                  "qproperty-alignment: 'AlignCenter';"
                                  "font-size: 16px;"  // 设置字体大小
                                  "font-family: Georgia;"  // 设置字体类型
                                  "font-weight: bold;"  // 设置字体加粗
                                  "text-align: center;");  // 设置文本对齐);

    // 加载疾病数据
    loadDiseaseData("..\\..\\source\\diseaseInfo.csv");
    // 设置疾病名称
    ui->name_input->setText(QString::fromStdString(name));
    // 添加参数行
    addParameterRow("传染性:", diseaseParams[0], 0);
    addParameterRow("严重性:", diseaseParams[1], 1);
    addParameterRow("致命性:", diseaseParams[2], 2);
    addParameterRow("富裕抗性:", diseaseParams[3], 3);
    addParameterRow("贫穷抗性:", diseaseParams[4], 4);
    addParameterRow("城市抗性:", diseaseParams[5], 5);
    addParameterRow("农村抗性:", diseaseParams[6], 6);
    addParameterRow("炎热抗性:", diseaseParams[7], 7);
    addParameterRow("寒冷抗性:", diseaseParams[8], 8);
    addParameterRow("潮湿抗性:", diseaseParams[9], 9);
    addParameterRow("干旱抗性:", diseaseParams[10], 10);
    addParameterRow("尸体传播:", diseaseParams[11], 11);
    addParameterRow("治疗需求", diseaseParams[12], 12);
    addParameterRow("陆地传播:", diseaseParams[13], 13);
}

pre::~pre() {
    delete ui;
}

void pre::loadDiseaseData(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file for reading:" << file.errorString();
        return;
    }

    QTextStream in(&file);
    QString line = in.readLine();
    QStringList fields = line.split(",");
    if (!fields.isEmpty()) {
        name = fields[0].toStdString();  // 读取疾病名称
        for (int i = 1; i < fields.size(); ++i) {  // 从第二个数据开始匹配参数
            diseaseParams.append(fields[i].toDouble());
        }
    }

    file.close();
}

void pre::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap pixmap(":/pic2.png");

    QPixmap scaledPixmap = pixmap.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    painter.drawPixmap(this->rect(), scaledPixmap);

    QWidget::paintEvent(event);
}

void pre::toggleExpand() {
    isExpanded = !isExpanded;
    ui->scrollArea->setVisible(isExpanded);
    ui->unfold->setText(isExpanded ? "收起疾病参数列表" : "展开疾病参数列表");
}

void pre::addParameterRow(const QString &labelText, double initialValue, int parameterIndex) {
    QWidget *rowWidget = new QWidget(ui->scrollAreaWidgetContents);
    QHBoxLayout *rowLayout = new QHBoxLayout(rowWidget);

    QLabel *label = new QLabel(labelText, rowWidget);
    QDoubleSpinBox *spinBox = new QDoubleSpinBox(rowWidget);
    spinBox->setRange(0, 1000);  // 根据需要调整范围
    spinBox->setValue(initialValue);

    rowLayout->addWidget(label);
    rowLayout->addWidget(spinBox);
    scrollLayout->addWidget(rowWidget);

    connect(spinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [this, parameterIndex](double value) {
        onParameterChanged(parameterIndex, value);
    });
}

void pre::onParameterChanged(int parameterIndex, double value) {
    if (parameterIndex >= 0 && parameterIndex < diseaseParams.size()) {
        diseaseParams[parameterIndex] = value;
        emit parameterChanged(parameterIndex, value);  // 发射信号以通知变化
    }
}
