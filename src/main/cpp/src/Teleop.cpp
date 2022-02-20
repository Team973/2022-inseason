#include <iostream>

#include "src/Robot.h"

namespace frc973 {

void Robot::TeleopInit() {
    // default drive mode
    m_drive->SetDriveMode(Drive::DriveMode::arcade);
    m_drive->Zero();
    m_drive->ClampSpeed(-DRIVE_TELEOP_LIMIT, DRIVE_TELEOP_LIMIT);

    m_turret->SetNeutralMode(NeutralMode::Brake);
    m_climbTalonA->SetNeutralMode(NeutralMode::Brake);
    m_climbTalonB->SetNeutralMode(NeutralMode::Brake);
    m_conveyor->SetTowerState(Conveyor::TowerState::Manual);
    m_conveyor->SetFloorState(Conveyor::FloorState::Manual);
}

void Robot::TeleopPeriodic() {
    // shoot btn
    if (m_driverStick->GetRawButton(Stick::RightTrigger)) {  // Right Trigger
        m_conveyor->SetFloorState(Conveyor::FloorState::FeedIn);
        m_conveyor->SetTowerState(Conveyor::TowerState::FeedIn);
        m_intake->SetIntakeMotorState(Intake::IntakeMotorState::FeedIn);
    } else {
        m_conveyor->SetFloorState(Conveyor::FloorState::Off);
        m_conveyor->SetTowerState(Conveyor::TowerState::Off);
        m_intake->SetIntakeMotorState(Intake::IntakeMotorState::Off);
    }

    // shooter
    if (m_operatorStick->RightTriggerAxis()) {
        if (m_shooter->IsAtSpeed()) {
            m_lights->SetLightsState(Lights::LightsState::ReadyToShoot);
        } else {
            m_lights->SetLightsState(Lights::LightsState::Off);
        }

        m_shooter->SetFlywheelRPM(3600);
        m_shooter->SetShooterState(Shooter::ShooterState::Tracking);
    } else {
        m_shooter->SetShooterState(Shooter::ShooterState::Off);
        m_lights->SetLightsState(Lights::LightsState::Off);
    }

    // turret
    m_turret->Turn(m_turret->CalcJoystickAngleInDegrees(-m_operatorStick->GetRawAxis(5), -m_operatorStick->GetRawAxis(4)),
                   // m_gyro->GetWrappedAngle()
                   0);

    // if (m_operatorStick->GetRawButton(Stick::BtnX)) {
    //     m_turret->SetTurretAngle(90);
    // }
    // if(m_operatorStick->GetRawButton(Stick::BtnB)) {
    //     m_turret->SetTurretAngle(-90);
    // }
    // if(m_operatorStick->GetRawButton(Stick::BtnY)) {
    //     m_turret->SetTurretAngle(0);
    // }

    // if(m_operatorStick->GetRightBumper()) {
    //     m_limelight->SetVisionCamera();

    //     if(m_limelight->isTargetValid()){
    //         m_turret->CalcOutput(m_limelight->GetXOffset(), m_gyro->GetAngularRate(),
    //         m_turret->CalcTransitionalCompensations(m_drive->GetVelocity(), m_limelight->GetHorizontalDist()));
    //     } else {
    //         m_turret->CalcOutput(0.0, m_gyro->GetAngularRate(), 0.0);
    //     }
    // } else {
    //     m_limelight->SetCameraDriver();
    // }

    // limelight
    // if (m_operatorStick->GetLeftBumper()) {
    //     m_limelight->SetVisionCamera();
    // } else {
    //     m_limelight->SetCameraDriver();
    // }

    // intake
    m_intake->SetIntakeMotorState(Intake::IntakeMotorState::Manual);

    if (m_operatorStick->GetLeftTriggerAxis() >= 0.8) {
        m_intake->Deploy();
    } else {
        m_intake->Retract();
    }

    m_intake->SetPercentOutput(
        m_operatorStick->GetRawAxisWithDeadband(0, false, 0.12));  // left stick x-axis for co-driver

    // drive
    if (m_driverStick->GetLeftBumper()) {
        m_drive->SetQuickTurn(true);
    } else {
        m_drive->SetQuickTurn(false);
    }

    m_drive->SetThrottleTurn(m_driverStick->GetRawAxisWithDeadband(1, false, 0.05),
                             m_driverStick->GetRawAxisWithDeadband(2, false, 0.05));

    // conveyor
    m_conveyor->SetManualTowerSpeed(m_operatorStick->GetRawAxisWithDeadband(1, false, 0.15) *
                                    1.0);  // left stick y-axis for co-driver
    m_conveyor->SetManualFloorSpeed(m_operatorStick->GetRawAxisWithDeadband(0, false, 0.15) *
                                    1.0);  // left stick x-axis for co-driver

    // gyro
    if (m_driverStick->GetRawButton(Stick::RightBumper)) {
        m_gyro->Zero();
    }
}

}  // namespace frc973
