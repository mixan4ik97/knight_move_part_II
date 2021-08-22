#include "movecalcul.h"

MoveCalcul::MoveCalcul()
{
    is_stop = false;

}


MoveCalcul::MoveCalcul(uint8_t num){
    c_num  = num;
    is_stop = false;

}

MoveCalcul::~MoveCalcul(){
    stopCalcul();
}



/*
Рекурсивная функция вычисления кротчайшего пути
uint8_t k1 - порядковый номер текущего положения коня
uint8_t k2 - конечное положение коня
uint64_t k_flags - битовые флаги порядковых номеров, в которых конь уже был
uint8_t count - текущий ход конём
*/
knight_pair MoveCalcul::calk_knight(uint8_t k1, const uint8_t &k2, uint64_t k_flags, uint8_t count, knight_pair cur_min) {
    k_flags |= _BV(k1);
    if (k1 == k2){
          return knight_pair(count,k_flags);
    }
    if(is_stop.load())
        return knight_pair(0xFF,0);

      if (count > cur_min.first || count > CalculeState::inst().getCountMin())
          return knight_pair(0xFF,0);
      if (count >= MAX_MOVES)
          return knight_pair(0xFF,0);
      uint16_t n_flags;
      getCorrectMove(k1, n_flags);
      knight_pair temp;
      temp.first=0xFF;
      temp.second=0;
      if (n_flags & (_BV(0)) && !(k_flags & _BV(GET_H0(k1))))
          temp = calk_knight(GET_H0(k1), k2, k_flags, count + 1,cur_min);
      if (cur_min.first > temp.first){ cur_min.first = temp.first; cur_min.second = temp.second;}
      if (n_flags & (_BV(1)) && !(k_flags & _BV(GET_H1(k1))))
          temp = calk_knight(GET_H1(k1), k2, k_flags, count + 1,cur_min);
      if (cur_min.first > temp.first){ cur_min.first = temp.first; cur_min.second = temp.second;}
      if (n_flags & (_BV(2)) && !(k_flags & _BV(GET_H2(k1))))
          temp = calk_knight(GET_H2(k1), k2, k_flags, count + 1,cur_min);
      if (cur_min.first > temp.first){ cur_min.first = temp.first; cur_min.second = temp.second;}
      if (n_flags & (_BV(3)) && !(k_flags & _BV(GET_H3(k1))))
          temp = calk_knight(GET_H3(k1), k2, k_flags, count + 1,cur_min);
      if (cur_min.first > temp.first){ cur_min.first = temp.first; cur_min.second = temp.second;}
      if (n_flags & (_BV(4)) && !(k_flags & _BV(GET_H4(k1))))
         temp = calk_knight(GET_H4(k1), k2, k_flags, count + 1,cur_min);
      if (cur_min.first > temp.first){ cur_min.first = temp.first; cur_min.second = temp.second;}
      if (n_flags & (_BV(5)) && !(k_flags & _BV(GET_H5(k1))))
          temp = calk_knight(GET_H5(k1), k2, k_flags, count + 1,cur_min);
      if (cur_min.first > temp.first){ cur_min.first = temp.first; cur_min.second = temp.second;}
      if (n_flags & (_BV(6)) && !(k_flags & _BV(GET_H6(k1))))
          temp = calk_knight(GET_H6(k1), k2, k_flags, count + 1,cur_min);
      if (cur_min.first > temp.first){ cur_min.first = temp.first; cur_min.second = temp.second;}
      if (n_flags & (_BV(7)) && !(k_flags & _BV(GET_H7(k1))))
          temp = calk_knight(GET_H7(k1), k2, k_flags, count + 1,cur_min);
      if (cur_min.first > temp.first){ cur_min.first = temp.first; cur_min.second = temp.second;}

      return cur_min;
}

void MoveCalcul::startCalcul(uint8_t pos1, uint8_t pos2){
    knight_pair ret;
    is_stop = false;
    ret.first =0xFF;
    ret.second |= 0;
    if(!getOneCorrectMove(pos1,c_num)){
        emit finishCalc(ret.second, ret.first);
        return;
    }
    try {
        ret.first = 0xFF;
        uint16_t n_flags=0;
        knight_pair cur_min;
        cur_min.first = 0xFF;
        cur_min.second = 0;
        getCorrectMove(pos1, n_flags);
        switch(c_num){
            case 0 :if(!(n_flags & (_BV(0)))) break;ret =  calk_knight(GET_H0(pos1), pos2, ret.second, 1,cur_min); break;
            case 1 :if(!(n_flags & (_BV(1)))) break;ret =  calk_knight(GET_H1(pos1), pos2, ret.second, 1,cur_min); break;
            case 2 :if(!(n_flags & (_BV(2)))) break;ret =  calk_knight(GET_H2(pos1), pos2, ret.second, 1,cur_min); break;
            case 3 :if(!(n_flags & (_BV(3)))) break;ret =  calk_knight(GET_H3(pos1), pos2, ret.second, 1,cur_min); break;
            case 4 :if(!(n_flags & (_BV(4)))) break;ret =  calk_knight(GET_H4(pos1), pos2, ret.second, 1,cur_min); break;
            case 5 :if(!(n_flags & (_BV(5)))) break;ret =  calk_knight(GET_H5(pos1), pos2, ret.second, 1,cur_min); break;
            case 6 :if(!(n_flags & (_BV(6)))) break;ret =  calk_knight(GET_H6(pos1), pos2, ret.second, 1,cur_min); break;
            case 7 :if(!(n_flags & (_BV(7)))) break;ret =  calk_knight(GET_H7(pos1), pos2, ret.second, 1,cur_min); break;
        }
        emit finishCalc(ret.second, ret.first);
    }
    catch (...){
        emit finishCalc(ret.second, ret.first);
    }
}

void MoveCalcul::stopCalcul(){
    is_stop = true;
}
