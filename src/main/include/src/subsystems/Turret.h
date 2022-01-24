#pragma once 

#include "lib/bases/Subsystem.h"
#include <ctre/Phoenix.h>
#include <cmath>
#include "lib/util/Constants.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "lib/helpers/PID.h"

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
    void CalcOutput(double lightlightTarget, double gyroFF = 0.0, double translateFF = 0.0);

    void Update() override;

    void DashboardUpdate() override;

private:
    WPI_TalonFX *m_turretMotor;

    SupplyCurrentLimitConfiguration m_currentLimit;
    StatorCurrentLimitConfiguration m_statorLimit;

    double m_currentAngleInDegrees;
    double m_tickPosition;

    PID m_limeLightPID;

};

} // namespace frc973