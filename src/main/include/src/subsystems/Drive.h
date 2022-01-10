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

    /**
     * Gets the position of the left set of motors.
     * @return the position.
     */
    double GetLeftPosition() const;

    /**
     * Gets the position of the right set of motors.
     * @return the position.
     */
    double GetRightPosition() const;

    /**
     * Gets the average betweeen left and right positions.
     * @return the average.
     */
    double GetPos() const;

    /**
     * Zeros the left and right drive positions.
     */
    void Zero();

    /**
     * Gets the velocity in inches per second for the left drive.
     * @return the velocity.
     */
    double GetLeftRate() const;

    /**
     * Gets the velocity in inches per second for the right drive.
     * @return the velocity.
     */
    double GetRightRate() const;

    /**
     * Gets the average velocity in inches per second for the drive.
     * @return the velocity.
     */
    double GetRate() const;

    /**
     * Gets the velocity in inches per second for turning.
     * @return the velocity.
     */
    double GetAngularRate() const;

    /**
     * Sets the position to go to.
     * @param linearPositionTarget Target distance in inches.
     * @param anglePositionTarget Target angle.
     */
    void SetPositionTarget(double linearPositionTarget, double anglePositionTarget);

    /**
     * Drive the robot a given distance.
     * @param inches The distance to travel in inches.
     */
    void SetDrivePositionInches(double inches);

    /**
     * Sets the percentage output for left and right TalonFXs.
     * @param leftOutput The percent output for the left TalonFXs.
     * @param rightOutput The percent output for the right TalonFXs.
     */
    void SetPercentOutput(double leftOutput, double rightOutput);

    /**
     * Sets the speed target for the left and right TalonFXs.
     * @param leftOutput The left velocity target in ticks/100ms.
     * @param rightOutput The right velocity target in ticks/100ms.
     */
    void SetVelocity(double leftOutput, double rightOutput);

    /**
     * Enables brake mode on falcons.
     */
    void EnableBrakeMode();

    /**
     * Enables coast mode on falcons.
     */
    void EnableCoastMode();

    /**
     * Sets the universal throttle and turn values, and clamps them between -1.0 and 1.0.
     * @param throttle The value to set throttle to.
     * @param turn The value to set turn to.
     */
    void SetThrottleAndTurn(const double throttle, const double turn);

    /**
     * Sets the drive mode/the controller to use.
     * @param mode The drive mode to begin using.
     */
    void SetDriveMode(DriveMode mode);

    /**
     * Determines if the drive mode thats selected has reached its target.
     * @return If the target has been reached or not.
     */
    bool OnTarget();

    /**
     * Set quick turn on or off
     * @param state true or false, on or off
     */
    void SetQuickTurn(bool state);

    /**
     * Set high gear on or off
     * @param state true or false, on or off
     */
    void SetHighGear(bool state);

    /**
     * Checks for limelight on target with a tolerance.
     * @param tolerance The tolerance in degrees to use.
     * @return true or false on if its on target.
     */
    bool LimelightOnTargetWithinTolerance(double tolerance);

    /**
     * Clamp the drive motor speed.
     * @param minSpeed The minimum speed to limit to.
     * @param maxSpeed The maximum speed to limit to.
     */
    void ClampSpeed(double minSpeed, double maxSpeed);

    /**
     * Checks to see if limelight has disconnected.
     * @return true or false on if its disconnected.
     */
    bool IsLimelightDead();


private:
    /**
     * Checks to see if the left and right output values are valid values. Defaults to zero if they're undefined.
     */
    void CheckForIsNaN();

    DriveMode m_driveMode;

    double m_throttle;
    double m_turn;

    double m_leftOutput;
    double m_rightOutput;

    double m_linearPositionTarget;
    double m_anglePositionTarget;
    double m_angularRate;

    double m_leftPosZero;
    double m_rightPosZero;

    double m_minSpeed;
    double m_maxSpeed;

    double m_previousLatency;

};















} //namespace frc973
