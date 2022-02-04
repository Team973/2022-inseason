// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "src/Robot.h"

namespace frc973 {

void Robot::RobotInit() {
  m_gyroTalon = new TalonSRX(9);
  m_gyro = new Gyro(m_gyroTalon);
  m_gyro->Zero();
  m_intakeTalon = new TalonFX(INTAKE_FALCON);
  m_intakeSolenoid = new Solenoid(PCM_ID, PneumaticsModuleType::CTREPCM, INTAKE_SOLENOID_ID);
  m_intake = new Intake(m_intakeTalon, m_intakeSolenoid);
  m_bottomLeftSensor = new DigitalInput(1);
  m_bottomRightSensor = new DigitalInput(1);
  m_topLeftSensor = new DigitalInput(1);
  m_topRightSensor = new DigitalInput(1);
  m_climbTalonA = new WPI_TalonFX(CLIMB_FALCON_A_ID);
  m_climbTalonB = new WPI_TalonFX(CLIMB_FALCON_B_ID);
  m_climb = new Climb(m_climbTalonA, m_climbTalonB, m_bottomLeftSensor, m_bottomRightSensor,
                        m_topLeftSensor, m_topRightSensor);
}

void Robot::RobotPeriodic() {
  m_gyro->Update();
  m_gyro->DashboardUpdate();
  m_intake->Update();
  m_climb->Update();
}
  
} // namespace frc973

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<frc973::Robot>();
}
#endif