#include "src/subsystems/AutoManager.h"

namespace frc973 {

AutoManager::AutoManager(Drive *drive, Intake *intake, Conveyor *conveyor, Turret *turret, Shooter *shooter,
                         Limelight *limelight, Gyro *gyro)
        : m_currentAuto(Test)
        , m_drive(drive)
        , m_intake(intake)
        , m_conveyor(conveyor)
        , m_turret(turret)
        , m_shooter(shooter)
        , m_limelight(limelight)
        , m_gyro(gyro)
        , m_autoName("test")
        // clang-format off

/*< Test >*/
, m_test(AutoMode({
    new SetTurretAngleCommand(m_turret, 47.466, 500),
    new TrackingTargetCommand(m_drive, m_limelight, m_turret, m_gyro, 500),
    new WaitCommand(3000),
    new PositionDriveCommand(m_drive, 150.0, 0.0, 0.3, 30000),
    new WaitCommand(1000),
    new PositionDriveCommand(m_drive, -140.0, 0.0, 0.3, 30000)
}))

/*< DoNothing >*/   
, m_doNothing((AutoMode({})))

/*< Position 2, 2 Ball >*/
, m_p2_2Ball(AutoMode({
    new SetGyroAutoAngleCommand(m_gyro,P2_ANGLE),
    new DeployIntakeCommand(m_intake),
    new SetFlywheelRPMCommand(m_shooter, TARMAC_FLYWHEEL_RPM_SETPOINT, 500),
    new WaitCommand(100),
    new ConcurrentCommand({
        new PositionDriveCommand(m_drive, -40.91, 0.0, 0.5, 1500),
        new RunIntakeCommand(m_intake, 1.0, 1500),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 1500),
        new SetTurretAngleCommand(m_turret, -8.7, 1500),
    }),
    new WaitForFlywheelCommand(m_shooter, 2000),
    new ConcurrentCommand({
        new RunIntakeCommand(m_intake, 1.0, 2000),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 2000),
        new ConveyorTowerCommand(m_conveyor, Conveyor::TowerState::FeedIn, 2000),
        new TrackingTargetCommand(m_drive, m_limelight, m_turret, m_gyro, 2000),
    }),
}))

/*< Position 3, 2 Ball >*/
, m_p3_2Ball(AutoMode({
    new SetGyroAutoAngleCommand(m_gyro,P3_ANGLE),
    new DeployIntakeCommand(m_intake),
    new SetFlywheelRPMCommand(m_shooter, TARMAC_FLYWHEEL_RPM_SETPOINT, 2000),
    new WaitCommand(100),
    new ConcurrentCommand({
        new PositionDriveCommand(m_drive, -42.91, 5.353, 0.5, 2000),
        new RunIntakeCommand(m_intake, 1.0, 5000),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 1000),
        new SetTurretAngleCommand(m_turret, 8.69, 2000),
    }),
    new WaitForFlywheelCommand(m_shooter, 2000),
    new ConcurrentCommand({
        new RunIntakeCommand(m_intake, 1.0, 2000),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 2000),
        new ConveyorTowerCommand(m_conveyor, Conveyor::TowerState::FeedIn, 2000),
        new TrackingTargetCommand(m_drive, m_limelight, m_turret, m_gyro, 2000),
    }),
    new PositionDriveCommand(m_drive, 0.0, -90.0, 0.4, 1000),
}))

/*< Position 5, 2 Ball >*/
, m_p5_2Ball(AutoMode({
    new SetGyroAutoAngleCommand(m_gyro, P5_ANGLE),
    new DeployIntakeCommand(m_intake),
    new SetFlywheelRPMCommand(m_shooter, TARMAC_FLYWHEEL_RPM_SETPOINT, 500),
    new WaitCommand(100),
    new ConcurrentCommand({
        new PositionDriveCommand(m_drive, -40.91, 0.0, 0.5, 1500),
        new RunIntakeCommand(m_intake, 1.0, 1500),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 1500),
        new SetTurretAngleCommand(m_turret, 15.7, 1500),
        new TrackingTargetCommand(m_drive, m_limelight, m_turret, m_gyro, 1500),
    }),
    new WaitForFlywheelCommand(m_shooter, 2000),
    new ConcurrentCommand({
        new RunIntakeCommand(m_intake, 1.0, 2000),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 2000),
        new ConveyorTowerCommand(m_conveyor, Conveyor::TowerState::FeedIn, 2000),
    }),
}))

/*< Position 2, 3 Ball >*/
, m_p2_3Ball(m_p2_2Ball + AutoMode({
    new PositionDriveCommand(m_drive, 0.0, -114.0, 0.5, 1000),
    new ConcurrentCommand({
        new PositionDriveCommand(m_drive, -79.458, -111.0, 0.8, 1700), 
        new RunIntakeCommand(m_intake, 1.0, 1700),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 1700),   
        new SetTurretAngleCommand(m_turret, 77.0, 1700),
        new SetFlywheelRPMCommand(m_shooter, TARMAC_FLYWHEEL_RPM_SETPOINT + 100.0, 500),
    }),
    new WaitForFlywheelCommand(m_shooter, 200),
    new ConcurrentCommand({
        new RunIntakeCommand(m_intake, 1.0, 1800),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 1800),
        new ConveyorTowerCommand(m_conveyor, Conveyor::TowerState::FeedIn, 1800),
        new TrackingTargetCommand(m_drive, m_limelight, m_turret, m_gyro, 1800),
    }),
}))

