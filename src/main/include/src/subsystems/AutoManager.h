#pragma once

#include <vector>

#include "lib/bases/Subsystem.h"
#include "lib/bases/Command.h"

#include "src/auto/AutoMode.h"

#include "src/subsystems/AutoManager.h"
#include "src/subsystems/Conveyor.h"
#include "src/subsystems/Gyro.h"
#include "src/subsystems/Intake.h"
#include "src/subsystems/Shooter.h"
#include "src/subsystems/Drive.h"
#include "src/subsystems/Turret.h"
#include "lib/sensors/Limelight.h"
 
#include "src/auto/commands/ConcurrentCommand.h"
#include "src/auto/commands/ConveyorFloorCommand.h"
#include "src/auto/commands/ConveyorTowerCommand.h"
#include "src/auto/commands/DeployIntakeCommand.h"
#include "src/auto/commands/PositionDriveCommand.h"
#include "src/auto/commands/RetractIntakeCommand.h"
#include "src/auto/commands/RunIntakeCommand.h"
#include "src/auto/commands/SequentialCommand.h"
#include "src/auto/commands/SetGyroAngleCommand.h"
#include "src/auto/commands/SetTurretAngleCommand.h"
#include "src/auto/commands/SetFlywheelRPMCommand.h"
#include "src/auto/commands/ShooterCommand.h"
#include "src/auto/commands/TrackingTargetCommand.h"
#include "src/auto/commands/WaitCommand.h"
#include "src/auto/commands/WaitForFlywheelCommand.h"



namespace frc973 {

/**
 * Define the names of the Autos.
 */

enum AutoName
{
    DoNothing, /**< Does nothing.*/
    P2_2Ball, /**< Position 2, 2 Ball*/
    P3_2Ball, /**< Position 3, 2 Ball*/
    P5_2Ball, /**< Position 5, 2 Ball*/
    P2_3Ball, /**< Position 2, 3 Ball*/
    P5_4Ball, /**< Position 5, 4 Ball*/
};

/**
 * Manages Auto commands.
 */
class AutoManager : public Subsystem {
public:
    AutoManager();

    /**
     * Constructs an AutoManager.
     * @param intake The intake subsystem.
     * @param shooter The shooter subsystem.
     * @param conveyor The conveyor subsystem.
     * @param gyro The conveyor subsystem.
     * @param drive The drive subsystem.
     * @param turret The turret subsystem.
     */
    AutoManager(Intake *intake, Shooter *shooter, Conveyor *conveyor, Gyro *gyro, Drive *drive, Turret *turret);

    /**
     * Updates AutoManager.
     */
    void Update() override;

    /**
     * Update the smart dashboard network tables.
     */
    void DashboardUpdate() override;

    /**
     * Updates which automode is selected.
     */
    void UpdateAutoMode();

    /**
     * Indexes the automode + or - 1.
     * @param next True or false to go next or previous.
     */
    void IndexAutoMode(bool next);

private:
    /**
     * Time in milliseconds each auto command goes for.
     */
    static constexpr uint32_t TOWER_RUN_TIME = 0;  // the zero is a placeholder 
    static constexpr uint32_t SHOOTER_RUN_TIME = 0;  // the zero is a placeholder 
    static constexpr uint32_t DRIVE_RUN_TIME = 0;  // the zero is a placeholder 
    static constexpr uint32_t FLOOR_RUN_TIME = 0;  // the zero is a placeholder 

    AutoName m_currentAuto;
    Limelight *m_limelight;
    Turret *m_turret;
    Intake *m_intake;
    Shooter *m_shooter;
    Conveyor *m_conveyor;
    Gyro *m_gyro;
    Drive *m_drive;

    std::string m_autoName;

    AutoMode m_doNothing;
    AutoMode m_p2_2Ball;
    AutoMode m_p3_2Ball;
    AutoMode m_p5_2Ball;
    AutoMode m_p2_3Ball;
    AutoMode m_p5_4Ball;
    AutoMode m_currentMode;

    double m_autoIndex;
};
}