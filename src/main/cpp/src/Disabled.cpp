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
    switch (m_turret->SensorCalibrate(m_turretTalon->IsRevLimitSwitchClosed(),
             m_turretTalon->IsFwdLimitSwitchClosed(), !m_turretSensor->Get())) {
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
        m_lights->SetLightsState(Lights::LightsState::Initialization);
        m_turretTalon->SetNeutralMode(NeutralMode::Brake);
        break;
    default:
        m_lights->SetLightsState(Lights::LightsState::Off);
        break;
    }
}
}  // namespace frc973