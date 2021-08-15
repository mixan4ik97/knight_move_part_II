#ifndef KNIGHTMOVECALCULATOR_H
#define KNIGHTMOVECALCULATOR_H

#include <QObject>
#include <QThread>
#include "movecalcul.h"

#define N_DESK 8 // Размерность доски
#define MAX_MOVES 64 // Максимальное количество ходов конём
#define MAX_WARRING_MOVES 32 // Максимальное найденное количество ходов, после которого у пользователя спрашивается, нужно ли продолжать расчёт
#define SYSTEM_ERROR -1 // Ошибка работы главного тела программы
#define CALCULATION_ERROR -2 // Ошибка при вычислении
#define NOT_RESULT_ERROR -3 // Не был вычислен результат
#define GET_NUMBER(pos)  ((pos[0] - notate[0])*8 + pos[1]-48) // Преоводит число из символа в ASII  в целочисленное однобайтовое значение
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

class KnightMoveCalculator
{
public:
    KnightMoveCalculator();
public slots:
   virtual void startCalcul(uint8_t pos1, uint8_t pos2);
   virtual void stopCalcul();
protected slots:
    finishCalcul(uint8_t flags, uint8_t count);
protected:
    void getCorrectMove(uint8_t k, uint8_t &n);
signals:
    void startAll(uint8_t pos1, uint8_t pos2);
    finish(QVector<uint8_t> ret);
    void stopAll();
private:
    QVector<uint8_t> getQVectorFromFlags(const uint8_t &flags, const uint8_t &count, const uint8_t &pos1,const uint8_t &pos2, bool flags_this);
    uint8_t countCalcul;
    MoveCalcul *mc[8];
    QThread t_mc[8];
    uint8_t count_min;
    uint8_t flags_min;
    uint8_t cur_pos1;
    uint8_t cur_pos2;
};

#endif // KNIGHTMOVECALCULATOR_H
