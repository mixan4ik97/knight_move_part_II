#include "knightmovecalculator.h"

KnightMoveCalculator::KnightMoveCalculator()
{
    CalculeState::inst().resetState();
}

KnightMoveCalculator::~KnightMoveCalculator()
{
}

void KnightMoveCalculator::startCalcul(const uint8_t & pos1, const uint8_t & pos2){
    CalculeState::inst().resetState();
    CalculeState::inst().setCurPos1( pos1);
    CalculeState::inst().setCurPos2( pos2);
    emit startAll(pos1,pos2);
}

void KnightMoveCalculator::stopCalcul(){

}



QByteArray KnightMoveCalculator::getQVectorFromFlags(const uint64_t &flags,const uint8_t &count ,QByteArray ret,uint8_t pos1,const uint8_t &pos2, uint64_t flags_this){
    flags_this |= _BV(pos1);
    ret.push_back(pos1);
    if (pos1 == pos2){
          return ret;
    }
    uint8_t size = ret.size();
      if ( size >= count)
          return QByteArray();
      QByteArray ret_t;
      if ( !(flags_this & (_BV(GET_H1(pos1)))) && ((flags & (_BV( GET_H1(pos1)))))){
          ret_t = getQVectorFromFlags(flags, count, ret, GET_H1(pos1),pos2,flags_this );
          if (ret_t.size() == count){ return ret_t;}
      }

      if ( !(flags_this & (_BV(GET_H2(pos1)))) && ((flags & (_BV(GET_H2(pos1)))))){
          ret_t = getQVectorFromFlags(flags, count, ret, GET_H2(pos1),pos2,flags_this );
          if (ret_t.size() == count){ return ret_t;}
      }

      qDebug()<<pos1<<"   "<<GET_H4(pos1)<<(flags & (_BV(GET_H4(pos1))) ? "tr" : "fl" ) ;
      if ( !(flags_this & (_BV(GET_H3(pos1)))) && ((flags & (_BV(GET_H3(pos1)))))){
          ret_t = getQVectorFromFlags(flags, count, ret, GET_H3(pos1),pos2,flags_this );
          if (ret_t.size() == count){ return ret_t;}
      }
         if ( !(flags_this & (_BV(GET_H4(pos1)))) && ((flags & (_BV(GET_H4(pos1)))))){
          ret_t = getQVectorFromFlags(flags, count, ret, GET_H4(pos1),pos2,flags_this );
          if (ret_t.size() == count){ return ret_t;}
      }

      if ( !(flags_this & (_BV(GET_H5(pos1)))) && ((flags & (_BV(GET_H5(pos1)))))){
          ret_t = getQVectorFromFlags(flags, count, ret, GET_H5(pos1),pos2,flags_this );
          if (ret_t.size() == count){ return ret_t;}
      }

      if ( !(flags_this & (_BV(GET_H6(pos1)))) && ((flags & (_BV(GET_H6(pos1)))))){
          ret_t = getQVectorFromFlags(flags, count, ret, GET_H6(pos1),pos2,flags_this );
          if (ret_t.size() == count){ return ret_t;}
      }

      if ( !(flags_this & (_BV(GET_H7(pos1)))) && ((flags & (_BV(GET_H7(pos1)))))){
          ret_t = getQVectorFromFlags(flags, count, ret, GET_H7(pos1),pos2,flags_this );
          if (ret_t.size() == count){ return ret_t;}
      }

      if ( !(flags_this & (_BV(GET_H8(pos1)))) && ((flags & (_BV(GET_H8(pos1)))))){
          ret_t = getQVectorFromFlags(flags, count, ret, GET_H8(pos1),pos2,flags_this );
          if (ret_t.size() == count){ return ret_t;}
      }

    return QByteArray();
}



void KnightMoveCalculator::finishCalcul(uint64_t flags, unsigned char count){
    if(count < CalculeState::inst().getCountMin() && count <= MAX_MOVES && count > 0 && flags != 0){
        qDebug()<<"Min: "<<CalculeState::inst().getCountCalcul()<< " "<<count<<" "<<flags;
        CalculeState::inst().setCountMin( count);
        CalculeState::inst().setFlagsMin( flags);
    }
    uint8_t countCalcul = CalculeState::inst().getCountCalcul();
    CalculeState::inst().incrCalcul();
    countCalcul++;
    if(countCalcul == 8){
        if(CalculeState::inst().getCountMin() > MAX_MOVES || CalculeState::inst().getCountMin() ==0 || CalculeState::inst().getFlagsMin() == 0){
            emit calculOut(QByteArray());
            return;
        }
        qDebug()<<CalculeState::inst().getCountCalcul()<< " "<<CalculeState::inst().getCountMin()<<" "<<CalculeState::inst().getFlagsMin();
        QByteArray t;
        uint64_t flags_min = CalculeState::inst().getFlagsMin();
        uint8_t count_min = CalculeState::inst().getCountMin()+1;
        uint8_t p1 = CalculeState::inst().getCurPos1();
        uint8_t p2 = CalculeState::inst().getCurPos2();
        for(uint8_t i =0;i<8;i++){
            QString temp;
            for(uint8_t j =0;j<8;j++){
                if(i*8+j == p1 && (flags_min & (_BV(i*8+j))) )
                    temp+="* ";
                else
                    if(i*8+j == p2 && (flags_min & (_BV(i*8+j))))
                        temp+="# ";
                    else
                        temp+=(flags_min & (_BV(i*8+j)) ? "1 " : "0 ");
            }
                qDebug()<<temp;
        }
        qDebug()<<"count_min = "<<count_min;
        emit calculOut(getQVectorFromFlags(flags_min, count_min,t,p1,p2,_BV(p1)));
    }
}
