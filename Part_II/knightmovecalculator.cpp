#include "knightmovecalculator.h"

//Главный конструктор
KnightMoveCalculator::KnightMoveCalculator()
{
    CalculeState::inst().resetState();
}

//Деструктор
KnightMoveCalculator::~KnightMoveCalculator()
{
    emit stopAll();
}

// Функция, завучкающая процесс вычисления
//const uint8_t & pos1 - номер позиции коня
//const uint8_t & pos2 - конечное положение коня
void KnightMoveCalculator::startCalcul(const uint8_t & pos1, const uint8_t & pos2){
    CalculeState::inst().resetState();
    CalculeState::inst().setCurPos1( pos1);
    CalculeState::inst().setCurPos2( pos2);

    emit startAll(pos1,pos2);
}

// Функция, принудительно завершающая процесс вычисления
void KnightMoveCalculator::stopCalcul(){
    emit stopAll();
}

/*
    В данной реализации, вычисления происходят в 8 потокв, результаты вычислений которых (рещзультат вычисленного пути) возвращается в виде номеро клеток (битовых флагов)
    без соответствующих номеров. Данная функция предназнгачена для нумерации клеток или по просту говоря, перевода битовых флагов в упорядоченный вектор значений
    Это сделано для того, чтобы в с стаках не хранить контейнеры, чем облегчается работа программы.
const uint64_t &flags - Найденные флаги, которые показывают, какой путь был проделан конём
const uint8_t &count  - количество ходов, которые совершены конём до конечного положения
QByteArray ret - переменная для рекурсивного стека, в которой хранится текущие проделанные ходы
uint8_t pos1 - изначальное положение коня
const uint8_t &pos2 - конечное положение коня
 uint64_t flags_this - флаги , отмечающие в каком месте побывал конь для данного стека
*/
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
      uint16_t n_flags;
      getCorrectMove(pos1, n_flags);
      if ( !(flags_this & (_BV(GET_H0(pos1)))) && ((flags & (_BV( GET_H0(pos1))))) && n_flags & (_BV(0)) ){
          ret_t = getQVectorFromFlags(flags, count, ret, GET_H0(pos1),pos2,flags_this );
          if (ret_t.size() == count){ return ret_t;}
      }

      if ( !(flags_this & (_BV(GET_H1(pos1)))) && ((flags & (_BV(GET_H1(pos1))))) && n_flags & (_BV(1)) ){
          ret_t = getQVectorFromFlags(flags, count, ret, GET_H1(pos1),pos2,flags_this );
          if (ret_t.size() == count){ return ret_t;}
      }

      if ( !(flags_this & (_BV(GET_H2(pos1)))) && ((flags & (_BV(GET_H2(pos1))))) && n_flags & (_BV(2)) ){
          ret_t = getQVectorFromFlags(flags, count, ret, GET_H2(pos1),pos2,flags_this );
          if (ret_t.size() == count){ return ret_t;}
      }

      if ( !(flags_this & (_BV(GET_H3(pos1)))) && ((flags & (_BV(GET_H3(pos1))))) && n_flags & (_BV(3)) ){
          ret_t = getQVectorFromFlags(flags, count, ret, GET_H3(pos1),pos2,flags_this );
          if (ret_t.size() == count){ return ret_t;}
      }

      if ( !(flags_this & (_BV(GET_H4(pos1)))) && ((flags & (_BV(GET_H4(pos1))))) && n_flags & (_BV(4)) ){
          ret_t = getQVectorFromFlags(flags, count, ret, GET_H4(pos1),pos2,flags_this );
          if (ret_t.size() == count){ return ret_t;}
      }

      if ( !(flags_this & (_BV(GET_H5(pos1)))) && ((flags & (_BV(GET_H5(pos1))))) && n_flags & (_BV(5)) ){
          ret_t = getQVectorFromFlags(flags, count, ret, GET_H5(pos1),pos2,flags_this );
          if (ret_t.size() == count){ return ret_t;}
      }

      if ( !(flags_this & (_BV(GET_H6(pos1)))) && ((flags & (_BV(GET_H6(pos1))))) && n_flags & (_BV(6)) ){
          ret_t = getQVectorFromFlags(flags, count, ret, GET_H6(pos1),pos2,flags_this );
          if (ret_t.size() == count){ return ret_t;}
      }

      if ( !(flags_this & (_BV(GET_H7(pos1)))) && ((flags & (_BV(GET_H7(pos1))))) && n_flags & (_BV(7)) ){
          ret_t = getQVectorFromFlags(flags, count, ret, GET_H7(pos1),pos2,flags_this );
          if (ret_t.size() == count){ return ret_t;}
      }

    return QByteArray();
}

// Слот, принимащий в себя результат вычисления
//uint64_t flags - вычисленные флаги со значениями, в каких местах побывал конь до конечной точки
//unsigned char count - количество ходов от начальной до конечной точки
void KnightMoveCalculator::finishCalcul(uint64_t flags, unsigned char count){
    if(count < CalculeState::inst().getCountMin() && count <= MAX_MOVES && count > 0 && flags != 0){
        CalculeState::inst().setCountMin( count);
        CalculeState::inst().setFlagsMin( flags);
    }
    uint8_t countCalcul = CalculeState::inst().getCountCalcul();
    CalculeState::inst().incrCalcul();
    countCalcul++;
    if(countCalcul == 8){
        if(CalculeState::inst().getCountMin() > MAX_MOVES || CalculeState::inst().getCountMin() ==0 || CalculeState::inst().getFlagsMin() == 0){
            emit calculOut(QByteArray());
            CalculeState::inst().resetState();
            return;
        }
         uint64_t k_flags = 0;
        k_flags |= 1 << CalculeState::inst().getCurPos2();
        QByteArray t;
        uint64_t flags_min = CalculeState::inst().getFlagsMin();
        uint8_t count_min = CalculeState::inst().getCountMin()+1;
        uint8_t p1 = CalculeState::inst().getCurPos1();
        uint8_t p2 = CalculeState::inst().getCurPos2();
        CalculeState::inst().resetState();
        emit calculOut(getQVectorFromFlags(flags_min, count_min,t,p1,p2,0));
    }
}
