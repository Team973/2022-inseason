#include <iostream>

#include "src/Robot.h"

namespace frc973 {

void Robot::TeleopInit() {
    m_turret->SetNeutralMode(NeutralMode::Brake);
    m_shooter->SetShooterState(Shooter::ShooterState::Manual);
}

void Robot::TeleopPeriodic() {
    m_shooter->SetFlywheelSpeed(Util::deadband(m_operatorStick->GetRawAxis(5), 0.1));
    m_shooter->SetShooterState(Shooter::ShooterState::Manual);
}

}  // namespace frc973
