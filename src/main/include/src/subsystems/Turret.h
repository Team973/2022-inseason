#pragma once 

#include "lib/bases/Subsystem.h"
#include <ctre/Phoenix.h>
#include <cmath>
#include "lib/util/Constants.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "lib/helpers/PID.h"
#include "lib/util/Constants.h"

namespace frc973 {

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
    void CalcOutput(double lightlightTarget, double angularVelocity = 0.0);

    /**
     * Returns current turret angle
     */
    double GetTurretAngle();

    /**
     * Computes the translational variables of rate of transitional angle 
     * change and rate of change in distance from target.
     */
    void CalcTransitionalCompensations(double driveVelocity, double distanceFromTarget);

    void Update() override;

    void DashboardUpdate() override;

private:
    WPI_TalonFX *m_turretMotor;

    SupplyCurrentLimitConfiguration m_currentLimit;
    StatorCurrentLimitConfiguration m_statorLimit;

    double m_currentAngleInDegrees;
    double m_tickPosition;

    PID m_limeLightPID;

    double m_limeLightToMotorPower;
    double m_translationalAngularRate;

};

} // namespace frc973