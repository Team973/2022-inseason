#pragma once

#include <ctre/Phoenix.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "lib/bases/Subsystem.h"
#include "lib/util/Util.h"
#include "lib/util/Constants.h"
#include "src/RobotInfo.h"

namespace frc973 {

class Shooter : public Subsystem {
public:
    /**
     * Constructs the shooter subsystem.
     * @param flywheelA The flywheel A falcon.
     * @param flywheelB The flywheel B falcon.
     */
    Shooter(WPI_TalonFX *flywheelA, WPI_TalonFX *flywheelB);

    enum class ShooterState {
        Off,     /* Shooter motors do not run */
        Fixed,   /* Shooter motors run CL Velocity on a fixed setpoint */
        Tracking /* Shooter motors run CL Velocity on a tracking setpoint */
    };

    /**
     * Set the flywheel velocity.
     * @param setpoint The velocity setpoint to go to.
     */
    void SetFlywheelRPM(double setpoint);

    /**
     * Checks to see if the flywheel is at speed or not.
     * @return true or false on if its at speed.
     */
    bool IsAtSpeed();

    /**
     * Change state of Shooter
     */
    void SetShooterState(ShooterState state);

    /**
     * Enables the shooter
     */
    void EnableShooter();

    /**
     * Disables the shooter
     */
    void DisableShooter();

    /**
     * Update this subsystem example each cycle or TeleopPeriodic.
     */
    void Update() override;

    /**
     * Updates the dashboard every robot cycle.
     */
    void DashboardUpdate() override;

private:
    WPI_TalonFX *m_flywheelA;
    WPI_TalonFX *m_flywheelB;

    double m_flywheelRPMSetpoint;

    ShooterState m_shooterState;

    SupplyCurrentLimitConfiguration m_currentLimit;
    StatorCurrentLimitConfiguration m_statorLimit;
};

}  // namespace frc973
