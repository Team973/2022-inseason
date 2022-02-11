#pragma once

#include "lib/bases/Command.h"

namespace frc973 {
using namespace Util;

/**
 * The command to wait.
 */
class WaitCommand : public Command {
public:
    /**
     * Constructs WaitCommand.
     * @param targetTime The time to wait in miliseconds.
     */
    WaitCommand(uint32_t targetTime);

    /**
     * Executes when WaitCommand starts.
     */
    void Init() override;

    /**
     * Runs WaitCommand.
     */
    void Run() override;

    /**
     * Checks if the command is finished.
     * @return if the target time has elapsed or not.
     */
    bool IsCompleted() override;

private:
    uint32_t m_targetTime;
};
}
