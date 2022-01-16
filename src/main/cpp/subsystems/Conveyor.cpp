#include "src/subsystems/Conveyor.h"

namespace frc973 {

Conveyor::Conveyor(TalonSRX *towerMotor, TalonSRX *floorMotor)
        : m_towerMotor(towerMotor)
        , m_floorMotor(floorMotor)
        , m_towerState(TowerState::Off)
        , m_floorState(FloorState::Off)
        , m_manualTowerSpeed(0.0)
        , m_manualFloorSpeed(0.0) {
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
            m_towerMotor->Set(ControlMode::PercentOutput, 0.0);
            break;
        case TowerState::FeedIn:
            m_towerMotor->Set(ControlMode::PercentOutput, 1.0);
            break;
        case TowerState::FeedOut:
            m_towerMotor->Set(ControlMode::PercentOutput, -1.0);
            break;
        case TowerState::Manual:
            m_towerMotor->Set(ControlMode::PercentOutput, m_manualTowerSpeed);
            break;
    }

    switch (m_floorState) {  
        case FloorState::FeedIn:
            m_floorMotor->Set(ControlMode::PercentOutput, 1.0);
            break;
        case FloorState::FeedOut:
            m_floorMotor->Set(ControlMode::PercentOutput, -1.0);
            break;
        case FloorState::Manual:
            m_floorMotor->Set(ControlMode::PercentOutput, m_manualFloorSpeed);
            break;
        case FloorState::Off:
            m_floorMotor->Set(ControlMode::PercentOutput, 0.0);
            break;
    }
}

void Conveyor::DashboardUpdate() {
}

void Conveyor::SetTowerSpeed(double speed) {
    m_towerMotor->Set(ControlMode::PercentOutput, speed);
}

void Conveyor::SetFloorSpeed(double speed) {
    m_floorMotor->Set(ControlMode::PercentOutput, speed);
}

float Conveyor::getTowerState() {
    float state = 0.0;
    switch (m_towerState) {   
        case TowerState::Off:
            state = 0.0;
            break;
        case TowerState::FeedIn:
            state = 1.0;
            break;
        case TowerState::FeedOut:
            state = 2.0;
            break;
        case TowerState::Manual:
            state = 3.0;
            break;
    }
}
float Conveyor::getFloorState() {
    float state = 0.0;
    switch (m_floorState) {  
        case FloorState::FeedIn:
            state += 0.0;
            break;
        case FloorState::FeedOut:
            state += 0.1;
            break;
        case FloorState::Manual:
            state += 0.2;
            break;
        case FloorState::Off:
            state += 0.3;
            break;
    }
    return state;
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
}