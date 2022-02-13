#include <iostream>

#include "src/Robot.h"

namespace frc973 {

void Robot::DisabledInit() {
    m_turret->SetNeutralMode(NeutralMode::Coast);
    m_lights->SetLightsState(Lights::LightsState::Off);
}

void Robot::DisabledPeriodic() {
    // lights
    bool foundHome = false;

    if (foundHome == false) {
        if (!m_turretSensor->Get()) {
            foundHome = true;
            m_turret->SetHomeOffset();
            m_lights->SetLightsState(Lights::LightsState::Middle);
            m_turret->SetNeutralMode(NeutralMode::Brake);
        }
    }

    // turret
    m_turret->Turn(
        m_turret->CalcJoystickAngleInDegrees(-m_operatorStick->GetRawAxis(5), -m_operatorStick->GetRawAxis(4)),
        m_gyro->GetWrappedAngle());

    if (m_operatorStick->GetLeftBumper()) {
        m_limelight->SetVisionCamera();

        // m_turret->CalcTransitionalCompensations(m_drive->GetVelocity(), 36.0);

        // SmartDashboard::PutNumber("Velocity", m_drive->GetVelocity());

        m_turret->CalcOutput(m_limelight->GetXOffset(), m_gyro->GetAngularRate());
        // m_turret->CalcOutput(0, 0);

        // SmartDashboard::PutNumber("Distance", m_limelight->GetHorizontalDist());
    } else {
        m_limelight->SetCameraDriver();
    }

    // drive
    m_drive->SetThrottleTurn(m_driverStick->GetRawAxisWithDeadband(1, false, 0.05),
                             m_driverStick->GetRawAxisWithDeadband(2, false, 0.05));
}
}  // namespace frc973