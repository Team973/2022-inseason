#include "src/Robot.h"

#include <iostream>

namespace frc973 {
    
void Robot::TeleopInit() {
}

void Robot::TeleopPeriodic() {
    if (m_operatorStick->GetYButton()) {
        m_limelight->SetVisionCamera();
    } else {
        m_limelight->SetCameraDriver();
    }
    m_drive->SetThrottleTurn(Util::deadband(-m_operatorStick->GetRawAxis(1), 0.05), Util::deadband(m_operatorStick->GetRawAxis(4), 0.05));
}

} // namespace frc973