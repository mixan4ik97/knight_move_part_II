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
}



/*
Рекурсивная функция вычисления кротчайшего пути
uint8_t k1 - порядковый номер текущего положения коня
uint8_t k2 - конечное положение коня
uint64_t k_flags - битовые флаги порядковых номеров, в которых конь уже был
uint8_t count - текущий ход конём
*/
uint8_t MoveCalcul::calk_knight(uint8_t k1,const uint8_t &k2, uint64_t k_flags, uint8_t &count) {
    count++;
    try{
        if(is_stop)
            throw;
        if (k1 == k2)
            return k_flags;

        if (is_warring && count > MAX_WARRING_MOVES) {
            return k_flags;
        }

        if (count > cur_min)
            return count;
        k_flags |= 1 << k1;
        if (count >= MAX_MOVES)
            return 0;
         uint8_t m_count;
        uint8_t i_min = 0;
        uint8_t n_flags;
        getCorrectMove(k1, n_flags);
        uint8_t hods[8];
        memset(hods, 0, 8);
        if (n_flags & (1 << 1) && ~(k_flags & (GET_H1(k1))))
        hods[0] = calk_knight(GET_H1(k1), k2, k_flags, m_count );
        if (cur_min > m_count){ cur_min = m_count; i_min = 0;}
        if (n_flags & (1 << 2) && ~(k_flags & (GET_H2(k1))))
        hods[1] = calk_knight(GET_H2(k1), k2, k_flags, m_count );
        if (cur_min > m_count){ cur_min = m_count; i_min = 1;}
        if (n_flags & (1 << 3) && ~(k_flags & (GET_H3(k1))))
        hods[2] = calk_knight(GET_H3(k1), k2, k_flags, m_count );
        if (cur_min > m_count){ cur_min = m_count; i_min = 2;}
        if (n_flags & (1 << 4) && ~(k_flags & (GET_H4(k1))))
        hods[3] = calk_knight(GET_H4(k1), k2, k_flags, m_count );
        if (cur_min > m_count){ cur_min = m_count; i_min = 3;}
        if (n_flags & (1 << 5) && ~(k_flags & (GET_H5(k1))))
        hods[4] = calk_knight(GET_H5(k1), k2, k_flags, m_count);
        if (cur_min > m_count){ cur_min = m_count; i_min = 3;}
        if (n_flags & (1 << 6) && ~(k_flags & (GET_H6(k1))))
        hods[5] = calk_knight(GET_H6(k1), k2, k_flags, m_count );
        if (cur_min > m_count){ cur_min = m_count; i_min = 5;}
        if (n_flags & (1 << 7) && ~(k_flags & (GET_H7(k1))))
        hods[6] = calk_knight(GET_H7(k1), k2, k_flags, m_count );
        if (cur_min > m_count){ cur_min = m_count; i_min = 6;}
        if (n_flags & (1 << 8) && ~(k_flags & (GET_H8(k1))))
        hods[7] = calk_knight(GET_H8(k1), k2, k_flags, m_count );
        if (cur_min > m_count){ cur_min = m_count; i_min = 7;}
        return hods[i_min];
    }
    catch(...){
        qDebug()<< "Er2"<<c_num ;
        return k_flags;
    }

}

void MoveCalcul::startCalcul(uint8_t pos1, uint8_t pos2){
    uint8_t count = 0,k_flags = 0;
    try {
        is_stop = false;
        is_warring = false;
        k_flags |= 1 << pos2;
        cur_min = 0xFF;
        uint8_t n_flags=0;
        getCorrectMove(pos1, n_flags);
        switch(c_num){
            case 1 :if(!(n_flags & (1 << 1))) throw; calk_knight(GET_H1(pos1), pos2, k_flags, count); break;
            case 2 :if(!(n_flags & (1 << 2))) throw; calk_knight(GET_H2(pos1), pos2, k_flags, count); break;
            case 3 :if(!(n_flags & (1 << 3))) throw; calk_knight(GET_H3(pos1), pos2, k_flags, count); break;
            case 4 :if(!(n_flags & (1 << 4))) throw; calk_knight(GET_H4(pos1), pos2, k_flags, count); break;
            case 5 :if(!(n_flags & (1 << 5))) throw; calk_knight(GET_H5(pos1), pos2, k_flags, count); break;
            case 6 :if(!(n_flags & (1 << 6))) throw; calk_knight(GET_H6(pos1), pos2, k_flags, count); break;
            case 7 :if(!(n_flags & (1 << 7))) throw; calk_knight(GET_H7(pos1), pos2, k_flags, count); break;
            case 8 :if(!(n_flags & (1 << 8))) throw; calk_knight(GET_H8(pos1), pos2, k_flags, count); break;
        }
        emit finishCalcul(k_flags, count);
    }
    catch (...) {
        qDebug()<< "Er1"<<c_num ;
        emit finishCalcul(k_flags, count);
    }
}

void MoveCalcul::stopCalcul(){
    QMutexLocker locker (&m_mutex);
    is_stop = true; //Подумай, как вызвать исключение правильно
}