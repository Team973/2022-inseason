#pragma once

#include <frc/smartdashboard/SmartDashboard.h>

#include <iostream>
#include <vector>

#include "lib/bases/Command.h"

namespace frc973 {

/**
 * Controls the AutoMode.
 */
class AutoMode {
public:
    /**
     * Construct an AutoMode.
     * @param cmdList The std::vector of commands to be run.
     */
    AutoMode(std::vector<Command *> cmdList);

    /**
     * Runs AutoMode.
     */
    void Run();

    /**
     * Checks if the command is finished.
     * @return false when command doesn't end.
     */
    bool IsCompleted();

    /**
     * Get the current command index.
     * @return index
     */
    unsigned int GetCurrentCommandIndex() const {
        return m_currIndex;
    }

    AutoMode operator+(const AutoMode &other) {
        AutoMode a = AutoMode({this->m_cmdList.begin(), this->m_cmdList.end()});
        a.m_cmdList.insert(a.m_cmdList.end(), other.m_cmdList.begin(), other.m_cmdList.end());
        return a;
    }

private:
    std::vector<Command *> m_cmdList;
    unsigned int m_currIndex;
    bool m_needsInit;
};
}  // namespace frc973