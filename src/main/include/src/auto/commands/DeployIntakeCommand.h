#pragma once

#include "lib/bases/Command.h"
#include "lib/util/Util.h"
#include "src/subsystems/Intake.h"

namespace frc973 {
using namespace Util;

/**
 * The example command. Functionally equivalent to WaitCommand.
 */
class DeployIntakeCommand : public Command {
public:
    /**
     * Constructs DeployIntakeCommand.
     * @param intake The intake subsystem.
     */
    DeployIntakeCommand(Intake *intake);

    /**
     * Executes when DeployIntakeCommand starts.
     */
    void Init() override;

    /**
     * Runs DeployIntakeCommand.
     */
    void Run() override;

    /**
     * Checks if the command is finished.
     * @return if the target time has elapsed or not.
     */
    bool IsCompleted() override;

    /**
     * Executes when DeployIntakeCommand concludes.
     */
    void PostExecute() override;

private:
    Intake *m_intake;
};
}