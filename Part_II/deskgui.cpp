#include "deskgui.h"
#include "ui_deskgui.h"
#include <QDir>
#include <QResizeEvent>

//Главный конструктор
DeskGUI::DeskGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DeskGUI)
{
    ui->setupUi(this);
    qmb.setWindowTitle("Внимание!");
    connect(this, SIGNAL(resized(int)), this, SLOT(resizeWindow()));
     ui->desk->horizontalHeader()->hide();
     ui->desk->verticalHeader()->hide();
    QTableWidgetItem *it;
    ui->desk->setSelectionMode(QAbstractItemView::NoSelection);
    for(uint8_t i =0; i< table_rang;i++)
         for(uint8_t j =0; j< table_rang;j++){
             it = new QTableWidgetItem();
             it->setFlags( it->flags() ^ Qt::ItemIsEditable );
             ui->desk->setItem(i, j, it);
         }


        ui->desk->setRowHeight(0,16);
        ui->desk->setRowHeight(table_rang-1,16);
        ui->desk->setColumnWidth(0,16);
        ui->desk->setColumnWidth(table_rang-1,16);

    for(uint8_t i =1; i< table_rang-1;i++){
        ui->desk->item(i,0)->setText(QString::number(table_rang-i-1));
        ui->desk->item(i,table_rang-1)->setText(QString::number(table_rang-i-1));
        ui->desk->item(0,i)->setText(QString(notate[i-1]));
        ui->desk->item(table_rang-1,i)->setText(QString(notate[i-1]));
    }

    QString patch = QDir::currentPath() + "/img/";
    QString name;
    for(uint8_t i =1; i<= 4;i++){
        name = patch +QString::number(i) + ".png";
        bool b = img[i-1].load(name, "PNG" );
        img[i-1].scaled(32,32, Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);
        ic[i-1].setTextureImage(img[i-1]);
    }
    ui->desk->setSelectionMode(QAbstractItemView::NoSelection);
    for(uint8_t i =1; i< table_rang-1;i++)
         for(uint8_t j =1; j< table_rang-1;j++){
             it = new QTableWidgetItem();
             it->setFlags( it->flags() ^ Qt::ItemIsEditable );
             if((i+j )%2 == 0 )
                 it->setBackground( ic[2]);
             else
                 it->setBackground( ic[3]);
             it->setSelected(true);
             ui->desk->setItem(i, j, it);

         }
    resizeEvent(NULL);
     connect(&timer, SIGNAL(timeout()), this, SLOT(addHodForTimeout()));
     setState(0);
}

//Функция очищающая доску
void DeskGUI::cleanDesk(){
    for(uint8_t i =1; i< table_rang-1;i++)
         for(uint8_t j =1; j< table_rang-1;j++){
             if((i+j )%2 == 0 )
                 ui->desk->item(i,j)->setBackground( ic[2]);
             else
                 ui->desk->item(i,j)->setBackground( ic[3]);
         }
}

// Слот, реализующий ход конём
void DeskGUI::addHodForTimeout(){
    timer.setInterval(500);
    int out = CalculeState::inst().getCurHod(cur_hod);
    if(out < 0){
       cur_hod=0;
       timer.stop();
       setState(0);
    }
    else{
        uint8_t w;
        char h;
        if(cur_hod>0){
            uint8_t temp = CalculeState::inst().getCurHod(cur_hod-1);
            w = GET_WIDTH(temp);
            h  = (char) GET_HEIGHT(temp);
            if((w+h )%2 == 0 )
                ui->desk->item(8-w,h+1)->setBackground( ic[3]);
            else
                ui->desk->item(8-w,h+1)->setBackground( ic[2]);
        }
        w = GET_WIDTH(out);
        h  = (char) GET_HEIGHT(out);
        if((w+h )%2 == 0 )
            ui->desk->item(8-w,h+1)->setBackground( ic[1]);
        else
            ui->desk->item(8-w,h+1)->setBackground( ic[0]);
        cur_hod++;
    }
}

