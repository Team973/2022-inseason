#pragma once

#include <vector>

#include "lib/bases/Command.h"
#include "lib/bases/Subsystem.h"
#include "lib/sensors/Limelight.h"
#include "lib/util/Util.h"
#include "src/auto/AutoMode.h"
#include "src/auto/commands/ConcurrentCommand.h"
#include "src/auto/commands/ConveyorFloorCommand.h"
#include "src/auto/commands/ConveyorTowerCommand.h"
#include "src/auto/commands/DeployIntakeCommand.h"
#include "src/auto/commands/PositionDriveCommand.h"
#include "src/auto/commands/RetractIntakeCommand.h"
#include "src/auto/commands/RunIntakeCommand.h"
#include "src/auto/commands/SequentialCommand.h"
#include "src/auto/commands/SetFlywheelRPMCommand.h"
#include "src/auto/commands/SetGyroAutoAngleCommand.h"
#include "src/auto/commands/SetGyroAngleCommand.h"
#include "src/auto/commands/SetTurretAngleCommand.h"
#include "src/auto/commands/ShooterCommand.h"
#include "src/auto/commands/TrackingTargetCommand.h"
#include "src/auto/commands/WaitCommand.h"
#include "src/auto/commands/WaitForFlywheelCommand.h"
#include "src/subsystems/AutoManager.h"
#include "src/subsystems/Conveyor.h"
#include "src/subsystems/Drive.h"
#include "src/subsystems/Gyro.h"
#include "src/subsystems/Intake.h"
#include "src/subsystems/Shooter.h"
#include "src/subsystems/Turret.h"

namespace frc973 {

/**
 * Define the names of the Autos.
 */
enum AutoName {
    Test,         /**< Test auto with every command in it*/
    DoNothing,    /**< Does nothing.*/
    P2_2Ball,     /**< Position 2, 2 Ball*/
    P3_2Ball,     /**< Position 3, 2 Ball*/
    P5_2Ball,     /**< Position 5, 2 Ball*/
    P2_3Ball,     /**< Position 2, 3 Ball*/
    P5_4Ball,     /**< Position 5, 4 Ball*/
    Citrus_5Ball, /**< 5 Ball auto in honor of frc 1678 */
    P4_Steal1,    /**< Position 6, Steal 1 */
    P5_Steal1,    /**< Complement to 5 Ball Auto */
    P6_Steal2,    /**< Position 6, Steal 1 */
};

/**
 * Manages Auto commands.
 */
class AutoManager : public Subsystem {
public:
    /**
     * Constructs an AutoManager.
     * @param drive The drive subsystem.
     * @param intake The intake subsystem.
     * @param conveyor The conveyor subsystem.
     * @param turret The turret subsystem.
     * @param shooter The shooter subsystem.
     * @param limelight The limelight.
     * @param gyro The gyro.
     */
    AutoManager(Drive *drive, Intake *intake, Conveyor *conveyor, Turret *turret, Shooter *shooter,
                Limelight *limelight, Gyro *gyro);

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
    static constexpr uint32_t TOWER_RUN_TIME = 0;    // the zero is a placeholder
    static constexpr uint32_t SHOOTER_RUN_TIME = 0;  // the zero is a placeholder
    static constexpr uint32_t DRIVE_RUN_TIME = 0;    // the zero is a placeholder
    static constexpr uint32_t FLOOR_RUN_TIME = 0;    // the zero is a placeholder

    AutoName m_currentAuto;
    Drive *m_drive;
    Intake *m_intake;
    Conveyor *m_conveyor;
    Turret *m_turret;
    Shooter *m_shooter;
    Limelight *m_limelight;
    Gyro *m_gyro;

    std::string m_autoName;

    AutoMode m_test;
    AutoMode m_doNothing;
    AutoMode m_p2_2Ball;
    AutoMode m_p3_2Ball;
    AutoMode m_p5_2Ball;
    AutoMode m_p2_3Ball;
    AutoMode m_p5_4Ball;
    AutoMode m_citrus_5Ball;
    AutoMode m_p4_Steal1;
    AutoMode m_p5_Steal1;
    AutoMode m_p6_Steal2;
    AutoMode m_currentMode;

    double m_autoIndex;
};

}  // namespace frc973