#include <iostream>

#include "src/Robot.h"

namespace frc973 {

void Robot::DisabledInit() {
    m_turret->SetNeutralMode(NeutralMode::Coast);
    m_climbTalonA->SetNeutralMode(NeutralMode::Brake);
    m_climbTalonB->SetNeutralMode(NeutralMode::Brake);
    m_lights->SetLightsState(Lights::LightsState::Off);

    // m_turret->CheckedSensorsToFalse();
}

void Robot::DisabledPeriodic() {
    // turret calibration + light to signal the side needed
    // will move to subsystem manager when leo creates proper functions
    SmartDashboard::PutBoolean("Left Switch", m_turretTalon->IsRevLimitSwitchClosed());
    SmartDashboard::PutBoolean("Right Switch", m_turretTalon->IsFwdLimitSwitchClosed());
    SmartDashboard::PutBoolean("Middle Switch", !m_turretSensor->Get());
}
}  // namespace frc973