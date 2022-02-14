#include "src/subsystems/Turret.h"

namespace frc973 {

Turret::Turret(WPI_TalonFX *turretMotor, DigitalInput *turretSensor) 
        : m_turretMotor(turretMotor)
        , m_turretSensor(turretSensor)
        , m_currentLimit(SupplyCurrentLimitConfiguration(true, 40, 50, 0.05))
        , m_statorLimit(StatorCurrentLimitConfiguration(true, 20, 40, 0.05))
        , m_limeLightPID(0.04, 0.0, 0.0, 0)
        , m_limeLightToMotorPower(0.0)
        , m_turretState(TurretState::Manual)
        , m_checkStatus(0)
        , m_leftSensorChecked(false)
        , m_rightSensorChecked(false)
        , m_centerSensorChecked(false)
        {
    m_turretMotor->ConfigFactoryDefault();

    m_turretMotor->SetInverted(TalonFXInvertType::Clockwise);

    m_turretMotor->SetNeutralMode(NeutralMode::Coast);

    m_turretMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 30);

    m_turretMotor->ConfigClosedloopRamp(0.1);

    m_turretMotor->ConfigNominalOutputForward(0, 30);
    m_turretMotor->ConfigNominalOutputReverse(0, 30);
    m_turretMotor->ConfigPeakOutputForward(1.0, 30);
    m_turretMotor->ConfigPeakOutputReverse(-1.0, 30);

    m_turretMotor->Config_kP(0, 0.13, 30);
    m_turretMotor->Config_kI(0, 0.0, 30);
    m_turretMotor->Config_kD(0, 0.0, 30);
    m_turretMotor->Config_kF(0, 0.0, 30);

    m_turretMotor->SetSelectedSensorPosition(0, 0, 0);

    m_turretMotor->ConfigSupplyCurrentLimit(m_currentLimit);
    m_turretMotor->ConfigStatorCurrentLimit(m_statorLimit);

    m_limeLightPID.SetTarget(0.0);
}

void Turret::Turn(double angleInDegrees, double gyroOffset) { 

    // 2048 per rotation and gear ratio of 1:TURRET_GEAR_RATIO
    m_turretMotor->Set(ControlMode::Position, ((angleInDegrees - gyroOffset) / 360)  * 2048 * TURRET_GEAR_RATIO);
    m_tickPosition = (angleInDegrees / 360) * 2048 * TURRET_GEAR_RATIO;
}

double Turret::CalcJoystickAngleInDegrees(double x, double y){
    double angleInDegrees;
    double distance;
    
    //deadband 
    distance = sqrt(pow(x, 2.0) + pow(y, 2.0)); 
    if (distance < 0.5){
        return 0.0; 
    }
    
    //converts radians to degrees after setting the location of the wrap around point.

    angleInDegrees = atan2(y, x) * 180 / Constants::PI; 

    return angleInDegrees;
}

void Turret::CalcOutput(double limeLightXOffset, double angularVelocity) {
    //double output;
    m_limeLightPID.SetTarget(0);
    double output = m_limeLightPID.CalcOutput(limeLightXOffset);

    output += (-angularVelocity * Constants::GYRO_CONSTANT); //+ (m_translationalAngularRate * Constants::TRANSLATION_CONSTANT);

    m_limeLightToMotorPower = output;
    SmartDashboard::PutNumber("output", output);


    m_turretMotor->Set(ControlMode::PercentOutput, output);
}

double Turret::GetTurretAngle() {
    return m_currentAngleInDegrees;
}

