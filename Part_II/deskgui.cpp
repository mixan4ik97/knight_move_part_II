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
    cur_hod=0;
    qmb.setWindowTitle("Внимание!");
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


        ui->desk->setRowHeight(0,32);
        ui->desk->setRowHeight(table_rang-1,32);
        ui->desk->setColumnWidth(0,16);
        ui->desk->setColumnWidth(table_rang-1,32);

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
        img_c[i-1].load(name, "PNG" );
        img[i-1]=img_c[i-1].scaled(32,32, Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);
        ic[i-1].setTexture(img_c[i-1]);
    }
    ui->desk->setSelectionMode(QAbstractItemView::NoSelection);


     ui->desk->setStyleSheet("border: none;");
    for(uint8_t i =1; i< table_rang-1;i++)
         for(uint8_t j =1; j< table_rang-1;j++){
             it = new QTableWidgetItem();
             it->setFlags( it->flags() ^ Qt::ItemIsEditable );
             if((i+j )%2 == 0 )
                 it->setBackground( ic[2]);
             else
                 it->setBackground( ic[3]);
             ui->desk->setItem(i, j, it);

         }

     connect(&timer, SIGNAL(timeout()), this, SLOT(addHodForTimeout()));
     setState(0);
}

void DeskGUI::drawCellImage(uint8_t h,uint8_t w,int8_t num){
    ui->desk->item(h,w)->setBackground(ic[num]);
}

//Функция очищающая доску
void DeskGUI::cleanDesk(){
    for(uint8_t i =1; i< table_rang-1;i++)
         for(uint8_t j =1; j< table_rang-1;j++){
             if((i+j )%2 == 0 )
                 drawCellImage(i,j,2);
             else
                 drawCellImage(i,j,3);
         }
    if(cur_hod){
            uint8_t out = CalculeState::inst().getCurPos2();
            uint8_t w = GET_WIDTH(out);
            uint8_t h  = GET_HEIGHT(out);
            if((w+h )%2 == 0 )
                drawCellImage(8-w,h+1,1);
            else
                drawCellImage(8-w,h+1,0);
    }
}

//Слот, реализующий ход конём
void DeskGUI::addHodForTimeout(){
    timer.setInterval(500);
    int out = CalculeState::inst().getCurHod(cur_hod);
    if(out < 0){
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
               drawCellImage(8-w,h+1,3);
            else
                drawCellImage(8-w,h+1,2);
        }
        w = GET_WIDTH(out);
        h  = (char) GET_HEIGHT(out);
        if((w+h )%2 == 0 )
            drawCellImage(8-w,h+1,1);
        else
            drawCellImage(8-w,h+1,0);
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
     QWidget::closeEvent(event);
}

//Функция, обрабатывающия изменение размера виджета
void DeskGUI::resizeEvent(QResizeEvent *event){
    int h = ui->desk->height()- ui->desk->rowHeight(0)*3;
    int w = ui->desk->width()- ui->desk->columnWidth(0)*3;

    if(h<w && h >0)
        r_kl = h/8;
    else
        r_kl = w/8;
    if(r_kl < 16)
        r_kl = 16;
    for(uint8_t i =1; i< table_rang-1;i++){
        ui->desk->setRowHeight(i,r_kl);
        ui->desk->setColumnWidth(i,r_kl);
    } 

    for(uint8_t i=0;i<4;i++){
        img[i] = img_c[i].scaled(QSize(r_kl.load(),r_kl.load()),Qt::KeepAspectRatio);
        ic[i].setTexture(img[i]);
    }

    cleanDesk();
    QWidget::resizeEvent(event);
}

void DeskGUI::showEvent(QShowEvent *event){
    resizeEvent(nullptr);
    QWidget::showEvent(event);
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
            drawCellImage(8-w,h+1,1);
        else
            drawCellImage(8-w,h+1,1);
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
    if(state){
        timer.stop();
        cleanDesk();
        cur_hod =0;
        setState(0);
        cleanDesk();
        emit stopCalcul();
    }
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
        cur_hod=0;
        ui->pushButton_start->setEnabled(false);
    break;
    }
}

