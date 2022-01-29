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
    
}

} // namespace frc973