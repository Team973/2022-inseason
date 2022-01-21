// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/Joystick.h>
#include <frc/XboxController.h>

#include <ctre/Phoenix.h>

#include "src/subsystems/Gyro.h"
#include "src/subsystems/Turret.h"
#include "lib/Util.h"
#include <frc/Joystick.h>
#include <frc/XboxController.h>
#include "subsystems/Drive.h"
#include "RobotInfo.h"
#include "lib/Util.h"



using namespace frc;
namespace frc973 {
class Robot : public TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;

 private:
 //gyro
  TalonSRX* m_gyroTalon;
  Gyro* m_gyro;

  //joysticks
  Joystick *m_driverStick;
  XboxController *m_operatorStick;

  //turret
  WPI_TalonFX *m_turretTalon;
  Turret *m_turret;
    
    WPI_TalonFX *m_leftDriveTalonA;
    WPI_TalonFX *m_leftDriveTalonB;
    WPI_TalonFX *m_leftDriveTalonC;
    WPI_TalonFX *m_rightDriveTalonA;
    WPI_TalonFX *m_rightDriveTalonB; 
    WPI_TalonFX *m_rightDriveTalonC;  
    Drive *m_drive; 
    Joystick *m_driverStick;
    XboxController *m_operatorStick;
};

} //namespace frc973