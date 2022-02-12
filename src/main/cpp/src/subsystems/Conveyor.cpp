#include "src/subsystems/Conveyor.h"

namespace frc973 {

Conveyor::Conveyor(TalonSRX *towerMotorA, TalonSRX *towerMotorB, TalonSRX *floorMotor)
        : m_towerMotorA(towerMotorA)
        , m_towerMotorB(towerMotorB)
        , m_floorMotor(floorMotor)
        , m_towerState(TowerState::Off)
        , m_floorState(FloorState::Off)
        , m_manualTowerSpeed(0.0)
        , m_manualFloorSpeed(0.0) {
    m_floorMotor->SetInverted(true);
    m_towerMotorB->Follow(*m_towerMotorA);
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
            m_towerMotorA->Set(ControlMode::PercentOutput, 0.0);
            break;
        case TowerState::FeedIn:
            m_towerMotorA->Set(ControlMode::PercentOutput, 0.7);
            break;
        case TowerState::FeedOut:
            m_towerMotorA->Set(ControlMode::PercentOutput, -0.7);
            break;
        case TowerState::Manual:
            m_towerMotorA->Set(ControlMode::PercentOutput, m_manualTowerSpeed);
            break;
    }

    switch (m_floorState) {
        case FloorState::Off:
            m_floorMotor->Set(ControlMode::PercentOutput, 0.0);
            break;
        case FloorState::FeedIn:
            m_floorMotor->Set(ControlMode::PercentOutput, 0.7);
            break;
        case FloorState::FeedOut:
            m_floorMotor->Set(ControlMode::PercentOutput, -0.7);
            break;
        case FloorState::Manual:
            m_floorMotor->Set(ControlMode::PercentOutput, m_manualFloorSpeed);
            break;
    }

}

void Conveyor::DashboardUpdate() {
    frc::SmartDashboard::PutNumber("Conveyor Tower A", m_towerMotorA->GetOutputCurrent());
    frc::SmartDashboard::PutNumber("Conveyor Tower B", m_towerMotorB->GetOutputCurrent());
    frc::SmartDashboard::PutNumber("Conveyor Floor Motor", m_towerMotorA->GetOutputCurrent());
    frc::SmartDashboard::PutNumber("Conveyor Tower A", m_towerMotorA->GetMotorOutputPercent());
    frc::SmartDashboard::PutNumber("Conveyor Tower B", m_towerMotorB->GetMotorOutputPercent());
    frc::SmartDashboard::PutNumber("Conveyor Floor Motor", m_towerMotorA->GetMotorOutputPercent());
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