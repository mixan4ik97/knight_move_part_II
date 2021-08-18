#ifndef CALCULESTATE_H
#define CALCULESTATE_H

#include <QObject>


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

class CalculeState  : public Single<CalculeState>
{
public:
    CalculeState() : countCalcul(0),count_min(0xFF), flags_min(0){};
    void setCountCalcul(const uint8_t &temp){countCalcul = temp;}
    void setCountMin(const uint8_t &temp){ count_min = temp;}
    void setFlagsMin(const uint64_t &temp){ flags_min = temp;}

    void incrCalcul(){countCalcul++;}

    uint8_t getCountCalcul(){return countCalcul.load();}
    uint8_t getCountMin(){return count_min.load();}
    uint64_t getFlagsMin(){ return flags_min.load();}

    void resetState(){countCalcul =0;count_min=0xFF;flags_min=0;};

private:
    std::atomic<uint8_t> countCalcul;
    std::atomic<uint8_t> count_min;
    std::atomic<uint64_t> flags_min;
};

#endif // CALCULESTATE_H
