#include "src/subsystems/Climb.h"

namespace frc973 {

Climb::Climb(TalonFX *climbTalonA, TalonFX *climbTalonB, DigitalInput *bottomLeftSensor,
             DigitalInput *bottomRightSensor, DigitalInput *topLeftSensor, DigitalInput *topRightSensor,
             Solenoid *climbSolenoid)
        : m_climbTalonA(climbTalonA)
        , m_climbTalonB(climbTalonB)
        , m_bottomLeftSensor(bottomLeftSensor)
        , m_bottomRightSensor(bottomRightSensor)
        , m_topLeftSensor(topLeftSensor)
        , m_topRightSensor(topRightSensor)
        , m_climbSolenoid(climbSolenoid)
        , m_currentLimit(
              SupplyCurrentLimitConfiguration(true, 40, 80, 0.05))
        , m_statorLimit(
              StatorCurrentLimitConfiguration(true, 80, 100, 0.05))
        , m_currentState(ClimbState::Off)
        , m_inClimbState(false)
        , m_climbSpeed(0.0)
        , m_climbTarget(0.0)
        , m_timer(0.0)
        , m_lv3Climb(false) {
    m_climbTalonA->ConfigFactoryDefault();
    m_climbTalonB->ConfigFactoryDefault();

    m_climbTalonA->SetInverted(TalonFXInvertType::CounterClockwise);
    m_climbTalonB->SetInverted(TalonFXInvertType::Clockwise);

    m_climbTalonA->ConfigVoltageCompSaturation(12.0);
    m_climbTalonA->EnableVoltageCompensation(true);
    m_climbTalonB->ConfigVoltageCompSaturation(12.0);
    m_climbTalonB->EnableVoltageCompensation(true);

    m_climbTalonA->Config_kP(0, 0.0, 0);
    m_climbTalonA->Config_kI(0, 0.0, 0);
    m_climbTalonA->Config_kD(0, 0.0, 0);
    m_climbTalonA->Config_kF(0, 0.0, 0);

    m_climbTalonB->Config_kP(0, 0.0, 0);
    m_climbTalonB->Config_kI(0, 0.0, 0);
    m_climbTalonB->Config_kD(0, 0.0, 0);
    m_climbTalonB->Config_kF(0, 0.0, 0);

    m_climbTalonA->ConfigSupplyCurrentLimit(m_currentLimit);
    m_climbTalonB->ConfigStatorCurrentLimit(m_statorLimit);

    m_climbTalonA->ConfigSupplyCurrentLimit(m_currentLimit);
    m_climbTalonA->ConfigStatorCurrentLimit(m_statorLimit);

    m_climbTalonA->SetNeutralMode(Brake);
    m_climbTalonB->SetNeutralMode(Brake);

    m_climbTalonB->Follow(*m_climbTalonA);

    m_climbTalonB->SetStatusFramePeriod(Status_1_General, 255);
    m_climbTalonB->SetStatusFramePeriod(Status_2_Feedback0, 255);
}

void Climb::EnableClimb() {
    m_currentState = ClimbState::Deploy;
    m_inClimbState = true;
}

void Climb::DisableClimb() {
    m_currentState = ClimbState::Off;
    m_inClimbState = false;
}

void Climb::SetClimbState(Climb::ClimbState state) {
    m_currentState = state;
}

void Climb::SetClimbSpeed(double speed) {
    m_climbSpeed = speed;
}

void Climb::SetClimbTarget(double target) {
    m_climbTarget = target;
}

void Climb::SetNeutralMode(NeutralMode mode) {
    m_climbTalonA->SetNeutralMode(mode);
    m_climbTalonB->SetNeutralMode(mode);
}

bool Climb::GetClimbStatus() {
    return m_inClimbState;
}

bool Climb::GetTopHalls() {
    return !m_topLeftSensor->Get() || !m_topRightSensor->Get();
}

bool Climb::GetBottomHalls() {
    return !m_bottomLeftSensor->Get() || !m_bottomRightSensor->Get();
}

void Climb::DashboardUpdate() {
    // SmartDashboard::PutBoolean("CL Top left sensor", m_topLeftSensor->Get());
    // SmartDashboard::PutBoolean("CL Top right sensor", m_topRightSensor->Get());
    // SmartDashboard::PutBoolean("CL Bottom left sensor", m_bottomLeftSensor->Get());
    // SmartDashboard::PutBoolean("CL Bottom right sensor", m_bottomRightSensor->Get());
    SmartDashboard::PutString("CL State", m_climbState);
    SmartDashboard::PutBoolean("inClimbState",m_inClimbState);
    }

void Climb::Update() {
    double climbMotorOutput = 0.0;

    switch (m_currentState) {
        case ClimbState::Off:
            m_climbState = "Off";
            m_inClimbState = false;
            climbMotorOutput = 0.0;
            m_climbSolenoid->Set(false);
            m_timer = Util::GetMsecTime();
            SetNeutralMode(Brake);
            break;
        case ClimbState::Deploy:
            m_climbState = "Deploy";
            m_inClimbState = true;
            climbMotorOutput = 0.0;

            if (m_climbSpeed != 0.0) {
                m_currentState = ClimbState::Manual;
            }

            m_timer = Util::GetMsecTime();
            SetNeutralMode(Brake);
            break;
        case ClimbState::Manual:
            m_climbState = "Manual";
            m_inClimbState = true;
            climbMotorOutput = m_climbSpeed;
            m_climbSolenoid->Set(false);
            m_timer = Util::GetMsecTime();
            SetNeutralMode(Brake);
            break;
        case ClimbState::Level_3:
            m_climbState = "Level 3";
            m_inClimbState = true;

            m_climbSolenoid->Set(true);
            if ((Util::GetMsecTime() - m_timer) > CLIMB_COAST_DELAY) {
                SetNeutralMode(Coast);
            } else {
                SetNeutralMode(Brake);
            }
            
            climbMotorOutput = m_climbSpeed;
            break;
        default:
            m_climbState = "Off";
            m_inClimbState = false;
            climbMotorOutput = 0.0;
            m_climbSolenoid->Set(false);
            m_timer = Util::GetMsecTime();
            SetNeutralMode(Brake);
            break;
    }

    if (GetTopHalls()) {
        climbMotorOutput = std::clamp(climbMotorOutput, -0.7, 0.0);
    }

    if (GetBottomHalls()) {
        climbMotorOutput = std::clamp(climbMotorOutput, 0.0, 0.7); 
    }

    if (m_currentState == ClimbState::Deploy) {
        m_climbTalonA->Set(ControlMode::Position, m_climbTarget / CLIMB_INCHES_PER_TICK);
    } else {
        m_climbTalonA->Set(ControlMode::PercentOutput, climbMotorOutput);
    }
}

}  // namespace frc973
