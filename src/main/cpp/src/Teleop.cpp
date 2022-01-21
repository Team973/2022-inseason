#include "src/Robot.h"

#include <iostream>

namespace frc973 {
    
void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
    m_turret->Turn(m_turret->SetJoystickAngle(Util::deadband(m_operatorStick->GetRawAxis(4), 0.05), m_operatorStick->GetRawAxis(5)));
}

} // namespace frc973