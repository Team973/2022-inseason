#include <iostream>

#include "src/Robot.h"

namespace frc973 {

void Robot::TeleopInit() {
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
    if (m_driverStick->GetRawButton(Stick::RightTrigger) && m_subsystemManager->ReadyToShoot()) {  // Right Trigger
        m_conveyor->SetFloorState(Conveyor::FloorState::FeedIn);
        m_conveyor->SetTowerState(Conveyor::TowerState::FeedIn);
        m_intake->SetIntakeMotorState(Intake::IntakeMotorState::FeedIn);
    } else {
        // m_conveyor->SetFloorState(Conveyor::FloorState::Off);
        // m_conveyor->SetTowerState(Conveyor::TowerState::Off);
        // m_intake->SetIntakeMotorState(Intake::IntakeMotorState::Off);
    }

    // drive
    if (m_driverStick->GetLeftBumper()) {
        m_drive->SetQuickTurn(true);
    } else {
        m_drive->SetQuickTurn(false);
    }

    m_drive->SetThrottleTurn(m_driverStick->GetRawAxisWithDeadband(1, false, 0.05),
                             m_driverStick->GetRawAxisWithDeadband(2, false, 0.05));

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

    // turret
    // m_turret->Turn(
    //     m_turret->CalcJoystickAngleInDegrees(-m_operatorStick->GetRawAxis(5), -m_operatorStick->GetRawAxis(4)),
    //     m_gyro->GetWrappedAngle());

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

    // intake
    m_intake->SetIntakeMotorState(Intake::IntakeMotorState::Manual);

    if (m_operatorStick->GetLeftTriggerAxis() >= 0.8) {
        m_intake->Deploy();
    } else {
        m_intake->Retract();
    }

    m_intake->SetPercentOutput(
        m_operatorStick->GetRawAxisWithDeadband(0, false, 0.12));  // left stick x-axis for co-driver

    // conveyor
    m_conveyor->SetManualTowerSpeed(m_operatorStick->GetRawAxisWithDeadband(1, false, 0.15) *
                                    1.0);  // left stick y-axis for co-driver
    m_conveyor->SetManualFloorSpeed(m_operatorStick->GetRawAxisWithDeadband(0, false, 0.15) *
                                    1.0);  // left stick x-axis for co-driver
}

}  // namespace frc973
