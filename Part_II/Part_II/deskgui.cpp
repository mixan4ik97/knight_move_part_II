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

bool DeskGUI::isCorrectCoordinate(QString pos) {
    if (pos.size() != 2)
        return false;
    if (pos[1] - 48 < 1 || pos[1] - 48 > 8)
        return false;
    for (uint8_t i = 0; i<8; i++)
        if (pos[0] == notate[i])
            return true;
    return false;

}

void DeskGUI::on_pushButton_start_clicked()
{
    try {
        QString pos1 = ui->lineEdit_knight->text();
        if(!isCorrectCoordinate( pos1))
                return;
        QString pos2 = ui->lineEdit_pos->text();
        if(!isCorrectCoordinate( pos2))
                return;
        uint8_t k1 = GET_NUMBER(pos1);
        uint8_t k2 = GET_NUMBER(pos2);
        is_warring = false;
        emit startCalcul(k1, k2);

    }
    catch (...) {
        return CALCULATION_ERROR;
    }
}

void DeskGUI::finish(QVector<uint8_t> out){
    int k;

}



void DeskGUI::on_pushButton_stop_clicked()
{
        emit stopCalcul();
}
