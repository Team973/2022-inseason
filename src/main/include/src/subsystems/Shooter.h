#pragma once

#include "lib/bases/Subsystem.h"
#include "lib/Util.h"
#include "lib/Constants.h"
#include "src/RobotInfo.h"

#include <ctre/Phoenix.h>
#include <frc/DigitalInput.h>
#include <frc/smartdashboard/SmartDashboard.h>

namespace frc973 {

class Shooter : public Subsystem {
public:
    /**
     * Constructs the shooter subsystem.
     * @param flywheelA The flywheel A falcon.
     * @param flywheelB The flywheel B falcon.
     * @param precharger The precharger falcon.
     */
    Shooter(TalonFX *flywheelA, TalonFX *flywheelB, TalonFX *precharger);

    enum class ShooterStates{
        Off,       //idle; not active
        FarShot,   //shoots from far range
        CloseShot, //shoots from close range
    };

    /**
     * Enables the shooter.
     */
    void EnableShooter();
    
    /**
     * Enables the shooter with distance calculation.
     */
    void EnableShooterWithDist();

    /**
     * Disables the shooter.
     */
    void DisableShooter();

    /**
     * Set the flywheel velocity.
     * @param setpoint The velocity setpoint to go to.
     */
    void SetFlywheelVelocity(double setpoint);

    /**
     * Set the precharger velocity.
     * @param setpoint The velocity setpoint to go to.
     */
    void SetPrechargerVelocity(double setpoint);

    /**
     * Set the flywheel rpm.
     * @param setpoint The rpm setpoint to go to.
     */
    void SetFlywheelRPM(double setpoint);

    /**
     * Set the precharger rpm.
     * @param setpoint The rpm setpoint to go to.
     */
    void SetPrechargerRPM(double setpoint);

    /**
     * Update this subsystem example each cycle or TeleopPeriodic.
     */
    void Update() override;

    /**
     * Updates the dashboard every robot cycle.
     */
    void DashboardUpdate() override;

     /**
     * Checks to see if the flywheel is at speed or not.
     * @return true or false on if its at speed.
     */
    bool IsAtSpeed();

private:
    TalonFX *m_flywheelA;
    TalonFX *m_flywheelB;
    TalonFX *m_precharger;

    double m_flywheelRPMSetpoint;
    double m_prechargerRPMSetpoint;
};
}