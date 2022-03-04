#pragma once

#include <ctre/Phoenix.h>
#include <frc/motorcontrol/PWMTalonFX.h>
#include <fmt/core.h>
#include <frc/Solenoid.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <string>

#include "lib/bases/Subsystem.h"
#include "lib/util/Util.h"
#include "src/RobotInfo.h"

namespace frc973 {

class Intake : public Subsystem {
public:
    /**
     * Constructs the intake subsystem
     */
    Intake(frc::PWMTalonFX *intakeTalon, frc::Solenoid *intakeSolenoid, frc::Solenoid *intakeSoftSolenoid);

    enum class IntakeState {
        Deploy, /* Deploys the Intake */
        Retract /* Retracts the Intake */
    };

    enum class IntakeMotorState {
        Off,     /* Intake wheels don't run */
        FeedIn,  /* Runs the intake wheels towards the conveyer */
        FeedOut, /* Runs the intake wheels away from the conveyer */
        Manual   /* Driver controls the intake speed */
    };

    /**
     * Deploys the Intake
     */
    void Deploy();

    /**
     * Retracts the Intake
     */
    void Retract();

    /**
     * Gets current intake stake
     */
    Intake::IntakeState GetIntakeState();

    /**
     * Sets current intake stake
     */
    void SetIntakeState(IntakeState state);

    /**
     * Sets current intake stake
     */
    void SetIntakeMotorState(IntakeMotorState state);

    /**
     * Changes the speed of the intake moves at
     */
    void SetPercentOutput(double speed);

    /**
     * Updates the intake subsystem
     */
    void Update();

    /**
     * Updates the intake subsystem in Smartdashboard
     */
    void DashboardUpdate();

private:
    double m_intakeSpeed;
    double m_timer;

    frc::PWMTalonFX *m_intakeTalon;
    frc::Solenoid *m_intakeSolenoid;
    frc::Solenoid *m_intakeSoftSolenoid;
    IntakeState m_intakeState;
    IntakeMotorState m_intakeMotorState;

    std::string m_intakeStatus;

    const double INTAKE_SOLENOID_DELAY = 1000.0; //delay in msec
};

}  // namespace frc973
