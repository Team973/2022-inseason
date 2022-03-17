// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "src/Robot.h"

namespace frc973 {

void Robot::RobotInit() {
}

void Robot::RobotPeriodic() {
}

}  // namespace frc973

#ifndef RUNNING_FRC_TESTS
int main() {
    return frc::StartRobot<frc973::Robot>();
}
#endif