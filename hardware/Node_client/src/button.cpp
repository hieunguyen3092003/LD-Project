#include "global.h"
#include "button.h"

#ifdef BUTTON

#define DEBOUNCE 300
#define PRESSED 3000

void initButton(void);
bool isButtonDown(void);

// global variables
bool is_button_down = false;

// Handle debounce and long pressed
unsigned long last_pushed_time = 0;
bool last_button_state = HIGH;

void initButton()
{
    pinMode(BUTTON_PIN, INPUT_PULLUP);
}

bool isButtonDown()
{
    bool button_state = digitalRead(BUTTON_PIN);

    if (current_time - last_pushed_time >= DEBOUNCE) // process button every DEBOUNCE milliseconds
    {
        if (button_state == LOW) // Pushed
        {
            if (last_button_state == HIGH || (current_time - last_pushed_time >= PRESSED)) // button pushed && (last_button_state is not pushed or current_time - last_pushed_time is > PRESSED milliseconds)
            {
                last_pushed_time = current_time;
                last_button_state = LOW;
                return true;
            }
        }
        else // released
        {
            last_button_state = HIGH;
        }
    }
    return false;
}

#endif /* BUTTON */