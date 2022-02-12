// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "src/Robot.h"

namespace frc973 {

void Robot::RobotInit() {
    // Drive
    m_leftDriveTalonA = new WPI_TalonFX(LEFT_DRIVE_TALON_A);
    m_leftDriveTalonB = new WPI_TalonFX(LEFT_DRIVE_TALON_B);
    m_leftDriveTalonC = new WPI_TalonFX(LEFT_DRIVE_TALON_C);
    m_rightDriveTalonA = new WPI_TalonFX(RIGHT_DRIVE_TALON_A);
    m_rightDriveTalonB = new WPI_TalonFX(RIGHT_DRIVE_TALON_B);
    m_rightDriveTalonC = new WPI_TalonFX(RIGHT_DRIVE_TALON_C);

    m_drive = new Drive(m_leftDriveTalonA, m_leftDriveTalonB, m_leftDriveTalonC, m_rightDriveTalonA, m_rightDriveTalonB,
                        m_rightDriveTalonC);

    // Intake
    m_intakeTalon = new PWMTalonFX(INTAKE_FALCON);
    m_intakeSolenoid = new Solenoid(PCM_ID, PneumaticsModuleType::REVPH, INTAKE_SOLENOID_ID);
    m_intake = new Intake(m_intakeTalon, m_intakeSolenoid);

    // Conveyor
    m_conveyorFloorMotor = new TalonSRX(CONVEYOR_FLOOR_TALON_SRX);
    m_conveyorTowerMotorA = new TalonSRX(CONVEYOR_TOWER_A_TALON_SRX);
    m_conveyorTowerMotorB = new TalonSRX(CONVEYOR_TOWER_B_TALON_SRX);
    m_conveyor = new Conveyor(m_conveyorTowerMotorA, m_conveyorTowerMotorB, m_conveyorFloorMotor);

    // Turret
    m_turretTalon = new WPI_TalonFX(TURRET_TALON);
    m_turretSensor = new DigitalInput(TURRET_SENSOR);
    m_turret = new Turret(m_turretTalon, m_turretSensor);
    m_turret->SetNeutralMode(NeutralMode::Brake);

    // Shooter
    m_shooterFlywheelMotorA = new WPI_TalonFX(FLYWHEEL_A_CAN_ID);
    m_shooterFlywheelMotorB = new WPI_TalonFX(FLYWHEEL_B_CAN_ID);
    m_shooter = new Shooter(m_shooterFlywheelMotorA, m_shooterFlywheelMotorB);

    // Limelight
    m_limelight = new Limelight("limelight");

    // Climb
    m_bottomLeftSensor = new DigitalInput(CLIMB_BOTTOM_LEFT_SENSOR);
    m_bottomRightSensor = new DigitalInput(CLIMB_BOTTOM_RIGHT_SENSOR);
    m_topLeftSensor = new DigitalInput(CLIMB_TOP_LEFT_SENSOR);
    m_topRightSensor = new DigitalInput(CLIMB_TOP_RIGHT_SENSOR);
    m_climbTalonA = new WPI_TalonFX(CLIMB_FALCON_A_ID);
    m_climbTalonB = new WPI_TalonFX(CLIMB_FALCON_B_ID);
    m_climb = new Climb(m_climbTalonA, m_climbTalonB, m_bottomLeftSensor, m_bottomRightSensor, m_topLeftSensor,
                        m_topRightSensor);

    // Gyro
    m_gyroTalon = new TalonSRX(GYRO_TALON);
    m_gyro = new Gyro(m_gyroTalon);
    m_gyro->Zero();

    // Lights
    m_CANdle = new CANdle(CANDLE_ID);
    m_lights = new Lights(m_CANdle);

    // Joystick
    m_driverStick = new StickController(DRIVER_STICK);
     m_operatorStick = new StickController(OPERATOR_STICK);
}

void Robot::RobotPeriodic() {
    // SmartDashboard::PutNumber("pipeline", m_limelight->GetPipeline());
    // SmartDashboard::PutNumber("x offset", m_limelight->GetXOffset());
    // SmartDashboard::PutNumber("y offset", m_limelight->GetYOffset());
    // SmartDashboard::PutNumber("horizontal dist to target", m_limelight->GetHorizontalDist());
    // SmartDashboard::PutBoolean("valid target?", m_limelight->isTargetValid());

    m_gyro->Update();
    // m_gyro->DashboardUpdate();
    m_intake->Update();
    m_intake->DashboardUpdate();
    m_conveyor->Update();
    m_shooter->Update();
    m_turret->DashboardUpdate();
    m_climb->Update();
    m_climb->DashboardUpdate();
    m_lights->Update();
    // m_lights->DashboardUpdate();
    m_drive->Update();
}

}  // namespace frc973

#ifndef RUNNING_FRC_TESTS
int main() {
    return frc::StartRobot<frc973::Robot>();
}
#endif