/*< Position 5, 4 Ball >*/
, m_p5_4Ball(m_p5_2Ball + AutoMode({
    new ConcurrentCommand({
        new PositionDriveCommand(m_drive, -220.0, 87.0, 0.5, 3000),
        new RunIntakeCommand(m_intake, 1.0, 3000),
        new SequentialCommand({
            new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 2000),
            new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedOut, 200),
            new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 1000),
        }),
    }),
    new ConcurrentCommand({
        new WaitCommand(500),
        new RunIntakeCommand(m_intake, 1.0, 500),
    }),
    new ConcurrentCommand({
        new PositionDriveCommand(m_drive, 209.0, 87.0, 0.5, 3000),
        new RunIntakeCommand(m_intake, 1.0, 3000),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 3000),
        new SetTurretAngleCommand(m_turret, -90.0, 3000),
        new SetFlywheelRPMCommand(m_shooter, TARMAC_FLYWHEEL_RPM_SETPOINT, 3000),
        new TrackingTargetCommand(m_drive, m_limelight, m_turret, m_gyro, 5000),
    }),
    new WaitForFlywheelCommand(m_shooter, 1500),
    new ConcurrentCommand({
        new RunIntakeCommand(m_intake, 1.0, 5000),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 5000),
        new ConveyorTowerCommand(m_conveyor, Conveyor::TowerState::FeedIn, 5000),
    }),
}))

/*< Citrus, 5 Ball >*/
, m_citrus_5Ball(m_p2_3Ball + AutoMode({
    new PositionDriveCommand(m_drive, 0.0, -88.0, 0.5, 1500),
    new ConcurrentCommand({
        new PositionDriveCommand(m_drive, -158.0, -88.0, 0.7, 2000),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 2000),
        new RunIntakeCommand(m_intake, 1.0, 2000),
    }),
    new ConcurrentCommand({
        new RunIntakeCommand(m_intake, 1.0, 1800),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 2000),
        new PositionDriveCommand(m_drive, 180.0, -88.0, 1.0, 2000),
        new SetFlywheelRPMCommand(m_shooter, TARMAC_FLYWHEEL_RPM_SETPOINT, 2000),
    }),
    new WaitForFlywheelCommand(m_shooter, 500),
    new ConcurrentCommand({
        new RunIntakeCommand(m_intake, 1.0, 2000),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 1800),
        new ConveyorTowerCommand(m_conveyor, Conveyor::TowerState::FeedIn, 2000),
        new TrackingTargetCommand(m_drive, m_limelight, m_turret, m_gyro, 1800),
    }),
}))

, m_p4_Steal1(AutoMode({
    new SetGyroAutoAngleCommand(m_gyro, P4_ANGLE),
    new DeployIntakeCommand(m_intake),
    new SetFlywheelRPMCommand(m_shooter, TARMAC_FLYWHEEL_RPM_SETPOINT, 500),
    new ConcurrentCommand({
        new PositionDriveCommand(m_drive, -41.0, 0.0, 0.8, 2000),
        new RunIntakeCommand(m_intake, 1.0, 2000),
        new ConveyorTowerCommand(m_conveyor, Conveyor::TowerState::Shoot, 2000),
        new TrackingTargetCommand(m_drive, m_limelight, m_turret, m_gyro, 2000),
    }),
    new SetFlywheelRPMCommand(m_shooter, LOW_FLYWHEEL_RPM_SETPOINT, 500),
    new ConcurrentCommand({
        new RunIntakeCommand(m_intake, 1.0, 2000),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::Shoot, 2000),
        new ConveyorTowerCommand(m_conveyor, Conveyor::TowerState::Shoot, 2000),
    })
}))

/*< Position 5, Steal 1 >*/
, m_p5_Steal1(m_p5_2Ball + AutoMode({
    new PositionDriveCommand(m_drive, 0.0, -75.0, 0.5, 1500),
    new ConcurrentCommand({
        new PositionDriveCommand(m_drive, -63.0, -75.0, 0.5, 1500),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 1500),
        new RunIntakeCommand(m_intake, 1.0, 1500),
    }),
    new PositionDriveCommand(m_drive, 0.0, 70.0, 0.5, 2000),
    new ConcurrentCommand({
        new RunIntakeCommand(m_intake, -0.3, 2000),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedOut, 2000),
        new ConveyorTowerCommand(m_conveyor,Conveyor::TowerState::FeedOut, 2000),
    }),
}))

