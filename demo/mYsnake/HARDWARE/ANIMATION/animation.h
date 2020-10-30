#ifndef _ANIMATION_H
#define _ANIMATION_H
#include<sys.h>
#include<lcd.h>
#include<delay.h>
#include"usart.h"
void columnPixelsUpdate(u16 column,u16 x1, u16 y1, u16 x2, u16 y2, u16 ms);
void animationMove(u16 x1, u16 y1, u16 x2, u16 y2, short s, float ts, u8 direction);
void verticalPixelsUpdate(short row, u16 x1, u16 y1, u16 x2, u16 y2, u16 ms);
#endif

