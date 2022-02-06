#include "src/Robot.h"

#include <iostream>

namespace frc973 {
    
void Robot::TeleopInit() {
    m_turret->SetNeutralMode(NeutralMode::Brake);
}

void Robot::TeleopPeriodic() {

    //tells if turret should be in manual or auto

        m_turret->Turn(m_turret->CalcJoystickAngleInDegrees(-m_operatorStick->GetRawAxis(5), -m_operatorStick->GetRawAxis(4)), m_gyro->GetWrappedAngle());

        // if(m_operatorStick->GetLeftBumper()) {
            // m_limelight->SetVisionCamera();

            m_turret->CalcTransitionalCompensations(m_drive->GetVelocity(), 36.0);
            // m_turret->CalcTransitionalCompensations(m_drive->GetVelocity(), 36);


            SmartDashboard::PutNumber("Velocity", m_drive->GetVelocity());

            // m_turret->CalcOutput(m_limelight->GetXOffset(), m_gyro->GetAngularRate());
            m_turret->CalcOutput(0, 0);


            SmartDashboard::PutNumber("Distance", m_limelight->GetHorizontalDist());
        // } else {
        //     m_limelight->SetCameraDriver();
        // }

        // if(m_operatorStick->GetRightBumper()) {
        // } else {
        //     m_turret->CalcOutput(m_limelight->GetXOffset(), 0.0);

        // }
    // }

    // if(m_operatorStick->GetAButton()) {
    //     m_turret->Turn(90, 0);
    // }
    // if(m_operatorStick->GetXButton()) {
    //     m_turret->Turn(69, 0);
    // }

    m_drive->SetThrottleTurn(m_driverStick->GetRawAxisWithDeadband(1, false, 0.05), m_driverStick->GetRawAxisWithDeadband(2, false, 0.05));
    m_drive->Update();

    //tempomove drive to codriver xbox instead of joystick for testing
    // m_drive->SetThrottleTurn(m_operatorStick->GetRawAxisWithDeadband(1, false, 0.05), m_operatorStick->GetRawAxisWithDeadband(4, false, 0.05));
    // m_drive->Update();

    


    SmartDashboard::PutNumber("leftoutput", m_drive->GetLeftOuput());
    SmartDashboard::PutNumber("rightoutput", m_drive->GetRightOuput());

    
}

} // namespace frc973