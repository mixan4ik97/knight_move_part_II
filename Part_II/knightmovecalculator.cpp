#include "knightmovecalculator.h"

KnightMoveCalculator::KnightMoveCalculator()
{
    CalculeState::inst().resetState();
}

KnightMoveCalculator::~KnightMoveCalculator()
{
}

void KnightMoveCalculator::startCalcul(uint8_t pos1, uint8_t pos2){
    CalculeState::inst().resetState();
    CalculeState::inst().setCurPos1( pos1);
    CalculeState::inst().setCurPos2( pos2);
    emit startAll(pos1,pos2);
}

void KnightMoveCalculator::stopCalcul(){
    emit stopAll();
    QThread::currentThread()->exit();
}



QByteArray KnightMoveCalculator::getQVectorFromFlags(const uint64_t &flags,const uint8_t &count ,QByteArray ret,uint8_t pos1,const uint8_t &pos2, uint64_t flags_this){
    flags_this |= 1 << pos1;
    ret.push_back(pos1);
    if (pos1 == pos2){
          return ret;
    }
    uint8_t size = ret.size();
      if ( size >= count)
          return QByteArray();
      QByteArray ret_t;
      if ( !(flags_this & (1 << GET_H1(pos1))) && ((flags & (1 << GET_H1(pos1))))){
          ret_t = getQVectorFromFlags(flags, count, ret, GET_H1(pos1),pos2,flags_this );
          if (ret_t.size() == count){ return ret_t;}
      }

      if ( !(flags_this & (1 << GET_H2(pos1))) && ((flags & (1 << GET_H2(pos1))))){
          ret_t = getQVectorFromFlags(flags, count, ret, GET_H2(pos1),pos2,flags_this );
          if (ret_t.size() == count){ return ret_t;}
      }

      if ( !(flags_this & (1 << GET_H3(pos1))) && ((flags & (1 << GET_H3(pos1))))){
          ret_t = getQVectorFromFlags(flags, count, ret, GET_H3(pos1),pos2,flags_this );
          if (ret_t.size() == count){ return ret_t;}
      }

      if ( !(flags_this & (1 << GET_H4(pos1))) && ((flags & (1 << GET_H4(pos1))))){
          ret_t = getQVectorFromFlags(flags, count, ret, GET_H4(pos1),pos2,flags_this );
          if (ret_t.size() == count){ return ret_t;}
      }

      if ( !(flags_this & (1 << GET_H5(pos1))) && ((flags & (1 << GET_H5(pos1))))){
          ret_t = getQVectorFromFlags(flags, count, ret, GET_H5(pos1),pos2,flags_this );
          if (ret_t.size() == count){ return ret_t;}
      }

      if ( !(flags_this & (1 << GET_H6(pos1))) && ((flags & (1 << GET_H6(pos1))))){
          ret_t = getQVectorFromFlags(flags, count, ret, GET_H6(pos1),pos2,flags_this );
          if (ret_t.size() == count){ return ret_t;}
      }

      if ( !(flags_this & (1 << GET_H7(pos1))) && ((flags & (1 << GET_H7(pos1))))){
          ret_t = getQVectorFromFlags(flags, count, ret, GET_H7(pos1),pos2,flags_this );
          if (ret_t.size() == count){ return ret_t;}
      }

      if ( !(flags_this & (1 << GET_H8(pos1))) && ((flags & (1 << GET_H8(pos1))))){
          ret_t = getQVectorFromFlags(flags, count, ret, GET_H8(pos1),pos2,flags_this );
          if (ret_t.size() == count){ return ret_t;}
      }

    return QByteArray();
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
            emit calculOut(QByteArray());
            return;
        }
        qDebug()<<"Yeeee!!!!";
        emit calculOut(getQVectorFromFlags(CalculeState::inst().getFlagsMin(), CalculeState::inst().getCountMin()+1,QByteArray(),CalculeState::inst().getCurPos1(),CalculeState::inst().getCurPos2(),0));
    }
}
