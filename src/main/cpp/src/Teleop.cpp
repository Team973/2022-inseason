#include "src/Robot.h"

#include <iostream>

namespace frc973 {
    
void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
    m_turret->Turn(m_turret->CalcJoystickAngleInDegrees(-m_operatorStick->GetRawAxis(4), m_operatorStick->GetRawAxis(5)), m_gyro->GetWrappedAngle());

    if(m_operatorStick->GetAButton()) {
        m_turret->Turn(90, 0);
    }
    if(m_operatorStick->GetXButton()) {
        m_turret->Turn(69, 0);
    }

    SmartDashboard::PutNumber("X", m_operatorStick->GetRawAxis(4));
    SmartDashboard::PutNumber("Y", -m_operatorStick->GetRawAxis(5));

    m_drive->SetThrottleTurn(Util::deadband(m_driverStick->GetRawAxis(1), 0.05), Util::deadband(m_driverStick->GetRawAxis(2), 0.05));
    m_drive->Update();
}

} // namespace frc973