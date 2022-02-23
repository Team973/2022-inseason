#include <iostream>

#include "src/Robot.h"

namespace frc973 {

void Robot::DisabledInit() {
    m_drive->SetNeutralMode(NeutralMode::Coast);
    m_turret->SetNeutralMode(NeutralMode::Coast);
    // m_climbTalonA->SetNeutralMode(NeutralMode::Brake);
    // m_climbTalonB->SetNeutralMode(NeutralMode::Brake);
    m_lights->SetLightsState(Lights::LightsState::Off);

    m_turret->CheckedSensorsToFalse();
}

void Robot::DisabledPeriodic() {
    m_gyro->Update();
    m_lights->Update();
    m_subsystemManager->TurretCalibration();

    if (m_operatorStick->GetRawButtonPressed(Stick::BtnX)) {
        m_autoManager->IndexAutoMode(true);
    }

    if (m_operatorStick->GetRawButtonPressed(Stick::BtnB)) {
        m_autoManager->IndexAutoMode(false);
    }
}
}  // namespace frc973