#include <iostream>

#include "src/Robot.h"

namespace frc973 {

void Robot::TeleopInit() {
    m_turret->SetNeutralMode(NeutralMode::Brake);
    m_climbTalonA->SetNeutralMode(NeutralMode::Brake);
    m_climbTalonB->SetNeutralMode(NeutralMode::Brake);
    m_conveyor->SetTowerState(Conveyor::TowerState::Manual);
    m_conveyor->SetFloorState(Conveyor::FloorState::Manual);

    m_drive->SetDriveMode(Drive::DriveMode::arcade);
    m_drive->ClampSpeed(-DRIVE_TELEOP_LIMIT, DRIVE_TELEOP_LIMIT);

    m_shooter->SetFlywheelRPM(TARMAC_FLYWHEEL_RPM_SETPOINT);

    m_limelight->SetVisionCamera();

    m_gyro->SetFieldCentricGyroAngle();
}

void Robot::TeleopPeriodic() {
    // Shooter
    if (m_operatorStick->RightTriggerAxis()) {  // Right Trigger - Spin Up Flywheel

        if (m_operatorStick->GetAButton()) {  // Btn A - Set Lowgoal RPM
            m_shooter->SetShooterState(Shooter::ShooterState::Fixed);
            m_shooter->SetFlywheelRPM(LOW_FLYWHEEL_RPM_SETPOINT);
        } else if (m_operatorStick->GetRawButton(Stick::RightBumper)) {  // Right Bumper - Set Tarmac RPM
            m_shooter->SetShooterState(Shooter::ShooterState::Fixed);
            m_shooter->SetFlywheelRPM(TARMAC_FLYWHEEL_RPM_SETPOINT);
        } else {
            m_shooter->SetShooterState(Shooter::ShooterState::Tracking);
        }

    } else {
        m_shooter->SetShooterState(Shooter::ShooterState::Off);
        m_lights->SetLightsState(Lights::LightsState::Off);
    }

    // Turret
    if (m_operatorStick->GetAButton()) {  // Btn A - Set Lowgoal Angle
        m_turret->SetTurretState(TurretState::Manual);
        m_turret->SetTurnValue(0.0);
    } else {
        if (m_operatorStick->GetRawAxisWithDeadband(5, false, 0.5) ||
            m_operatorStick->GetRawAxisWithDeadband(4, false, 0.5)) {
            m_turret->SetTurretState(TurretState::Manual);
            m_turret->SetTurnValue(
                m_turret->CalcJoystickAngleInDegrees(-m_operatorStick->GetRawAxis(5), -m_operatorStick->GetRawAxis(4)));
        } else {
            m_turret->SetTurretState(TurretState::Tracking);
        }
    }

    // Conveyors and Intake
    if (m_driverStick->GetRawButton(Stick::RightBumper)) {  // Right Bumper -
        m_intake->Deploy();
        m_intake->SetIntakeMotorState(Intake::IntakeMotorState::FeedIn);
        m_conveyor->SetFloorState(Conveyor::FloorState::FeedIn);
        m_conveyor->SetTowerState(Conveyor::TowerState::FeedOut);
    } else if (m_driverStick->GetRawButton(Stick::LeftTrigger)) {  // Left Trigger -
        m_intake->Deploy();
        m_intake->SetIntakeMotorState(Intake::IntakeMotorState::FeedOut);
        m_conveyor->SetFloorState(Conveyor::FloorState::FeedOut);
        m_conveyor->SetTowerState(Conveyor::TowerState::FeedOut);
    } else if (m_operatorStick->GetLeftTriggerAxis()) {  // Left Trigger - Deploy Intake
        m_intake->Deploy();
    } else {
        m_intake->Retract();
        m_intake->SetIntakeMotorState(Intake::IntakeMotorState::Off);
        m_conveyor->SetFloorState(Conveyor::FloorState::Off);
        m_conveyor->SetTowerState(Conveyor::TowerState::Off);
    }

    if (m_driverStick->GetRawButton(Stick::RightTrigger)) {  // Right Trigger - Shoot Button
        m_conveyor->SetFloorState(Conveyor::FloorState::Shoot);
        m_conveyor->SetTowerState(Conveyor::TowerState::Shoot);
    } else {
        if (m_operatorStick->GetRawAxisWithDeadband(0, false, 0.2)) {  // left stick x-axis
            m_intake->SetIntakeMotorState(Intake::IntakeMotorState::Manual);
            m_conveyor->SetFloorState(Conveyor::FloorState::Manual);
        }
        m_intake->SetPercentOutput(m_operatorStick->GetRawAxisWithDeadband(0, false, 0.2));
        m_conveyor->SetManualFloorSpeed(m_operatorStick->GetRawAxisWithDeadband(0, false, 0.2));

        if (m_operatorStick->GetRawAxisWithDeadband(1, false, 0.2)) {  // left stick y-axis
            m_conveyor->SetTowerState(Conveyor::TowerState::Manual);
        }
        m_conveyor->SetManualTowerSpeed(m_operatorStick->GetRawAxisWithDeadband(1, false, 0.2));
    }

    // Drive
    if (m_driverStick->GetLeftBumper()) {
        m_drive->SetQuickTurn(true);
    } else {
        m_drive->SetQuickTurn(false);
    }

    m_drive->SetThrottleTurn(m_driverStick->GetRawAxisWithDeadband(1, false, 0.1),
                             m_driverStick->GetRawAxisWithDeadband(2, false, 0.1));

    // Gyro

    // Limelight
    if (m_driverStick->GetRightBumper()) {
        m_limelight->SetCameraDriver();
    } else {
        m_limelight->SetVisionCamera();
    }

    // Climb
    double manualClimb = m_operatorStick->GetRawAxisWithDeadband(1, false, 0.15);
    if (m_operatorStick->GetBackButton()) {
        m_climb->SetClimbState(Climb::ClimbState::Manual);
    }

    if (m_operatorStick->GetStartButton()) {
        m_climb->SetClimbState(Climb::ClimbState::Off);
    }

    if (m_operatorStick->GetYButton()) {
        m_climb->SetClimbState(Climb::ClimbState::Level_3);
    }

    if (m_climb->GetClimbStatus()) {
        m_climb->SetClimbSpeed(manualClimb);
        m_intake->SetIntakeState(Intake::IntakeState::Deploy);
        m_intake->SetIntakeMotorState(Intake::IntakeMotorState::Off);
        m_conveyor->SetFloorState(Conveyor::FloorState::Off);
        m_conveyor->SetTowerState(Conveyor::TowerState::Off);
        m_turret->SetTurretState(TurretState::Manual);
        m_turret->SetTurnValue(0.0);
        m_limelight->SetCameraDriver();
    } else {
        m_compressor->EnableDigital();
        m_climb->SetClimbSpeed(0.0);
    }

    /** Post Periodic */
    m_subsystemManager->Update();
    m_drive->Update();
    m_intake->Update();
    m_conveyor->Update();
    m_turret->Update();
    m_shooter->Update();
    m_climb->Update();
    m_gyro->Update();
    m_lights->Update();
}

}  // namespace frc973
