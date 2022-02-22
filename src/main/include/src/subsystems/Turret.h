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
    Off,    /**< Disables turret. */
    Manual, /**< Manual turret control. */
    AutoAim /**< Limelight targeting mode. */
};

class Turret : public Subsystem {
public:
    Turret(WPI_TalonFX *turretMotor, DigitalInput *talonSensor);

    /**
     * @param angleInDegrees angle its going to turn to
     */
    void Turn(double angleInDegrees, double gyroOffset);

    /**
     * @param x x-value of operator stick
     * @param y y-value of operator stick
     */
    double CalcJoystickAngleInDegrees(double x, double y);

    /**
     * Calculates output to feed into a percent output loops
     */
    void CalcOutput(double lightlightTarget, double angularVelocity, double translationalAngularRate);

    /**
     * Returns current turret angle
     */
    double GetTurretAngle();

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
    WPI_TalonFX *m_turretMotor;
    DigitalInput *m_turretSensor;

    SupplyCurrentLimitConfiguration m_currentLimit;
    StatorCurrentLimitConfiguration m_statorLimit;

    double m_currentAngleInDegrees;
    double m_tickPosition;

    PID m_limelightPID;

    double m_limelightToMotorPower;
    double m_translationalAngularRate;

    TurretState m_turretState;

    int m_checkStatus;
    double m_leftSensorChecked;
    double m_rightSensorChecked;
    double m_centerSensorChecked;
    double m_leftSideTurnSensor;
    double m_rightSideTurnSensor;
};

}  // namespace frc973