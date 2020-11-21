

#include "animation.h"

//最大支持一下绘制65536行
//xru yru 是右上角的xy坐标
//column就是要移动的列像素
void verticalPixelsUpdate(short row, u16 x1, u16 y1, u16 x2, u16 y2, u16 ms, u16 backColor)
{
    //首先获取某点的颜色,范围是
    short i, j;
    u16 color; //nextcolor//小优化,判断是否颜色相等,若相等则不draw
    u16 width = y2 - y1;
    if (row >= 0)
    {
        short end = y1 + row;
        if (end > 800)
        {
            end = 800;
        }
        for (i = y1 - 1; i <= y2, y1 <= end; i++, y1++, y2++)
        {
            for (j = x1; j <= x2; j++)
            {
                //读取坐标颜色后
                color = LCD_ReadPoint(j, i);
                // nextcolor = LCD_ReadPoint(i + length + 1, j);
                // color = RED;
                //向右画点
                LCD_Fast_DrawPoint(j, i + 1 + width, color);
                LCD_Fast_DrawPoint(j, i, backColor);
            }
        }
    }
    else
    {
        short end = y2 + row + 1;
        if (end <= 0)
        {
            end = 0;
        }
        for (i = y2; i >= y1, y2 >= end; i--, y1--, y2--)
        {
            for (j = x1; j <= x2; j++)
            {
                //读取坐标颜色后
                color = LCD_ReadPoint(j, i);
                // nextcolor = LCD_ReadPoint(i + length + 1, j);
                // color = RED;
                //向右画点
                LCD_Fast_DrawPoint(j, i - 1 - width, color);
                LCD_Fast_DrawPoint(j, i, backColor);
            }
        }
    }
    delay_ms(ms);
}
void horizontalPixelsUpdate(short column, u16 x1, u16 y1, u16 x2, u16 y2, u16 ms, u16 backColor)
{
    //首先获取某点的颜色,范围是
    short i, j;
    u16 color; //nextcolor//小优化,判断是否颜色相等,若相等则不draw
    u16 length = x2 - x1;
    if (column >= 0)
    {
        short end = x1 + column - 2;
        if (end > 800)
        {
            end = 800;
        }
        // trick
        for (i = x1 - 2; i <= x2, x1 <= end; i++, x1++, x2++)
        {
            for (j = y1; j <= y2; j++)
            {
                //读取坐标颜色后
                color = LCD_ReadPoint(i, j);
                // nextcolor = LCD_ReadPoint(i + length + 1, j);
                // color = RED;
                //向右画点
                LCD_Fast_DrawPoint(i + 1 + length, j, color);
                LCD_Fast_DrawPoint(i, j, backColor);
            }
        }

        delay_ms(ms);
    }
    else
    {
        short end = x2 + column;
        if (end < 0)
        {
            end = 0;
        }
        for (i = x2; i >= x1, x2 >= end; i--, x1--, x2--)
        {
            for (j = y1; j <= y2; j++)
            {
                //读取坐标颜色后
                color = LCD_ReadPoint(i, j);
                // nextcolor = LCD_ReadPoint(i + length + 1, j);
                // color = RED;
                //向右画点
                LCD_Fast_DrawPoint(i - 1 - length, j, color);
                LCD_Fast_DrawPoint(i, j, backColor);
            }
            delay_ms(ms);
        }
    }
}
void animationMove(u16 x1, u16 y1, u16 x2, u16 y2, short s, float ts, u8 direction, u16 backColor)
{

    float tms;       //
    tms = ts * 1000; //1000
    tms = (u16)(s < 0 ? tms / -s : tms / s);
    if (direction == 'x')
    {
        horizontalPixelsUpdate(s, x1, y1, x2, y2, tms, backColor);
    }
    else if (direction == 'y')
    {
        verticalPixelsUpdate(s, x1, y1, x2, y2, tms, backColor);
    }
}
