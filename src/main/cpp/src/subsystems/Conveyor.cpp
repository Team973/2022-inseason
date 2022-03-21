#include "src/subsystems/Conveyor.h"

namespace frc973 {

Conveyor::Conveyor(TalonFX *towerMotor, TalonSRX *ceilingMotor, TalonSRX *floorMotor)
        : m_towerMotor(towerMotor)
        , m_ceilingMotor(ceilingMotor)
        , m_floorMotor(floorMotor)
        , m_towerState(TowerState::Off)
        , m_floorState(FloorState::Off)
        , m_manualTowerSpeed(0.0)
        , m_manualFloorSpeed(0.0)
        , m_currentTowerState("Off")
        , m_currentFloorState("Off")
        , m_readyToShoot(false) {
    m_towerMotor->ConfigFactoryDefault();
    m_ceilingMotor->ConfigFactoryDefault();

    m_towerMotor->SetNeutralMode(Coast);
    m_ceilingMotor->SetNeutralMode(Coast);

    // Motor Directions
    m_towerMotor->SetInverted(TalonFXInvertType::CounterClockwise);

    m_floorMotor->SetInverted(false);
    m_ceilingMotor->SetInverted(true);

    m_towerMotor->ConfigSupplyCurrentLimit(SupplyCurrentLimitConfiguration(true, 30, 60, 0.1));
    m_ceilingMotor->ConfigSupplyCurrentLimit(SupplyCurrentLimitConfiguration(true, 30, 60, 0.1));
    m_floorMotor->ConfigSupplyCurrentLimit(SupplyCurrentLimitConfiguration(true, 30, 60, 0.1));

    m_ceilingMotor->Follow(*m_floorMotor);

    // Voltage Compensation
    m_towerMotor->ConfigVoltageCompSaturation(12.0);
    m_towerMotor->EnableVoltageCompensation(true);
    m_floorMotor->ConfigVoltageCompSaturation(12.0);
    m_floorMotor->EnableVoltageCompensation(true);
}

void Conveyor::Update() {
    switch (m_towerState) {
        case TowerState::Off:
            m_currentTowerState = "Off";
            m_towerMotor->Set(ControlMode::PercentOutput, 0.0);
            break;
        case TowerState::FeedIn:
            m_currentTowerState = "FeedIn";
            m_towerMotor->Set(ControlMode::PercentOutput, 0.5);
            break;
        case TowerState::FeedOut:
            m_currentTowerState = "FeedOut";
            m_towerMotor->Set(ControlMode::PercentOutput, -0.5);
            break;
        case TowerState::Manual:
            m_currentTowerState = "Manual";
            m_towerMotor->Set(ControlMode::PercentOutput, m_manualTowerSpeed);
            break;
        case TowerState::Shoot:
            m_currentTowerState = "Shoot";
            if (m_readyToShoot) {
                m_towerMotor->Set(ControlMode::PercentOutput, 1.0);
            }

            m_towerMotor->Set(ControlMode::PercentOutput, 0.0);
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
        case FloorState::Shoot:
            m_currentFloorState = "Shoot";
            if (m_readyToShoot) {
                m_floorMotor->Set(ControlMode::PercentOutput, 1.0);
            }

            m_floorMotor->Set(ControlMode::PercentOutput, 0.0);
            break;
    }
}

void Conveyor::DashboardUpdate() {
    frc::SmartDashboard::PutString("CO Tower State", m_currentTowerState);
    frc::SmartDashboard::PutString("CO Floor State", m_currentFloorState);

    // frc::SmartDashboard::PutNumber("CO Tower Current", m_towerMotor->GetOutputCurrent());
    // frc::SmartDashboard::PutNumber("CO Ceiling Current", m_ceilingMotor->GetOutputCurrent());
    // frc::SmartDashboard::PutNumber("CO Floor Motor Current", m_floorMotor->GetOutputCurrent());
}

void Conveyor::SetTowerSpeed(double speed) {
    m_towerMotor->Set(ControlMode::PercentOutput, speed);
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
    return m_towerMotor->GetSelectedSensorVelocity();
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

void Conveyor::SetReadyToShoot(bool isReadyToShoot) {
    m_readyToShoot = isReadyToShoot;
}

}  // namespace frc973