#include <Arduino.h>
#include "bms.hpp"
#include "teensy_can.h"

VirtualTimerGroup timer_group;
TeensyCAN<3> drive_bus; // fix bus number

void bms_init() {
  Serial.begin(115200);
  BMS_State = BMSState::Shutdown;
  drive_bus.Initialize(TeensyCAN<3>::BaudRate::kBaud1M);

  // add all functions to timers
  timer_group.AddTimer(10, change_bms_state);
  timer_group.AddTimer(100, process_bms_state);
}

void change_bms_state() {
  switch(BMS_State) {
    case BMSState::Shutdown:
      if (BMS_Command == BMSCommand::PrechargeAndCloseContactors) {
        BMS_State = BMSState::Precharge;
      }
      break;
    case BMSState::Precharge:
      // Handle Precharge state
      break;
    case BMSState::Active:
      // Handle active state
      break;
    case BMSState::Charging:
      // Handle charging state
      break;
    case BMSState::Fault:
      // Handle fault state
      break;
  }
}

void process_bms_state() {
    switch (BMS_State) {
        case BMSState::Shutdown:
            // Process shutdown state
            break;
        case BMSState::Precharge:
            // Process Precharge state
            break;
        case BMSState::Active:
            // Process active state
            break;
        case BMSState::Charging:
            // Process charging state
            break;
        case BMSState::Fault:
            // Process fault state
            break;
    }
}

void tick_bms() {
    // This function should be called periodically to update the BMS state
    process_bms_state();
    change_bms_state();
}

CANSignal<BMSState, 0, 8, CANTemplateConvertFloat(1), CANTemplateConvertFloat(0), false> BMS_State{};
CANSignal<float, 40, 8, CANTemplateConvertFloat(0.5), CANTemplateConvertFloat(0), false> BMS_SOC{};
CANSignal<BMSCommand, 0, 8, CANTemplateConvertFloat(1), CANTemplateConvertFloat(0), false> BMS_Command{};
CANTXMessage<2> BMS_Status{drive_bus, 0x175, 1, 100, timer_group, BMS_State, BMS_SOC}; // these addresses might be wrong, check DBC
CANRXMessage<1> ECU_BMS_Command_Message{drive_bus, 0x205, BMS_Command};