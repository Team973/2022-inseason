#pragma once

#include "lib/bases/Command.h"
#include "src/subsystems/Shooter.h"

namespace frc973 {

/**
 * The example command. Functionally equivalent to WaitCommand.
 */
class ShooterCommand : public Command {
public:
    /**
     * Constructs ShooterCommand.
     * @param shooter The shooter subsystem.
     * @param targetTime The time to wait in milliseconds.
     */
    ShooterCommand(Shooter *shooter, Shooter::ShooterState shooterState, u_int32_t targetTime);

    /**
     * Executes when ShooterCommand starts.
     */
    void Init() override;

    /**
     * Runs ShooterCommand.
     */
    void Run() override;

    /**
     * Checks if the command is finished.
     * @return if the target time has elapsed or not.
     */
    bool IsCompleted() override;

    /**
     * Executes when ShooterCommand concludes.
     */
    void PostExecute() override;

private:
    Shooter *m_shooter;
    Shooter::ShooterState m_shooterState;
    u_int32_t m_targetTime;
};
}