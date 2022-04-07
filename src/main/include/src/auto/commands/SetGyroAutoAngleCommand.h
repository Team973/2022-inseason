#pragma once

#include "lib/bases/Command.h"
#include "src/subsystems/Gyro.h"

namespace frc973 {

class SetGyroAutoAngleCommand : public Command {
public:
    /**
     * Constructs the SetGyroAngleCommand.
     * @param gyro The gyro subsystem.
     * @param autoAngle The angle offset of the start of auto.
     */
    SetGyroAutoAngleCommand(Gyro *gyro, double autoAngle);

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
    double m_autoAngle;
};
}  // namespace frc973