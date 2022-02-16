#include <iostream>

#include "src/Robot.h"

namespace frc973 {

void Robot::DisabledInit() {
    m_turret->SetNeutralMode(NeutralMode::Coast);
    m_climbTalonA->SetNeutralMode(NeutralMode::Brake);
    m_climbTalonB->SetNeutralMode(NeutralMode::Brake);
    m_lights->SetLightsState(Lights::LightsState::Off);

    m_turret->CheckedSensorsToFalse();
}

void Robot::DisabledPeriodic() {
    // turret calibration + light to signal the side needed
    SmartDashboard::PutBoolean("Left Switch", m_turretTalon->IsRevLimitSwitchClosed());
    SmartDashboard::PutBoolean("Right Switch", m_turretTalon->IsFwdLimitSwitchClosed());
    SmartDashboard::PutBoolean("Middle Switch", !m_turretSensor->Get());
    
    // turret calibration + CANdle switching
    switch (m_turret->SensorCalibrate()) {
    case 0:
        m_lights->SetLightsState(Lights::LightsState::Middle);
        break;
    case 1:
        m_lights->SetLightsState(Lights::LightsState::Left);
        break;
    case 2:
        m_lights->SetLightsState(Lights::LightsState::Right);
        break;
    case 3:
        m_lights->SetLightsState(Lights::LightsState::Middle);
        break;
    case 4:
        m_lights->SetLightsState(Lights::LightsState::Initialization);
        break;
    default:
        m_lights->SetLightsState(Lights::LightsState::Off);
        break;
    }
}
}  // namespace frc973