#pragma once

#include <frc/smartdashboard/SmartDashboard.h>

#include "ctre/phoenix/led/CANdle.h"
#include "ctre/phoenix/led/RainbowAnimation.h"
#include "ctre/phoenix/led/StrobeAnimation.h"
#include "lib/bases/Subsystem.h"
#include "src/RobotInfo.h"

namespace frc973 {
class Lights : public Subsystem {
public:
    /**
     * Constructs the lights subsystem
     */
    Lights(ctre::phoenix::led::CANdle *CANdle);

    /**
     * Sets the tower state to either Off, Initialization, NotReadyToShoot, ReadyToShoot, Fault, Climb, Left, Middle, or
     * Right.
     */
    enum class LightsState {
        Off,             /**< State for turning the off the lights. */
        Initialization,  /**< State for setting the lights to a special state for when the robot is initializing. */
        NotReadyToShoot, /**< State for setting the lights to a special state for when the robot is not ready to shoot.
                          */
        ReadyToShoot,    /**< State for setting the lights to a special state for when the robot is ready to shoot. */
        Fault,           /**< State for setting the lights to a special state for when the robot has an error. */
        Climb,           /**< State for setting the lights to a special state for when the robot is climbing. */
        Left,            /**< State for setting the top left light to green. */
        Middle,          /**< State for setting the two top middle lights to green. */
        Right,           /**< State for setting the top right light to green. */
    };

    /**
     * Updates the intake subsystem
     */
    void Update();

    /**
     * Updates the intake subsystem in Smartdashboard
     */
    void DashboardUpdate();

    /**
     * Where the state of the lights is set to
     * either Off, Initialization, NotReadyToShoot, ReadyToShoot, Fault, or Climb.
     */
    Lights::LightsState GetLightsState();

    /**
     * Where the state of the lights is set to
     * either Off, Initialization, NotReadyToShoot, ReadyToShoot, Fault, or Climb.
     * @param state new lights state
     */
    void SetLightsState(LightsState state);

    void UpdateLightsStateMode();

private:
    ctre::phoenix::led::CANdle *m_candle;

    LightsState m_lightsState;

    ctre::phoenix::led::RainbowAnimation m_rainbow;
    ctre::phoenix::led::StrobeAnimation m_strobe;

    std::string m_currentLightsStateName;
};
}  // namespace frc973