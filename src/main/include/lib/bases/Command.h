#pragma once
#include "lib/Util.h"
namespace frc973 {

/**
 * The Command base class.
 */
class Command {
public:
    /**
     * Calculated timer's elapsed time.
     * @return If the target time has been reached.
     */
    bool HasElapsed() {
        bool hasElapsed = Util::GetMsecTime() - m_startMSec >= m_targetMSec;

        return hasElapsed;
    }

    /**
     * Executes when the Command starts.
     */
    virtual void Init() {
    }

    /**
     * Runs the Command.
     */
    virtual void Run() {
    }
    /**
     * Checks if the command is finished.
     * @return false when command doesn't end.
     */
    virtual bool IsCompleted() {
        return false;
    }

    /**
     * Executes when the command ends.
     */
    virtual void PostExecute() {
    }

    /**
     * Sets the target time and starts the timer.
     * @param target the target time.
     */
    void SetTargetMSec(uint32_t target) {
        m_targetMSec = target;
        m_startMSec = Util::GetMsecTime();
    }

protected:
    uint32_t m_targetMSec;
    uint32_t m_startMSec;
};
}