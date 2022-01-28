#pragma once

#include "lib/bases/Command.h"
#include "src/subsystems/Intake.h"

namespace frc973 {
using namespace Util;

/**
 * The RetractIntakeCommand.
 */
class RetractIntakeCommand : public Command {
public:
    /**
     * Constructs RetractIntakeCommand.
     * @param intake The intake subsystem.
     */
    RetractIntakeCommand(Intake *intake);

    /**
     * Executes when RetractIntakeCommand starts.
     */
    void Init() override;

    /**
     * Runs RetractIntakeCommand.
     */
    void Run() override;

    /**
     * Checks if the command is finished.
     * @return if the target time has elapsed or not.
     */
    bool IsCompleted() override;

    /**
     * Executes when RetractIntakeCommand concludes.
     */
    void PostExecute() override;

private:
    Intake *m_intake;
};
}