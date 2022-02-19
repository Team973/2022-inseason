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
    // new SetGyroAngleCommand(m_gyro, 100.0, 500), // n
    new PositionDriveCommand(m_drive, 6.0, 0.0, 0.2, 2000),

    // new SetFlywheelRPMCommand(m_shooter, 2000.0, 2000),
    // new WaitForFlywheelCommand(m_shooter),
    // new ConveyorTowerCommand(m_conveyor, Conveyor::TowerState::FeedIn, 2000),
    // new ShooterCommand(m_shooter, Shooter::ShooterState::Tracking, 2000),
    // new TrackingTargetCommand(m_drive, m_limelight, m_turret, m_gyro, 2000),
}))

/*< DoNothing >*/
, m_doNothing(AutoMode({}))

/*< Position 2, 2 Ball >*/
, m_p2_2Ball(AutoMode({
    new SetGyroAngleCommand(m_gyro, P2_ANGLE, 500),
    new ConcurrentCommand({
        new PositionDriveCommand(m_drive, -34.048, -177.683, 0.5, 2000),
        new DeployIntakeCommand(m_intake),
        new RunIntakeCommand(m_intake, 1.0, 2000),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 2000),
        new SetTurretAngleCommand(m_turret, -15.7, 2000),
        new SetFlywheelRPMCommand(m_shooter, 1000.0, 2000),
    }),
    new ConcurrentCommand({
        new DeployIntakeCommand(m_intake),
        new RunIntakeCommand(m_intake, 1.0, 13000),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 13000),
        new ConveyorTowerCommand(m_conveyor, Conveyor::TowerState::FeedIn, 13000),
        new TrackingTargetCommand(m_drive, m_limelight, m_turret, m_gyro, 13000),
        new ShooterCommand(m_shooter, Shooter::ShooterState::Tracking, 13000),
    }),
}))

/*< Position 3, 2 Ball >*/
, m_p3_2Ball(AutoMode({
    new SetGyroAngleCommand(m_gyro, P3_ANGLE, 500)
}))

/*< Position 5, 2 Ball >*/
, m_p5_2Ball(AutoMode({
}))

/*< Position 2, 3 Ball >*/
, m_p2_3Ball(AutoMode({
    new SetGyroAngleCommand(m_gyro, P2_ANGLE, 500),
    new ConcurrentCommand({
        new PositionDriveCommand(m_drive, -34.048, -177.683, 0.5, 2000),
        new DeployIntakeCommand(m_intake),
        new RunIntakeCommand(m_intake, 1.0, 2000),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 2000),
        new SetTurretAngleCommand(m_turret, -15.7, 2000),
        new SetFlywheelRPMCommand(m_shooter, 1000.0, 2000),
    }),
    new ConcurrentCommand({
        new DeployIntakeCommand(m_intake),
        new RunIntakeCommand(m_intake, 1.0, 5000),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 5000),
        new ConveyorTowerCommand(m_conveyor, Conveyor::TowerState::FeedIn, 5000),
        new TrackingTargetCommand(m_drive, m_limelight, m_turret, m_gyro, 5000),
        new ShooterCommand(m_shooter, Shooter::ShooterState::Tracking, 5000),
    }),
    new ConcurrentCommand({
        new PositionDriveCommand(m_drive, -77.458, 69.971, 0.5, 2000),
        new DeployIntakeCommand(m_intake),
        new RunIntakeCommand(m_intake, 1.0, 2000),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 2000),
        new SetTurretAngleCommand(m_turret, 67.79, 2000),
        new SetFlywheelRPMCommand(m_shooter, 1000.0, 2000),
    }),
    new ConcurrentCommand({
        new DeployIntakeCommand(m_intake),
        new RunIntakeCommand(m_intake, 1.0, 5000),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 5000),
        new ConveyorTowerCommand(m_conveyor, Conveyor::TowerState::FeedIn, 5000),
        new TrackingTargetCommand(m_drive, m_limelight, m_turret, m_gyro, 5000),
        new ShooterCommand(m_shooter, Shooter::ShooterState::Tracking, 5000),
    }),
}))

/*< Position 5, 4 Ball >*/
, m_p5_4Ball(AutoMode({
    new SetGyroAngleCommand(m_gyro, P5_ANGLE, 500),
    new ConcurrentCommand({
        new PositionDriveCommand(m_drive, -34.048, 45.683, 0.5, 2000),
        new DeployIntakeCommand(m_intake),
        new RunIntakeCommand(m_intake, 1.0, 2000),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 2000),
        new SetTurretAngleCommand(m_turret, 15.696, 2000),
        new SetFlywheelRPMCommand(m_shooter, 1000.0, 2000),
    }),
    new ConcurrentCommand({
        new DeployIntakeCommand(m_intake),
        new RunIntakeCommand(m_intake, 1.0, 2000),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 2000),
        new ConveyorTowerCommand(m_conveyor, Conveyor::TowerState::FeedIn, 2000),
        new TrackingTargetCommand(m_drive, m_limelight, m_turret, m_gyro, 2000),
        new ShooterCommand(m_shooter, Shooter::ShooterState::Tracking, 2000),
    }),
    new ConcurrentCommand({
        new PositionDriveCommand(m_drive, -222.535, 136.428, 0.5, 3000),
        new DeployIntakeCommand(m_intake),
        new RunIntakeCommand(m_intake, 1.0, 3000),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 3000),
        new SetTurretAngleCommand(m_turret, 15.696, 3000),
        new SetFlywheelRPMCommand(m_shooter, 1000.0, 3000),
    }),
    new ConcurrentCommand({
        new PositionDriveCommand(m_drive, 245.637, 135.618 , 0.5, 3000),
        new DeployIntakeCommand(m_intake),
        new RunIntakeCommand(m_intake, 1.0, 3000),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 3000),
        new SetTurretAngleCommand(m_turret, 15.696, 3000),
        new SetFlywheelRPMCommand(m_shooter, 1000.0, 3000),
    }),
    new ConcurrentCommand({
        new DeployIntakeCommand(m_intake),
        new RunIntakeCommand(m_intake, 1.0, 5000),
        new ConveyorFloorCommand(m_conveyor, Conveyor::FloorState::FeedIn, 5000),
        new ConveyorTowerCommand(m_conveyor, Conveyor::TowerState::FeedIn, 5000),
        new TrackingTargetCommand(m_drive, m_limelight, m_turret, m_gyro, 5000),
        new ShooterCommand(m_shooter, Shooter::ShooterState::Tracking, 5000),
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
            m_autoName = "Position 2, 3 Ball";
            break;
        case P5_4Ball:
            m_autoName = "Position 5, 4 Ball";
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
    }
}

void AutoManager::IndexAutoMode(bool next) {
    if (next) {
        m_autoIndex += 1;
    } else {
        m_autoIndex -= 1;
    }

    if (m_autoIndex == -1) {
        m_autoIndex = 6;  // amount of autos we have +1
    }

    if (m_autoIndex == 7) {  // amount of autos we have +2
        m_autoIndex = 0;
    }

    m_currentAuto = AutoName(m_autoIndex);
    UpdateAutoMode();
}
}  // namespace frc973