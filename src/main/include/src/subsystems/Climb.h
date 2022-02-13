#pragma once

#include <ctre/Phoenix.h>
#include <frc/DigitalInput.h>
#include <frc/Solenoid.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "lib/bases/Subsystem.h"
#include "src/RobotInfo.h"

using namespace frc;

namespace frc973 {

class Climb : public Subsystem {
public:
    /**
     * Constructs the Climb subsystem
     * @param climbTalonA left climb TalonFX
     * @param climbTalonB right climb TalonFX
     * @param bottomLeftSensor the bottom left sensor
     * @param bottomRightsensor the bottom right sensor
     * @param topLeftSensor the top left sensor
     * @param topRightSensor the top right sensor
     */
    Climb(WPI_TalonFX *climbTalonA, WPI_TalonFX *climbTalonB, DigitalInput *bottomLeftSensor,
          DigitalInput *bottomRightSensor, DigitalInput *topLeftSensor, DigitalInput *topRightSensor);

    /**
     * Sets the climb to run automatically, manually through joystick, or lock and stop moving.
     */
    enum class ClimbState {
        Deploy, /**< Runs the climb up automatically. */
        Manual, /**< Sets the climb motors to manual control. */
        Off     /**< Locks the climb and sets motors to 0. */
    };

    /**
     * Enables the climb.
     */
    void EnableClimb();

    /**
     * Disables the climb.
     */
    void DisableClimb();

    /**
     * Sets the climb state.
     * @param state The state to set to.
     */
    void SetClimbState(ClimbState state);

    /**
     * Sets the speed of the climb.
     * @param speed The speed as a percent for the motors.
     */
    void SetClimbSpeed(double speed);

    /**
     * Sets the height for the target to reach when deployed
     * @param target the target in inches
     */
    void SetClimbTarget(double target);

    /**
     * Gets the climbs current status.
     * @return True or false on if its enabled.
     */
    bool GetClimbStatus();

    /**
     * Gets the status of the top sensors.
     * @return true if both are activated.
     */
    bool GetTopHalls();

    /**
     * Gets the status of the bottom sensors.
     * @return true if both are activated.
     */
    bool GetBottomHalls();

    /**
     * Updates this subsystem
     */
    void Update() override;

    /**
     * Updates the Dashboard
     */
    void DashboardUpdate() override;

private:
    WPI_TalonFX *m_climbTalonA;
    WPI_TalonFX *m_climbTalonB;

    DigitalInput *m_bottomLeftSensor;
    DigitalInput *m_bottomRightSensor;
    DigitalInput *m_topLeftSensor;
    DigitalInput *m_topRightSensor;

    SupplyCurrentLimitConfiguration m_currentLimit;
    StatorCurrentLimitConfiguration m_statorLimit;

    ClimbState m_currentState;
    bool m_inClimbState;
    double m_climbSpeed;
    double m_climbTarget;

    std::string m_climbState;
};

}  // namespace frc973