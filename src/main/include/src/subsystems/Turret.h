#pragma once 

#include <ctre/Phoenix.h>
#include <frc/smartdashboard/SmartDashboard.h>
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
enum class TurretState 
{
    Off, /**< Disables turret. */
    Manual, /**< Manual turret control. */
    AutoAim /**< Limelight targeting mode. */
};

class Turret : public Subsystem {
public:
    Turret(WPI_TalonFX *turretMotor);
    
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
    void CalcOutput(double limelightTarget, double angularVelocity = 0.0);

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
    void CalcTransitionalCompensations(double driveVelocity, double distanceFromTarget);

    /**
     * Set Turret to Brake
     */
    void SetNeutralMode(NeutralMode mode);

    

    void Update() override;

    void DashboardUpdate() override;

private:
    WPI_TalonFX *m_turretMotor;

    SupplyCurrentLimitConfiguration m_currentLimit;
    StatorCurrentLimitConfiguration m_statorLimit;

    double m_currentAngleInDegrees;
    double m_tickPosition;

    PID m_limelightPID;

    double m_limelightToMotorPower;
    double m_translationalAngularRate;

    TurretState m_turretState;

};

} // namespace frc973