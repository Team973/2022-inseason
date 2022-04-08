// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <fmt/core.h>
#include <frc/Joystick.h>
#include <frc/motorcontrol/PWMTalonFX.h>

#include <string>
#include <cameraserver/CameraServer.h>
#include <ctre/Phoenix.h>
#include <frc/Compressor.h>
#include <frc/Solenoid.h>
#include <frc/XboxController.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "RobotInfo.h"
#include "SubsystemManager.h"
#include "lib/PatchedTimedRobot.h"
#include "lib/helpers/StickController.h"
#include "lib/sensors/Limelight.h"
#include "lib/util/Util.h"
#include "src/subsystems/AutoManager.h"
#include "src/subsystems/Climb.h"
#include "src/subsystems/Conveyor.h"
#include "src/subsystems/Drive.h"
#include "src/subsystems/Gyro.h"
#include "src/subsystems/Intake.h"
#include "src/subsystems/Lights.h"
#include "src/subsystems/Shooter.h"
#include "src/subsystems/Turret.h"

using namespace frc;
namespace frc973 {
class Robot : public PatchedTimedRobot {
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
    /**
     * Automanager
     */
    AutoManager *m_autoManager;

    /**
     * Drive
     */
    TalonFX *m_leftDriveTalonA;
    TalonFX *m_leftDriveTalonB;
    TalonFX *m_leftDriveTalonC;
    TalonFX *m_rightDriveTalonA;
    TalonFX *m_rightDriveTalonB;
    TalonFX *m_rightDriveTalonC;
    Drive *m_drive;

    /**
     * Intake
     */
    PWMTalonFX *m_intakeTalon;
    Solenoid *m_intakeSolenoid;
    Solenoid *m_intakeSoftSolenoid;
    Intake *m_intake;

    /**
     * Conveyor
     */
    TalonSRX *m_conveyorFloorMotor;
    TalonFX *m_conveyorTowerMotor;
    TalonFX *m_conveyorCeilingMotor;
    Conveyor *m_conveyor;

    /**
     * Turret
     */
    TalonFX *m_turretTalon;
    DigitalInput *m_turretSensor;
    Turret *m_turret;

    /**
     * Shooter
     */
    TalonFX *m_shooterFlywheelMotorA;
    TalonFX *m_shooterFlywheelMotorB;
    Shooter *m_shooter;

    /**
     * Climb
     */
    TalonFX *m_climbTalonA;
    TalonFX *m_climbTalonB;
    DigitalInput *m_bottomLeftSensor;
    DigitalInput *m_bottomRightSensor;
    DigitalInput *m_topLeftSensor;
    DigitalInput *m_topRightSensor;
    Solenoid *m_climbSolenoid;
    Climb *m_climb;

    /**
     * Gyro
     */
    TalonSRX *m_gyroSRX;
    Gyro *m_gyro;

    /**
     * Limelight
     */
    Limelight *m_limelight;

    /**
     * Lights
     */
    CANdle *m_CANdle;
    Lights *m_lights;

    /**
     * Pneumatics
     */
    frc::Compressor *m_compressor;

    /**
     * Subsystem Manager
     */
    SubsystemManager *m_subsystemManager;

    /**
     * Joysticks
     */
    StickController *m_operatorStick;
    StickController *m_driverStick;
    StickController *m_testStick;
};

}  // namespace frc973