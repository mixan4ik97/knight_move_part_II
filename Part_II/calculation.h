#ifndef CALCULATION_H
#define CALCULATION_H

#include <QObject>
#include <QThread>
#include <QMutex>

const char  notate[8] = { 'a','b','c','d','e','f','g','h' };  // таблица символов столбцов шахматной доск
#define N_DESK 8 // Размерность доски
#define MAX_MOVES 32 // Максимальное количество ходов конём
#define GET_NUMBER(pos)  ((pos[0] - notate[0])*8 + pos[1]-48)-1 // Преоводит число из символа в ASII  в целочисленное однобайтовое значение
#define GET_WIDTH(k)  ((k) % 8) // Вычисляет из порядкового номера клетки её номер в текущей строке
#define GET_HEIGHT(k)  ((k)/8) // Вчисляет номер строки
#define _BV(k)( (uint64_t) 1 << (uint64_t) k) // Единая функция для определения

// Функции реализующие ходы коня с ячейки под номером K
#define GET_H0(K) (K + 8 - 2)
#define GET_H1(K) (K + 8 * 2 - 1)
#define GET_H2(K) (K + 8 * 2 + 1)
#define GET_H3(K) (K + 8 + 2)
#define GET_H4(K) (K - 8 - 2)
#define GET_H5(K) (K - 8 * 2 - 1)
#define GET_H6(K) (K - 8 * 2 + 1)
#define GET_H7(K) (K - 8 + 2)


//Виртуальный клас с чистыми абстрактными функциями и общими функциями для потомков.
//Класс представляет из себя объект, реализующий вычисления кротчайшего пути для коня
class Calculation : public QObject
{
protected slots:
    virtual void startCalcul(const uint8_t &pos1, const uint8_t &pos2) =0; // Функция, завучкающая процесс вычисления
    virtual void stopCalcul() = 0;// Функция, принудительно завершающая процесс вычисления
    Calculation();
protected:
    void getCorrectMove(const uint8_t &k, uint16_t &n); // Функция возвращающая
    bool getOneCorrectMove(const uint8_t & k,const uint8_t & i);
};

#endif
