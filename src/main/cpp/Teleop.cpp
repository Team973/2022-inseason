#include "src/Robot.h"

#include <iostream>

namespace frc973 {
    
void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
    m_drive->SetThrottleTurn(Util::deadband(-m_driverStick->GetRawAxis(1), 0.05), Util::deadband(m_driverStick->GetRawAxis(2), 0.05));
    m_drive->Update();
    
}

} // namespace frc973