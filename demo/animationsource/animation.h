#ifndef _ANIMATION_H
#define _ANIMATION_H
#include<sys.h>
#include<lcd.h>
#include<delay.h>
void verticalPixelsUpdate(short row, u16 x1, u16 y1, u16 x2, u16 y2, u16 ms,u16 backColor);

void horizontalPixelsUpdate(short column, u16 x1, u16 y1, u16 x2, u16 y2, u16 ms,u16 backColor);
void animationMove(u16 x1, u16 y1, u16 x2, u16 y2, short s, float ts,u8 direation,u16 backColor);
#endif

