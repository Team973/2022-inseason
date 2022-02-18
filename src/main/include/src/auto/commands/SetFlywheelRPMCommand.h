#pragma once

#include "lib/bases/Command.h"
#include "src/subsystems/Shooter.h"

namespace frc973 {

/**
 * The example command. Functionally equivalent to WaitCommand.
 */
class SetFlywheelRPMCommand : public Command {
public:
    /**
     * Constructs SetFlywheelRPMCommand.
     * @param shooter The shooter subsystem.
     * @param setpoint The rpm to set the shooter to.
     * @param targetTime The time to wait in milliseconds.
     */
    SetFlywheelRPMCommand(Shooter *shooter, double setpoint, u_int32_t targetTime);

    /**
     * Executes when SetFlywheelRPMCommand starts.
     */
    void Init() override;

    /**
     * Runs SetFlywheelRPMCommand.
     */
    void Run() override;

    /**
     * Checks if the command is finished.
     * @return if the target time has elapsed or not.
     */
    bool IsCompleted() override;

    /**
     * Executes when SetFlywheelRPMCommand concludes.
     */
    void PostExecute() override;

private:
    Shooter *m_shooter;
    double m_setpoint;
    u_int32_t m_targetTime;
};
}