#include "movecalcul.h"

MoveCalcul::MoveCalcul()
{
    is_stop = false;
    is_warring = false;
}


MoveCalcul::MoveCalcul(uint8_t num){
    c_num  = num;
    is_stop = false;
    is_warring = false;
}

MoveCalcul::MoveCalcul(uint8_t num, bool war){
    is_stop = false;
    c_num = num;
    is_warring = war;
}

MoveCalcul::~MoveCalcul(){
    stopCalcul();
    emit finished();
}



/*
Рекурсивная функция вычисления кротчайшего пути
uint8_t k1 - порядковый номер текущего положения коня
uint8_t k2 - конечное положение коня
uint64_t k_flags - битовые флаги порядковых номеров, в которых конь уже был
uint8_t count - текущий ход конём
*/
knight_pair MoveCalcul::calk_knight(uint8_t k1, const uint8_t &k2, uint64_t k_flags, uint8_t count, knight_pair cur_min) {
    k_flags |= 1 << k1;
    if (k1 == k2){
          return knight_pair(count,k_flags);
    }
      if (count > cur_min.first)
          return knight_pair(count,k_flags);
      if (count >= MAX_MOVES)
          return knight_pair(count,k_flags);
      uint8_t n_flags;
      getCorrectMove(k1, n_flags);
      knight_pair ret;
      ret.first = count;
      ret.second = k_flags;
      if (n_flags & (1 << 1) && !(k_flags & (GET_H1(k1))))
          ret = calk_knight(GET_H1(k1), k2, k_flags, count + 1,cur_min);
      if (cur_min.first > ret.first){ cur_min.first = ret.first; cur_min.second = ret.second;}
      if (n_flags & (1 << 2) && !(k_flags & (GET_H2(k1))))
          ret = calk_knight(GET_H2(k1), k2, k_flags, count + 1,cur_min);
      if (cur_min.first > ret.first){ cur_min.first = ret.first; cur_min.second = ret.second;}
      if (n_flags & (1 << 3) && !(k_flags & (GET_H3(k1))))
          ret = calk_knight(GET_H3(k1), k2, k_flags, count + 1,cur_min);
      if (cur_min.first > ret.first){ cur_min.first = ret.first; cur_min.second = ret.second;}
      if (n_flags & (1 << 4) && !(k_flags & (GET_H4(k1))))
          ret = calk_knight(GET_H4(k1), k2, k_flags, count + 1,cur_min);
      if (cur_min.first > ret.first){ cur_min.first = ret.first; cur_min.second = ret.second;}
      if (n_flags & (1 << 5) && !(k_flags & (GET_H5(k1))))
          ret = calk_knight(GET_H5(k1), k2, k_flags, count + 1,cur_min);
      if (cur_min.first > ret.first){ cur_min.first = ret.first; cur_min.second = ret.second;}
      if (n_flags & (1 << 6) && !(k_flags & (GET_H6(k1))))
          ret = calk_knight(GET_H6(k1), k2, k_flags, count + 1,cur_min);
      if (cur_min.first > ret.first){ cur_min.first = ret.first; cur_min.second = ret.second;}
      if (n_flags & (1 << 7) && !(k_flags & (GET_H7(k1))))
          ret = calk_knight(GET_H7(k1), k2, k_flags, count + 1,cur_min);
      if (cur_min.first > ret.first){ cur_min.first = ret.first; cur_min.second = ret.second;}
      if (n_flags & (1 << 8) && !(k_flags & (GET_H8(k1))))
          ret = calk_knight(GET_H8(k1), k2, k_flags, count + 1,cur_min);
      if (cur_min.first > ret.first){ cur_min.first = ret.first; cur_min.second = ret.second;}

      return cur_min;
}

void MoveCalcul::startCalcul(uint8_t pos1, uint8_t pos2){
    knight_pair ret;
    try {
        is_stop = false;
        is_warring = false;
        ret.second =0;
        ret.second |= 1 << pos2;
        ret.first = 0xFF;
        uint8_t n_flags=0;
        knight_pair cur_min;
        cur_min.first = 0xFF;
        cur_min.second = 0;
        getCorrectMove(pos1, n_flags);
        switch(c_num){
            case 1 :if(!(n_flags & (1 << 1))) break;ret = calk_knight(GET_H1(pos1), pos2, ret.second, 1,cur_min); break;
            case 2 :if(!(n_flags & (1 << 2))) break;ret =  calk_knight(GET_H2(pos1), pos2, ret.second, 1,cur_min); break;
            case 3 :if(!(n_flags & (1 << 3))) break;ret =  calk_knight(GET_H3(pos1), pos2, ret.second, 1,cur_min); break;
            case 4 :if(!(n_flags & (1 << 4))) break;ret =  calk_knight(GET_H4(pos1), pos2, ret.second, 1,cur_min); break;
            case 5 :if(!(n_flags & (1 << 5))) break;ret =  calk_knight(GET_H5(pos1), pos2, ret.second, 1,cur_min); break;
            case 6 :if(!(n_flags & (1 << 6))) break;ret =  calk_knight(GET_H6(pos1), pos2, ret.second, 1,cur_min); break;
            case 7 :if(!(n_flags & (1 << 7))) break;ret =  calk_knight(GET_H7(pos1), pos2, ret.second, 1,cur_min); break;
            case 8 :if(!(n_flags & (1 << 8))) break;ret =  calk_knight(GET_H8(pos1), pos2, ret.second, 1,cur_min); break;
        }
        emit finishCalcul(ret.second, ret.first);
    }
    catch (...) {
        qDebug()<< "Er1"<<c_num ;
        emit finishCalcul(ret.second, ret.first);
    }
}

void MoveCalcul::stopCalcul(){
    QMutexLocker locker (&m_mutex);
    is_stop = true; //Подумай, как вызвать исключение правильно
}
