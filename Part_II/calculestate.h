#ifndef CALCULESTATE_H
#define CALCULESTATE_H

#include <QObject>
#include <QMutex>
#include <QDebug>

//Классический класс, предназначенный для объявления глобальных, статических потомков
template <class T>
class Single
{
  public:
    inline static T& inst()
    {
      static T state;
      return state;
    }
};

//Класс - контейнер, хранящий в себе глобальные переменные и состояния вычислений
class CalculeState  : public Single<CalculeState>
{
public:
    CalculeState(){resetState();}
    ~CalculeState(){}

    void setCountCalcul(const uint8_t &temp){countCalcul = temp;} // Функция устанавливает значение текущего количества потоков, закончивших вычисления
    void setCountMin(const uint8_t &temp){ count_min = temp;} // Функция устанавливает значение текущего текущего минимального количества ходов
    void setFlagsMin(const uint64_t &temp){ flags_min = temp;} // Функция устанавливает значение текущих флагов пути для минимального количества ходов
    void setCurPos1(const uint8_t &temp){ cur_pos1 = temp;} // Устанавливает текущее глобальное положение коня
    void setCurPos2(const uint8_t &temp){ cur_pos2 = temp;} // Устанавливает текущую глобальную конечную точку
    void setOutput(const  QByteArray &temp){QMutexLocker ml(&mutex); output = temp;} //Устанавливает текущее решение

    void incrCalcul(){countCalcul++;} // Глобальный инкремент для количества потоков, закончевших вычисления

    uint8_t getCountCalcul(){return countCalcul.load();} // Возвращает значение текущего количества потоков, закончивших вычисления
    uint8_t getCountMin(){return count_min.load();} // Возвращает значение текущего текущего минимального количества ходов
    uint64_t getFlagsMin(){ return flags_min.load();} // Возвращает значение текущих флагов пути для минимального количества ходов
    uint8_t getCurPos1(){ return cur_pos1.load();} // Возвращает текущее глобальное положение коня
    uint8_t getCurPos2(){ return cur_pos2.load();}// Возвращает текущую глобальную конечную точку
    QByteArray getOutput(){QMutexLocker ml(&mutex); return output;} //Возвращает текущее решение
    int getCurHod(uint8_t hod){QMutexLocker ml(&mutex); if(hod < output.size()) return output[hod]; else return -1;} // Функция возврает положение коня при текущем ходе

    void resetState(){QMutexLocker ml(&mutex); countCalcul =0;count_min=0xFF;flags_min=0;cur_pos1=0;cur_pos2=0;output.clear();} // Функция очищает все переменные


private:
    std::atomic<uint8_t> countCalcul; //Текущее количество потоков, закончевших вычисления
    std::atomic<uint8_t> count_min;// Текеущий вычисленный минимум
    std::atomic<uint64_t> flags_min; // Текущие флаги пути для вычисления минимума
    std::atomic<uint8_t>  cur_pos1; // Глобальное положение коня
    std::atomic<uint8_t>  cur_pos2; // Глобальное положение конечной точки
    QByteArray output; // Контейнер, хранящий в себе путь
    QMutex mutex; // Мьютекс, предназначенный для блокировки функции для остальных потоков
};

#endif // CALCULESTATE_H
