#pragma once

#include "lib/bases/Command.h"
#include "src/subsystems/Intake.h"

namespace frc973 {
/**
 * The command to run the intake.
 */
class RunIntakeCommand : public Command {
public:
    /**
     * Constructs the run intake command.
     * @param intake The intake subsystem.
     * @param speed The intake speed to set.
     * @param targetTime the target amount of time to run the intake.
     */
    RunIntakeCommand(Intake *intake, double speed, uint32_t targetTime);

    /**
     * Executes when RunIntakeCommand starts.
     */
    void Init() override;

    /**
     * Runs RunIntakeState.
     */
    void Run() override;

    /**
     * Checks if the command is finished
     * @return whether or not the target time has elapsed.
     */
    bool IsCompleted() override;

    /**
     * Executes after RunIntakeCommand concludes.
     */
    void PostExecute() override;

private:
    Intake *m_intake;
    double m_speed;
    uint32_t m_targetTime;
};
}  // namespace frc973