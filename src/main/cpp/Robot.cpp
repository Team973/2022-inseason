// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "src/Robot.h"

#include <fmt/core.h>

#include <frc/smartdashboard/SmartDashboard.h>

namespace frc973 {

void Robot::RobotInit() {
  m_conveyorFloorMotor = new TalonSRX(CONVEYOR_FLOOR_TALON_SRX);
  m_conveyorTowerMotorA = new TalonSRX(CONVEYOR_TOWER_A_TALON_SRX);
  m_conveyorTowerMotorB = new TalonSRX(CONVEYOR_TOWER_B_TALON_SRX);

   m_conveyor = new Conveyor(m_conveyorTowerMotorA, m_conveyorTowerMotorB, m_conveyorFloorMotor);
}

void Robot::RobotPeriodic() {
  m_conveyor->Update();
}

} // namespace frc973

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<frc973::Robot>();
}
#endif