#pragma once

#include <ctre/Phoenix.h>
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
    Drive(WPI_TalonFX *leftDriveTalonA, WPI_TalonFX *leftDriveTalonB, WPI_TalonFX *leftDriveTalonC, 
    WPI_TalonFX *rightDriveTalonA, WPI_TalonFX *rightDriveTalonB, WPI_TalonFX *rightDriveTalonC);

    /**
     * Updates this subsystem.
     */
    void Update() override;

    /**
     * Updates the dashboard every robot cycle.
     */
    void DashboardUpdate() override;

    /**
     * Set correct Left motor and Right motor outputs on drive
     */
    void Drive::ArcadeCalcOutput();
    
    /**
     * Called to update the current throttle and turn values of the joysticks
     */
    void SetThrottleTurn(double throttle, double turn);



private:
    /**
     * Checks to see if the left and right output values are valid values. Defaults to zero if they're undefined.
     */
    void CheckForIsNaN();

    WPI_TalonFX *m_leftDriveTalonA;
    WPI_TalonFX *m_leftDriveTalonB;
    WPI_TalonFX *m_leftDriveTalonC;

    WPI_TalonFX *m_rightDriveTalonA;
    WPI_TalonFX *m_rightDriveTalonB;
    WPI_TalonFX *m_rightDriveTalonC;

    DriveMode m_driveMode;

    double m_leftOutput;
    double m_rightOutput;

    double m_throttle;
    double m_turn;

    SupplyCurrentLimitConfiguration m_currentLimit;
    StatorCurrentLimitConfiguration m_statorLimit;

};

} //namespace frc973
