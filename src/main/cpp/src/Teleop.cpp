#include "src/Robot.h"

#include <iostream>

namespace frc973 {
    
void Robot::TeleopInit() {
}

void Robot::TeleopPeriodic() {
    // m_turret->Turn(m_turret->CalcJoystickAngleInDegrees(-m_operatorStick->GetRawAxis(5), -m_operatorStick->GetRawAxis(4)), m_gyro->GetWrappedAngle());

    // if(m_operatorStick->GetAButton()) {
    //     m_turret->Turn(90, 0);
    // }
    // if(m_operatorStick->GetXButton()) {
    //     m_turret->Turn(69, 0);
    // }

    m_drive->SetThrottleTurn(m_driverStick->GetRawAxisWithDeadband(1, false, 0.05), m_driverStick->GetRawAxisWithDeadband(2, false, 0.05));
    m_drive->Update();

    m_turret->CalcTransitionalCompensations(m_drive->GetVelocity(), 0.0);
    m_turret->CalcOutput(0.0, 0.0);


    if (m_operatorStick->GetYButton()) {
        m_limelight->SetVisionCamera();
    } else {
        m_limelight->SetCameraDriver();
    }
    
}

} // namespace frc973