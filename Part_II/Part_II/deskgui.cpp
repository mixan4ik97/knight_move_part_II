#include "deskgui.h"
#include "ui_deskgui.h"

DeskGUI::DeskGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DeskGUI)
{
    ui->setupUi(this);
}

DeskGUI::~DeskGUI()
{
    delete ui;
}

void DeskGUI::on_pushButton_start_clicked()
{

}

void DeskGUI::on_pushButton_stop_clicked()
{

}
