#ifndef CALCULESTATE_H
#define CALCULESTATE_H

#include <QObject>
#include <QMutex>

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
    CalculeState(){resetState();}
    ~CalculeState(){mutex.unlock();}
    void setCountCalcul(const uint8_t &temp){countCalcul = temp;}
    void setCountMin(const uint8_t &temp){ count_min = temp;}
    void setFlagsMin(const uint64_t &temp){ flags_min = temp;}
    void setCurPos1(const uint8_t &temp){ cur_pos1 = temp;}
    void setCurPos2(const uint8_t &temp){ cur_pos2 = temp;}
    void setOutput(const  QByteArray &temp){QMutexLocker ml(&mutex); output = temp;}

    void incrCalcul(){countCalcul++;}

    uint8_t getCountCalcul(){return countCalcul.load();}
    uint8_t getCountMin(){return count_min.load();}
    uint64_t getFlagsMin(){ return flags_min.load();}
    uint8_t getCurPos1(){ return cur_pos1.load();}
    uint8_t getCurPos2(){ return cur_pos2.load();}
    QByteArray getOutput(){QMutexLocker ml(&mutex); return output;}
    int getCurHod(uint8_t hod){QMutexLocker ml(&mutex); if(hod < output.size()) return output[hod]; else return -1;}

    void resetState(){countCalcul =0;count_min=0xFF;flags_min=0;cur_pos1=0;cur_pos2=0;output.clear();}


private:
    std::atomic<uint8_t> countCalcul;
    std::atomic<uint8_t> count_min;
    std::atomic<uint64_t> flags_min;
    std::atomic<uint8_t>  cur_pos1;
    std::atomic<uint8_t>  cur_pos2;
    QByteArray output;
    QMutex mutex;
};

#endif // CALCULESTATE_H
