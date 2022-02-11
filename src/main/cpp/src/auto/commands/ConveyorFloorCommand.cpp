#include "src/auto/commands/ConveyorFloorCommand.h"

namespace frc973 {

ConveyorFloorCommand::ConveyorFloorCommand(Conveyor *conveyor, Conveyor::FloorState floorState, uint32_t targetTime)
        : m_conveyorFloorState(floorState), m_targetTime(targetTime) {
}

void ConveyorFloorCommand::Init() {
    SetTargetMSec(m_targetTime);
    m_conveyor->SetFloorState(m_conveyorFloorState);
}

void ConveyorFloorCommand::Run() {
}

bool ConveyorFloorCommand::IsCompleted() {
    return HasElapsed();
}

void ConveyorFloorCommand::PostExecute() {
    m_conveyor->SetFloorState(Conveyor::FloorState::Off);
}
}