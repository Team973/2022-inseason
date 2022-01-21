#include "src/Robot.h"

#include <iostream>

namespace frc973 {
    
void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
    m_turret->Turn(m_turret->CalcJoystickAngleInDegrees(m_operatorStick->GetRawAxis(4), -m_operatorStick->GetRawAxis(5)));

    if(m_operatorStick->GetAButton()) {
        m_turret->Turn(90);
    }
    if(m_operatorStick->GetXButton()) {
        m_turret->Turn(69);
    }

    SmartDashboard::PutNumber("X", m_operatorStick->GetRawAxis(4));
    SmartDashboard::PutNumber("Y", -m_operatorStick->GetRawAxis(5));
}

} // namespace frc973