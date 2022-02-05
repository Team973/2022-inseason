// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "src/Robot.h"

namespace frc973 {

void Robot::RobotInit() {
  m_CANdle = new CANdle(candleID);
  m_lights = new Lights(m_CANdle);
  m_conveyorFloorMotor = new TalonSRX(CONVEYOR_FLOOR_TALON_SRX);
  m_conveyorTowerMotorA = new TalonSRX(CONVEYOR_TOWER_A_TALON_SRX);
  m_conveyorTowerMotorB = new TalonSRX(CONVEYOR_TOWER_B_TALON_SRX);
  m_conveyor = new Conveyor(m_conveyorTowerMotorA, m_conveyorTowerMotorB, m_conveyorFloorMotor);
  m_shooterFlywheelMotorA = new TalonFX(FLYWHEEL_A_CAN_ID);
  m_shooterFlywheelMotorB = new TalonFX(FLYWHEEL_B_CAN_ID);
  m_shooterPrecharger = new TalonFX(PRECHARGER_CAN_ID);
  m_shooter = new Shooter(m_shooterFlywheelMotorA, m_shooterFlywheelMotorB, m_shooterPrecharger);
  m_gyroTalon = new TalonSRX(9);
  m_gyro = new Gyro(m_gyroTalon);
  m_gyro->Zero();
  m_intakeTalon = new TalonFX(INTAKE_FALCON);
  m_intakeSolenoid = new Solenoid(PCM_ID, PneumaticsModuleType::CTREPCM, INTAKE_SOLENOID_ID);
  m_intake = new Intake(m_intakeTalon, m_intakeSolenoid);
}

void Robot::RobotPeriodic() {
  m_gyro->Update();
  m_gyro->DashboardUpdate();
  m_intake->Update();
  m_shooter->Update();
  m_conveyor->Update();
  m_lights->Update();
  m_lights->DashboardUpdate();
}
  
} // namespace frc973

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<frc973::Robot>();
}
#endif