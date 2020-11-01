#include "game.h"

#define WIDTH 480
#define HEIGHT 800
#define TOPMARGIN 150
#define BOTTOMMARGIN 150
#define XMARGIN 0
#define GRIDWIDTH 120
#define GRIDHEIGHT GRIDWIDTH
#define GRIDXNUM 4
#define GRIDYNUM 4
#define GRIDXINTERVAL 10
#define GRIDYINTERVAL GRIDXINTERVAL
#define BACKGROUND 0X841F
#define SENSITIVITY 30 //灵敏度
#define MOVETIME 0.2
//

u8 rectArr[GRIDYNUM][GRIDXNUM] = {
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {0, 0, 0, 0},
    {2, 0, 0, 0}};
// //
u16 colorTable[] = {WHITE, BLACK, BLUE, BRED, GRED, RED, MAGENTA, GREEN, CYAN, YELLOW, BROWN, GRAY};
//控制产生新方块
u8 newTile = 0;
int t;
u8 click = 0;
short temp;
u8 move = 1;
float pitch, roll, yaw;
short horizontal = 0, vertical = 0;

void moveListen()
{
    if (mpu_dmp_get_data(&pitch, &roll, &yaw) == 0)
    {
        if ((click % SENSITIVITY) == 0)
        {

            temp = pitch * 10;
            if (temp < 0)
            {
                LCD_ShowChar(250 + 48, 70, '-', 16, 0); //显示负号
                temp = -temp;                           //转为正数
            }
            else
                LCD_ShowChar(250 + 48, 70, ' ', 16, 0); //去掉负号

            LCD_ShowNum(250 + 48 + 8, 70, temp / 10, 3, 16); //显示整数部分

            LCD_ShowNum(250 + 48 + 40, 70, temp % 10, 1, 16); //显示小数部分
            temp = roll * 10;
            if (temp < 0)
            {
                LCD_ShowChar(250 + 48, 90, '-', 16, 0); //显示负号
                temp = -temp;                           //转为正数
            }
            else
                LCD_ShowChar(250 + 48, 90, ' ', 16, 0);       //去掉负号
            LCD_ShowNum(250 + 48 + 8, 90, temp / 10, 3, 16);  //显示整数部分
            LCD_ShowNum(250 + 48 + 40, 90, temp % 10, 1, 16); //显示小数部分
            temp = yaw * 10;
            if (temp < 0)
            {
                LCD_ShowChar(250 + 48, 110, '-', 16, 0); //显示负号
                temp = -temp;                            //转为正数
            }
            else
                LCD_ShowChar(250 + 48, 110, ' ', 16, 0);       //去掉负号
            LCD_ShowNum(250 + 48 + 8, 110, temp / 10, 3, 16);  //显示整数部分
            LCD_ShowNum(250 + 48 + 40, 110, temp % 10, 1, 16); //显示小数部分
            click = 0;

            if (pitch > 20)
            {
                move = 1;
                horizontal = 0;
                vertical = 1;
                moveDown();
            }
            else if (pitch < -20)
            {
                move = 1;
                horizontal = 0;
                vertical = -1;
                moveUp();
            }
            else if (roll < -20)
            {
                move = 1;
                horizontal = 1;
                vertical = 0;
                moveRight();
            }
            else if (roll > 20)
            {
                move = 1;
                horizontal = -1;
                vertical = 0;
                moveLeft();
            }
        }
    }
    click++;
}
//以下几个函数是可以合并的，但是懒得改
void moveRight()
{
    int x, y;
    u8 cur, next;
    //从1开始
    for (x = GRIDXNUM - 2; x >= 0; x--)
    {
        //从右逐渐移动
        for (y = 0; y < GRIDYNUM; y++)
        {
            cur = rectArr[y][x];
            next = rectArr[y][x + 1];

            if (cur > 0)
            {
                for (t = x; t <= GRIDXNUM - 2; t++)
                {
                    cur = rectArr[y][t];
                    next = rectArr[y][t + 1];
                    if (next == 0)
                    {

                        rectArr[y][t + 1] = cur;
                        rectArr[y][t] = 0;
                    }
                    else
                    {
                        //否则有数，判断是否相等
                        if (next == cur)
                        {
                            //若相等，则合并
                            //例如 2+2 =4 那么就是2的2次方
                            // 4+4=8 就是2的3次方
                            rectArr[y][t + 1] = cur + 1;
                            rectArr[y][t] = 0;
                            newTile = 1;
                            // break;
                        }
                        else
                        {
                            rectArr[y][t + 1] = next;
                            rectArr[y][t] = cur;
                        }
                    }
                    animationMove(XMARGIN + t * GRIDWIDTH + GRIDXINTERVAL, TOPMARGIN + y * GRIDHEIGHT + GRIDYINTERVAL, (1 + t) * GRIDWIDTH - XMARGIN - GRIDXINTERVAL, TOPMARGIN + (y + 1) * GRIDHEIGHT - GRIDYINTERVAL, horizontal * GRIDWIDTH, MOVETIME, 'x', BACKGROUND);
                }
            }
        }
    }
    if (newTile)
    {
        initRect();
        initRect();
        newTile = 0;
    }
}
void moveDown()
{
    int x, y;
    u8 cur, next;
    //从1开始

    /// 数值运算的时候注意有无符号数据类型，数值运算最好都采用有符号类型数据
    for (y = GRIDYNUM - 2; y >= 0; y--)
    {
        //从z逐渐移动
        for (x = 0; x < GRIDXNUM; x++)
        {
            cur = rectArr[y][x];
            next = rectArr[y + 1][x];

            if (cur > 0)
            {

                for (t = y; t < GRIDYNUM - 1; t++)
                {
                    cur = rectArr[t][x];
                    next = rectArr[t + 1][x];
                    if (next == 0)
                    {
                        rectArr[t + 1][x] = cur;
                        rectArr[t][x] = 0;
                    }
                    else
                    {
                        //否则有数，判断是否相等
                        if (next == cur)
                        {
                            //若相等，则合并
                            //例如 2+2 =4 那么就是2的2次方
                            // 4+4=8 就是2的3次方
                            rectArr[t + 1][x] = cur + 1;
                            rectArr[t][x] = 0;
                            newTile = 1;
                            //  break;
                        }
                        else
                        {
                            rectArr[t + 1][x] = next;
                            rectArr[t][x] = cur;
                        }
                    }
                    animationMove(XMARGIN + x * GRIDWIDTH + GRIDXINTERVAL, TOPMARGIN + t * GRIDHEIGHT + GRIDYINTERVAL, (1 + x) * GRIDWIDTH - XMARGIN - GRIDXINTERVAL, TOPMARGIN + (t + 1) * GRIDHEIGHT - GRIDYINTERVAL, vertical * GRIDWIDTH, MOVETIME, 'y', BACKGROUND);
                }
            }
        }
    }
    if (newTile)
    {
        initRect();
        initRect();
        newTile = 0;
    }
}
void moveUp()
{
    int x, y;
    u8 cur, next;
    //从1开始

    /// 数值运算的时候注意有无符号数据类型，数值运算最好都采用有符号类型数据
    for (y = 1; y < GRIDYNUM; y++)
    {
        //从z逐渐移动
        for (x = 0; x < GRIDXNUM; x++)
        {
            cur = rectArr[y][x];
            next = rectArr[y - 1][x];

            if (cur > 0)
            {
                //如果向z移的位置是空的,那么让他想后移一格
                //一直到底才行
                for (t = y; t > 0; t--)
                {
                    cur = rectArr[t][x];
                    next = rectArr[t - 1][x];
                    if (next == 0)
                    {

                        rectArr[t - 1][x] = cur;
                        rectArr[t][x] = 0;
                    }
                    else
                    {
                        //否则有数，判断是否相等
                        if (next == cur)
                        {
                            //若相等，则合并
                            //例如 2+2 =4 那么就是2的2次方
                            // 4+4=8 就是2的3次方
                            rectArr[t - 1][x] = cur + 1;
                            rectArr[t][x] = 0;
                            newTile = 1;
                            //break;
                        }
                        else
                        {
                            rectArr[t - 1][x] = next;
                            rectArr[t][x] = cur;
                        }
                    }
                    animationMove(XMARGIN + x * GRIDWIDTH + GRIDXINTERVAL, TOPMARGIN + t * GRIDHEIGHT + GRIDYINTERVAL, (1 + x) * GRIDWIDTH - XMARGIN - GRIDXINTERVAL, TOPMARGIN + (t + 1) * GRIDHEIGHT - GRIDYINTERVAL, vertical * GRIDWIDTH, MOVETIME, 'y', BACKGROUND);
                }
            }
        }
    }
    if (newTile)
    {
        initRect();
        initRect();
        newTile = 0;
    }
}
void moveLeft()
{
    int x, y;
    u8 cur, next;
    //从1开始

    /// 数值运算的时候注意有无符号数据类型，数值运算最好都采用有符号类型数据
    for (x = 1; x < GRIDXNUM; x++)
    {
        //从z逐渐移动
        for (y = 0; y < GRIDYNUM; y++)
        {
            cur = rectArr[y][x];
            next = rectArr[y][x - 1];
            if (cur > 0)
            {
                //如果向z移的位置是空的,那么让他想后移一格
                //一直到底才行
                for (t = x; t > 0; t--)
                {
                    cur = rectArr[y][t];
                    next = rectArr[y][t - 1];
                    if (next == 0)
                    {
                        rectArr[y][t - 1] = cur;
                        rectArr[y][t] = 0;
                    }
                    else
                    {
                        //否则有数，判断是否相等
                        if (next == cur)
                        {
                            //若相等，则合并
                            //例如 2+2 =4 那么就是2的2次方
                            // 4+4=8 就是2的3次方
                            rectArr[y][t - 1] = cur + 1;
                            rectArr[y][t] = 0;
                            newTile = 1;
                            //break;
                        }
                        else
                        {
                            rectArr[y][t - 1] = next;
                            rectArr[y][t] = cur;
                        }
                    }
                    animationMove(XMARGIN + t * GRIDWIDTH + GRIDXINTERVAL, TOPMARGIN + y * GRIDHEIGHT + GRIDYINTERVAL, (1 + t) * GRIDWIDTH - XMARGIN - GRIDXINTERVAL, TOPMARGIN + (y + 1) * GRIDHEIGHT - GRIDYINTERVAL, horizontal * GRIDWIDTH, MOVETIME, 'x', BACKGROUND);
                }
            }
        }
    }
    if (newTile)
    {
        initRect();
        initRect();
        newTile = 0;
    }
}
void initRect()
{
    //初始化rect
    u8 x, y;
    x = getRandom();
    y = getRandom();
    // x = 1;
    // y = 1;

    if (rectArr[y][x] != 0)
    {
        initRect();
    }
    else
    {
        rectArr[y][x] = 1;
    }
}

