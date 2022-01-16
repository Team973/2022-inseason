#pragma once 

#include "lib/bases/Subsystem.h"
#include <ctre/Phoenix.h>

namespace frc973 {

class Turret : public Subsystem {
public:
    Turret(WPI_TalonFX *turretMotor);
    
    /**
     * @param turnPower input in the joystick's x direction for turn percent power and direction
     */
    void Turn(double turnPower);

    void Update() override;

    void DashboardUpdate() override;

private:
    WPI_TalonFX *m_turretMotor;

    SupplyCurrentLimitConfiguration m_currentLimit;
    StatorCurrentLimitConfiguration m_statorLimit;

};

} // namespace frc973