#pragma once

#include "lib/bases/Command.h"
#include "src/subsystems/Turret.h"

namespace frc973 {

class SetTurretAngleCommand : public Command {
public:
    /**
     * Constructs the SetTurretAngleCommand.
     * @param turret The turret subsystem.
     * @param targetTime the target amount of time to run the gyro.
     */
    SetTurretAngleCommand(Turret *turret, double setAngle, uint32_t targetTime);

    /**
     * Executes when SetTurretAngleCommand starts.
     */
    void Init() override;

    /**
     * Runs SetTurretAngleCommand.
     */
    void Run() override;

    /**
     * Checks if the command is finished.
     * @return if the target time has elapsed or not.
     */
    bool IsCompleted() override;

    /**
     * Executes after SetTurretAngleCommand concludes.
     */
    void PostExecute() override;

private:
    Turret *m_turret;
    double m_setAngle;
    uint32_t m_targetTime;
};
}  // namespace frc973