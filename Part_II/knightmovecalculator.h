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
    void calculOut(QByteArray out);
    void stopAll();
private:
    QByteArray getQVectorFromFlags(const uint64_t &flags,const uint8_t &count ,QByteArray ret,uint8_t pos1,const uint8_t &pos2, uint64_t flags_this);
    QMutex m_mutex;
};

#endif // KNIGHTMOVECALCULATOR_H
