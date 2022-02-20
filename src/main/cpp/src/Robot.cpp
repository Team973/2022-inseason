// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "src/Robot.h"

namespace frc973 {

void Robot::RobotInit() {
    /**
     * Drive
     */
    m_leftDriveTalonA = new WPI_TalonFX(LEFT_DRIVE_FX_A_ID);
    m_leftDriveTalonB = new WPI_TalonFX(LEFT_DRIVE_FX_B_ID);
    m_leftDriveTalonC = new WPI_TalonFX(LEFT_DRIVE_FX_C_ID);
    m_rightDriveTalonA = new WPI_TalonFX(RIGHT_DRIVE_FX_A_ID);
    m_rightDriveTalonB = new WPI_TalonFX(RIGHT_DRIVE_FX_B_ID);
    m_rightDriveTalonC = new WPI_TalonFX(RIGHT_DRIVE_FX_C_ID);

    m_drive = new Drive(m_leftDriveTalonA, m_leftDriveTalonB, m_leftDriveTalonC, m_rightDriveTalonA, m_rightDriveTalonB,
                        m_rightDriveTalonC);
    m_drive->Zero();

    /**
     * Intake
     */
    m_intakeTalon = new PWMTalonFX(INTAKE_FX_PWM_ID);
    m_intakeSolenoid = new Solenoid(PNEU_HUB_CAN_ID, PneumaticsModuleType::REVPH, INTAKE_SOLENOID_ID);

    m_intake = new Intake(m_intakeTalon, m_intakeSolenoid);

    /**
     * Conveyor
     */
    m_conveyorFloorMotor = new TalonSRX(CONVEYOR_FLOOR_SRX_ID);
    m_conveyorTowerMotorA = new TalonSRX(CONVEYOR_TOWER_A_SRX_ID);
    m_conveyorTowerMotorB = new TalonSRX(CONVEYOR_TOWER_B_SRX_ID);

    m_conveyor = new Conveyor(m_conveyorTowerMotorA, m_conveyorTowerMotorB, m_conveyorFloorMotor);

    /**
     * Turret
     */
    m_turretTalon = new WPI_TalonFX(TURRET_FX_ID);
    m_turretSensor = new DigitalInput(TURRET_HOME_SENSOR);

    m_turret = new Turret(m_turretTalon, m_turretSensor);
    m_turret->SetNeutralMode(NeutralMode::Coast);

    /**
     * Shooter
     */
    m_shooterFlywheelMotorA = new WPI_TalonFX(FLYWHEEL_FX_A_ID);
    m_shooterFlywheelMotorB = new WPI_TalonFX(FLYWHEEL_FX_B_ID);

    m_shooter = new Shooter(m_shooterFlywheelMotorA, m_shooterFlywheelMotorB);

    /**
     * Climb
     */
    m_climbTalonA = new WPI_TalonFX(CLIMB_FX_A_ID);
    m_climbTalonB = new WPI_TalonFX(CLIMB_FX_B_ID);
    m_bottomLeftSensor = new DigitalInput(CLIMB_BOTTOM_LEFT_SENSOR);
    m_bottomRightSensor = new DigitalInput(CLIMB_BOTTOM_RIGHT_SENSOR);
    m_topLeftSensor = new DigitalInput(CLIMB_TOP_LEFT_SENSOR);
    m_topRightSensor = new DigitalInput(CLIMB_TOP_RIGHT_SENSOR);

    m_climb = new Climb(m_climbTalonA, m_climbTalonB, m_bottomLeftSensor, m_bottomRightSensor, m_topLeftSensor,
                        m_topRightSensor);

    /**
     * Gyro
     */
    m_gyro = new Gyro(m_conveyorTowerMotorB);
    m_gyro->Zero();

    /**
     * Limelight
     */
    m_limelight = new Limelight("limelight");

    /**
     * Lights
     */
    m_CANdle = new CANdle(CANDLE_ID);

    m_lights = new Lights(m_CANdle);

    /**
     * Pneumatics
     */
    m_pneumaticsHub = new frc::PneumaticHub{PNEU_HUB_CAN_ID};

    /**
     * Joysticks
     */
    m_driverStick = new StickController(DRIVER_STICK);
    m_operatorStick = new StickController(OPERATOR_STICK);
    m_testStick = new StickController(TEST_STICK);

    /**
     * Automanager
     */
    m_autoManager = new AutoManager(m_drive, m_intake, m_conveyor, m_turret, m_shooter, m_limelight, m_gyro);
}

void Robot::RobotPeriodic() {
    m_drive->Update();
    m_drive->SetAngle(-m_gyro->GetWrappedAngle());
    m_intake->Update();
    m_conveyor->Update();
    m_turret->Update();
    m_shooter->Update();
    // m_climb->Update();
    m_gyro->Update();
    m_lights->Update();
    // m_autoManager->Update();

    m_drive->DashboardUpdate();
    m_intake->DashboardUpdate();
    m_conveyor->DashboardUpdate();
    m_turret->DashboardUpdate();
    m_shooter->DashboardUpdate();
    m_climb->DashboardUpdate();
    m_gyro->DashboardUpdate();
    m_lights->DashboardUpdate();
    m_autoManager->DashboardUpdate();

    m_pneumaticsHub->EnableCompressorAnalog(units::pounds_per_square_inch_t{60}, units::pounds_per_square_inch_t{120});
    frc::SmartDashboard::PutNumber("Pneu PSI", m_pneumaticsHub->GetPressure(0).value());

    // limelight
    frc::SmartDashboard::PutBoolean("LIM valid target?", m_limelight->isTargetValid());
    frc::SmartDashboard::PutNumber("LIM pipeline", m_limelight->GetPipeline());
    frc::SmartDashboard::PutNumber("LIM get x offset (deg)", m_limelight->GetXOffset());
    frc::SmartDashboard::PutNumber("LIM get y offset (deg)", m_limelight->GetYOffset());
    frc::SmartDashboard::PutNumber("LIM dist to target (in)", m_limelight->GetHorizontalDist());
    frc::SmartDashboard::PutBoolean("LIM dead?", m_limelight->IsLimelightDead());
}

}  // namespace frc973

#ifndef RUNNING_FRC_TESTS
int main() {
    return frc::StartRobot<frc973::Robot>();
}
#endif