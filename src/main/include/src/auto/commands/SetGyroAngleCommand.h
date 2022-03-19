#pragma once

#include "lib/bases/Command.h"
#include "lib/sensors/Gyro.h"

namespace frc973 {

class SetGyroAngleCommand : public Command {
public:
    /**
     * Constructs the SetGyroAngleCommand.
     * @param gyro The gyro subsystem.
     * @param targetTime the target amount of time to run the gyro.
     */
    SetGyroAngleCommand(Gyro *gyro, double setAngle, uint32_t targetTime); 

    /**
     * Executes when SetGyroAngleCommand starts.
     */
    void Init() override;

    /**
     * Runs SetGyroAngleCommand.
     */
    void Run() override;

    /**
     * Checks if the command is finished.
     * @return if the target time has elapsed or not.
     */
    bool IsCompleted() override;

    /**
     * Executes after SetGyroAngleCommand concludes.
     */
    void PostExecute() override;

private:
    Gyro *m_gyro;
    double m_setAngle;
    uint32_t m_targetTime;
};
}