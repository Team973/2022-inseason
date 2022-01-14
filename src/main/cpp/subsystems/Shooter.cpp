#include "src/subsystems/Shooter.h"

namespace frc973 {

Shooter::Shooter(TalonFX *flywheelA, TalonFX *flywheelB, TalonFX *precharger)
        : m_flywheelA(flywheelA)
        , m_flywheelB(flywheelB)
        , m_precharger(precharger)
{
    m_flywheelA->SelectProfileSlot(0, 0);
    m_flywheelA->ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor);
    m_flywheelB->Follow(*m_flywheelA);
}

void Shooter::EnableShooter() {
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

void Shooter::Update() {
}

void Shooter::DashboardUpdate() {
}
}