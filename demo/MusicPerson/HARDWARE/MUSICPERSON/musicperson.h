#ifndef _MUSICPERSON_H
#define _MUSICPERSON_H
#include"animation.h"
#include"sys.h"
#include"lcd.h"
#include"key.h"

typedef struct PersonStruct
{
    /* data */
    u16 x1,y1,x2,y2;
}Person;
Person * personInit(void);
void drawPerson(Person *p);
void keyListen(void);
void personMove(Person *p);
void drawGround(Person *p);
#endif

