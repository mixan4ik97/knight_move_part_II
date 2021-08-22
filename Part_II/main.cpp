#include <QThread>
#include <QObject>
#include <QApplication>
#include "deskgui.h"
#include "knightmovecalculator.h"
#include "movecalcul.h"

//Главная функция работы программы
int main(int argc, char *argv[])
{
    qRegisterMetaType<uint8_t>("uint8_t");
    qRegisterMetaType<uint64_t>("uint64_t");
    QApplication a(argc, argv);
    DeskGUI dg; // Экземпляр класса с релизацией главного окна
    KnightMoveCalculator kmc; // Экземпляр класса предназначенный для организации вычисления
    MoveCalcul *mc[8]; // Классы для вычисления задачи в 8 потоков
    QThread t_mc[8]; // Потоки для вычисления
    for(uint8_t i =0;i<8;i++){
        mc[i] = new MoveCalcul(i); // Инициализируем классы для вычисления используя конструктор, который позволяет указать номер
    }
    //Объявляем сигналы
    QObject::connect(&dg,SIGNAL(startCalcul(uint8_t,uint8_t)),&kmc,SLOT(startCalcul(uint8_t,uint8_t)));
    QObject::connect(&dg,SIGNAL(stopCalcul()),&kmc,SLOT(stopCalcul()));
    QObject::connect(&kmc,SIGNAL(calculOut(QByteArray)),&dg,SLOT(calculOut(QByteArray)));
    for(uint8_t i =0;i<8;i++){
      QObject::connect(&kmc,SIGNAL(startAll(uint8_t , uint8_t )),mc[i],SLOT(startCalcul(uint8_t , uint8_t )));
      QObject::connect(&kmc,SIGNAL(stopAll()),mc[i],SLOT(stopCalcul()));
      QObject::connect(mc[i],SIGNAL(finishCalc(uint64_t , unsigned char  )),&kmc,SLOT(finishCalcul(uint64_t , unsigned char  )),Qt::UniqueConnection);
    }

    for(uint8_t i =0;i<8;i++)
        mc[i]->moveToThread(&t_mc[i]); // Запускаем работу класса в соответсвующем птотоке по индексу
    for(uint8_t i =0;i<8;i++)
        t_mc[i].start(); // Запускаем потоки
    QObject::connect(&dg,SIGNAL(exit()),&a,SLOT(quit())); // Подключаем сигнал, говорящий о закрытии приложения с объектом QApplication
    dg.show();
    int ret = a.exec(); // Ожидаем сигнала exit() от DeskGUI

    for(uint8_t i =0;i<8;i++){ // Аккуратно завершаем потоки
        t_mc[i].quit();
        t_mc[i].wait();
    }
    for(uint8_t i =0;i<8;i++) // Удаляекм экземпляры класса  MoveCalcul
        delete mc[i];
    return ret;// Завершаем работу приложения
}
