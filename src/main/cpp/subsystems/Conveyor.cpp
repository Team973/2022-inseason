#include "src/subsystems/Conveyor.h"

namespace frc973 {

Conveyor::Conveyor()
        : m_towerState(TowerState::Off)
        , m_floorState(FloorState::Off)
        , m_reindexingStartTime(0)
        , m_lastB(false)
        , m_hasStartedReindexing(false)
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
            break;
        case TowerState::FeedIn:
            break;
        case TowerState::FeedOut:
            break;
        case TowerState::Manual:
            break;
    }

    switch (m_floorState) {  
        case FloorState::FeedIn:
            break;
        case FloorState::FeedOut:
            break;
        case FloorState::Manual:
            break;
        case FloorState::Off:
            break;
    }
}

void Conveyor::DashboardUpdate() {
}

void Conveyor::SetQueuerWheel(double speed) {
}

void Conveyor::SetTowerSpeed(double speed) {
}

void Conveyor::SetFloorSpeed(double speed) {
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