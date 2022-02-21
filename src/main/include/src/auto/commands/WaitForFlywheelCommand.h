#pragma once

#include "lib/bases/Command.h"

#include "src/subsystems/Shooter.h"

namespace frc973 {

/**
 * Command to wait for the flywheel to get to speed.
 */
class WaitForFlywheelCommand : public Command {
public:
    /**
     * Constructs the WaitForFlywheelCommand.
     * @param shooter The shooter subsystem.
     */
    WaitForFlywheelCommand(Shooter *shooter, u_int32_t targetTime);

    /**
     * Executes when WaitForFlywheelCommand starts.
     */
    void Init() override;

    /**
     * Runs WaitForFlywheelCommand.
     */
    void Run() override;

    /**
     * Checks if the command is finished.
     * @return if the target time has elapsed or not.
     */
    bool IsCompleted() override;

    /**
     * Executes after WaitForFlywheelCommand concludes.
     */
    void PostExecute() override;

private:
    Shooter *m_shooter;
    uint32_t m_targetTime;
};

}  // namespace frc973