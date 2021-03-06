#include "src/subsystems/Lights.h"

#include <iostream>

#include "ctre/phoenix/led/RainbowAnimation.h"

namespace frc973 {
Lights::Lights(ctre::phoenix::led::CANdle *CANdle)
        : m_candle(CANdle)
        , m_lightsCurrentState(LightsState::Off)
        , m_rainbow{1.0, 1.0, 8}
        , m_strobe{0, 255, 0, 0, 0.2, 8}
        , m_lowStrobe{0, 0, 255, 0, 0.2, 8}
        , m_inStateTransition(false) {
    m_candle->ConfigFactoryDefault();
}

void Lights::Update() {
    if (!m_inStateTransition) {
        return;
    }

    if (m_lightsCurrentState == m_lightsNextState) {
        m_inStateTransition = false;
    }

    switch (m_lightsCurrentState) {
        case LightsState::Off:
            m_candle->SetLEDs(0, 0, 0, 0, 0, 8);
            m_lightsCurrentState = m_lightsNextState;
            break;
        case LightsState::Initialization:
            m_candle->SetLEDs(217, 91, 0, 0, 0, 8);
            break;
        case LightsState::NotReadyToShoot:
            m_candle->Animate(m_strobe);
            break;
        case LightsState::ReadyToShoot:
            m_candle->SetLEDs(0, 255, 0, 0, 0, 8);
            break;
        case LightsState::Fault:
            m_candle->SetLEDs(255, 0, 0, 0, 0, 8);
            break;
        case LightsState::Climb:
            m_candle->Animate(m_rainbow);
            break;
        case LightsState::Left:
            m_candle->SetLEDs(0, 255, 0, 0, 0, 1);
            break;
        case LightsState::Middle:
            m_candle->SetLEDs(0, 255, 0, 0, 1, 2);
            break;
        case LightsState::Right:
            m_candle->SetLEDs(0, 255, 0, 0, 3, 1);
            break;
        case LightsState::LowNotReady:
            m_candle->Animate(m_lowStrobe);
            break;
        case LightsState::LowReady:
            m_candle->SetLEDs(0, 0, 255, 0, 0, 8);
            break;
        default:
            break;
    }
}

Lights::LightsState Lights::GetLightsState() {
    return m_lightsCurrentState;
}

void Lights::SetLightsState(LightsState state) {
    if (m_lightsCurrentState != state) {
        m_inStateTransition = true;
        m_lightsNextState = state;
        m_lightsCurrentState = LightsState::Off;
    }
}

void Lights::DashboardUpdate() {
    switch (m_lightsCurrentState) {
        case LightsState::Off:
            m_currentLightsStateName = "Off";
            break;
        case LightsState::Initialization:
            m_currentLightsStateName = "Initialization";
            break;
        case LightsState::NotReadyToShoot:
            m_currentLightsStateName = "NotReadyToShoot";
            break;
        case LightsState::ReadyToShoot:
            m_currentLightsStateName = "ReadyToShoot";
            break;
        case LightsState::Fault:
            m_currentLightsStateName = "Fault";
            break;
        case LightsState::Climb:
            m_currentLightsStateName = "Climb";
            break;
        case LightsState::Left:
            m_currentLightsStateName = "Left";
            break;
        case LightsState::Middle:
            m_currentLightsStateName = "Middle";
            break;
        case LightsState::Right:
            m_currentLightsStateName = "Right";
            break;
        case LightsState::LowNotReady:
            m_currentLightsStateName = "LowNotReady";
            break;
        case LightsState::LowReady:
            m_currentLightsStateName = "LowReady";
            break;
    }

    frc::SmartDashboard::PutString("L State: ", m_currentLightsStateName);
}

}  // namespace frc973