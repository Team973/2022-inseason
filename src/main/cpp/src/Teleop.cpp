#include <iostream>

#include "src/Robot.h"

namespace frc973 {

void Robot::TeleopInit() {
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
    /**
     * Driver
     */
    // shoot btn
    if (m_driverStick->GetRawButton(Stick::RightTrigger)) { //&& m_subsystemManager->ReadyToShoot()) {  // Right Trigger
        m_conveyor->SetFloorState(Conveyor::FloorState::FeedIn);
        m_conveyor->SetTowerState(Conveyor::TowerState::FeedIn);
        m_intake->SetIntakeMotorState(Intake::IntakeMotorState::FeedIn);
    } else {
        m_conveyor->SetFloorState(Conveyor::FloorState::Off);
        m_conveyor->SetTowerState(Conveyor::TowerState::Off);
        m_intake->SetIntakeMotorState(Intake::IntakeMotorState::Off);
    }

    // drive
    if (m_driverStick->GetLeftBumper()) {
        m_drive->SetQuickTurn(true);
    } else {
        m_drive->SetQuickTurn(false);
    }

    m_drive->SetThrottleTurn(m_driverStick->GetRawAxisWithDeadband(1, false, 0.1),
                             m_driverStick->GetRawAxisWithDeadband(2, false, 0.1));

    // gyro
    if (m_driverStick->GetRawButton(Stick::RightBumper)) {
        m_gyro->Zero();
    }
   
    /**
     * Co-driver
     */
    // shooter
    if (m_operatorStick->RightTriggerAxis()) {  // Right Trigger
        m_shooter->SetFlywheelRPM(3000);
        m_shooter->SetShooterState(Shooter::ShooterState::Tracking);
    } else {
        m_shooter->SetShooterState(Shooter::ShooterState::Off);
        m_lights->SetLightsState(Lights::LightsState::Off);
    }

    // limelight
    if (m_driverStick->GetRightBumper()) {
        m_limelight->SetVisionCamera();
    } else {
        m_limelight->SetCameraDriver();
    }

    // turret
    if (!m_driverStick->GetRightBumper()) {
        m_turret->Turn(
            m_turret->CalcJoystickAngleInDegrees(-m_operatorStick->GetRawAxis(5), -m_operatorStick->GetRawAxis(4)), 0);
    }

    // intake
    m_intake->SetIntakeMotorState(Intake::IntakeMotorState::Manual);

    if (m_operatorStick->GetLeftTriggerAxis() >= 0.8) {
        m_intake->Deploy();
    } else {
        m_intake->Retract();
    }

    m_intake->SetPercentOutput(
        m_operatorStick->GetRawAxisWithDeadband(0, false, 0.12));  // left stick x-axis for co-driver

    // climb state
    double manualClimb = m_operatorStick->GetRawAxisWithDeadband(1, false, 0.15);
    if (m_operatorStick->GetRawButton(Stick::Back)) {
        m_climb->SetClimbState(Climb::ClimbState::Manual);
        m_climb->SetClimbSpeed(manualClimb);
    }

    if (m_operatorStick->GetRawButton(Stick::Start)) {
        m_climb->SetClimbState(Climb::ClimbState::Off);
        m_climb->SetClimbSpeed(manualClimb);
    }

    if (m_climb->GetClimbStatus()) {
        m_climb->SetClimbState(Climb::ClimbState::Manual);
        m_conveyor->SetFloorState(Conveyor::FloorState::Off);
        m_conveyor->SetTowerState(Conveyor::TowerState::Off);
    } else {
        // conveyor
        m_conveyor->SetManualTowerSpeed(m_operatorStick->GetRawAxisWithDeadband(1, false, 0.15) *
                                        1.0);  // left stick y-axis for co-driver
        m_conveyor->SetManualFloorSpeed(m_operatorStick->GetRawAxisWithDeadband(0, false, 0.15) *
                                        1.0);  // left stick x-axis for co-driver
    }

    m_drive->Update();
    m_drive->SetAngle(m_gyro->GetWrappedAngle());
    m_intake->Update();
    m_conveyor->Update();
    m_turret->Update();
    m_shooter->Update();
    m_climb->Update();
    m_gyro->Update();
    m_lights->Update();
    m_subsystemManager->Update();
}

}  // namespace frc973
