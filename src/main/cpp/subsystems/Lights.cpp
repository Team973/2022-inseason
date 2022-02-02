#include <iostream>
#include "src/subsystems/Lights.h" 

namespace frc973 {
    Lights::Lights(ctre::phoenix::led::CANdle *CANdle)
    : m_candle(CANdle) 
    , m_lightsState(LightsState::Off)
    {
        
}
    //m_candle->SetLEDs(0,0,0,0,8);

void Lights::Update() {
    switch (m_lightsState) { 
        case LightsState::Off:
            break; 
        case LightsState::Rainbow:
            m_candle->Animate(m_rainbow);
            break;
        case LightsState::Larson:
            m_candle->Animate(m_larson);
            break;
        case LightsState::RgbFade:
            m_candle->Animate(m_rgbFade);
            break;
        case LightsState::SingleFade:
            m_candle->Animate(m_singleFade);
            break;
        case LightsState::ColorFlow:
            m_candle->Animate(m_flow);
            break;
        case LightsState::Strobe:
            m_candle->Animate(m_strobe);
            break;
        case LightsState::Twinkle:
            m_candle->Animate(m_twinkle);
            break;
        case LightsState::TwinkleOff:
            m_candle->Animate(m_twinkleOff);   
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