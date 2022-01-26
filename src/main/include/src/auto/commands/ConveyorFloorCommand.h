#pragma once

#include "lib/bases/Command.h"
#include "src/subsystems/Conveyor.h"

namespace frc973 {

class ConveyorFloorCommand : public Command {
public:
    /**
     * Constructs the conveyor floor command.
     * @param floorState the conveyors current floor state.
     * @param targetTime the target amount of time to run the conveyor.
     */
    ConveyorFloorCommand(Conveyor *conveyor, Conveyor::FloorState floorState, uint32_t targetTime); 

    /**
     * Executes when ConveyorFloorCommand starts.
     */
    void Init() override;

    /**
     * Runs ConveyorFloorCommand.
     */
    void Run() override;

    /**
     * Checks if the command is finished.
     * @return if the target time has elapsed or not.
     */
    bool IsCompleted() override;

    /**
     * Executes after ConveyorFloorCommand concludes.
     */
    void PostExecute() override;

private:
    Conveyor *m_conveyor;
    Conveyor::FloorState m_conveyorFloorState;
    uint32_t m_targetTime;
};
}