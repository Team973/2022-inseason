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

#include "src/auto/commands/ConcurrentCommand.h"
#include "src/auto/commands/ShooterCommand.h"
#include "src/auto/commands/ConveyorFloorCommand.h"
#include "src/auto/commands/ConveyorTowerCommand.h"
#include "src/auto/commands/DeployIntakeCommand.h"
#include "src/auto/commands/RetractIntakeCommand.h"
#include "src/auto/commands/RunIntakeCommand.h"
#include "src/auto/commands/SequentialCommand.h"
#include "src/auto/commands/ShooterCommand.h"
#include "src/auto/commands/WaitCommand.h"
#include "src/auto/commands/WaitForFlywheelCommand.h"



namespace frc973 {

/**
 * Define the names of the Autos.
 */

enum AutoName
{
    DoNothing, /**< Does nothing.*/
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
     */
    AutoManager(Intake *intake, Shooter *shooter, Conveyor *conveyor, Gyro *gyro);

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
    Intake *m_intake;
    Shooter *m_shooter;
    Conveyor *m_conveyor;
    Gyro *m_gyro;

    std::string m_autoName;

    AutoMode m_doNothing;
    AutoMode m_currentMode;

    double m_autoIndex;
};
}