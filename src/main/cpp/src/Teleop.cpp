#include <iostream>

#include "src/Robot.h"

namespace frc973 {

void Robot::TeleopInit() {
    m_turret->SetNeutralMode(NeutralMode::Brake);
    m_conveyor->SetTowerState(Conveyor::TowerState::Manual);
    m_conveyor->SetFloorState(Conveyor::FloorState::Manual);
}

void Robot::TeleopPeriodic() {
    // shooter
    if (m_driverStick->GetRawButton(Stick::RightTrigger)) {  // Right Trigger
        m_shooter->SetFlywheelRPM(2800);
        m_shooter->SetShooterState(Shooter::ShooterState::Tracking);
    } else {
        m_shooter->SetShooterState(Shooter::ShooterState::Off);
    }

    // turret
    m_turret->Turn(
        m_turret->CalcJoystickAngleInDegrees(-m_operatorStick->GetRawAxis(5), -m_operatorStick->GetRawAxis(4)),
        m_gyro->GetWrappedAngle());

    if (m_operatorStick->GetLeftBumper()) {
        m_limelight->SetVisionCamera();
    }

    // intake
    m_intake->SetIntakeMotorState(Intake::IntakeMotorState::Manual);

    if (m_operatorStick->GetLeftTriggerAxis() >= 0.8) {
        m_intake->Deploy();
    } else {
        m_intake->Retract();
    }

    // drive
    m_drive->SetThrottleTurn(m_driverStick->GetRawAxisWithDeadband(1, false, 0.05),
                             m_driverStick->GetRawAxisWithDeadband(2, false, 0.05));

    m_intake->SetPercentOutput(
        m_operatorStick->GetRawAxisWithDeadband(0, false, 0.12));  // left stick x-axis for co-driver

    // conveyor
    m_conveyor->SetManualTowerSpeed(m_operatorStick->GetRawAxisWithDeadband(1, false, 0.15) *
                                    -1.0);  // left stick y-axis for co-driver
    m_conveyor->SetManualFloorSpeed(m_operatorStick->GetRawAxisWithDeadband(0, false, 0.15) *
                                    1.0);  // left stick x-axis for co-driver
}

}  // namespace frc973
