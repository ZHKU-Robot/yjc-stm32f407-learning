#ifndef _GAME_H
#define _GAME_H
#include "rng.h"
#include "lcd.h"
#include "delay.h"
#include"sys.h"

void initRandom(void); //init所有外设
u8 getRandom(void);//获得随机数
void initRect(void);
void rectPrint(void);
#endif
