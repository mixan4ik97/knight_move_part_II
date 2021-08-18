#include "knightmovecalculator.h"

KnightMoveCalculator::KnightMoveCalculator()
{
    CalculeState::inst().resetState();
    cur_pos1 = 0;
    cur_pos2 = 0;
}

KnightMoveCalculator::~KnightMoveCalculator()
{
    emit stopAll();
}

void KnightMoveCalculator::startCalcul(uint8_t pos1, uint8_t pos2){
    CalculeState::inst().resetState();
    cur_pos1 = pos1;
    cur_pos2 = pos2;
    emit startAll(pos1,pos2);
}

void KnightMoveCalculator::stopCalcul(){
    emit stopAll();
}



QVector<uint8_t> KnightMoveCalculator::getQVectorFromFlags(const uint8_t &flags,const uint8_t &count ,QVector<uint8_t> ret,uint8_t pos1,const uint8_t &pos2, uint64_t flags_this){
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



void KnightMoveCalculator::finishCalcul(uint64_t flags, unsigned char count){
    if(count < CalculeState::inst().getCountMin() && count <= MAX_MOVES && count > 0 && flags != 0){
        CalculeState::inst().setCountMin( count);
        CalculeState::inst().setFlagsMin( flags);
    }
    CalculeState::inst().incrCalcul();
    uint8_t countCalcul = CalculeState::inst().getCountCalcul();
    if(countCalcul == 8){
        if(CalculeState::inst().getCountMin() > MAX_MOVES || CalculeState::inst().getCountMin() ==0 || CalculeState::inst().getFlagsMin() == 0){
            qDebug()<<"getCountMin "<< CalculeState::inst().getCountMin()<<" getFlagsMin"<<CalculeState::inst().getFlagsMin();
            emit finish(QVector<uint8_t>());
            return;
        }
        qDebug()<<"Yeeee!!!!";
        QVector<uint8_t> ret = getQVectorFromFlags(CalculeState::inst().getFlagsMin(), CalculeState::inst().getCountMin(),QVector<uint8_t>(),cur_pos1,cur_pos2,0);
        emit finish(ret);
    }
}