//Деструктор
DeskGUI::~DeskGUI()
{
    emit stopCalcul();
    timer.stop();
    emit exit();
    delete ui;
}

// Функция, обрабатывающая закрытия окна
//QCloseEvent *event - класс - контейнер хранящий в себе информацию характеристик закрытия окна
void DeskGUI::closeEvent(QCloseEvent *event) {
    emit stopCalcul();
     setState(0);
     timer.stop();
     emit exit();
}

void DeskGUI::resizeEvent(QResizeEvent *event){

    uint16_t h = ui->desk->height()- ui->desk->rowHeight(0)*3;
    uint16_t w = ui->desk->width()- ui->desk->columnWidth(0)*3;
    if(h<w)
        r_kl = h/8;
    else
        r_kl = w/8;
    for(uint8_t i =1; i< table_rang-1;i++){
        ui->desk->setRowHeight(i,r_kl);
        ui->desk->setColumnWidth(i,r_kl);
    }

    for(uint8_t i =1; i<= 4;i++){
        img[i-1].scaled(r_kl,r_kl, Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);
        ic[i-1].setTextureImage(img[i-1]);
    }

    ui->desk->setIconSize(QSize(r_kl,r_kl));
    QWidget::resizeEvent(event);
}

// Функция проверяющая на корректность введённой строки с координатами
//QString pos - введённая строка позиции
bool DeskGUI::isCorrectCoordinate(QString pos) {
    if (pos.size() != 2)
        return false;
    if (pos.toStdString()[1] - 48 < 1 || pos.toStdString()[1] - 48 > 8)
        return false;
    for (uint8_t i = 0; i<8; i++)
        if (pos[0] == notate[i])
            return true;
    return false;

}

//Слот, обрабатывающий сигнал нажатия на кнопку "Старт"
void DeskGUI::on_pushButton_start_clicked()
{
    try {
       setState(1);
        QString pos1 = ui->lineEdit_knight->text();
        if(!isCorrectCoordinate( pos1)){
            qmb.setText("Первая координата введена не корректно.");
            qmb.exec();
            setState(0);
            return;
        }
        QString pos2 = ui->lineEdit_pos->text();
        if(!isCorrectCoordinate( pos2)){
            qmb.setText("Вторая координата введена не корректно.");
            qmb.exec();
            setState(0);
                return;
        }
        uint8_t k1 = GET_NUMBER(pos1.toStdString());
        uint8_t k2 = GET_NUMBER(pos2.toStdString());

        if(k1 == k2){
            qmb.setText("Вы ввели одинаковые координаты.");
            qmb.exec();
            setState(0);
            return;
        }
        cleanDesk();
       CalculeState::inst().resetState();
       uint8_t w = GET_WIDTH(k1);
       uint8_t  h  = (char) GET_HEIGHT(k1);
        if((w+h )%2 == 0 )
            ui->desk->item(8-w,h+1)->setBackground( ic[1]);
        else
            ui->desk->item(8-w,h+1)->setBackground( ic[0]);
        ui->desk->repaint();
        timer.start(500);
        emit startCalcul(k1, k2);
    }
    catch (...) {
        setState(0);
        emit stopCalcul();
    }
}

// Слот, принимающий сигнал с конечным значением пути
void DeskGUI::calculOut(QByteArray out){
    if(out.size() <= 1){
        qmb.setText("Решение не было найдено.");
        qmb.exec();
        setState(0);
        return;
    }
    CalculeState::inst().setOutput(out);
    cur_hod =1;
}

//Слот, обрабатывающий сигнал по нажатию на кнопку "Стоп"
void DeskGUI::on_pushButton_stop_clicked()
{
    timer.stop();
    cleanDesk();
    setState(0);
    emit stopCalcul();
}

// Устанавливает текущее состояние работы окна
//const uint8_t& st - номер состояния 0 или 1
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

