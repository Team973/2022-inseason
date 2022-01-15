#include "src/subsystems/Shooter.h"

namespace frc973 {

Shooter::Shooter(TalonFX *flywheelA, TalonFX *flywheelB, TalonFX *precharger)
        : m_flywheelA(flywheelA)
        , m_flywheelB(flywheelB)
        , m_precharger(precharger)
        , m_flywheelRPMSetpoint(FLYWHEEL_RPM_SETPOINT)
        , m_prechargerRPMSetpoint(PRECHARGER_RPM_SETPOINT)
{
    m_flywheelB->Follow(*m_flywheelA);
}

void Shooter::EnableShooter() {
    SetFlywheelVelocity(m_flywheelRPMSetpoint / FLYWHEEL_VELOCITY_RPM);
    SetPrechargerVelocity(m_prechargerRPMSetpoint / PRECHARGER_VELOCITY_RPM);
}

void Shooter::EnableShooterWithDist() {
    /* I want a function to to be able to calcuate the rpm based on the distance from the goal.
    To do that, it requires the lime light subsystem.*/
}

void Shooter::DisableShooter() {
    m_flywheelA->Set(ControlMode::PercentOutput, 0.0);
    m_precharger->Set(ControlMode::PercentOutput, 0.0);
}

void Shooter::SetFlywheelVelocity(double setpoint) {
    m_flywheelA->Set(ControlMode::Velocity, setpoint);
}

void Shooter::SetPrechargerVelocity(double setpoint) {
    m_precharger->Set(ControlMode::Velocity, setpoint);
}

void Shooter::SetFlywheelRPM(double setpoint) {
    m_flywheelRPMSetpoint = setpoint;
}

void Shooter::SetPrechargerRPM(double setpoint) {
    m_prechargerRPMSetpoint = setpoint;
}

void Shooter::Update() {
}

void Shooter::DashboardUpdate() {
     frc::SmartDashboard::PutString(
        "Shooter Info",
        "Flywheel RPM: " + std::to_string(m_flywheelA->GetSelectedSensorVelocity() * FLYWHEEL_VELOCITY_RPM) +
            "; Flywheel Setpoint: " + std::to_string(m_flywheelRPMSetpoint) +
            "; Precharger RPM: " + std::to_string(m_precharger->GetSelectedSensorVelocity() * PRECHARGER_VELOCITY_RPM) +
            "; Precharger Setpoint: " + std::to_string(m_prechargerRPMSetpoint));
    frc::SmartDashboard::PutNumber("FlywheelA temp",m_flywheelA->GetTemperature());
    frc::SmartDashboard::PutNumber("FlywheelB temp",m_flywheelB->GetTemperature());
    frc::SmartDashboard::PutNumber("Flywheel rpm",m_flywheelA->GetSelectedSensorVelocity() * FLYWHEEL_VELOCITY_RPM);
}

bool Shooter::IsAtSpeed() {
    return (m_flywheelA->GetSelectedSensorVelocity() * FLYWHEEL_VELOCITY_RPM) > (m_flywheelRPMSetpoint - 50);
}
}