#pragma once

#include <ctre/Phoenix.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DigitalInput.h>
#include <cmath>

#include "lib/util/Constants.h"
#include "lib/bases/Subsystem.h"
#include "lib/helpers/PID.h"
#include "lib/util/Constants.h"
#include "src/RobotInfo.h"

namespace frc973 {

/**
 * The set of intake states; deployed or retracted.
 */
enum class TurretState {
    Off,     /**< Disables turret. */
    Manual,  /**< Manual turret control. */
    Shoop,   /**< Shoop angle turret tracking. */
    Tracking /**< Limelight targeting mode. */
};

class Turret : public Subsystem {
public:
    Turret(TalonFX *turretMotor, DigitalInput *talonSensor);

    /**
     * Sets turret state
     */
    void SetTurretState(TurretState state);

    /**
     * Sets the manual turn amount
     */
    void SetTurnValue(double angle);

    /**
     * Sets the manual turn amount
     */
    void SetShoopAngle(double angle);

    /**
     * @param angleInDegrees angle its going to turn to
     */
    void Turn(double angleInDegrees);

    /**
     * @param x x-value of operator stick
     * @param y y-value of operator stick
     */
    double CalcJoystickAngleInDegrees(double x, double y);

    /**
     * Sets Tracking values
     */
    void SetTrackingValues(double xOffset, double angularRate, double translationalValue);

    /**
     * Calculates output to feed into a percent output loops
     * @param limelightTarget xoffset of the target
     * @param angularVelocity how fast the robot is turning compensation
     * @param translationalAngularRate how fast the robot is moving compensation
     */
    void CalcOutput(double limelightTarget, double angularVelocity, double translationalAngularRate);

    /**
     * Returns current turret angle
     */
    double GetTurretAngle();

    /**
     * Returns if turret is at the correct angle
     */
    bool IsAtAngle();

    /**
     * Computes the translational variables of rate of transitional angle
     * change and rate of change in distance from target.
     * @param driveVelocity drive velocity in ticks per 100ms
     * @param distanceFromTarget distance from target in inches
     */
    double CalcTransitionalCompensations(double driveVelocity, double distanceFromTarget);

    /**
     * Set Turret to chosen mode (coast or break)
     * @param mode the chosen mode
     */
    void SetNeutralMode(NeutralMode mode);

    /**
     * Sets the current angle of the turret
     * @param angle the desired angle to set the turret too
     */
    void SetTurretAngle(double angle);

    /**
     * Sets turret angle to home angle
     */
    void SetHomeOffset();

    /**
     * Turret sensor checks to false every disabled init
     */
    void CheckedSensorsToFalse();

    /**
     * If the turret has seen center sensor to zero during disabled
     * Sensor calibration
     */
    int SensorCalibrate();

    /**
     * Check if passed the super soft stop, 0 is for normal, 1 means passed the right limit, 2 for passed left limit
     */
    int PassedSuperSoft();

    /**
     * checks if the joysticks are trying to be moved, true if moved, false if radial distance is zero
     * @param x x-value of operator stick
     * @param y y-value of operator stick
     */
    bool StickMoved(double x, double y);

    /**
     * updates values the turret needs to know from other subsystems
     * @param gyroAngle current wrapped gyro angle
     */
    void UpdateValues(double gyroAngle);

    /**
     * if the turret is in the middle of wrapping around the hardstop, true if wrapping, false if not
     */
    bool GetWrappedState();

    /**
     * Wrap to left sensor
     */
    void WrapToLeft();

    /**
     * Wrap to right sensor
     */
    void WrapToRight();

    /**
     * Checks the left sensor
     */
    bool GetLeftSensor();

    /**
     * Checks the right sensor
     */
    bool GetRightSensor();

    /**
     * Checks the middle sensor
     */
    bool GetMiddleSensor();

    /**
     * Updates the turret subsystem
     */
    void Update() override;

    /**
     * Updates the dashboard
     */
    void DashboardUpdate() override;

private:
    TalonFX *m_turretMotor;
    DigitalInput *m_turretSensor;

    SupplyCurrentLimitConfiguration m_currentLimit;
    StatorCurrentLimitConfiguration m_statorLimit;

    // update values
    double m_gyroAngle;

    double m_currentAngleInDegrees;
    double m_tickPosition;

    PID m_limelightPID;

    TurretState m_turretState;

    int m_checkStatus;
    double m_leftSensorChecked;
    double m_rightSensorChecked;
    double m_centerSensorChecked;
    double m_leftSideTurnSensor;
    double m_rightSideTurnSensor;

    bool m_wrappingToLeftSensor;
    bool m_wrappingToRightSensor;
    bool m_wrappingInProgress;
    double m_gyroSnapshotWrapping;

    // turn value
    double m_angleInDegrees;
    double m_shoopAngle;

    // tracking values
    double m_limelightXOffset;
    double m_angularRate;
    double m_translationalValue;

    double TURRET_ANGLE_TOLERANCE = 5.0;  // degrees
};

}  // namespace frc973