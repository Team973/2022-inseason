#include "src/subsystems/Climb.h" 

namespace frc973 {

Climb::Climb(WPI_TalonFX *climbTalonA, WPI_TalonFX *climbTalonB, DigitalInput *bottomLeftSensor, DigitalInput *bottomRightSensor, 
            DigitalInput *topLeftSensor, DigitalInput *topRightSensor)
    : m_climbTalonA(climbTalonA)
    , m_climbTalonB(climbTalonB)
    , m_bottomLeftSensor(bottomLeftSensor)
    , m_bottomRightSensor(bottomRightSensor)
    , m_topLeftSensor(topLeftSensor)
    , m_topRightSensor(topRightSensor)
    , m_currentLimit(SupplyCurrentLimitConfiguration(true, 0, 0, 0.0)) //TODO: update values
    , m_statorLimit(StatorCurrentLimitConfiguration(true, 0, 0, 0.0))  //TODO: update values
    , m_currentState(ClimbState::Off)
    , m_inClimbState(false) 
    , m_climbSpeed(0.0)
    {
    m_climbTalonA->ConfigFactoryDefault();
    m_climbTalonB->ConfigFactoryDefault();
    
    m_climbTalonA->SetInverted(false);
    m_climbTalonB->SetInverted(false);

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

    m_climbTalonB->Follow(*m_climbTalonA);
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

bool Climb::GetClimbStatus() {
    return m_inClimbState;
}

bool Climb::GetTopHalls() {
    return !m_topLeftSensor->Get() || !m_topRightSensor->Get();
}

bool Climb::GetBottomHalls() {
    return !m_bottomLeftSensor->Get() || !m_bottomRightSensor->Get();
}

void Climb::DashboardUpdate() {}

void Climb::Update() {
    double climbMotorOutput = 0.0;

    switch (m_currentState) {
    case ClimbState::Off:
        
        break;
    case ClimbState::Deploy:
        
        break;
    case ClimbState::Manual:
        
        break;
    default:
        //default is off
        break;
    }

    if (GetTopHalls()) {
        climbMotorOutput = std::clamp(climbMotorOutput, -0.2, 0.0); //TODO: update min
    }

    if (GetBottomHalls()) {
        climbMotorOutput = std::clamp(climbMotorOutput, 0.0, 0.5);
    }
    
    if (m_currentState == ClimbState::Deploy) {
        // TODO: position movement
    }
    else {
        m_climbTalonA->Set(ControlMode::PercentOutput, climbMotorOutput);
    }
    
}
    
} // namespace frc973

