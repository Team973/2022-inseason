#pragma once

#include <ctre/Phoenix.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/kinematics/DifferentialDriveKinematics.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>

#include "lib/bases/Subsystem.h"
#include "lib/util/Util.h"
#include "src/RobotInfo.h"


namespace frc973{

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
     * */
    Drive(WPI_TalonFX *leftDriveTalonA, WPI_TalonFX *leftDriveTalonB, WPI_TalonFX *leftDriveTalonC, 
          WPI_TalonFX *rightDriveTalonA, WPI_TalonFX *rightDriveTalonB, WPI_TalonFX *rightDriveTalonC);

    /**
    * The drive subsystem mode.
    */
    enum class DriveMode
    {
        arcade,               /**< The arcade drive mode. */
        position,             /**< The position drive mode. */
        cheesyDrive,          /**< The cheesy drive mode. */
    };

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
    void ArcadeCalcOutput();

    /**
     * Set correct Left motor and Right motor outputs on drive
     */
    void CheesyCalcOutput();
    
    /**
     * Called to update the current throttle and turn values of the joysticks
     */
    void SetThrottleTurn(double throttle, double turn);

    //test del later
    double GetRightOuput();

    //test del later
    double GetLeftOuput();

    /**
     * Return the average of the left and right motor speeds
     */
    double GetVelocity();

private:
    WPI_TalonFX *m_leftDriveTalonA;
    WPI_TalonFX *m_leftDriveTalonB;
    WPI_TalonFX *m_leftDriveTalonC;

    WPI_TalonFX *m_rightDriveTalonA;
    WPI_TalonFX *m_rightDriveTalonB;
    WPI_TalonFX *m_rightDriveTalonC;

    double m_leftOutput;
    double m_rightOutput;

    double m_throttle;
    double m_turn;

    SupplyCurrentLimitConfiguration m_currentLimit;
    StatorCurrentLimitConfiguration m_statorLimit;

    bool m_isQuickTurn;
    DriveMode m_driveMode;
};
}
