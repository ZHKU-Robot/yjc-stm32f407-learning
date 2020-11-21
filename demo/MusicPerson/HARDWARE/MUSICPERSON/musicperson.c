#include "musicperson.h"
//
#define LCDWIDTH 480
#define LCDHEIGHT 800
#define GROUNDCOLOR 0X0000

u8 personRun = 1;  //人是否在跑
u16 positionIndex; //绝对位置
// u8 horizontal = 1;
u8 pixelStep = 5; //步长
u8 runJump = 1;   //从走路到run的跳变或者run到走路的跳变
//初始化火柴人
Person *personInit()
{
    return (Person *)malloc(sizeof(Person));
}
void drawGround(Person *p)
{

    LCD_Fill(p->x2, p->y2, LCDWIDTH, LCDHEIGHT, GROUNDCOLOR);
}
void keyListen()
{

    switch (KEY_Scan(1))
    {
    case 1:
        //检测跳变  这里从走路变成了run
        if (personRun == 0)
        {
            runJump = 1;
        }

        personRun = 1;
        break;
    // case 3:
    //     personRun = 1;
    //     horizontal = -1;

    //     break;
    default:
        //从 1跳到0 产生跳变
        if (personRun == 1)
        {
            runJump = 1;
        }
        personRun = 0;
        break;
    }
}
void personMove(Person *p)
{
    if (personRun == 1)
    {
        // LCD_Fill(p->x1, p->y1, p->x2, p->y2, BACK_COLOR);
        if (p->x1 < LCDWIDTH / 3)
        {
            animationMove(p->x1, p->y1, p->x2, p->y2, pixelStep, 1., 'x', BACK_COLOR);
            LCD_Fill(p->x1, p->y2, p->x2, LCDHEIGHT, GREEN);
            p->x1 += pixelStep;
            p->x2 += pixelStep;
        }
        positionIndex += pixelStep;
    }
    // else if (horizontal == -1)
    // {
    //     // LCD_Fill(p->x1, p->y1, p->x2, p->y2, BACK_COLOR);
    //     //    delay_ms(50);
    //     if (p->x1 > 0)
    //     {
    //         animationMove(p->x1, p->y1, p->x2, p->y2, -pixelStep, 1., 'x', BACK_COLOR);
    //         p->x1 -= pixelStep;
    //         p->x2 -= pixelStep;
    //     }
    // }
}

//绘画火柴人
void drawPerson(Person *p)
{
    //由一个圆和若干直线组成
    // 1/3作为头部 2/3作为躯体
    //宽度则是1/2
    u16 x1 = p->x1;
    u16 y1 = p->y1;
    u16 x2 = p->x2;
    u16 y2 = p->y2;

    short PERSONRECTWIDTH = x2 - x1;
    short PERSONRECTHEIGHT = y2 - y1; //矩形人高度
    //
    short headHeight = PERSONRECTHEIGHT / 3;
    short bodyHeight = PERSONRECTHEIGHT - headHeight;
    short headWidth = PERSONRECTWIDTH / 2;
    short bodyWidth = PERSONRECTWIDTH / 2;
    short headSize = PERSONRECTWIDTH / 4;
    short headPointX = x1 + headWidth;
    short headPointY = y1 + headHeight / 2;
    short neckPointX = x1 + headWidth;
    short neckPointY = y1 + headHeight;
    short jjPointX = x1 + headWidth;
    short jjPointY = y1 + bodyHeight;
    POINT_COLOR = BLACK;
    if (personRun || runJump)
    {
        LCD_Fill(x1, y1, x2, y2, BACK_COLOR);
        runJump = 0; //取消跳变
    }
    //LCD_DrawRectangle(x1, y1, x2, y2);
    LCD_Draw_Circle(headPointX, headPointY, headSize, POINT_COLOR);
    //开始画身体
    //头的中心是x1+headWidth,y1+headHeight
    //往下一点画条线
    //脖子到jj
    LCD_DrawLine(neckPointX, neckPointY, jjPointX, jjPointY);
    //左手
    LCD_DrawLine(neckPointX, neckPointY, neckPointX - bodyWidth / 2, jjPointY);
    //右手
    LCD_DrawLine(neckPointX, neckPointY, neckPointX + bodyWidth / 2, jjPointY);

    if (personRun == 0)
    {
        //开始绘画,先画头
        //左脚
        LCD_DrawLine(jjPointX, jjPointY, jjPointX - bodyWidth / 3, y1 + PERSONRECTHEIGHT);
        // 右脚
        LCD_DrawLine(jjPointX, jjPointY, jjPointX + bodyWidth / 3, y1 + PERSONRECTHEIGHT);
    }
    else if (personRun == 1)
    {
        LCD_Draw_Circle(jjPointX, jjPointY + bodyHeight / 4, (u8)(bodyHeight / 4), POINT_COLOR);
    }
}
