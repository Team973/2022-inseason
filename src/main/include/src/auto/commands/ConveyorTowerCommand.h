#pragma once

#include "lib/bases/Command.h"
#include "src/subsystems/Conveyor.h"

namespace frc973 {

class ConveyorTowerCommand : public Command {
public:
    /**
     * Constructs the conveyor tower command.
     * @param towerState the conveyors current tower state.
     * @param targetTime the target amount of time to run the conveyor.
     */
    ConveyorTowerCommand(Conveyor *conveyor, Conveyor::TowerState towerState, uint32_t targetTime);

    /**
     * Executes when ConveyorTowerCommand starts.
     */
    void Init() override;

    /**
     * Runs ConveyorTowerCommand.
     */
    void Run() override;

    /**
     * Checks if the command is finished.
     * @return if the target time has elapsed or not.
     */
    bool IsCompleted() override;

    /**
     * Executes after ConveyorTowerCommand concludes.
     */
    void PostExecute() override;

private:
    Conveyor *m_conveyor;
    Conveyor::TowerState m_conveyorTowerState;
    uint32_t m_targetTime;
};
}  // namespace frc973