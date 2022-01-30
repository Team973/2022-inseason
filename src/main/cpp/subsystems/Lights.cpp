#include <iostream>
#include "src/subsystems/Lights.h" 

namespace frc973 {
    Lights::Lights(ctre::phoenix::led::CANdle *CANdle)
    : m_candle(CANdle) 
    , m_rainbow{1.0, 1.0, 8}
    , m_larson(0.0, 200.0, 217.0, 0.0, 0.01, 8.0, ctre::phoenix::led::LarsonAnimation::Center, 1)
    , m_fire(1.0, 0.01, 8, 1.0, 1.0)
    , m_rgbFade{1.0, 1.0, 8}
    , m_singleFade{118, 0, 118, 0, 1.0, 8}
    , m_flow{255, 20, 147, 0, 1.0, 8, ctre::phoenix::led::ColorFlowAnimation::Direction::Forward}
    , m_strobe{219, 112, 147, 0, 1.0, 8}
    , m_twinkle{217, 69, 0, 0, 1.0, 8, ctre::phoenix::led::TwinkleAnimation::TwinklePercent::Percent100}
    , m_twinkleOff{217, 91, 0, 0, 0.2, 8, ctre::phoenix::led::TwinkleOffAnimation::TwinkleOffPercent::Percent100}
    {
}

void Lights::Update() {
    m_candle->Animate(m_rainbow);
    //m_candle->SetLEDs(0,254,0,1,3);
}

void Lights::DashboardUpdate() {
}
} //frc name