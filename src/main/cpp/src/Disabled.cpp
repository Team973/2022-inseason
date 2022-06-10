#include <iostream>

#include "src/Robot.h"

namespace frc973 {

void Robot::DisabledInit() {
    m_drive->SetNeutralMode(NeutralMode::Coast);
    m_turret->SetNeutralMode(NeutralMode::Coast);
    m_climbTalonA->SetNeutralMode(NeutralMode::Brake);
    m_climbTalonB->SetNeutralMode(NeutralMode::Brake);

    // m_intake->SetIntakeState(Intake::IntakeState::Retract);
    m_lights->SetLightsState(Lights::LightsState::Off);

    m_turret->CheckedSensorsToFalse();
}

void Robot::DisabledPeriodic() {
    m_gyro->Update();
    m_lights->Update();
    m_subsystemManager->TurretCalibration();

    if (m_operatorStick->GetRawButtonPressed(Stick::BtnX)) {
        m_autoManager->IndexAutoMode(true);
    }

    if (m_operatorStick->GetRawButtonPressed(Stick::BtnB)) {
        m_autoManager->IndexAutoMode(false);
    }

    if (m_driverStick->GetRightBumper()) {
        m_limelight->SetCameraDriver();
    } else {
        m_limelight->SetVisionCamera();
    }

    if (m_climb->GetClimbStatus()) {
        if (m_operatorStick->GetRawButton(Stick::BtnA)) {
            m_climb->SetNeutralMode(NeutralMode::Coast);
        } else {
            m_climb->SetNeutralMode(NeutralMode::Brake);
        }
    }
}
}  // namespace frc973