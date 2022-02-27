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

    // limelight
    if (m_driverStick->GetRightBumper()) {
        m_limelight->SetCameraDriver();
    } else {
        m_limelight->SetVisionCamera();
    }
   
    /**
     * Co-driver
     */
    // shooter
    if (m_operatorStick->RightTriggerAxis()) {  // Right Trigger
        m_shooter->SetFlywheelRPM(2800);
        m_shooter->SetShooterState(Shooter::ShooterState::Tracking);
    } else {
        m_shooter->SetShooterState(Shooter::ShooterState::Off);
        m_lights->SetLightsState(Lights::LightsState::Off);
    }

    //limelight
    if (m_driverStick->GetRightBumper()) {
        m_limelight->SetCameraDriver();
    } else {
        m_limelight->SetVisionCamera();
    }

    // turret
    if (m_turret->StickMoved(-m_operatorStick->GetRawAxis(5), -m_operatorStick->GetRawAxis(4))) {
        m_turret->SetTurretState(TurretState::Manual);
        m_turret->SetTurnValue(
            m_turret->CalcJoystickAngleInDegrees(-m_operatorStick->GetRawAxis(5), -m_operatorStick->GetRawAxis(4)));
    } else {
        m_turret->SetTurretState(TurretState::Tracking);
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
    if (m_operatorStick->GetBackButton()) {
        m_climb->SetClimbState(Climb::ClimbState::Manual);
    }

    if (m_operatorStick->GetStartButton()) {
        m_climb->SetClimbState(Climb::ClimbState::Off);
    }

    if (m_climb->GetClimbStatus()) {
        m_climb->SetClimbSpeed(manualClimb);
        m_intake->SetIntakeState(Intake::IntakeState::Deploy);
        m_conveyor->SetFloorState(Conveyor::FloorState::Off);
        m_conveyor->SetTowerState(Conveyor::TowerState::Off);
        m_turret->SetTurretState(TurretState::Off);
    } else {
        m_climb->SetClimbSpeed(0.0);
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
