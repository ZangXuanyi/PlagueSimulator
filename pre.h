#ifndef PRE_H
#define PRE_H

#include <QWidget>
#include <QVector>
#include <QVBoxLayout>
#include <QLabel>
#include <QDoubleSpinBox>

namespace Ui {
class pre;
}

class pre : public QWidget {
    Q_OBJECT

public:
    explicit pre(QWidget *parent = nullptr);
    ~pre();

    void paintEvent(QPaintEvent *event);

    void addParameterRow(const QString &labelText, double initialValue, int parameterIndex);
    void loadDiseaseData(const QString &filePath);  // 声明 loadDiseaseData 函数

    QVector<double> diseaseParams;  // 用于存储疾病参数的向量
    int inputcount;
    QVBoxLayout *scrollLayout;
    bool isExpanded;
    std::string name;

signals:
    void intogame();
    void nameset(const QString &text);
    void parameterChanged(int parameterIndex, double value);

private slots:
    void toggleExpand();
    void onParameterChanged(int parameterIndex, double value);

private:
    Ui::pre *ui;
};

#endif // PRE_H
