#include "game.h"

#define WIDTH 800
#define HEIGHT 480
#define TOPMARGIN 150
#define BOTTOMMARGIN 150
#define XMARGIN 0
#define GRIDWIDTH 50
#define GRIDHEIGHT 50
#define GRIDXNUM 4
#define GRIDYNUM 4
//

u8 rectArr[HEIGHT][WIDTH] = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}};
//
u8 rectx = 0, recty = 0;
u8 i=0,j=0;
void initRect()
{
    //初始化rect
    u8 x,y;
    // x=getRandom();
    // y=getRandom();
    x=1;y=1;
    if (rectArr[y][x] != 0)
    {
        initRect();
    }
}
void rectPrint()
{

    // for (i=0; recty < GRIDYNUM; recty++)
    // {
    //     for (j=0; rectx < GRIDXNUM; rectx++)
    //     {
    //         // if (rectArr[recty][rectx] == 1)
    //         {
    //             // LCD_DrawRectangle(XMARGIN + rectx * GRIDWIDTH, TOPMARGIN + recty * GRIDHEIGHT,  (1 + rectx) * GRIDWIDTH-XMARGIN , TOPMARGIN + (recty + 1) * GRIDHEIGHT);
    //         }
    //     }
    // }
    // rectx=0;
    // recty=0;
}
// u8 getRandom()
// {
//     return (u8)RNG_Get_RandomRange(0, 3);
// }

void initRandom()
{
    while (RNG_Init()) //初始化随机数发生器
    {
        LCD_ShowString(30, 130, 200, 16, 16, "  RNG Error! ");
        delay_ms(200);
        LCD_ShowString(30, 130, 200, 16, 16, "RNG Trying...");
    }
}
