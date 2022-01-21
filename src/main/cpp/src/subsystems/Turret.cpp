#include "src/subsystems/Turret.h"

namespace frc973 {

Turret::Turret(WPI_TalonFX *turretMotor) 
        : m_turretMotor(turretMotor)
        , m_currentLimit(SupplyCurrentLimitConfiguration(true, 40, 50, 0.05))
        , m_statorLimit(StatorCurrentLimitConfiguration(true, 80, 100, 0.05)) {

    m_turretMotor->ConfigFactoryDefault();

    m_turretMotor->SetInverted(TalonFXInvertType::Clockwise);

    m_turretMotor->SetNeutralMode(NeutralMode::Brake);

    m_turretMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 30);

    m_turretMotor->ConfigClosedloopRamp(0.1);

    m_turretMotor->ConfigNominalOutputForward(0, 30);
    m_turretMotor->ConfigNominalOutputReverse(0, 30);
    m_turretMotor->ConfigPeakOutputForward(1.0, 30);
    m_turretMotor->ConfigPeakOutputReverse(-1.0, 30);

    m_turretMotor->Config_kP(0, 0.13, 30);
    m_turretMotor->Config_kI(0, 0.0, 30);
    m_turretMotor->Config_kD(0, 0.0, 30);
    m_turretMotor->Config_kF(0, 0.05, 30);

    m_turretMotor->SetSelectedSensorPosition(0, 0, 0);

    m_turretMotor->ConfigSupplyCurrentLimit(m_currentLimit);
    m_turretMotor->ConfigStatorCurrentLimit(m_statorLimit);
}

void Turret::Turn(double angleInDegrees) {
    m_currentAngleInRadians = angleInDegrees; 

    // 2048 per rotation and gear ratio of 1:70
    m_turretMotor->Set(ControlMode::Position, m_currentAngleInRadians / (2 * (Constants::PI)) * 2048 * 70);
    m_tickPosition = m_currentAngleInRadians / (2 * (Constants::PI)) * 2048;
}

double Turret::SetJoystickAngle(double x, double y){

    m_currentAngleInRadians = atan2(x, y);

    return m_currentAngleInRadians;
}



void Turret::Update() {}

void Turret::DashboardUpdate() {
    frc::SmartDashboard::PutNumber("CurrAngle", m_currentAngleInRadians);
    frc::SmartDashboard::PutNumber("ticksPosition", m_tickPosition);
}


}//namespace frc973 