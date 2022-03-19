#pragma once

#include <ctre/Phoenix.h>
#include <frc/DigitalInput.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "lib/util/Util.h"
#include "lib/bases/Subsystem.h"

using namespace frc;

namespace frc973 {

class Conveyor : public Subsystem {
public:
    /**
     * Contructs the conveyor system.
     * @param towerMotorA one of the two motors for the tower.
     * @param towerMotorB one of the two motors for the tower.
     * @param floorMotor the motor for the floor.
     */
    Conveyor(TalonSRX *towerMotorA, TalonSRX *towerMotorB, TalonSRX *floorMotor);

    /**
     * Sets the tower state to either off, feed in, feed out, or manual.
     */
    enum class TowerState {
        Off,     /**< State for the tower being off. */
        FeedIn,  /**< State when the tower is moving the balls up */
        FeedOut, /**< State to empty the tower back into the floor. */
        Manual   /**< State for manual control of the tower. */
    };

    /**
     * Sets the floor state to either feed in, feed out, manual, or off.
     */
    enum class FloorState {
        Off,     /**< State for the floor being off. */
        FeedIn,  /**< Brings power cells to tower. */
        FeedOut, /**< Brings power cells to Intake. */
        Manual   /**< Manual control over the speed of the floor. */

    };

    /**
     * Update this subsystem example each cycle or TeleopPeriodic.
     */
    void Update() override;

    /**
     * Updates the dashboard every robot cycle.
     */
    void DashboardUpdate() override;

    /**
     * Sets the tower speed.
     * @param speed The percent speed to set to.
     */
    void SetTowerSpeed(double speed);

    /**
     * Sets the floor speed.
     * @param speed The percent speed to set to.
     */
    void SetFloorSpeed(double speed);

    /**
     * Where the state of the tower is set to
     * either off, feed in, feed out, or manual.
     */
    Conveyor::TowerState GetTowerState();

    /**
     * Where the state of the tower is set to
     * either feed in, feed out, manual, or off.
     */
    Conveyor::FloorState GetFloorState();

    /**
     * Gets the current velocity of the floor
     */
    double GetFloorVelocity();

    /**
     * Gets the current velocity of the tower
     */
    double GetTowerVelocity();

    /**
     * Where the state of the tower is set to
     * either off, feed in, feed out, or manual.
     * @param state new tower state
     */
    void SetTowerState(TowerState state);

    /**
     * Where the state of the floor is set to
     * either feed in, feed out, manual, or off.
     * @param state new floor state
     */
    void SetFloorState(FloorState state);

    /**
     * Sets the manual control tower speed.
     * @param speed The percent speed to set to.
     */
    void SetManualTowerSpeed(double speed);

    /**
     * Sets the manual control floor speed.
     * @param speed The percent speed to set to.
     */
    void SetManualFloorSpeed(double speed);

private:
    TalonSRX *m_towerMotor;
    TalonSRX *m_ceilingMotor;
    TalonSRX *m_floorMotor;
    TowerState m_towerState;
    FloorState m_floorState;

    uint32_t m_reindexingStartTime;
    uint32_t m_elapsedTime;
    bool m_lastB;
    bool m_hasStartedReindexing;
    double m_manualTowerSpeed;
    double m_manualFloorSpeed;
    std::string m_currentTowerState;
    std::string m_currentFloorState;
};
}  // namespace frc973