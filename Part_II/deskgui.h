#ifndef DESKGUI_H
#define DESKGUI_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include "knightmovecalculator.h"
#define table_rang 10

namespace Ui {
class DeskGUI;
}

//Класс реализующий работу главного окна
class DeskGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit DeskGUI(QWidget *parent = 0);
    ~DeskGUI();
public slots:
    void calculOut(QByteArray out); // Слот, принимающий сигнал с конечным значением пути
protected:
    void closeEvent(QCloseEvent *event); // Функция, обрабатывающая закрытия окна
    void resizeEvent(QResizeEvent *event);
private slots:
    void on_pushButton_start_clicked(); //Слот, обрабатывающий сигнал нажатия на кнопку "Старт"

    void on_pushButton_stop_clicked(); //Слот, обрабатывающий сигнал по нажатию на кнопку "Стоп"

    void addHodForTimeout(); // Слот, реализующий ход конём

signals:
    void startCalcul(uint8_t pos1, uint8_t pos2); //  Сигнал начала вычисления
    void stopCalcul(); // Сигнал остановки вычисления
    void exit(); // Сигнал закрытия приложения
private:
    bool isCorrectCoordinate(QString pos); // Функция проверяющая на корректность введённой строки с координатами
    void setState(const uint8_t& st); // Устанавливает текущее состояние работы окна
    void cleanDesk(); // Очищает доску
    QIcon ic[4]; // Контейнер, хранящий в себе значки для шахматной доски
    uint8_t state; // Значение текущего состояния работы виджета. 0 - окно готово к работе, 1 - программа в состоянии расчёта, возможно только остановить
    QMessageBox qmb; // Класс, реализующий работу окно с сообщением
    Ui::DeskGUI *ui; // Класс, хранящий в себе описание, структуру и характеристики объектов на главном окне
    QTimer timer; // Класс, реализующий работу таймера
    uint8_t cur_hod; // Переменная, хранящая в себе текущий номер хода
    QPixmap img[4];  // Контейнер, хранящий в себе загруженные изображения значков для шахматной доски в виде класса - контейнера QImage
    std::atomic<uint16_t> r_kl;
};

#endif // DESKGUI_H
