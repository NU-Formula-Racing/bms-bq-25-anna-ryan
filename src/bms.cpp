#include <Arduino.h>
#include "bms.hpp"
#include "teensy_can.h"

VirtualTimerGroup timer_group;
TeensyCAN<3> drive_bus; // fix bus number

void bms_init() {
    Serial.begin(115200);
    BMS_State = BMSState::shutdown;
    drive_bus.Initialize(TeensyCAN<3>::BaudRate::kBaud1M);
    
}

void change_bms_state() {
    switch(BMS_State) {
        case BMSState::shutdown:
            // Handle shutdown state
            break;
        case BMSState::precharge:
            // Handle precharge state
            break;
        case BMSState::active:
            // Handle active state
            break;
        case BMSState::charging:
            // Handle charging state
            break;
        case BMSState::fault:
            // Handle fault state
            break;
    }
}

void process_bms_state() {
    switch (BMS_State) {
        case BMSState::shutdown:
            // Process shutdown state
            break;
        case BMSState::precharge:
            // Process precharge state
            break;
        case BMSState::active:
            // Process active state
            break;
        case BMSState::charging:
            // Process charging state
            break;
        case BMSState::fault:
            // Process fault state
            break;
    }
}

CANSignal<BMSState, 0, 8, CANTemplateConvertFloat(1), CANTemplateConvertFloat(0), false> BMS_State{};
CANSignal<float, 40, 8, CANTemplateConvertFloat(0.5), CANTemplateConvertFloat(0), false> BMS_SOC{};
CANTXMessage<2> BMS_Status{drive_bus, 0x175, 1, 100, timer_group, BMS_State, BMS_SOC}; // these addresses might be wrong, check DBC
