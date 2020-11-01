#ifndef _GAME_H
#define _GAME_H
#include "rng.h"
#include "lcd.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "key.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include"animation.h"
void initRandom(void); //init所有外设
u8 getRandom(void);    //获得随机数
void initRect(void);
void rectPrint(void);
void moveRight(void);
void moveListen(void);
void moveLeft(void);
void moveUp(void);
void     moveDown(void);
#endif
