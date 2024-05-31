/*
                /\/\
               /'^.^)
        .-^^^-/  /
     _/         /7
    <__.|_|--|_|
*/

#include "global.h"

#include "lcd.h"
#include "esp_nowServer.h"
#include "button.h"
#include "numpad.h"
#include "espFirebase.h"

#define ACTIVE_REQUEST_CYCLE 10 // 10 secconds
#define ACTIVE_TIME 30          // 30 seconds

void initSystem(void);

// global variables
unsigned long current_time = 0;
unsigned long last_request_time = 0;

Message_Send packet_send = {false, 1, 50, 5};
Message_Receive packet_receive = {0, 0, 0, false, false, false, false};

Pump_Mode current_pump_mode = mode_auto;

// local variables
Pump_Mode temp_pump_mode;

enum Mode
{
  mode_init,
  mode_modify_password,
  mode_warning,
  mode_modify_pump_mode,
  mode_modify_pump_limit,
  mode_modify_pump_interval,
  mode_security,
  mode_running,
  mode_running_2
};
Mode current_mode = mode_init;
Mode previous_mode = mode_init;

String Password = "";
String password_input = "";

unsigned long last_action_time = 0; // used to switch to mode security

bool is_need_update_lcd = false;

// System
void setup()
{
  Serial.begin(9600);
  initSystem();

  delay(1000);
}

