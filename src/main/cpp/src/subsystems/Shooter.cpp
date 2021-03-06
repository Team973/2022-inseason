#include "src/subsystems/Shooter.h"

namespace frc973 {

Shooter::Shooter(TalonFX *flywheelA, TalonFX *flywheelB)
        : m_flywheelA(flywheelA)
        , m_flywheelB(flywheelB)
        , m_flywheelRPMSetpoint(TARMAC_FLYWHEEL_RPM_SETPOINT)
        , m_flywheelTrackingRPMSetpoint(TARMAC_FLYWHEEL_RPM_SETPOINT)
        , m_flywheelShoopRPMSetpoint(SHOOP_RPM_CLOSE)
        , m_flywheelSpeed(0.0)
        , m_shooterState(ShooterState::Off)
        , m_shooterStatus("off")
        , m_currentLimit(SupplyCurrentLimitConfiguration(true, 40, 50, 0.05))
        , m_statorLimit(StatorCurrentLimitConfiguration(true, 80, 100, 0.05)) {
    // Factory Defualt
    m_flywheelA->ConfigFactoryDefault();
    m_flywheelB->ConfigFactoryDefault();

    // Motor Directions
    m_flywheelA->SetInverted(TalonFXInvertType::Clockwise);
    m_flywheelB->SetInverted(TalonFXInvertType::CounterClockwise);

    // Neutral Mode
    m_flywheelA->SetNeutralMode(NeutralMode::Coast);
    m_flywheelB->SetNeutralMode(NeutralMode::Coast);

    // Current limits
    m_flywheelA->ConfigSupplyCurrentLimit(m_currentLimit);
    m_flywheelA->ConfigStatorCurrentLimit(m_statorLimit);

    m_flywheelB->ConfigSupplyCurrentLimit(m_currentLimit);
    m_flywheelB->ConfigStatorCurrentLimit(m_statorLimit);

    // Deadband config
    m_flywheelA->ConfigNeutralDeadband(0.01);
    m_flywheelB->ConfigNeutralDeadband(0.01);

    // Set motor to follow A
    m_flywheelB->Follow(*m_flywheelA);

    // Motor feedback
    m_flywheelA->ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 30);

    // Ramp rate
    m_flywheelA->ConfigClosedloopRamp(0.0);

    // Voltage Compensation
    m_flywheelA->ConfigVoltageCompSaturation(12.0);
    m_flywheelA->EnableVoltageCompensation(true);

    // Velocity PID Parameters
    m_flywheelA->Config_kP(0, 0.025, 30);
    m_flywheelA->Config_kI(0, 0.0, 30);
    m_flywheelA->Config_kD(0, 0.000, 30);
    m_flywheelA->Config_kF(0, 0.048, 30);

    m_flywheelB->SetStatusFramePeriod(Status_1_General, 255);
    m_flywheelB->SetStatusFramePeriod(Status_2_Feedback0, 255);
}

void Shooter::Update() {
    m_flywheelSpeed = std::clamp(m_flywheelSpeed, -0.2, 0.2);

    switch (m_shooterState) {
        case ShooterState::Off:
            m_flywheelA->Set(ControlMode::PercentOutput, 0.0);
            m_shooterStatus = "off";
            break;
        case ShooterState::Fixed:
            m_flywheelA->Set(ControlMode::Velocity, m_flywheelRPMSetpoint / FLYWHEEL_VELOCITY_RPM);
            m_shooterStatus = "fixed";
            break;
        case ShooterState::Tracking:
            m_flywheelA->Set(ControlMode::Velocity, m_flywheelTrackingRPMSetpoint / FLYWHEEL_VELOCITY_RPM);
            m_shooterStatus = "tracking";
            break;
        case ShooterState::Shoop:
            m_flywheelA->Set(ControlMode::Velocity, m_flywheelShoopRPMSetpoint / FLYWHEEL_VELOCITY_RPM);
            m_shooterStatus = "Shoop";
            break;
        case ShooterState::Manual:
            m_flywheelA->Set(ControlMode::PercentOutput, m_flywheelSpeed);
            m_shooterStatus = "manual";
            break;
        default:
            m_flywheelA->Set(ControlMode::PercentOutput, 0.0);
            m_shooterStatus = "default";
            break;
    }
}

void Shooter::DashboardUpdate() {
    SmartDashboard::PutNumber("S flywheel rpm", m_flywheelA->GetSelectedSensorVelocity() * FLYWHEEL_VELOCITY_RPM);
    SmartDashboard::PutNumber("S flywheel rpm setpoint", m_flywheelTrackingRPMSetpoint);
    SmartDashboard::PutNumber("S FlywheelA temp", m_flywheelA->GetTemperature());
    SmartDashboard::PutNumber("S FlywheelB temp", m_flywheelB->GetTemperature());

    SmartDashboard::PutNumber("S stator", m_flywheelA->GetStatorCurrent());
    SmartDashboard::PutNumber("S supply", m_flywheelA->GetSupplyCurrent());
}

void Shooter::SetShooterState(ShooterState state) {
    m_shooterState = state;
}

Shooter::ShooterState Shooter::GetShooterState() {
    return m_shooterState;
}

void Shooter::SetFlywheelRPM(double setpoint) {
    m_flywheelRPMSetpoint = setpoint;
}

void Shooter::SetTrackingFlywheelRPM(double setpoint) {
    m_flywheelTrackingRPMSetpoint = setpoint;
}

void Shooter::SetShoopFlywheelRPM(double setpoint) {
    m_flywheelShoopRPMSetpoint = setpoint;
}

void Shooter::SetFlywheelSpeed(double speed) {
    m_flywheelSpeed = -speed;  // speed inverted
}

bool Shooter::IsAtSpeed() {
    switch (m_shooterState) {
        case ShooterState::Off:
            return true;
            break;
        case ShooterState::Fixed:
            return std::abs((m_flywheelA->GetSelectedSensorVelocity() * FLYWHEEL_VELOCITY_RPM) -
                            (m_flywheelRPMSetpoint)) < 80;
            break;
        case ShooterState::Tracking:
            return std::abs((m_flywheelA->GetSelectedSensorVelocity() * FLYWHEEL_VELOCITY_RPM) -
                            (m_flywheelTrackingRPMSetpoint)) < 80;
            break;
        case ShooterState::Shoop:
            return std::abs((m_flywheelA->GetSelectedSensorVelocity() * FLYWHEEL_VELOCITY_RPM) -
                            (m_flywheelShoopRPMSetpoint)) < 80;
            break;
        case ShooterState::Manual:
            return true;
            break;
        default:
            return true;
            break;
    }
}

void Shooter::EnableShooter() {
    m_shooterState = ShooterState::Fixed;
}

void Shooter::DisableShooter() {
    m_shooterState = ShooterState::Off;
}
}  // namespace frc973
