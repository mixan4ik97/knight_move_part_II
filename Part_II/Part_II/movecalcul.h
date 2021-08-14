#ifndef MOVECALCUL_H
#define MOVECALCUL_H
#include "knightmovecalculator.h"


class MoveCalcul : KnightMoveCalculator
{
protected:
    MoveCalcul();
    MoveCalcul(uint8_t num);
    MoveCalcul(uint8_t num, bool war);
protected slots:
    void calcul(uint8_t pos1, uint8_t pos2);
private:
    uint8_t c_num;
   bool is_warring;
};

#endif // MOVECALCUL_H
