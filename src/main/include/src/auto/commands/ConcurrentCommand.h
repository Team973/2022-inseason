#pragma once

#include <iostream>
#include <vector>

#include "lib/bases/Command.h"

using namespace std;
namespace frc973 {

/**
 * Controls the ConcurrentCommand structure.
 */
class ConcurrentCommand : public Command {
public:
    /**
     * Construct a ConcurrentCommand structure.
     * @param cmdList The std::vector of commands to be run.
     */
    ConcurrentCommand(std::vector<Command*> cmdList);

    /**
     * Executes when WaitCommand starts.
     */
    void Init() override;

    /**
     * Runs ConcurrentCommand.
     */
    void Run() override;

    /**
     * Checks if the command is finished.
     * @return false when command doesn't end.
     */
    bool IsCompleted() override;

    /**
     * Executes when the command ends.
     */
    void PostExecute() override;

private:
    std::vector<Command*> m_cmdList;
    bool m_allDone;
};
}