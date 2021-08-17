#ifndef MOVECALCUL_H
#define MOVECALCUL_H
#include "knightmovecalculator.h"
#include <QMutex>


class MoveCalcul : public KnightMoveCalculator
{
    Q_OBJECT
public:
    MoveCalcul();
    MoveCalcul(uint8_t num);
    MoveCalcul(uint8_t num, bool war);
    ~MoveCalcul();
protected slots:
    void startCalcul(uint8_t pos1, uint8_t pos2);
    void stopCalcul();
signals:
    void finishCalc(unsigned char flags, unsigned char count);
private:
    uint8_t calk_knight(uint8_t k1,const uint8_t &k2, uint64_t k_flags, uint8_t &count);
    uint8_t c_num;
    uint8_t cur_min;
    bool is_warring;
    bool is_stop;
    QMutex m_mutex;
};

#endif // MOVECALCUL_H
