#include <iostream>

#include "src/Robot.h"

namespace frc973 {

void Robot::TeleopInit() {
}

void Robot::TeleopPeriodic() {
    if (m_driverStick->GetRawButton(Stick::RightTrigger)) {  // Right Trigger
        m_shooter->SetFlywheelRPM(2800);
        m_shooter->SetShooterState(Shooter::ShooterState::Tracking);
    } else {
        m_shooter->SetShooterState(Shooter::ShooterState::Off);
    }
}

}  // namespace frc973
