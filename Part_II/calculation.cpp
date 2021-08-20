#include "calculation.h"

Calculation::Calculation()
{

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
void Calculation::getCorrectMove(const uint8_t & k,  uint8_t &n){
    uint8_t k_w = GET_WIDTH(k);
    uint8_t k_h = GET_HEIGHT(k);
    n = 0;
    if (k_w > 2 && k_h < 8)
        n |= 1 << 0;
    if (k_w > 1 && k_h < 7)
        n |= 1 << 1;
    if (k_w < 8 && k_h < 7)
        n |= 1 << 2;
    if (k_w < 7 && k_h < 8)
        n |= 1 << 3;
    if (k_w > 2 && k_h >1)
        n |= 1 << 4;
    if (k_w > 1 && k_h >2)
        n |= 1 << 5;
    if (k_w < 8 && k_h >2)
        n |= 1 << 6;
    if (k_w < 7 && k_h < 1)
        n |= 1 << 7;
}