/*< Position 6, Steal 2 >*/
, m_p6_Steal2(AutoMode({
    new SetGyroAutoAngleCommand(m_gyro,P6_ANGLE),
    new DeployIntakeCommand(m_intake),
    new PositionDriveCommand(m_drive, 0.0, 60.0, 0.8, 750),
    new ConcurrentCommand({
        new PositionDriveCommand(m_drive, -69.0, 60.0, 0.7, 1700),
        new RunIntakeCommand(m_intake, 1.0, 1700),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 1700),
        new SetTurretAngleCommand(m_turret, -30.0, 1700),
        new SetFlywheelRPMCommand(m_shooter, TARMAC_FLYWHEEL_RPM_SETPOINT + 50.0, 500),
    }),
    new WaitForFlywheelCommand(m_shooter, 200),
    new ConcurrentCommand({
        new RunIntakeCommand(m_intake, 1.0, 1800),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 1800),
        new ConveyorTowerCommand(m_conveyor, Conveyor::TowerState::FeedIn, 1800),
        new TrackingTargetCommand(m_drive, m_limelight, m_turret, m_gyro, 1800),
    }),
    new PositionDriveCommand(m_drive, 0.0, -50.0, 0.8, 1000),
    new ConcurrentCommand({
        new PositionDriveCommand(m_drive, -63.0, -50.0, 0.8, 1500),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 1500),
        new RunIntakeCommand(m_intake, 1.0, 1500),
    }),
    new PositionDriveCommand(m_drive, 0.0, -30.0, 0.8, 2500),
    new PositionDriveCommand(m_drive, 174.0, -25.0, 0.8, 2500),
    new PositionDriveCommand(m_drive, 0.0, 60.0, 0.7, 2500),
    new ConcurrentCommand({
        new PositionDriveCommand(m_drive, -60.0, 60.0, 0.8, 1500),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 1500),
        new RunIntakeCommand(m_intake, 1.0, 1500),
    }),
    new ConcurrentCommand({
        new PositionDriveCommand(m_drive, 0.0, 60.0, 0.7, 2000),
        new RunIntakeCommand(m_intake, -0.3, 2000),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedOut, 2000),
        new ConveyorTowerCommand(m_conveyor, Conveyor::TowerState::FeedOut, 2000),
    }),
}))

        // clang-format on
        , m_currentMode(m_test)
        , m_autoIndex(0) {
}

void AutoManager::Update() {
    if (m_currentMode.IsCompleted()) {
        return;
    }

    m_currentMode.Run();
}

void AutoManager::DashboardUpdate() {
    switch (m_currentAuto) {
        case Test:
            m_autoName = "Test";
            break;
        case DoNothing:
            m_autoName = "Do Nothing";
            break;
        case P2_2Ball:
            m_autoName = "Position 2, 2 Ball";
            break;
        case P3_2Ball:
            m_autoName = "Position 3, 2 Ball";
            break;
        case P5_2Ball:
            m_autoName = "Position 5, 2 Ball";
            break;
        case P2_3Ball:
            m_autoName = "3 Ball";
            break;
        case P5_4Ball:
            m_autoName = "4 Ball";
            break;
        case Citrus_5Ball:
            m_autoName = "Citrus 5 Ball";
            break;
        case P4_Steal1:
            m_autoName = "P4, Pooper Scooper 1";
            break;
        case P5_Steal1:
            m_autoName = "P5, Pooper Scooper 1";
            break;
        case P6_Steal2:
            m_autoName = "P6, Pooper Scooper 2";
            break;
    }

    frc::SmartDashboard::PutString(
        "Auto Info", "Mode: " + m_autoName + " Index: " + std::to_string(m_currentMode.GetCurrentCommandIndex()));
    frc::SmartDashboard::PutString("DB/String 0", "Mode: " + m_autoName);
}

void AutoManager::UpdateAutoMode() {
    switch (m_currentAuto) {
        case Test:
            m_currentMode = m_test;
            break;
        case DoNothing:
            m_currentMode = m_doNothing;
            break;
        case P2_2Ball:
            m_currentMode = m_p2_2Ball;
            break;
        case P3_2Ball:
            m_currentMode = m_p3_2Ball;
            break;
        case P5_2Ball:
            m_currentMode = m_p5_2Ball;
            break;
        case P2_3Ball:
            m_currentMode = m_p2_3Ball;
            break;
        case P5_4Ball:
            m_currentMode = m_p5_4Ball;
            break;
        case Citrus_5Ball:
            m_currentMode = m_citrus_5Ball;
            break;
        case P4_Steal1:
            m_currentMode = m_p4_Steal1;
            break;
        case P5_Steal1:
            m_currentMode = m_p5_Steal1;
            break;
        case P6_Steal2:
            m_currentMode = m_p6_Steal2;
            break;
    }
}

void AutoManager::IndexAutoMode(bool next) {
    if (next) {
        m_autoIndex += 1;
    } else {
        m_autoIndex -= 1;
    }

    if (m_autoIndex == -1) {
        m_autoIndex = 10;  // amount of autos we have -1
    }

    if (m_autoIndex == 11) {  // amount of autos we have +1 -1
        m_autoIndex = 0;
    }

    m_currentAuto = AutoName(m_autoIndex);
    UpdateAutoMode();
}
}  // namespace frc973