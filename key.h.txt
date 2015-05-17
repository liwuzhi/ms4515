#ifndef _KEY_
#define _KEY_
#include <reg52.h>
#include "global_var.h"

#define KEY_FUNC 0x01
#define KEY_SURE 0x02
#define KEY_BACK 0x03
#define KEY_ADD  0x04
#define KEY_SUB  0x05

unsigned char key();
void key_release();
unsigned int key_AddSub(unsigned int number,unsigned char point,unsigned char start_x,unsigned char start_y,unsigned int max);

#endif