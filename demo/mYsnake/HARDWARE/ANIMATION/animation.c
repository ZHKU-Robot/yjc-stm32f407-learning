

#include "animation.h"

//最大支持一下绘制65536行
//xru yru 是右上角的xy坐标
//column就是要移动的列像素
void columnPixelsUpdate(u16 column, u16 x1, u16 y1, u16 x2, u16 y2, u16 ms)
{
    //首先获取某点的颜色,范围是
    u16 i, j;
    u16 color; //nextcolor//小优化,判断是否颜色相等,若相等则不draw
    u16 length = x2 - x1;
    u16 end = x1 + column;
    //拿到颜色后需要循环获取
    //从右上角向左数开始

    for (i=x1; i <= x2,x1<=end; i++,x1++,x2++)
    {
        for (j = y1; j <= y2; j++)
        {
            //读取坐标颜色后
            // color = LCD_ReadPoint(i, j);
            // nextcolor = LCD_ReadPoint(i + length + 1, j);
            color = RED;
            //向右画点
            LCD_Fast_DrawPoint(i + 1 + length, j, color);
            LCD_Fast_DrawPoint(i, j, BACK_COLOR);
        }
        delay_ms(ms);
    }

    //去除尾巴
    // for(i=x1;i<x1+column;i++){
    //     for(j=y1;j<y2;j++){

    //     }
    // }
}
void animationMove(u16 x1, u16 y1, u16 x2, u16 y2, short s, float ts,u8 direction)
{

    float tms;  //
    float v;    //移动的速度
    u16 length; //矩形的像素距离

    tms = ts * 1000;     //1000
    length = (x2 - x1);  //
    v = s / tms;         //0.1 p/ms
    if ((u16)v > length) //如果速度快过了自己的长度,那么置为长度
    {
        v = (float)length - 1;
    }

    if (v > 0)
    {
        columnPixelsUpdate(s, x1, y1, x2, y2, (u16)tms / s);
    }

    delay_ms(10);
}
