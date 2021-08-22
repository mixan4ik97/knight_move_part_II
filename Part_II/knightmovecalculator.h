#ifndef KNIGHTMOVECALCULATOR_H
#define KNIGHTMOVECALCULATOR_H
#include "calculation.h"
#include "calculestate.h"

//Класс, предназначенный для реализации вычисления кротчайшего пути коня и
//Реализующий связь с GUI и функциями вычисления
class KnightMoveCalculator : public Calculation
{
    Q_OBJECT
public:
    KnightMoveCalculator();
    ~KnightMoveCalculator();
public:
public slots:
   virtual void startCalcul(const uint8_t &pos1, const uint8_t & pos2); // Функция, завучкающая процесс вычисления
    virtual void stopCalcul();// Функция, принудительно завершающая процесс вычисления
   void finishCalcul(uint64_t flags, unsigned char count); // Слот, принимащий в себя результат вычисления
signals:
    void startAll( uint8_t  pos1,  uint8_t pos2); // Сигнал, запускающий вычисление
    void calculOut(QByteArray out); //Сигнал, отправляющий результат вычисления в класс главного окна
    void stopAll(); // Сигнал принудительного завершения вычислений
private:
    /*
        В данной реализации, вычисления происходят в 8 потокв, результаты вычислений которых (рещзультат вычисленного пути) возвращается в виде номеро клеток (битовых флагов)
        без соответствующих номеров. Данная функция предназнгачена для нумерации клеток или по просту говоря, перевода битовых флагов в упорядоченный вектор значений
        Это сделано для того, чтобы в с стаках не хранить контейнеры, чем облегчается работа программы.
    */
    QByteArray getQVectorFromFlags(const uint64_t &flags,const uint8_t &count ,QByteArray ret,uint8_t pos1,const uint8_t &pos2, uint64_t flags_this);
};

#endif // KNIGHTMOVECALCULATOR_H
