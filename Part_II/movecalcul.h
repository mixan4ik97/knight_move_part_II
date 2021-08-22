#ifndef MOVECALCUL_H
#define MOVECALCUL_H
#include "knightmovecalculator.h"
#include <QPair>
typedef  QPair<uint8_t,uint64_t> knight_pair; // Тип, представляющий из себя пару из количества ходов и битовых флагов


//Класс, реализующий вычисления минимального пути коня
//Он является подклассом класса KnightMoveCalculator, так как потенциально может быть реализован
//подобно классу KnightMoveCalculator и запускать для вычислений 8 потоков
//В данной задаче это не применялось
class MoveCalcul : public KnightMoveCalculator
{
    Q_OBJECT
public:
    MoveCalcul();
    MoveCalcul(uint8_t num); // Конструктор, принимающий в себя номер хода.
    ~MoveCalcul();
protected slots:
    virtual void startCalcul(uint8_t pos1, uint8_t pos2); // Функция, завучкающая процесс вычисления
    virtual void stopCalcul();// Функция, принудительно завершающая процесс вычисления
signals:
    void finishCalc(uint64_t flags, unsigned char count ); // Сигнал завершения работы программы
private:
    //Рекурсивная функция вычисления кротчайшего пути
    knight_pair calk_knight(uint8_t k1, const uint8_t &k2, uint64_t k_flags, uint8_t count, knight_pair cur_min);
    uint8_t c_num; // Номер хода для данног очлена класса
    std::atomic_bool is_stop; // Флаг, предназначенныйй для принудительного завершения работы программы
};

#endif // MOVECALCUL_H
