// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "src/Robot.h"

namespace frc973 {

void Robot::RobotInit() {
    /**
     * USB Camera- http://10.9.73.2:1181/stream.mjpg
     */
    frc::CameraServer::StartAutomaticCapture();

    /**
     * Drive
     */
    m_leftDriveTalonA = new TalonFX(LEFT_DRIVE_FX_A_ID);
    m_leftDriveTalonB = new TalonFX(LEFT_DRIVE_FX_B_ID);
    m_leftDriveTalonC = new TalonFX(LEFT_DRIVE_FX_C_ID);
    m_rightDriveTalonA = new TalonFX(RIGHT_DRIVE_FX_A_ID);
    m_rightDriveTalonB = new TalonFX(RIGHT_DRIVE_FX_B_ID);
    m_rightDriveTalonC = new TalonFX(RIGHT_DRIVE_FX_C_ID);

    m_drive = new Drive(m_leftDriveTalonA, m_leftDriveTalonB, m_leftDriveTalonC, m_rightDriveTalonA, m_rightDriveTalonB,
                        m_rightDriveTalonC);
    m_drive->Zero();

    /**
     * Intake
     */
    m_intakeTalon = new PWMTalonFX(INTAKE_FX_PWM_ID);
    m_intakeSolenoid = new Solenoid(PCM_ID, PneumaticsModuleType::CTREPCM, INTAKE_SOLENOID_ID);
    m_intakeSoftSolenoid = new Solenoid(PCM_ID, PneumaticsModuleType::CTREPCM, INTAKE_SOFT_SOLENOID_ID);

    m_intake = new Intake(m_intakeTalon, m_intakeSolenoid, m_intakeSoftSolenoid);

    /**
     * Conveyor
     */
    m_conveyorFloorMotor = new TalonSRX(CONVEYOR_FLOOR_SRX_ID);
    m_conveyorTowerMotor = new TalonFX(CONVEYOR_TOWER_FX_ID);
    m_conveyorCeilingMotor = new TalonSRX(CONVEYOR_CEILING_SRX_ID);

    m_conveyor = new Conveyor(m_conveyorTowerMotor, m_conveyorCeilingMotor, m_conveyorFloorMotor);

    /**
     * Turret
     */
    m_turretTalon = new TalonFX(TURRET_FX_ID);
    m_turretSensor = new DigitalInput(TURRET_HOME_SENSOR);

    m_turret = new Turret(m_turretTalon, m_turretSensor);
    m_turret->SetNeutralMode(NeutralMode::Coast);

    /**
     * Shooter
     */
    m_shooterFlywheelMotorA = new TalonFX(FLYWHEEL_FX_A_ID);
    m_shooterFlywheelMotorB = new TalonFX(FLYWHEEL_FX_B_ID);

    m_shooter = new Shooter(m_shooterFlywheelMotorA, m_shooterFlywheelMotorB);

    /**
     * Climb
     */
    m_climbTalonA = new TalonFX(CLIMB_FX_A_ID);
    m_climbTalonB = new TalonFX(CLIMB_FX_B_ID);
    m_bottomLeftSensor = new DigitalInput(CLIMB_BOTTOM_LEFT_SENSOR);
    m_bottomRightSensor = new DigitalInput(CLIMB_BOTTOM_RIGHT_SENSOR);
    m_topLeftSensor = new DigitalInput(CLIMB_TOP_LEFT_SENSOR);
    m_topRightSensor = new DigitalInput(CLIMB_TOP_RIGHT_SENSOR);
    m_climbSolenoid = new Solenoid(PCM_ID, PneumaticsModuleType::CTREPCM, CLIMB_SOLENOID_ID);

    m_climb = new Climb(m_climbTalonA, m_climbTalonB, m_bottomLeftSensor, m_bottomRightSensor, m_topLeftSensor,
                        m_topRightSensor, m_climbSolenoid);

    /**
     * Gyro
     */
    m_gyro = new Gyro(m_conveyorCeilingMotor);
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
    m_compressor = new Compressor(PneumaticsModuleType::CTREPCM);
    m_compressor->EnableDigital();

    /**
     * Subsystem Manager
     */
    m_subsystemManager = new SubsystemManager(m_drive, m_intake, m_conveyor, m_turret, m_shooter, m_limelight, m_climb,
                                              m_gyro, m_lights);

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
    // m_drive->DashboardUpdate();
    // m_intake->DashboardUpdate();
    m_conveyor->DashboardUpdate();
    m_turret->DashboardUpdate();
    m_shooter->DashboardUpdate();
    // m_climb->DashboardUpdate();+
    m_gyro->DashboardUpdate();
    // m_lights->DashboardUpdate();
    m_autoManager->DashboardUpdate();

    // limelight
    frc::SmartDashboard::PutBoolean("LIM valid target?", m_limelight->isTargetValid());
    frc::SmartDashboard::PutBoolean("LIM dead?", m_limelight->IsLimelightDead());
    // frc::SmartDashboard::PutNumber("LIM pipeline", m_limelight->GetPipeline());
    frc::SmartDashboard::PutNumber("LIM dist to target (in)", m_limelight->GetHorizontalDist());
    frc::SmartDashboard::PutNumber("LIM Y offset", m_limelight->GetYOffset());
}

}  // namespace frc973

#ifndef RUNNING_FRC_TESTS
int main() {
    return frc::StartRobot<frc973::Robot>();
}
#endif