#pragma once

#include "lib/bases/Subsystem.h"

namespace frc973{

/**
 * The drive subsystem mode.
 */
enum class DriveMode
{
    arcade,               /**< The arcade drive mode. */
    position,             /**< The position drive mode. */
    cheesyDrive,          /**< The cheesy drive mode. */
};

class Drive : public Subsystem {
public:
    /**
     * Construct the Drive Subsystem.
     * @param leftDriveTalonA The first left drive TalonFX/Falcon.
     * @param leftDriveTalonB The second left drive TalonFX/Falcon.
     * @param leftDriveTalonC The third left drive TalonFX/Falcon.
     * @param rightDriveTalonA The first right drive TalonFX/Falcon.
     * @param rightDriveTalonB The second right drive TalonFX/Falcon.
     * @param rightDriveTalonC The third right drive TalonFX/Falcon.
     * @param gyro The gyro.
     * */
    Drive();

    /**
     * Updates this subsystem.
     */
    void Update() override;

    /**
     * Updates the dashboard every robot cycle.
     */
    void DashboardUpdate() override;

private:

    DriveMode m_driveMode;

};















} //namespace frc973
