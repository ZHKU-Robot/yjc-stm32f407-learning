#include "snake.h"

//画笔颜色
#define HEIGHT 800
#define WIDTH 480
#define GRIDX 12
#define GRIDY 20

#define GRIDWIDTH WIDTH / GRIDX
#define GRIDHEIGHT HEIGHT / GRIDY

//
//全局
u16 colorTable[] = {WHITE, BLACK, BLUE, BRED, GRED, RED, MAGENTA, GREEN, CYAN, YELLOW, BROWN, GRAY};
u16 init_X = 0, init_Y = 0;

// u8 radius = GRIDWIDTH / 2;
int horizontal = 1, vertical = 0;
u8 title[] = "RAINBOW SNAKE";
u8 titleLeng=sizeof(title)/sizeof(u8);

u8 fontSize=24;
u16 score=0;

snakeNode *food, *head;
void showTitle()
{
    // POINT_COLOR=colorTable[rand()%12];
    LCD_ShowString(0,0,fontSize*titleLeng,fontSize,fontSize,title);
    LCD_ShowString(0,GRIDHEIGHT,fontSize*6,fontSize,fontSize,"SCORE:");
    LCD_ShowxNum(fontSize*4,GRIDHEIGHT,score,5,fontSize,0);
}

void snakeTurn()
{

    switch (KEY_Scan(0))
    {
    case 1: //UP
        vertical = 0;
        horizontal = 1;
        break;
    case 2:
        vertical = 1;
        horizontal = 0;
        break;
    case 3:
        horizontal = -1;
        vertical = 0;
        break;
    case 4:
        horizontal = 0;
        vertical = -1;
    default:

        break;	
    }
}
void foodPrint()
{
    LCD_DrawRectangle(food->x * GRIDWIDTH, food->y * GRIDHEIGHT, (food->x + 1) * GRIDWIDTH, (food->y + 1) * GRIDWIDTH);
    LCD_Fill(food->x * GRIDWIDTH, food->y * GRIDHEIGHT, (food->x + 1) * GRIDWIDTH, (food->y + 1) * GRIDWIDTH, GREEN);
}
void createFood()
{
    snakeNode *food_1, *temp;

    // srand(food.);

    food_1 = (snakeNode *)malloc(sizeof(snakeNode));
    food_1->x = rand() % (GRIDX + 1);
    food_1->y = rand() % (GRIDY + 1);

    //printf("foodx,y=%d,%d\n", food_1->x, food_1->y);

    temp = head;
    while (temp->nextBody == NULL)
    {
        if ((temp->x == food_1->x && temp->y == food_1->y)) //判断蛇身是否与食物重合
        {
            free(food_1);
            createFood();
        }
        temp = temp->nextBody;
    }
    food = food_1;
}
void snakeErase(snakeNode *tempHead)
{
    LCD_Fill(tempHead->x * GRIDWIDTH, tempHead->y * GRIDHEIGHT, GRIDWIDTH * (tempHead->x + 1), (tempHead->y + 1) * GRIDHEIGHT, BACK_COLOR);
}
void snakeMove(snakeNode *temphead)
{
    snakeNode *nexthead, *temp;
    nexthead = (snakeNode *)malloc(sizeof(snakeNode));
    nexthead->x = head->x + horizontal;
    nexthead->y = head->y + vertical;
    //printf(" width= %d  height=%d \n", lcddev.width, lcddev.height);
    printf("nexthead.x==%d nexthead.y ==%d \n", nexthead->x, nexthead->y);
    if (nexthead->x == GRIDX)
    {
        nexthead->x = 0;
    }
    if (nexthead->y == GRIDY)
    {
        nexthead->y = 0;
    }
    if (nexthead->x <= -1)
    {
        nexthead->x = GRIDX - 1;
    }
    if (nexthead->y <= -1)
    {
        nexthead->y = GRIDY - 1;
    }
    if (nexthead->x == food->x && nexthead->y == food->y) //如果下一个有食物//
    {
        nexthead->nextBody = head;
        head = nexthead;
        temp = head;
        while (temp != NULL)
        {
            temp = temp->nextBody;
        }
        score+=10;
        createFood();
    }
    else //如果没有食物//
    {

        nexthead->nextBody = head;
        head = nexthead;
        temp = head;

        while (temp->nextBody->nextBody != NULL)
        {
            snakePrint(temp);

            temp = temp->nextBody;
        }
        snakeErase(temp->nextBody);
        free(temp->nextBody);

        temp->nextBody = NULL;
    }
}
snakeNode *initSnake(void)
{

    snakeNode *tempHead, *temp;
    int i;
    tempHead = (snakeNode *)malloc(sizeof(snakeNode)); //从蛇尾开始，tou插法，以x,y设定开始的位置//

    if (tempHead == NULL)
    {
        //printf("failed to malloc!");
    }
    tempHead->x = init_X;
    tempHead->y = init_Y;
    tempHead->nextBody = NULL;
    for (i = 1; i <= 4; i++)
    {
        temp = (snakeNode *)malloc(sizeof(snakeNode));
        temp->nextBody = tempHead;
        temp->x = init_X + i;
        temp->y = init_Y;
        tempHead = temp;
    }
    while (tempHead != NULL) //从头到为，输出蛇身
    {
        snakePrint(tempHead);
        tempHead = tempHead->nextBody;
    }
    head = temp;
    return temp;
    ;
}
void snakePrint(snakeNode *tempHead)
{

    LCD_Fill(tempHead->x * GRIDWIDTH, tempHead->y * GRIDHEIGHT, GRIDWIDTH * (tempHead->x + 1), (tempHead->y + 1) * GRIDHEIGHT, colorTable[rand() % 12]);
}
