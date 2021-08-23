#include "deskgui.h"
#include "ui_deskgui.h"
#include <QDir>


//Главный конструктор
DeskGUI::DeskGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DeskGUI)
{
    ui->setupUi(this);
    qmb.setWindowTitle("Внимание!");
    ui->desk->setHorizontalHeaderLabels({"a","b","c","d","e","f","g","h"});
    ui->desk->setVerticalHeaderLabels({"8","7","6","5","4","3","2","1"});
    QTableWidgetItem *it;
    ui->desk->setSelectionMode(QAbstractItemView::NoSelection);
    for(int i =0; i< 8;i++)
         for(int j =0; j< 8;j++){
             it = new QTableWidgetItem();
             it->setFlags( it->flags() ^ Qt::ItemIsEditable );
             ui->desk->setItem(i, j, it);
         }
    QString patch = QDir::currentPath() + "/img/";
    QString name;
    QImage img;
    for(uint8_t i =1; i<= 4;i++){
        name = patch +QString::number(i) + ".png";
        bool b = img.load(name, "PNG" );
        img = img.scaled(32,32);
        ic[i-1].setTextureImage(img);
    }
    ui->desk->setSelectionMode(QAbstractItemView::NoSelection);
    for(uint8_t i =0; i< 8;i++)
         for(uint8_t j =0; j< 8;j++){
             it = new QTableWidgetItem();
             it->setFlags( it->flags() ^ Qt::ItemIsEditable );
             if((i+j )%2 == 0 )
                 it->setBackground( ic[2]);
             else
                 it->setBackground( ic[3]);
             ui->desk->setItem(i, j, it);

         }
    for(int i =0; i< 8;i++){
        ui->desk->setRowHeight(i,32);
        ui->desk->setColumnWidth(i,32);
    }

     connect(&timer, SIGNAL(timeout()), this, SLOT(addHodForTimeout()));
     setState(0);
}

//Функция очищающая доску
void DeskGUI::cleanDesk(){
    for(uint8_t i =0; i< 8;i++)
         for(uint8_t j =0; j< 8;j++){
             if((i+j )%2 == 0 )
                 ui->desk->item(i,j)->setBackground( ic[2]);
             else
                 ui->desk->item(i,j)->setBackground( ic[3]);
         }
}

// Слот, реализующий ход конём
void DeskGUI::addHodForTimeout(){
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
                ui->desk->item(7-h,w)->setBackground( ic[3]);
            else
                ui->desk->item(7-h,w)->setBackground( ic[2]);
        }
        w = GET_WIDTH(out);
        h  = (char) GET_HEIGHT(out);
        if((w+h )%2 == 0 )
            ui->desk->item(7-h,w)->setBackground( ic[1]);
        else
            ui->desk->item(7-h,w)->setBackground( ic[0]);
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
        CalculeState::inst().resetState();
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
    cleanDesk();
    CalculeState::inst().setOutput(out);
    cur_hod =0;
    timer.start(500);
}

//Слот, обрабатывающий сигнал по нажатию на кнопку "Стоп"
void DeskGUI::on_pushButton_stop_clicked()
{
    timer.stop();
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


