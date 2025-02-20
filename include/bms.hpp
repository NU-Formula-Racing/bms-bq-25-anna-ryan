#pragma once
#include <Arduino.h>
#include "teensy_can.h"
#include "virtualTimer.h"

enum class BMSState
{
  Shutdown,
  Precharge,
  Active,
  Charging,
  Fault,
};

enum class BMSCommand
{
  NoAction = 0,
  PrechargeAndCloseContactors = 1,
  Shutdown = 2
};

extern TeensyCAN<3> drive_bus; // fix bus number

extern VirtualTimerGroup timer_group;

void bms_init();
void change_bms_state();
void process_bms_state();
void tick_bms();

extern CANSignal<BMSState, 0, 8, CANTemplateConvertFloat(1), CANTemplateConvertFloat(0), false> BMS_State;
extern CANSignal<float, 40, 8, CANTemplateConvertFloat(0.5), CANTemplateConvertFloat(0), false> BMS_SOC;
extern CANTXMessage<2> BMS_Status;
