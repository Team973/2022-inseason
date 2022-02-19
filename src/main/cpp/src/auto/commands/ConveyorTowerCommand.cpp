#include "src/auto/commands/ConveyorTowerCommand.h"

namespace frc973 {

ConveyorTowerCommand::ConveyorTowerCommand(Conveyor *conveyor, Conveyor::TowerState towerState, uint32_t targetTime)
        : m_conveyor(conveyor), m_conveyorTowerState(towerState), m_targetTime(targetTime) {
}

void ConveyorTowerCommand::Init() {
    SetTargetMSec(m_targetTime);
    m_conveyor->SetTowerState(m_conveyorTowerState);
}

void ConveyorTowerCommand::Run() {
}

bool ConveyorTowerCommand::IsCompleted() {
    return HasElapsed();
}

void ConveyorTowerCommand::PostExecute() {
    m_conveyor->SetTowerState(Conveyor::TowerState::Off);
}
}