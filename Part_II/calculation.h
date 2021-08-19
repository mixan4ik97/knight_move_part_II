#ifndef VIRTUALCALCULATION_H
#define VIRTUALCALCULATION_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QMutex>

#define N_DESK 8 // Размерность доски
#define MAX_MOVES 10 // Максимальное количество ходов конём
#define MAX_WARRING_MOVES 32 // Максимальное найденное количество ходов, после которого у пользователя спрашивается, нужно ли продолжать расчёт
#define SYSTEM_ERROR -1 // Ошибка работы главного тела программы
#define CALCULATION_ERROR -2 // Ошибка при вычислении
#define NOT_RESULT_ERROR -3 // Не был вычислен результат
#define GET_WIDTH(k)  (k % 8) // Вычисляет из порядкового номера клетки её номер в текущей строке
#define GET_HEIGHT(k)  (k/8) // Вчисляет номер строки

#define GET_H1(K) (K + 8 - 2)
#define GET_H2(K) (K + 8 * 2 - 1)
#define GET_H3(K) (K + 8 * 2 + 1)
#define GET_H4(K) (K + 8 + 2)
#define GET_H5(K) (K - 8 - 2)
#define GET_H6(K) (K - 8 * 2 - 1)
#define GET_H7(K) (K - 8 * 2 + 1)
#define GET_H8(K) (K - 8 + 2)
const char  notate[8] = { 'a','b','c','d','e','f','g','h' };  // таблица символов столбцов шахматной доск

class Calculation : public QObject
{
protected slots:
    virtual void startCalcul(uint8_t pos1, uint8_t pos2) =0;
    virtual void stopCalcul() = 0;
    Calculation();
protected:
    void getCorrectMove(uint8_t k, uint8_t &n);
};

#endif // VIRTUALCALCULATION_H
