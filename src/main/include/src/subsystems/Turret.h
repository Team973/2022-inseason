#pragma once 

#include "lib/bases/Subsystem.h"
#include <ctre/Phoenix.h>
#include <cmath>
#include "lib/Constants.h"
#include <frc/smartdashboard/SmartDashboard.h>

namespace frc973 {

class Turret : public Subsystem {
public:
    Turret(WPI_TalonFX *turretMotor);
    
    /**
     * @param angle angle its going to turn to 
     */
    void Turn(double angleInDegrees);

    /**
     * @param x x-value of operator stick
     * @param y y-value of operator stick
     */
    double SetJoystickAngle(double x, double y);

    void Update() override;

    void DashboardUpdate() override;

private:
    WPI_TalonFX *m_turretMotor;

    SupplyCurrentLimitConfiguration m_currentLimit;
    StatorCurrentLimitConfiguration m_statorLimit;

    double m_currentAngleInRadians;
    double m_tickPosition;

};

} // namespace frc973