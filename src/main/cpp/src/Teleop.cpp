#include <iostream>

#include "src/Robot.h"

namespace frc973 {

void Robot::TeleopInit() {
    m_turret->SetNeutralMode(NeutralMode::Brake);
    m_conveyor->SetTowerState(Conveyor::TowerState::Manual);
    m_conveyor->SetFloorState(Conveyor::FloorState::Manual);
}

void Robot::TeleopPeriodic() {
    // m_turret->Turn(m_turret->CalcJoystickAngleInDegrees(-m_operatorStick->GetRawAxis(5), -m_operatorStick->GetRawAxis(4)), m_gyro->GetWrappedAngle());

    // if(m_operatorStick->GetLeftBumper()) {
    //     m_limelight->SetVisionCamera();

    //     // m_turret->CalcTransitionalCompensations(m_drive->GetVelocity(), 36.0);

    //     // SmartDashboard::PutNumber("Velocity", m_drive->GetVelocity());

    //     m_turret->CalcOutput(m_limelight->GetXOffset(), m_gyro->GetAngularRate());
    //     // m_turret->CalcOutput(0, 0);

    //     // SmartDashboard::PutNumber("Distance", m_limelight->GetHorizontalDist());
    // } else {
    //     m_limelight->SetCameraDriver();
    // }

    m_drive->SetThrottleTurn(m_driverStick->GetRawAxisWithDeadband(1, false, 0.05), 
                            m_driverStick->GetRawAxisWithDeadband(2, false, 0.05));

m_conveyor->SetManualTowerSpeed(m_operatorStick->GetRawAxisWithDeadband(1, false, 0.15)* - 1.0); // left stick y-axis for co-driver
m_conveyor->SetManualFloorSpeed(m_operatorStick->GetRawAxisWithDeadband(0, false, 0.15)* 1.0); // left stick x-axis for co-driver

    }

}  // namespace frc973
