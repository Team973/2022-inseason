#pragma once

#include <ctre/Phoenix.h>

#include "lib/sensors/Limelight.h"

#include "src/subsystems/Drive.h"
#include "src/subsystems/Intake.h"
#include "src/subsystems/Conveyor.h"
#include "src/subsystems/Turret.h"
#include "src/subsystems/Shooter.h"
#include "src/subsystems/Climb.h"
#include "src/subsystems/Gyro.h"
#include "src/subsystems/Lights.h"

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
    SubsystemManager(Drive *drive, Intake *intake, Conveyor *conveyor, Turret *turret, Shooter *shooter, Climb *climb,
                     Gyro *gyro, Lights *lights);

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
    Climb *m_climb;
    Gyro *m_gyro;
    Lights *m_lights;
};
}  // namespace frc973
