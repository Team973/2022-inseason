// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "src/Robot.h"

#include <fmt/core.h>

#include <frc/smartdashboard/SmartDashboard.h>

namespace frc973 {

void Robot::RobotInit() {
  m_conveyorFloorMotor = new TalonFX(CONVEYOR_FLOOR_FALCON);
  m_conveyorTowerMotor = new TalonFX(CONVEYOR_TOWER_FALCON);
  m_conveyorQueuerMotor = new TalonFX(CONVEYOR_QUEUER_FALCON);

   m_conveyor = new Conveyor(m_conveyorFloorMotor, m_conveyorTowerMotor, m_conveyorQueuerMotor);
}

void Robot::RobotPeriodic() {
}

} // namespace frc973

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<frc973::Robot>();
}
#endif