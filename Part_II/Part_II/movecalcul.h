#ifndef MOVECALCUL_H
#define MOVECALCUL_H
#include "knightmovecalculator.h"
#include "QMutex"


class MoveCalcul : KnightMoveCalculator
{
protected:
    MoveCalcul();
    MoveCalcul(uint8_t num);
    MoveCalcul(uint8_t num, bool war);
signals:
    void finishCalcul(uint8_t flags, uint8_t count);
private:
    uint8_t calk_knight( uint8_t k, uint64_t k_flags, QVector<uint8_t> hods, uint8_t cur_min);
    uint8_t c_num;
    uint8_t cur_min;
    bool is_warring;
    bool is_stop;
    QMutex m_mutex;
};

#endif // MOVECALCUL_H
