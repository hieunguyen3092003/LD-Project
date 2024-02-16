#include "button.h"

int key_reg0 = NORMAL_STATE;
int key_reg1 = NORMAL_STATE;
int key_reg2 = NORMAL_STATE;
int key_reg3 = NORMAL_STATE;

int key_flag1 = 0;

int timer_for_key_pressed = 200;

int isButton1Pressed()
{
    if (key_flag1 == 1)
    {
        key_flag1 = 0;
        return 1;
    }
    else
        return 0;
}

void getKeyInput()
{
    key_reg0 = key_reg1;
    key_reg1 = key_reg2;
    key_reg2 = gpio_get_level(GPIO_NUM_16);

    if ((key_reg0 == key_reg1) && (key_reg1 == key_reg2))
    {
        if (key_reg3 != key_reg2)
        {
            key_reg3 = key_reg2;

            if (key_reg2 == PRESSED_STATE)
            {
                key_flag1 = 1;
                timer_for_key_pressed = 200;
            }
        }
        else
        {
            --timer_for_key_pressed;
            if (timer_for_key_pressed == 0)
            {
                key_reg3 = NORMAL_STATE;
            }
        }
    }
}