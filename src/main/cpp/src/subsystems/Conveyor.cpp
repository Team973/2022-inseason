#include "src/subsystems/Conveyor.h"

namespace frc973 {

Conveyor::Conveyor(TalonSRX *towerMotorA, TalonSRX *towerMotorB, TalonSRX *floorMotor)
        : m_towerMotorA(towerMotorA)
        , m_towerMotorB(towerMotorB)
        , m_floorMotor(floorMotor)
        , m_towerState(TowerState::Off)
        , m_floorState(FloorState::Off)
        , m_manualTowerSpeed(0.0)
        , m_manualFloorSpeed(0.0)
        , m_currentTowerState("Off")
        , m_currentFloorState("Off") {
    m_towerMotorA->ConfigFactoryDefault();
    m_towerMotorB->ConfigFactoryDefault();

    m_towerMotorA->SetNeutralMode(Coast);
    m_towerMotorB->SetNeutralMode(Coast);

    m_floorMotor->SetInverted(true);
    m_towerMotorA->SetInverted(true);
    m_towerMotorB->SetInverted(true);

    m_towerMotorB->Follow(*m_towerMotorA);

    m_towerMotorA->ConfigSupplyCurrentLimit(SupplyCurrentLimitConfiguration(true, 30, 60, 0.1));
    m_towerMotorB->ConfigSupplyCurrentLimit(SupplyCurrentLimitConfiguration(true, 30, 60, 0.1));
    m_floorMotor->ConfigSupplyCurrentLimit(SupplyCurrentLimitConfiguration(true, 30, 60, 0.1));

    // Voltage Compensation
    m_towerMotorA->ConfigVoltageCompSaturation(12.0);
    m_floorMotor->ConfigVoltageCompSaturation(12.0);
}

void Conveyor::Update() {
    if (m_manualTowerSpeed != 0) {
        m_towerState = TowerState::Manual;
    }

    if (m_manualFloorSpeed != 0) {
        m_floorState = FloorState::Manual;
    }

    switch (m_towerState) {
        case TowerState::Off:
            m_currentTowerState = "Off";
            m_towerMotorA->Set(ControlMode::PercentOutput, 0.0);
            break;
        case TowerState::FeedIn:
            m_currentTowerState = "FeedIn";
            m_towerMotorA->Set(ControlMode::PercentOutput, 0.5);
            break;
        case TowerState::FeedOut:
            m_currentTowerState = "FeedOut";
            m_towerMotorA->Set(ControlMode::PercentOutput, -0.7);
            break;
        case TowerState::Manual:
            m_currentTowerState = "Manual";
            m_towerMotorA->Set(ControlMode::PercentOutput, m_manualTowerSpeed);
            // m_towerMotorB->Set(ControlMode::PercentOutput, m_manualTowerSpeed);
            break;
    }

    switch (m_floorState) {
        case FloorState::Off:
            m_currentFloorState = "Off";
            m_floorMotor->Set(ControlMode::PercentOutput, 0.0);
            break;
        case FloorState::FeedIn:
            m_currentFloorState = "FeedIn";
            m_floorMotor->Set(ControlMode::PercentOutput, 0.7);
            break;
        case FloorState::FeedOut:
            m_currentFloorState = "FeedOut";
            m_floorMotor->Set(ControlMode::PercentOutput, -0.7);
            break;
        case FloorState::Manual:
            m_currentFloorState = "Manual";
            m_floorMotor->Set(ControlMode::PercentOutput, m_manualFloorSpeed);
            break;
    }
}

void Conveyor::DashboardUpdate() {
    frc::SmartDashboard::PutNumber("CO Tower A Current", m_towerMotorA->GetOutputCurrent());
    frc::SmartDashboard::PutNumber("CO Tower B Current", m_towerMotorB->GetOutputCurrent());
    frc::SmartDashboard::PutNumber("CO Floor Motor Current", m_floorMotor->GetOutputCurrent());
    frc::SmartDashboard::PutNumber("CO Tower A Percent", m_towerMotorA->GetMotorOutputPercent());
    frc::SmartDashboard::PutNumber("CO Tower B Percent", m_towerMotorB->GetMotorOutputPercent());
    frc::SmartDashboard::PutNumber("CO Floor Motor Percent", m_floorMotor->GetMotorOutputPercent());
    frc::SmartDashboard::PutString("CO Tower State", m_currentTowerState);
    frc::SmartDashboard::PutString("CO Floor State", m_currentFloorState);
}

void Conveyor::SetTowerSpeed(double speed) {
    m_towerMotorA->Set(ControlMode::PercentOutput, speed);
}

void Conveyor::SetFloorSpeed(double speed) {
    m_floorMotor->Set(ControlMode::PercentOutput, speed);
}

Conveyor::TowerState Conveyor::GetTowerState() {
    return m_towerState;
}
Conveyor::FloorState Conveyor::GetFloorState() {
    return m_floorState;
}

double Conveyor::GetFloorVelocity() {
    return m_floorMotor->GetSelectedSensorVelocity();
}

double Conveyor::GetTowerVelocity() {
    return m_towerMotorA->GetSelectedSensorVelocity();
}

void Conveyor::SetTowerState(TowerState state) {
    m_towerState = state;
}

void Conveyor::SetFloorState(FloorState state) {
    m_floorState = state;
}

void Conveyor::SetManualTowerSpeed(double speed) {
    m_manualTowerSpeed = speed;
}

void Conveyor::SetManualFloorSpeed(double speed) {
    m_manualFloorSpeed = speed;
}

}  // namespace frc973