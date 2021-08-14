#ifndef KNIGHTMOVECALCULATOR_H
#define KNIGHTMOVECALCULATOR_H

#include <QObject>

#define N_DESK 8 // Размерность доски
#define MAX_MOVES 64 // Максимальное количество ходов конём
#define MAX_WARRING_MOVES 32 // Максимальное найденное количество ходов, после которого у пользователя спрашивается, нужно ли продолжать расчёт
#define SYSTEM_ERROR -1 // Ошибка работы главного тела программы
#define CALCULATION_ERROR -2 // Ошибка при вычислении
#define NOT_RESULT_ERROR -3 // Не был вычислен результат
#define GET_NUMBER(pos)  ((pos[0] - notate[0])*8 + pos[1]-48) // Преоводит число из символа в ASII  в целочисленное однобайтовое значение
#define GET_WIDTH(k)  (k % 8) // Вычисляет из порядкового номера клетки её номер в текущей строке
#define GET_HEIGHT(k)  (k/8) // Вчисляет номер строки

class KnightMoveCalculator
{
public:
    KnightMoveCalculator();
public slots:
    void startCalcul(uint8_t pos1, uint8_t pos2);
protected slots:
    void finish_calc(QVector<uint8_t> out, uint8_t num);
signals:
    void finish(QVector<uint8_t> out);
private:
    uint8_t countCalcul;
};

#endif // KNIGHTMOVECALCULATOR_H
