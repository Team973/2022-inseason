#pragma once

#include <iostream>
#include <vector>

#include "lib/bases/Command.h"

using namespace std;
namespace frc973 {

/**
 * Controls the SequentialCommand structure.
 */
class SequentialCommand : public Command {
public:
    /**
     * Construct a SequentialCommand structure.
     * @param cmdList The std::vector of commands to be run.
     */
    SequentialCommand(std::vector<Command*> cmdList);

    /**
     * Executes when WaitCommand starts.
     */
    void Init() override;

    /**
     * Runs SequentialCommand.
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
    unsigned int m_currIndex;
    bool m_needsInit;
};
}