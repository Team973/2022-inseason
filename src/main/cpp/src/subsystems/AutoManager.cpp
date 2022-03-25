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
, m_test(AutoMode({}))

/*< DoNothing >*/   
, m_doNothing((AutoMode({})))

/*< Position 2, 2 Ball >*/
, m_p2_2Ball(AutoMode({
    new RetractIntakeCommand(m_intake),
    new WaitCommand(100),
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
    new RetractIntakeCommand(m_intake),
    new WaitCommand(100),
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
    // new PositionDriveCommand(m_drive, 0.0, -90.0, 0.4, 1000),
}))

/*< Position 5, 2 Ball >*/
, m_p5_2Ball(AutoMode({
    new RetractIntakeCommand(m_intake),
    new WaitCommand(100),
    new DeployIntakeCommand(m_intake),
    new SetFlywheelRPMCommand(m_shooter, TARMAC_FLYWHEEL_RPM_SETPOINT, 500),
    new WaitCommand(100),
    new ConcurrentCommand({
        new PositionDriveCommand(m_drive, -40.91, 0.0, 0.5, 2000),
        new RunIntakeCommand(m_intake, 1.0, 2000),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 2000),
        new SetTurretAngleCommand(m_turret, 15.7, 2000),
        new TrackingTargetCommand(m_drive, m_limelight, m_turret, m_gyro, 2000),
    }),
    new WaitForFlywheelCommand(m_shooter, 2000),
    new ConcurrentCommand({
        new RunIntakeCommand(m_intake, 1.0, 2000),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 2000),
        new ConveyorTowerCommand(m_conveyor, Conveyor::TowerState::FeedIn, 2000),
    }),
    new PositionDriveCommand(m_drive, 0.0, 87.0, 0.4, 1000),
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
    // new RetractIntakeCommand(m_intake),
    // new WaitCommand(150),                                   
    // new DeployIntakeCommand(m_intake),
    // new SetFlywheelRPMCommand(m_shooter, TARMAC_FLYWHEEL_RPM_SETPOINT, 1000),
    // new WaitCommand(100),
    // new ConcurrentCommand({
    //     new PositionDriveCommand(m_drive, -40.91, 0.0, 0.5, 2000),
    //     new RunIntakeCommand(m_intake, 1.0, 2000),
    //     new SequentialCommand({
    //         new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 1000),
    //         new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedOut, 200),
    //         new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 2000),
    //     }),
    //     new SetTurretAngleCommand(m_turret, 15.696, 1000),
    //     new TrackingTargetCommand(m_drive, m_limelight, m_turret, m_gyro, 2000),
    // }),
    // new WaitForFlywheelCommand(m_shooter, 1500),
    // new ConcurrentCommand({
    //     new RunIntakeCommand(m_intake, 1.0, 2000),
    //     new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 2000),
    //     new ConveyorTowerCommand(m_conveyor, Conveyor::TowerState::FeedIn, 2000),
    // }),

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
    }
}

void AutoManager::IndexAutoMode(bool next) {
    if (next) {
        m_autoIndex += 1;
    } else {
        m_autoIndex -= 1;
    }

    if (m_autoIndex == -1) {
        m_autoIndex = 7;  // amount of autos we have -1
    }

    if (m_autoIndex == 8) {  // amount of autos we have +1 -1
        m_autoIndex = 0;
    }

    m_currentAuto = AutoName(m_autoIndex);
    UpdateAutoMode();
}
}  // namespace frc973