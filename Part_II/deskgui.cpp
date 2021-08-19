#include "deskgui.h"
#include "ui_deskgui.h"
#include <QDir>

DeskGUI::DeskGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DeskGUI)
{
    ui->setupUi(this);

    for(uint8_t i =0;i<8;i++)
        for(uint8_t j =0;j<8;j++)
            if((i+j )%2 == 0 )
                ui->desk->item(i,j)->setIcon(QIcon("k4.PNG"));
            else
                ui->desk->item(i,j)->setIcon(QIcon("kb.PNG"));


    QString patch = QDir::currentPath() + "/img/";
    QString name;
    for(uint8_t i =1; i<= 4;i++){
        name = patch +QString::number(i) + ".png";
        bool b = img.load(name, "PNG" );
        //qDebug() <<( b ? "Is loading :" : "Is NOT loading :")<<name ;
        img = img.scaled(75,75);
        ic[i].setTextureImage(img) ;
    }

    QTableWidgetItem *it;
   // ui->tableWidget_bord->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->desk->setSelectionMode(QAbstractItemView::NoSelection);
    for(int i =0; i< 8;i++)
         for(int j =0; j< 8;j++){
             it = new QTableWidgetItem();
             it->setFlags( it->flags() ^ Qt::ItemIsEditable );
             if((i+j )%2 == 0 )
                 it->setIcon(QIcon("k4.PNG"));
             else
                 it->setIcon(QIcon("kb.PNG"));
             ui->desk->setItem(i, j, it);

         }
    for(int i =0; i< 8;i++){
        ui->desk->setRowHeight(i,75);
        ui->desk->setColumnWidth(i,75);
    }



     connect(&timer, SIGNAL(timeout()), this, SLOT(addHodForTimeout()));
     setState(0);
}



void DeskGUI::addHodForTimeout(){
    int out = CalculeState::inst().getCurHod(cur_hod);
    if(out < 0){
       timer.stop();
       setState(0);
    }
    else{
        uint8_t w = GET_WIDTH(out);
        char h  = (char) GET_WIDTH(out);
        if((w+h )%2 == 0 )
            ui->desk->item(w,h)->setIcon(QIcon("k4.PNG"));
        else
            ui->desk->item(w,h)->setIcon(QIcon("kb.PNG"));
    }
}

DeskGUI::~DeskGUI()
{
    timer.stop();
    emit exit();
    delete ui;
}


void DeskGUI::closeEvent(QCloseEvent *event) {
    setState(0);
     timer.stop();
     emit exit();
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
       setState(1);
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
        setState(0);
        emit stopCalcul();
    }
}

QString getStringFromNum(uint8_t num){
    uint8_t w = GET_WIDTH(num);
    char h  = (char) GET_WIDTH(num);
    return QString(QChar(notate[0] + w+1)) + QString(QChar(h + 48+1)) ;
}

void DeskGUI::calculOut(QByteArray out){
    qDebug()<<"Finish!";
    QString out_s = "Вывод пути: " ;
    for(uint8_t i = 0;i<out.size();i++)
        out_s+= getStringFromNum(out[i])+" ";
    qmb.setText(out_s);
    qmb.exec();
    CalculeState::inst().setOutput(out);
    cur_hod =0;
    timer.start(500);
}

void DeskGUI::on_pushButton_stop_clicked()
{
    timer.stop();
    setState(0);
    emit stopCalcul();
}

void DeskGUI::setState(const uint8_t& st){
    state = st;
    switch(state){
     case 0 :
         ui->pushButton_start->setEnabled(true);
    break;
    case  1 :
        ui->pushButton_start->setEnabled(false);
    break;
    }

}


