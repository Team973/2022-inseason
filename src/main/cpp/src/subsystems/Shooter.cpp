#include "src/subsystems/Shooter.h"

namespace frc973 {

Shooter::Shooter(WPI_TalonFX *flywheelA, WPI_TalonFX *flywheelB)
        : m_flywheelA(flywheelA)
        , m_flywheelB(flywheelB)
        , m_flywheelRPMSetpoint(TARMAC_FLYWHEEL_RPM_SETPOINT)
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

    // Velocity PID Parameters
    m_flywheelA->Config_kP(0, 0.2, 30);
    m_flywheelA->Config_kI(0, 0.0, 30);
    m_flywheelA->Config_kD(0, 0.0, 30);
    m_flywheelA->Config_kF(0, 0.0444, 30);
}

void Shooter::Update() {
    m_flywheelSpeed = std::clamp(m_flywheelSpeed, -0.2, 0.2);

    switch (m_shooterState) {
        case ShooterState::Off:
            m_flywheelA->Set(ControlMode::PercentOutput, 0.0);
            m_shooterStatus = "off";
            break;
        case ShooterState::Fixed:
            m_flywheelA->Set(ControlMode::Velocity, TARMAC_FLYWHEEL_RPM_SETPOINT / FLYWHEEL_VELOCITY_RPM);
            m_shooterStatus = "fixed";
            break;
        case ShooterState::Tracking:
            m_flywheelA->Set(ControlMode::Velocity, m_flywheelRPMSetpoint / FLYWHEEL_VELOCITY_RPM);
            m_shooterStatus = "tracking";
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
    frc::SmartDashboard::PutNumber("S Flywheel rpm", m_flywheelA->GetSelectedSensorVelocity() * FLYWHEEL_VELOCITY_RPM);
    SmartDashboard::PutNumber("S flywheel rpm setpoint", m_flywheelRPMSetpoint);
    SmartDashboard::PutNumber("S flywheel speed", m_flywheelSpeed);
    SmartDashboard::PutString("S flywheel state", m_shooterStatus);
    SmartDashboard::PutNumber("S stator current", m_flywheelA->GetStatorCurrent());
    SmartDashboard::PutNumber("S supply current", m_flywheelA->GetSupplyCurrent());
    frc::SmartDashboard::PutNumber("S FlywheelA temp",m_flywheelA->GetTemperature());
    frc::SmartDashboard::PutNumber("S FlywheelB temp",m_flywheelB->GetTemperature());
}

void Shooter::SetShooterState(ShooterState state) {
    m_shooterState = state;
}

void Shooter::SetFlywheelRPM(double setpoint) {
    m_flywheelRPMSetpoint = setpoint;
}

void Shooter::SetFlywheelSpeed(double speed) {
    m_flywheelSpeed = -speed;  // speed inverted
}

bool Shooter::IsAtSpeed() {
    return (m_flywheelA->GetSelectedSensorVelocity() * FLYWHEEL_VELOCITY_RPM) > (m_flywheelRPMSetpoint - 50);
}

void Shooter::EnableShooter() {
    m_shooterState = ShooterState::Fixed;
}

void Shooter::DisableShooter() {
    m_shooterState = ShooterState::Off;
}
}  // namespace frc973