void loop()
{
  current_time = millis();
  key = numpadGetKey();
  packet_send.is_button_down = isButtonDown();
  is_need_update_lcd = isPacketReceived();

  if (key || packet_send.is_button_down || current_time < last_action_time) // turn on backlight if actions
  {
    if (current_time - last_action_time >= ACTIVE_TIME * 1000)
    {
      last_action_time = current_time;
      lcdTurnOnBacklight();
      key = 0;                            // reset key
      packet_send.is_button_down = false; // reset button
    }
    else
    {
      last_action_time = current_time;
    }
  }
  if (current_time - last_action_time >= ACTIVE_TIME * 1000) // turn off after ACTIVE_TIME second
  {
    lcdTurnOffBacklight();
  }
  // fsm
  switch (current_mode)
  {
  case mode_init:
  {
    current_mode = mode_modify_password;
    break;
  }

  case mode_modify_password:
  {
    // preprocess
    if (previous_mode != current_mode)
    {
      previous_mode = current_mode;

      lcdClear();
      lcdDisplay(0, 0, "Set New Password", 0, "", false);
      lcdDisplay(16 - Password.length(), 1, Password, 0, "", false);
    }

    // process
    if (key)
    {
      if (key == 'A')
      {
        if (!Password.isEmpty())
        {
          Password.remove(Password.length() - 1);
        }
        lcdClear();
        lcdDisplay(0, 0, "Set New Password", 0, "", false);
      }
      else if (key == 'D')
      {
        Password = "";
        lcdClear();
        lcdDisplay(0, 0, "Set New Password", 0, "", false);
      }
      else if (key >= '0' && key <= '9')
      {
        if (Password.length() < 4)
        {
          Password += key;
        }
      }
      lcdDisplay(16 - Password.length(), 1, Password, 0, "", false);

      // postprocess
      if (Password.length() == 4)
      {
        switch (key)
        {
        case '#':
        {
          if (temp_pump_mode == current_pump_mode)
          {
            current_mode = mode_running;
          }
          else
          {
            current_mode = mode_modify_pump_mode;
          }
          break;
        }
        case '*':
        {
          current_mode = mode_modify_pump_mode;
          break;
        }
        }
      }
    }

    break;
  }
  case mode_warning:
  {
    // preprocess
    if (previous_mode != current_mode)
    {
      previous_mode = current_mode;
    }

    // process

    // postprocess
    current_mode = mode_init;
    break;
  }

  case mode_modify_pump_mode:
  {
    // preprocess
    if (previous_mode != current_mode)
    {
      previous_mode = current_mode;

      lcdClear();
      lcdDisplay(0, 0, "MODE: ", current_pump_mode, "", true);
      lcdDisplay(8, 0, "Auto:", 1, "", true);
      lcdDisplay(0, 1, "Timer:", 2, "", true);
      lcdDisplay(8, 1, "Manual:", 3, "", true);
      temp_pump_mode = current_pump_mode;
    }

    // process
    switch (key)
    {
    case '1':
    {
      temp_pump_mode = mode_auto;
      lcdDisplay(0, 0, "Mode: ", temp_pump_mode, "", true);
      break;
    }
    case '2':
    {
      temp_pump_mode = mode_timer;
      lcdDisplay(0, 0, "Mode: ", temp_pump_mode, "", true);
      break;
    }
    case '3':
    {
      temp_pump_mode = mode_manual;
      lcdDisplay(0, 0, "Mode: ", temp_pump_mode, "", true);
      break;
    }

    // postprocess
    case '#':
    {
      if (current_pump_mode != temp_pump_mode)
      {
        current_pump_mode = temp_pump_mode;

        switch (current_pump_mode)
        {
        case mode_auto:
        {
          current_mode = mode_modify_pump_limit;
          break;
        }
        case mode_timer:
        {
          current_mode = mode_modify_pump_interval;
          break;
        }
        default:
        {
          esp_nowSync();
          current_mode = mode_running;
        }
        }
      }
      else
      {
        current_mode = mode_running;
      }

      break;
    }

    case '*':
    {
      if (current_pump_mode != temp_pump_mode)
      {
        current_pump_mode = temp_pump_mode;

        switch (current_pump_mode)
        {
        case mode_auto:
        {
          current_mode = mode_modify_pump_limit;
          break;
        }
        case mode_timer:
        {
          current_mode = mode_modify_pump_interval;
          break;
        }
        default:
        {
          esp_nowSync();
          current_mode = mode_modify_password;
        }
        }
      }
      else
      {
        current_mode = mode_modify_password;
      }
      break;
    }
    }

    break;
  }

  case mode_modify_pump_limit:
  {
    // preprocess
    if (previous_mode != current_mode)
    {
      previous_mode = current_mode;

      lcdClear();
      lcdDisplay(0, 0, "MODE: ", current_pump_mode, "Auto", false);
      lcdDisplay(0, 1, "Moisture lim:", packet_send.pump_limit, "%", true);
    }

    // process
    if (key >= '1' && key <= '9')
    {
      packet_send.pump_limit = (key - '0') * 10;
      lcdDisplay(0, 1, "Moisture lim:", packet_send.pump_limit, "%", true);
    }

    // postprocess
    if (key == '#')
    {
      esp_nowSync();
      current_mode = mode_running;
    }
    break;
  }
  case mode_modify_pump_interval:
  {
    // preprocess
    if (previous_mode != current_mode)
    {
      previous_mode = current_mode;

      lcdClear();
      lcdDisplay(0, 0, "MODE: ", current_pump_mode, "Timer", false);
      lcdDisplay(0, 1, "Pump interval:", packet_send.pump_interval, "s", true);
    }

    // process
    if (key >= '1' && key <= '9')
    {
      packet_send.pump_interval = (key - '0');
      lcdDisplay(0, 1, "Pump interval:", packet_send.pump_interval, "s", true);
    }

    // postprocess
    if (key == '#')
    {
      esp_nowSync();
      current_mode = mode_running;
    }

    break;
  }
  case mode_security:
  {
    // preprocess
    if (previous_mode != current_mode)
    {
      previous_mode = current_mode;

      password_input = "";
      lcdClear();
      lcdDisplay(0, 0, "Enter Password:", 0, "", false);
    }

    // process
    if (current_time - last_action_time >= ACTIVE_TIME * 1000)
    {
      previous_mode = mode_running; // used to run preprocess
    }

    if (key)
    {
      if (key == 'A')
      {
        if (!password_input.isEmpty())
        {
          password_input.remove(password_input.length() - 1);
        }
        lcdClear();
        lcdDisplay(0, 0, "Enter Password:", 0, "", false);
      }
      else if (key == 'D')
      {
        password_input = "";
        lcdClear();
        lcdDisplay(0, 0, "Enter Password:", 0, "", false);
      }
      else if (key >= '0' && key <= '9')
      {
        if (password_input.length() < 4)
        {
          password_input += key;
        }
      }
      lcdDisplay(16 - password_input.length(), 1, password_input, 0, "", false);

      // postprocess
      if (key == '#')
      {
        if (password_input == Password)
        {
          current_mode = mode_running;
        }
        else
        {
          lcdDisplay(0, 0, "Wrong Password!", 0, "", false);
          previous_mode = mode_running;
          delay(1000);
        }
      }
    }

    break;
  }
  case mode_running:
  {
    // preprocess
    if (previous_mode != current_mode)
    {
      previous_mode = current_mode;

      lcdClear();
      lcdDisplay(0, 0, "Moisture:", packet_receive.moisture_pct, "%", true);
      lcdDisplay(0, 1, "Temp:", packet_receive.temp, "C", true);
      lcdDisplay(8, 1, "Humid:", packet_receive.humid, "%", true);

      esp_nowSync();
    }

    // process
    if (packet_send.is_button_down || ((current_time - last_request_time) >= ACTIVE_REQUEST_CYCLE * 1000) || current_time < last_request_time)
    {
      esp_nowSync();
    }

    if (isPacketCannotSent())
    {
      lcdClear();
      lcdDisplay(1, 0, "Not Connected   ", 0, "", false);
      lcdDisplay(0, 1, "Press C To RCN...", 0, "", false);
    }

    if (is_need_update_lcd)
    {
      lcdClear();
      lcdDisplay(0, 0, "Moisture:", packet_receive.moisture_pct, "%", true);
      lcdDisplay(0, 1, "Temp:", packet_receive.temp, "C", true);
      lcdDisplay(8, 1, "Humid:", packet_receive.humid, "%", true);
    }

    switch (key)
    {
    case 'C':
    {
      esp_nowSync();
      break;
    }

    // postprocess
    case '*':
    {
      current_mode = mode_modify_password;
      break;
    }
    case 'B':
    case 'A':
    {
      current_mode = mode_running_2;
      break;
    }
    }

    if (current_time - last_action_time >= ACTIVE_TIME * 1000) // turn off after ACTIVE_TIME second
    {
      current_mode = mode_security;
    }

    break;
  }
  case mode_running_2:
  {
    // preprocess
    if (previous_mode != current_mode)
    {
      previous_mode = current_mode;

      lcdClear();
      lcdDisplay(0, 0, "Moisture:", packet_receive.moisture_pct, "%", true);
      lcdDisplay(0, 1, "Temp:", packet_receive.temp, "C", true);
      lcdDisplay(8, 1, "Humid:", packet_receive.humid, "%", true);
      esp_nowSync();
    }

    // process
    if (packet_send.is_button_down || ((current_time - last_request_time) >= ACTIVE_REQUEST_CYCLE * 1000) || current_time < last_request_time)
    {
      esp_nowSync();
    }

    if (isPacketCannotSent())
    {
      lcdClear();
      lcdDisplay(1, 0, "Not Connected   ", 0, "", false);
      lcdDisplay(0, 1, "Press C To RCN...", 0, "", false);
    }

    if (is_need_update_lcd)
    {
      lcdClear();

      if (packet_receive.is_pump_on)
      {
        lcdDisplay(0, 0, "Pump ", packet_receive.is_pump_on, "ON", false);
      }
      else
      {
        lcdDisplay(0, 0, "Pump ", packet_receive.is_pump_on, "OFF", false);
      }
      if (packet_receive.is_dry)
      {
        lcdDisplay(10, 0, "Sunny", packet_receive.is_dry, "", false);
      }
      else
      {
        lcdDisplay(10, 0, "Rainy", packet_receive.is_dry, "", false);
      }

      switch (current_pump_mode)
      {
      case mode_auto:
      {
        lcdDisplay(0, 1, "Auto", current_mode, "", false);
        lcdDisplay(7, 1, "Limit:", packet_send.pump_limit, "%", true);
        break;
      }
      case mode_timer:
      {
        lcdDisplay(0, 1, "Timer", current_mode, "", false);
        lcdDisplay(7, 1, "Period:", packet_send.pump_interval, "s", true);
        break;
      }
      case mode_manual:
      {
        lcdDisplay(0, 1, "Manual", current_mode, "", false);
        break;
      }
      }
    }

    switch (key)
    {
    case 'C':
    {
      esp_nowSync();
      break;
    }

    // postprocess
    case '*':
    {
      current_mode = mode_modify_password;
      break;
    }
    case 'B':
    case 'A':
    {
      current_mode = mode_running;
      break;
    }
    }

    if (current_time - last_action_time >= ACTIVE_TIME * 1000) // turn off after ACTIVE_TIME second
    {
      current_mode = mode_security;
    }

    break;
  }

  default:
  {
    current_mode = mode_init;
    break;
  }
  }
}

void initSystem()
{
  initLCD();
  initEsp_now();
  initButton();
  initNumpad();

  initEspFirebase();
}