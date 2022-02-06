// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "src/Robot.h"

namespace frc973 {

void Robot::RobotInit() {
  m_gyroTalon = new TalonSRX(9);
  m_gyro = new Gyro(m_gyroTalon);
  m_gyro->Zero();

  m_limelight = new Limelight("limelight");

  //Joystick Init
  m_driverStick = new StickController(0);
  m_operatorStick = new StickController(1);

  //Turret Init
  m_turretTalon = new WPI_TalonFX(8); 
  m_turret = new Turret(m_turretTalon);

  //Drive
  m_leftDriveTalonA = new WPI_TalonFX(LEFT_DRIVE_TALON_A);
  m_leftDriveTalonB = new WPI_TalonFX(LEFT_DRIVE_TALON_B);
  m_leftDriveTalonC = new WPI_TalonFX(LEFT_DRIVE_TALON_C);
  m_rightDriveTalonA = new WPI_TalonFX(RIGHT_DRIVE_TALON_A);
  m_rightDriveTalonB = new WPI_TalonFX(RIGHT_DRIVE_TALON_B);
  m_rightDriveTalonC = new WPI_TalonFX(RIGHT_DRIVE_TALON_C);

  m_drive = new Drive(m_leftDriveTalonA, m_leftDriveTalonB, m_leftDriveTalonC, 
                      m_rightDriveTalonA, m_rightDriveTalonB, m_rightDriveTalonC);


}

void Robot::RobotPeriodic() {
  m_gyro->Update();
  m_turret->Update();

  m_gyro->DashboardUpdate();
  m_turret->DashboardUpdate();
  m_drive->DashboardUpdate();
}

} // namespace frc973

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<frc973::Robot>();
}
#endif