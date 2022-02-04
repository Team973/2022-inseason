#include "src/subsystems/Turret.h"

namespace frc973 {

Turret::Turret(WPI_TalonFX *turretMotor) 
        : m_turretMotor(turretMotor)
        , m_currentLimit(SupplyCurrentLimitConfiguration(true, 40, 50, 0.05))
        , m_statorLimit(StatorCurrentLimitConfiguration(true, 80, 100, 0.05))
        , m_limeLightPID(0.04, 0.0, 0.0, 0)
        , m_limeLightToMotorPower(0.0)
        {

    m_turretMotor->ConfigFactoryDefault();

    m_turretMotor->SetInverted(TalonFXInvertType::CounterClockwise);

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

    // 2048 per rotation and gear ratio of 1:70
    m_turretMotor->Set(ControlMode::Position, ((angleInDegrees - gyroOffset) / 360)  * 2048 * 70);
    m_tickPosition = (angleInDegrees / 360) * 2048 * 70;
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

    // //math to set wrap around to over the intake (270 degrees native to robot)
    // if(angleInDegrees < -90) {
    //     angleInDegrees += 360;
    // }

    m_currentAngleInDegrees = angleInDegrees;
    return angleInDegrees;
}

void Turret::CalcOutput(double limeLightXOffset, double angularVelocity) {
    //double output;
    m_limeLightPID.SetTarget(0);
    double output = m_limeLightPID.CalcOutput(limeLightXOffset);

    output += (-angularVelocity * Constants::GYRO_CONSTANT); // + (m_translationalAngularRate * Constants::TRANSLATION_CONSTANT);

    m_limeLightToMotorPower = output;
    SmartDashboard::PutNumber("Angular Velocity", angularVelocity);
    SmartDashboard::PutNumber("output", output);


    m_turretMotor->Set(ControlMode::PercentOutput, output);
}

double Turret::GetTurretAngle() {
    return m_currentAngleInDegrees;
}

void Turret::CalcTransitionalCompensations(double driveVelocity, double distanceFromTarget = 0.0) {
    //converted speed to inches per sec
    double speedConverted = (driveVelocity * 10) * DRIVE_INCHES_PER_TICK;

    //The position 100ms into the future calculated by current drive velocity converted into inches into the future
    double futurePosition = speedConverted;

    double futureDistance;
    double futureAngle;

    futureDistance = sqrt(pow(distanceFromTarget, 2.0) + pow(futurePosition, 2.0) - (2 * distanceFromTarget * futurePosition * (cos(m_currentAngleInDegrees * Constants::PI / 180))));

    futureAngle = 180 - ((acos(((pow(futureDistance, 2) + pow(futurePosition, 2) - pow(distanceFromTarget, 2)) / 2 * futureDistance * futurePosition))) * 180 / Constants::PI)   ;

    //result is the rate of turning due to transitional change
    m_translationalAngularRate = (futureAngle - m_currentAngleInDegrees) / Constants::TALON_FX_VELOCITY_UNIT_MS; 

}

void Turret::SetNeutralMode(NeutralMode mode) {
    m_turretMotor->SetNeutralMode(mode);
}



void Turret::Update() {}

void Turret::DashboardUpdate() {
    frc::SmartDashboard::PutNumber("CurrAngle", m_currentAngleInDegrees);
    frc::SmartDashboard::PutNumber("ticksPosition", m_tickPosition);
    frc::SmartDashboard::PutNumber("ActualTickPosition", m_turretMotor->GetSelectedSensorPosition());
    frc::SmartDashboard::PutNumber("turretStatorCurrent", m_turretMotor->GetStatorCurrent());
    frc::SmartDashboard::PutNumber("turretOuputCurrent", m_turretMotor->GetOutputCurrent());
    frc::SmartDashboard::PutNumber("turretSupplyCurrent", m_turretMotor->GetSupplyCurrent());



}


}//namespace frc973 