void rectPrint()
{

    u8 rectx, recty;
    for (recty = 0; recty < GRIDYNUM; recty++)
    {
        for (rectx = 0; rectx < GRIDXNUM; rectx++)
        {
            if (rectArr[recty][rectx] > 0)
            {
                // LCD_DrawRectangle(XMARGIN + rectx * GRIDWIDTH, TOPMARGIN + recty * GRIDHEIGHT,  (1 + rectx) * GRIDWIDTH-XMARGIN , TOPMARGIN + (recty + 1) * GRIDHEIGHT);
                LCD_Fill(XMARGIN + rectx * GRIDWIDTH + GRIDXINTERVAL, TOPMARGIN + recty * GRIDHEIGHT + GRIDYINTERVAL, (1 + rectx) * GRIDWIDTH - XMARGIN - GRIDXINTERVAL, TOPMARGIN + (recty + 1) * GRIDHEIGHT - GRIDYINTERVAL, colorTable[rectArr[recty][rectx]]); //colorTable[(u8)RNG_Get_RandomRange(0, 12)]
            }
            else
            {
                LCD_Fill(XMARGIN + rectx * GRIDWIDTH + GRIDXINTERVAL, TOPMARGIN + recty * GRIDHEIGHT + GRIDYINTERVAL, (1 + rectx) * GRIDWIDTH - XMARGIN - GRIDXINTERVAL, TOPMARGIN + (recty + 1) * GRIDHEIGHT - GRIDYINTERVAL, BACKGROUND);
            }
        }
    }
}
u8 getRandom()
{
    return (u8)RNG_Get_RandomRange(0, 3);
}

void initRandom()
{
    while (RNG_Init()) //初始化随机数发生器
    {
        LCD_ShowString(30, 130, 200, 16, 16, "  RNG Error! ");
        delay_ms(200);
        LCD_ShowString(30, 130, 200, 16, 16, "RNG Trying...");
    }
}