void Turret::CalcTransitionalCompensations(double driveVelocity, double distanceFromTarget) {
    //converted speed to inches per sec
    double speedConverted = driveVelocity * DRIVE_INCHES_PER_TICK * 10.0;

    //The position 100ms into the future calculated by current drive velocity converted into inches into the future
    double futurePosition = speedConverted / 10.0;

    double futureDistance = 0.0;
    double futureAngle = 0.0;

    // futureDistance = sqrt(pow(36, 2) + pow(5, 2) - (2.0 * 36 * 5 * (cos(86.018 * Constants::PI / 180.0))));
    futureDistance = sqrt(pow(distanceFromTarget, 2) + pow(futurePosition, 2) - (2.0 * distanceFromTarget * futurePosition * (cos(m_currentAngleInDegrees * Constants::PI / 180.0))));

    // futureAngle = 180.0 - ((acos(((pow(36, 2) + pow(5, 2) - pow(36, 2)) / (2.0 * 36 * 5)))) * 180 / Constants::PI);
    futureAngle = 180.0 - ((acos(((pow(futureDistance, 2) + pow(futurePosition, 2) - pow(distanceFromTarget, 2)) / (2.0 * futureDistance * futurePosition)))) * 180.0 / Constants::PI);
    SmartDashboard::PutNumber("Future Angle", futureAngle);

    //result is the rate of turning due to transitional change
    m_translationalAngularRate = (futureAngle - m_currentAngleInDegrees) / 0.1; 
    SmartDashboard::PutNumber("transanglerate", m_translationalAngularRate);
    SmartDashboard::PutNumber("Future Distance", futureDistance);
    SmartDashboard::PutNumber("Future Position", futurePosition);

}

void Turret::SetNeutralMode(NeutralMode mode) {
    m_turretMotor->SetNeutralMode(mode);
}

void Turret::SetTurretAngle(double angle){
    m_turretMotor->SetSelectedSensorPosition(angle / 360 * 2048 * TURRET_GEAR_RATIO);
}

void Turret::SetHomeOffset(){
    Turret::SetTurretAngle(Constants::TURRET_HOME_OFFSET);
}

void Turret::CheckedSensorsToFalse() {
    m_leftSensorChecked = false;
    m_rightSensorChecked = false;
    m_centerSensorChecked = false;
    m_checkStatus = 0;
}

int Turret::SensorCalibrate(bool leftTripped, bool rightTripped, bool centerTripped) {

    if(centerTripped == true) {
        m_checkStatus = 1;

        if(leftTripped == true) {
            m_checkStatus = 2;

            if(rightTripped == true) {
                if(m_checkStatus == 3) {
                    return m_checkStatus;
                }
            
                m_checkStatus = 3;
                m_rightSideTurnSensor = m_turretMotor->GetSelectedSensorPosition();
                return m_checkStatus;
            }
            m_leftSideTurnSensor = m_turretMotor->GetSelectedSensorPosition();
            return m_checkStatus;
        }
        SetHomeOffset();
        return m_checkStatus;
    }
    
    return m_checkStatus;
}

void Turret::Update() {
    m_currentAngleInDegrees = m_turretMotor->GetSelectedSensorPosition() / TURRET_GEAR_RATIO / 2048 * 360;

    switch (m_turretState) {
        case TurretState::Off:
            break;
        case TurretState::Manual:
            break;
        case TurretState::AutoAim:
            break;
    }
}

void Turret::DashboardUpdate() {
    frc::SmartDashboard::PutNumber("CurrAngle", m_currentAngleInDegrees);
    frc::SmartDashboard::PutNumber("ticksPosition", m_tickPosition);
    frc::SmartDashboard::PutNumber("ActualTickPosition", m_turretMotor->GetSelectedSensorPosition());
    frc::SmartDashboard::PutNumber("turretStatorCurrent", m_turretMotor->GetStatorCurrent());
    frc::SmartDashboard::PutNumber("turretOuputCurrent", m_turretMotor->GetOutputCurrent());
    frc::SmartDashboard::PutNumber("turretSupplyCurrent", m_turretMotor->GetSupplyCurrent());
    frc::SmartDashboard::PutNumber("Left Sensor", m_leftSideTurnSensor);
    frc::SmartDashboard::PutNumber("Right Sensor", m_rightSideTurnSensor);


    SmartDashboard::PutBoolean("turret digital input", m_turretSensor->Get());
    //right side limit switch
    SmartDashboard::PutBoolean("turret fwd sensor", m_turretMotor->IsFwdLimitSwitchClosed());
    //left side limit switch
    SmartDashboard::PutBoolean("turret rev sensor", m_turretMotor->IsRevLimitSwitchClosed());
}

}//namespace frc973 