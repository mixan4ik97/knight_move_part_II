#ifndef KNIGHTMOVECALCULATOR_H
#define KNIGHTMOVECALCULATOR_H
#include "calculation.h"
#include "calculestate.h"


class KnightMoveCalculator : public Calculation
{
    Q_OBJECT
public:
    KnightMoveCalculator();
    ~KnightMoveCalculator();
public:
public slots:
   virtual void startCalcul(uint8_t pos1, uint8_t pos2);
   virtual void stopCalcul();
   void finishCalcul(uint64_t flags, unsigned char count);
signals:
    void startAll(uint8_t pos1, uint8_t pos2);
    void finish(QVector<uint8_t> ret);
    void stopAll();
private:
    QVector<uint8_t> getQVectorFromFlags(const uint8_t &flags,const uint8_t &count ,QVector<uint8_t> ret,uint8_t pos1,const uint8_t &pos2, bool flags_this);
    uint8_t cur_pos1;
    uint8_t  cur_pos2;
    std::vector<int> test_stack;
    QMutex m_mutex;
};

#endif // KNIGHTMOVECALCULATOR_H
