#pragma once

#include "lib/bases/Command.h"
#include "lib/sensors/Limelight.h"
#include "src/subsystems/Turret.h"
#include "src/subsystems/Gyro.h"

namespace frc973 {

/**
 * The TrackingTargetCommand command.
 */
class TrackingTargetCommand : public Command {
public:
    /**
     * Constructs TrackingTargetCommand.
     * @param limeLight The lime light subsystem.
     */
    TrackingTargetCommand(Limelight *limeLight, Turret *turret, Gyro *gyro, uint32_t targetTime);

    /**
     * Executes when TrackingTargetCommand starts.
     */
    void Init() override;

    /**
     * Runs TrackingTargetCommand.
     */
    void Run() override;

    /**
     * Checks if the command is finished.
     * @return if the target time has elapsed or not.
     */
    bool IsCompleted() override;

    /**
     * Executes when TrackingTargetCommand concludes.
     */
    void PostExecute() override;

private:
    Limelight *m_limeLight;
    Turret *m_turret;
    Gyro *m_gyro;
    uint32_t m_targetTime;
};
}