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
    PositionDriveCommand(Drive *drive, double targetDist, double targetAngle, double speed, uint32_t targetTime);

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

    double m_targetDist;
    double m_targetAngle;
    double m_speed;

    uint32_t m_targetTime;

    bool m_endRun;
};
}  // namespace frc973