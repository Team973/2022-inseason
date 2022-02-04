#include <iostream>
#include "src/subsystems/Lights.h" 

#include "ctre/phoenix/led/RainbowAnimation.h"

namespace frc973 {
    Lights::Lights(ctre::phoenix::led::CANdle *CANdle)
    : m_candle(CANdle)
    , m_lightsState(LightsState::Off)
    , m_rainbow{1.0, 1.0, 8}
    , m_strobe{0,255,0,0,1.0,8}
    {
}

void Lights::Update() {
    switch (m_lightsState) { 
        case LightsState::Off:
            m_candle->SetLEDs(0,0,0,0,8);
            break; 
        case LightsState::Initialization:
            m_candle->SetLEDs(0,0,0,0,8);
            m_candle->SetLEDs(217,91,0,0,8);
            break;
        case LightsState::NotReadyToShoot:
            m_candle->SetLEDs(0,0,0,0,8);
            m_candle->Animate(m_strobe);
            break;
        case LightsState::ReadyToShoot:
            m_candle->SetLEDs(0,0,0,0,8);
            m_candle->SetLEDs(0,255,0,0,8);
            break;
        case LightsState::Fault:
            m_candle->SetLEDs(0,0,0,0,8);
            m_candle->SetLEDs(255,0,0,0,8);
            break;
        case LightsState::Climb:
            m_candle->SetLEDs(0,0,0,0,8);
            m_candle->Animate(m_rainbow);
            break;
        case LightsState::Left:
            m_candle->SetLEDs(0,0,0,0,8);
            //m_candle->SetLEDs(0,0,255,0,7,8);
            m_candle->SetLEDs(255,0,0,0,0,1);
            break;
        default:
            break;
    }
}

void Lights::DashboardUpdate() {
}

Lights::LightsState Lights::GetLightsState() {
    return m_lightsState;
}

void Lights::SetLightsState(LightsState state) {
    m_lightsState = state;
}
}