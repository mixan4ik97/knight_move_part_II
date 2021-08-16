#include "knightmovecalculator.h"

KnightMoveCalculator::KnightMoveCalculator()
{
    countCalcul =0;
    cur_pos1 = 0;
    cur_pos2 = 0;
}

KnightMoveCalculator::~KnightMoveCalculator()
{
    emit stopAll();
}

void KnightMoveCalculator::startCalcul(uint8_t pos1, uint8_t pos2){
    countCalcul =0;
    cur_pos1 = pos1;
    cur_pos2 = pos2;
    count_min = 0xFF;
    emit startAll(pos1,pos2);
}

void KnightMoveCalculator::stopCalcul(){
    emit stopAll();
}


/*
Функция возвращает переменную с битовыми флагами (n), говорящих о том,какой ход возможен для коня
uint8_t k - номер клетки, в которой находится конь
uint8_t &n - возвращаемое значение битовых флагов, которые определяют номера ходов по порядку от 1 - го до 8-го.

  2   3
1      4
    k
5      7
 6    8
*/
void KnightMoveCalculator::getCorrectMove(uint8_t k, uint8_t &n){
    uint8_t k_w = GET_WIDTH(k);
    uint8_t k_h = GET_HEIGHT(k);
    n = 0;
    if (k_w > 2 && k_h < 8)
        n |= 1 << 1;
    if (k_w > 1 && k_h < 7)
        n |= 1 << 2;
    if (k_w < 8 && k_h < 7)
        n |= 1 << 3;
    if (k_w < 7 && k_h < 8)
        n |= 1 << 4;
    if (k_w > 2 && k_h >1)
        n |= 1 << 5;
    if (k_w > 1 && k_h >2)
        n |= 1 << 6;
    if (k_w < 8 && k_h >2)
        n |= 1 << 7;
    if (k_w < 7 && k_h < 1)
        n |= 1 << 8;
}


QVector<uint8_t> KnightMoveCalculator::getQVectorFromFlags(const uint8_t &flags,const uint8_t &count ,QVector<uint8_t> ret,uint8_t pos1,const uint8_t &pos2, bool flags_this){
    uint8_t c_pos = pos1;
    if(ret.size() >= count &&  c_pos!= pos2)
        return QVector<uint8_t>();
    ret.push_back(c_pos);
    if(ret.size() == count &&  c_pos== pos2)
        return ret;
    flags_this |= 1 << c_pos;
    if(c_pos != pos2 && ret.size() < count ){
        uint8_t k_flags;
        getCorrectMove(c_pos, k_flags);
        if ((flags & (1 << GET_H1(c_pos)))  && (k_flags & (1 << 1)) && ~(flags_this & (1 << GET_H1(c_pos))) )
            ret += getQVectorFromFlags(flags,  count,ret, GET_H1(c_pos), pos2,flags_this);
        if ((flags & (1 << GET_H2(c_pos)))  && (k_flags & (1 << 2)) && ~(flags_this & (1 << GET_H2(c_pos))))
            ret += getQVectorFromFlags(flags,  count,ret, GET_H2(c_pos), pos2,flags_this);
        if ((flags & (1 << GET_H3(c_pos)))  && (k_flags & (1 << 3))  && ~(flags_this & (1 << GET_H3(c_pos))))
            ret += getQVectorFromFlags(flags,  count,ret, GET_H3(c_pos), pos2,flags_this);
        if ((flags & (1 << GET_H4(c_pos)))  && (k_flags & (1 << 4))  && ~(flags_this & (1 << GET_H4(c_pos))))
            ret += getQVectorFromFlags(flags,  count,ret, GET_H4(c_pos), pos2,flags_this);
        if ((flags & (1 << GET_H5(c_pos)))  && (k_flags & (1 << 5))  && ~(flags_this & (1 << GET_H5(c_pos))))
            ret += getQVectorFromFlags(flags,  count,ret, GET_H5(c_pos), pos2,flags_this);
        if ((flags & (1 << GET_H6(c_pos)))  && (k_flags & (1 << 6))  && ~(flags_this & (1 << GET_H6(c_pos))))
            ret += getQVectorFromFlags(flags,  count,ret, GET_H6(c_pos), pos2,flags_this);
        if ((flags & (1 << GET_H7(c_pos)))  && (k_flags & (1 << 7))  && ~(flags_this & (1 << GET_H7(c_pos))))
            ret += getQVectorFromFlags(flags,  count,ret, GET_H7(c_pos), pos2,flags_this);
        if ((flags & (1 << GET_H8(c_pos)))  && (k_flags & (1 << 8)) && ~(flags_this & (1 << GET_H8(c_pos))))
            ret += getQVectorFromFlags(flags,  count,ret, GET_H8(c_pos), pos2,flags_this);
        return ret;
    }
    return QVector<uint8_t>();
}

void KnightMoveCalculator::finishCalcul(uint8_t flags, uint8_t count){
    countCalcul++;
    if(count < count_min){
        count_min = count;
        flags_min = flags;
    }
    if(countCalcul >=7){
        if(count_min > MAX_MOVES || count_min ==0 || flags_min == 0)
            emit finish(QVector<uint8_t>());
        QVector<uint8_t> ret = getQVectorFromFlags(flags_min, count_min,QVector<uint8_t>(),cur_pos1,cur_pos2,0);
    }
}
