#pragma once

#include "lib/bases/Command.h"
#include "lib/util/Util.h"
#include "src/subsystems/Drive.h"

namespace frc973 {
using namespace Util;

class PositionDriveCommand : public Command {
public:
    /**
     * Constructs PositionDriveCommand.
     * @param drive The drive subsystem.
     */
    PositionDriveCommand(Drive *drive, uint32_t targetTime);

    /**
     * Executes when PositionDriveCommand starts.
     */
    void Init() override;

    /**
     * Runs PositionDriveCommand.
     * @return true when command ends.
     */
    void Run() override;

    /**
     * Checks if the command is finished.
     * @return if the target time has elapsed or not.false when command doesn't end.
     */
    bool IsCompleted() override;

    /**
     * Executes when PositionDriveCommand concludes.
     */
    void PostExecute() override;

private:
    Drive *m_drive;
    uint32_t m_targetTime;
};
}  // namespace frc973