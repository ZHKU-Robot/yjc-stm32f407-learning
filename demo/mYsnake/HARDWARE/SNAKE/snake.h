#ifndef __SNAKE_H
#define __SNAKE_H
#include "sys.h"
#include "key.h"
//LED端口定义
#define LED0 PFout(9)	// DS0
#define LED1 PFout(10)	// DS1	 

//蛇结构体
typedef struct snakeStruct
{
    int x,y;
    struct snakeStruct *nextBody;
}snakeNode;

  
//蛇函数
snakeNode *initSnake(void);
void snakePrint(snakeNode *tempHead);
void snakeMove(snakeNode *head);
void createFood(void);
void foodPrint(void);
void snakeTurn(void);
void snakeErase(snakeNode *tempHead);

void showTitle(void);

#endif
