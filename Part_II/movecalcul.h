#ifndef MOVECALCUL_H
#define MOVECALCUL_H
#include "knightmovecalculator.h"
#include <QMutex>
#include <QPair>
typedef  QPair<uint8_t,uint64_t> knight_pair;

class MoveCalcul : public KnightMoveCalculator
{
    Q_OBJECT
public:
    MoveCalcul();
    MoveCalcul(uint8_t num);
    MoveCalcul(uint8_t num, bool war);
    ~MoveCalcul();
protected slots:
    virtual void startCalcul(uint8_t pos1, uint8_t pos2);
    virtual void stopCalcul();
signals:
    void finishCalc(uint64_t flags, unsigned char count );
    void finished();


private:
    knight_pair calk_knight(uint8_t k1, const uint8_t &k2, uint64_t k_flags, uint8_t count, knight_pair cur_min);
    uint8_t c_num;
    uint8_t cur_min;
    uint8_t flags_min;
    bool is_warring;
    bool is_stop;
    QMutex m_mutex;
};

#endif // MOVECALCUL_H
