#ifndef DIALOG_H
#define DIALOG_H
#include"PlagueSimulatorLib.hpp"
#include <QDialog>
#include"QVBoxLayout"

namespace Ui {
class dialog;
}

class dialog : public QDialog
{
    Q_OBJECT


private slots:
    void toggleExpand();
    void addcheckbox(Ethene::CPolicy&);


public:

    void alter(QString text);
    QVBoxLayout *scrollLayout;
    bool isExpanded;
    void paintEvent(QPaintEvent* event);
    int num;
    Ethene::CWorld*world;
    Ethene::CDisease*disease;
    explicit dialog(QWidget *parent = nullptr,Ethene::CWorld *world=nullptr,Ethene::CDisease*disease=nullptr,int x=0);
    ~dialog();

private:
    Ui::dialog *ui;
};

#endif // DIALOG_H
