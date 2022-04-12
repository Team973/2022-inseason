#pragma once

#include "lib/bases/Command.h"
#include "src/subsystems/Shooter.h"

namespace frc973 {

/**
 * The example command. Functionally equivalent to WaitCommand.
 */
class SetFlywheelTrackingCommand : public Command {
public:
    /**
     * Constructs SetFlywheelTrackingCommand.
     * @param shooter The shooter subsystem.
     * @param targetTime The time to wait in milliseconds.
     */
    SetFlywheelTrackingCommand(Shooter *shooter, u_int32_t targetTime);

    /**
     * Executes when SetFlywheelTrackingCommand starts.
     */
    void Init() override;

    /**
     * Runs SetFlywheelTrackingCommand.
     */
    void Run() override;

    /**
     * Checks if the command is finished.
     * @return if the target time has elapsed or not.
     */
    bool IsCompleted() override;

    /**
     * Executes when SetFlywheelTrackingCommand concludes.
     */
    void PostExecute() override;

private:
    Shooter *m_shooter;
    u_int32_t m_targetTime;
};
}