#include "src/subsystems/Drive.h"

namespace frc973{

Drive::Drive(WPI_TalonFX *leftDriveTalonA, WPI_TalonFX *leftDriveTalonB, WPI_TalonFX *leftDriveTalonC, WPI_TalonFX *rightDriveTalonA,
             WPI_TalonFX *rightDriveTalonB, WPI_TalonFX *rightDriveTalonC)
        : m_leftDriveTalonA(leftDriveTalonA)
        , m_leftDriveTalonB(leftDriveTalonB)
        , m_leftDriveTalonC(leftDriveTalonC)
        , m_rightDriveTalonA(rightDriveTalonA)
        , m_rightDriveTalonB(rightDriveTalonB)
        , m_rightDriveTalonC(rightDriveTalonC)
        , m_leftOutput(0.0)
        , m_rightOutput(0.0)
        , m_throttle(0.0)
        , m_turn(0.0)
        , m_currentLimit(SupplyCurrentLimitConfiguration(true, 40, 50, 0.05))
        , m_statorLimit(StatorCurrentLimitConfiguration(true, 80, 100, 0.05)) 
        {
    
    //configure motor settings
    m_leftDriveTalonA->ConfigFactoryDefault();
    m_leftDriveTalonB->ConfigFactoryDefault();
    m_leftDriveTalonC->ConfigFactoryDefault();

    m_rightDriveTalonA->ConfigFactoryDefault();
    m_rightDriveTalonB->ConfigFactoryDefault();
    m_rightDriveTalonC->ConfigFactoryDefault();

    m_leftDriveTalonA->SetNeutralMode(Coast);
    m_leftDriveTalonB->SetNeutralMode(Coast);
    m_leftDriveTalonC->SetNeutralMode(Coast);

    m_rightDriveTalonA->SetNeutralMode(Coast);
    m_rightDriveTalonB->SetNeutralMode(Coast);
    m_rightDriveTalonC->SetNeutralMode(Coast);

    m_leftDriveTalonA->SetInverted(TalonFXInvertType::Clockwise);
    m_leftDriveTalonB->SetInverted(TalonFXInvertType::Clockwise);
    m_leftDriveTalonC->SetInverted(TalonFXInvertType::Clockwise);

    m_rightDriveTalonA->SetInverted(TalonFXInvertType::CounterClockwise);
    m_rightDriveTalonB->SetInverted(TalonFXInvertType::CounterClockwise);
    m_rightDriveTalonC->SetInverted(TalonFXInvertType::CounterClockwise);

    m_leftDriveTalonA->ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 30);
    m_rightDriveTalonA->ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 30);

    m_leftDriveTalonA->ConfigClosedloopRamp(0.1);
    m_rightDriveTalonA->ConfigClosedloopRamp(0.1);

    m_leftDriveTalonA->ConfigNominalOutputForward(0, 30);
    m_leftDriveTalonA->ConfigNominalOutputReverse(0, 30);
    m_leftDriveTalonA->ConfigPeakOutputForward(1.0, 30);
    m_leftDriveTalonA->ConfigPeakOutputReverse(-1.0, 30);

    m_rightDriveTalonA->ConfigNominalOutputForward(0, 30);
    m_rightDriveTalonA->ConfigNominalOutputReverse(0, 30);
    m_rightDriveTalonA->ConfigPeakOutputForward(1.0, 30);
    m_rightDriveTalonA->ConfigPeakOutputReverse(-1.0, 30);

    m_leftDriveTalonA->Config_kP(0, 0.2, 30);
    m_leftDriveTalonA->Config_kI(0, 0.0, 30);
    m_leftDriveTalonA->Config_kD(0, 0.0, 30);
    m_leftDriveTalonA->Config_kF(0, 0.0, 30);

    m_rightDriveTalonA->Config_kP(0, 0.2, 30);
    m_rightDriveTalonA->Config_kI(0, 0.0, 30);
    m_rightDriveTalonA->Config_kD(0, 0.0, 30);
    m_rightDriveTalonA->Config_kF(0, 0.0, 30);

    m_leftDriveTalonB->Follow(*m_leftDriveTalonA);
    m_leftDriveTalonC->Follow(*m_leftDriveTalonA);

    m_rightDriveTalonB->Follow(*m_rightDriveTalonA);
    m_rightDriveTalonC->Follow(*m_rightDriveTalonA);

    m_leftDriveTalonA->SetSelectedSensorPosition(0, 0, 0);
    m_rightDriveTalonA->SetSelectedSensorPosition(0, 0, 0);

    m_leftDriveTalonA->ConfigSupplyCurrentLimit(m_currentLimit);
    m_leftDriveTalonB->ConfigSupplyCurrentLimit(m_currentLimit);
    m_leftDriveTalonC->ConfigSupplyCurrentLimit(m_currentLimit);

    m_rightDriveTalonA->ConfigSupplyCurrentLimit(m_currentLimit);
    m_rightDriveTalonB->ConfigSupplyCurrentLimit(m_currentLimit);
    m_rightDriveTalonC->ConfigSupplyCurrentLimit(m_currentLimit);

    m_leftDriveTalonA->ConfigStatorCurrentLimit(m_statorLimit);
    m_leftDriveTalonB->ConfigStatorCurrentLimit(m_statorLimit);
    m_leftDriveTalonC->ConfigStatorCurrentLimit(m_statorLimit);

    m_rightDriveTalonA->ConfigStatorCurrentLimit(m_statorLimit);
    m_rightDriveTalonB->ConfigStatorCurrentLimit(m_statorLimit);
    m_rightDriveTalonC->ConfigStatorCurrentLimit(m_statorLimit);
}

void Drive::Update() {
    ArcadeCalcOutput();
    m_leftDriveTalonA->Set(ControlMode::Velocity, (m_leftOutput * 2000 * 4) * std::abs(m_throttle));
    m_rightDriveTalonA->Set(ControlMode::Velocity, (m_rightOutput * 2000 * 4) * std::abs(m_throttle));
}

void Drive::DashboardUpdate() {

}

void Drive::ArcadeCalcOutput() {
    m_throttle = std::clamp(m_throttle, -1.0, 1.0);
    m_turn = std::clamp(m_turn, -1.0, 1.0);
    double maxInput = std::copysign(std::max(std::abs(m_throttle), std::abs(m_turn)), m_throttle);
    if (m_throttle >= 0.0) {
        if(m_turn >= 0.0) {
            // Quadrant 1
            m_leftOutput = maxInput;
            m_rightOutput = m_throttle - m_turn;
        } else {
            // Quadrant 2
            m_leftOutput = m_throttle + m_turn;
            m_rightOutput = maxInput;
        }
    } else {
        if(m_turn >= 0.0) {
            // Quadrant 4
            m_leftOutput = maxInput;
            m_rightOutput =  m_throttle + m_turn;
        } else {
            // Quadrant 3
            m_leftOutput =  m_throttle - m_turn;
            m_rightOutput = maxInput;
        }
    }
}

void Drive::SetThrottleTurn(double throttle, double turn) {
    m_throttle = throttle;
    m_turn = turn;
}

double Drive::GetRightOuput() {
    return m_rightOutput;
}

double Drive::GetLeftOuput() {
    return m_leftOutput;
}

double Drive::GetVelocity() {
    double speed;
    speed = (m_leftDriveTalonA->GetSelectedSensorVelocity() + m_rightDriveTalonA->GetSelectedSensorVelocity()) / 2;
    return speed;
}

} //namespace frc973 
