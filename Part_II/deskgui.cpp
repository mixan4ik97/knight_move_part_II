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
    if (pos[1].toLatin1() - 48 < 1 || pos[1].toLatin1() - 48 > 8)
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
        emit startCalcul(k1, k2);
    }
    catch (...) {
        emit stopCalcul();
    }
}

QString getStringFromNum(uint8_t num){
    uint8_t w = GET_WIDTH(num);
    char h  = (char) GET_WIDTH(num);
    return QString(QChar(notate[0] + w)) + QString(QChar(h + 48)) ;
}

void DeskGUI::finish(QVector<uint8_t> out){
    qDebug()<<"Finish!";
    QString out_s = "Вывод пути: " ;
    for(uint8_t i = 0;i<out.size();i++)
        out_s+= getStringFromNum(out[i])+" ";
    qmb.setText(out_s);
    qmb.exec();
}



void DeskGUI::on_pushButton_stop_clicked()
{
    emit stopCalcul();
}


