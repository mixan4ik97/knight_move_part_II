#include "calculation.h"

Calculation::Calculation()
{

}

void get_hod(int &w,int &h, const uint8_t &I){
    switch(I){
        case 0 : w-=2; h+=1;break;
        case 1 : w-=1; h+=2;break;
        case 2 : w+=1; h+=2;break;
        case 3 : w+=2; h+=1;break;
        case 4 : w-=2; h-=1;break;
        case 5 : w-=1; h-=2;break;
        case 6 : w+=1; h-=2;break;
        case 7 : w+=2; h-=1;break;
    }
}


/*
Функция возвращает переменную с битовыми флагами (n), говорящих о том,какой ход возможен для коня
uint8_t k - номер клетки, в которой находится конь
uint8_t &n - возвращаемое значение битовых флагов, которые определяют номера ходов по порядку от 1 - го до 8-го.

  1   2
0      3
    k
4      7
 5    6
*/
void Calculation::getCorrectMove(const uint8_t & k,  uint16_t &n){
    n=0;
    for(uint8_t i=0;i<8;i++){
        if (getOneCorrectMove(k,i))
            n  |= 1 << i;
    }

}

bool Calculation::getOneCorrectMove(const uint8_t &k,const uint8_t & i){
    int t_w=GET_WIDTH(k);
    int t_h=GET_HEIGHT(k);
    get_hod(t_w,t_h,i);
    return (t_w >=0 && t_w <8 && t_h>=0 && t_h<8);
}
