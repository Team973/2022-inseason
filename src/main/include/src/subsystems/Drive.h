#pragma once

#include <array>
#include <ctre/Phoenix.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/kinematics/DifferentialDriveKinematics.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "lib/bases/Subsystem.h"
#include "lib/util/Util.h"
#include "lib/helpers/PID.h"
#include "src/RobotInfo.h"

namespace frc973 {

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
    enum class DriveMode {
        arcade,   /**< The arcade drive mode. */
        position, /**< The position drive mode. */
        cheesy,   /**< The cheesy drive mode. */
    };

    /**
     * Enum used for position drive
     */
    enum Target {
        angle = 0,
        dist = 1,
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
     * Called to update the current throttle and turn values of the joysticks
     */
    void SetThrottleTurn(double throttle, double turn);

    /**
     * Set Left/Right motor outputs using Arcade Drive.
     */
    void ArcadeCalcOutput();

    /**
     * Set Left/Right motor outputs using Cheesy Drive.
     */
    void CheesyCalcOutput();

    /**
     * Set Left/Right motor outputs using Position Drive.
     */
    void PositionCalcOutput();

    /**
     * Set the drive mode
     * @param mode the drive mode
     */ 
    void SetDriveMode(DriveMode mode);

    /**
     * Sets current angle of drive
     */
    void SetAngle(double angle);

    /**
     * Sets current position of drive
     */
    void SetPosition(double position);

    /**
     * Sets current pose of drive
     */
    void SetPose(Pose2d pose);

    /**
     * Sets quickturn true = turn in place
     */
    void SetQuickTurn(bool QT);

    // test del later
    double GetRightOuput();

    // test del later
    double GetLeftOuput();

    /**
     * Return the average of the left and right motor speeds
     */
    double GetVelocity();

    /**
     * Clamps the speed of the motors
     * @param minSpeed the minimum speed
     * @param maxSpeed the maximum speed
     */
    void ClampSpeed(double minSpeed, double maxSpeed);

    /**
     * Zeros the drive motors
     */ 
    void Zero();

    /**
     * Zeros the current drive positions
     */
    void ZeroPosition();

    /**
     * Set Drive to chosen mode (coast or break)
     * @param mode the chosen mode
     */
    void SetNeutralMode(NeutralMode mode);

    /**
     * Sets the target position
     * @param dist target distance
     * @param angle target angle
     */
    void SetPositionTarget(double dist, double angle);

    /**
     * Checks if the drive is on target
     * @return true if the drive is on target
     */
    std::array<bool, 2> &PositionOnTarget();

    /**
     * Checks if the drive in on target
     * @param dist the target distance tolerance
     * @param distRate the velocity tolerance
     * @param angle the target angle tolerance
     * @param angleRate the anglular rate tolerance
     * @return if the drive is on target within tolerance
     */
    std::array<bool, 2> &PositionOnTargetWithTolerance(const double dist, const double distRate, const double angle,
                                                       const double angleRate);

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

    double m_minSpeed;
    double m_maxSpeed;

    double m_gyroAngle;

    SupplyCurrentLimitConfiguration m_currentLimit;
    StatorCurrentLimitConfiguration m_statorLimit;

    bool m_isQuickTurn;
    DriveMode m_driveMode;

    units::meter_t m_xPos;
    units::meter_t m_yPos;
    units::degree_t m_theta;
    Translation2d m_translation2D;
    Rotation2d m_rotation2D;
    Pose2d m_drivePose;
    units::meter_t m_driveWidth;
    DifferentialDriveKinematics m_driveKinimatics;
    ChassisSpeeds m_driveChassisSpeeds;
    DifferentialDriveWheelSpeeds m_driveWheelSpeeds;
    DifferentialDriveOdometry m_driveOdometry;

    PID m_positionPID;
    PID m_turnPID;

    double m_targetPos;
    double m_targetAngle;
    double m_currentPos;
    double m_currentAngle;

    double m_leftPosZero;
    double m_rightPosZero;

    double m_angularRate;
    double m_rate;

    std::array<bool, 2> m_onTarget;
};
}  // namespace frc973
