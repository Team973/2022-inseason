#pragma once

#include <ctre/Phoenix.h>
#include <frc/DriverStation.h>

#include <string>

#include "lib/sensors/Limelight.h"

#include "src/subsystems/Drive.h"
#include "src/subsystems/Intake.h"
#include "src/subsystems/Conveyor.h"
#include "src/subsystems/Turret.h"
#include "src/subsystems/Shooter.h"
#include "src/subsystems/Climb.h"
#include "src/subsystems/Gyro.h"
#include "src/subsystems/Lights.h"
#include "lib/util/Constants.h"

namespace frc973 {
class SubsystemManager {
public:
    /**
     * Constructs the Subsystem Manager
     * @param drive drive subsystem
     * @param intake intake subsystem
     * @param conveyor conveyor subsystem
     * @param turret turret subsystem
     * @param shooter shooter subsystem
     * @param gyro gyro subsystem
     * @param lights light subsystem
     */
    SubsystemManager(Drive *drive, Intake *intake, Conveyor *conveyor, Turret *turret, Shooter *shooter,
                     Limelight *limelight, Climb *climb, Gyro *gyro, Lights *lights);

    /**
     * Sets 0 for the turret and sets the CANdle
     */
    void TurretCalibration();

    /**
     * Finds the current position on the field
     */
    double CalcPose();

    /**
     * uses the current dist from target to figure out how fast the flywheel should go
     */
    double CalcFlywheelRPM();

    /**
     * Checks if the flywheel is up to speed to see if the robot is ready to shoot
     */
    bool ReadyToShoot();

    /**
     * Sets te alliance color
     */
    void SetAllianceColor();

    /**
     * Updates the subsystem manager
     */
    void Update();

private:
    Drive *m_drive;
    Intake *m_intake;
    Conveyor *m_conveyor;
    Turret *m_turret;
    Shooter *m_shooter;
    Limelight *m_limelight;
    Climb *m_climb;
    Gyro *m_gyro;
    Lights *m_lights;

    // Stores char for current alliance color
    std::string m_allianceColor;
    
};
}  // namespace frc973
