#include "src/subsystems/Gyro.h"

namespace frc973 {
Gyro::Gyro(TalonSRX* gyroTalon) : m_gyro(PigeonIMU(gyroTalon)) {
    m_gyro.ConfigFactoryDefault();
}

double Gyro::GetWrappedAngle() {
    double currangle = std::fmod(m_gyro.GetFusedHeading() + 180, 360.0);
    if (currangle < 0) {
        currangle += 360;
    }
    currangle -= 180;

    return currangle;
}

double Gyro::GetAngle() {
    return m_gyro.GetFusedHeading();
}

double Gyro::GetAngularRate() {
    double rates[3];
    m_gyro.GetRawGyro(rates);

    return rates[2];
}

double Gyro::GetPitchAngle(){
    return m_gyro.GetPitch();
}

double Gyro::GetRollAngle(){
    return m_gyro.GetRoll();
}

void Gyro::Update() {
    m_currentAngle = GetAngle();
    m_wrappedAngle = GetWrappedAngle();
}

void Gyro::DashboardUpdate() {
    frc::SmartDashboard::PutNumber("G Angle", m_currentAngle);
    frc::SmartDashboard::PutNumber("G WrappedAngle", m_wrappedAngle);
    frc::SmartDashboard::PutNumber("G AngularRate", GetAngularRate());
}

void Gyro::SetAngle(double degrees) {
    m_gyro.SetFusedHeading(degrees, 0);
}

void Gyro::Zero() {
    m_gyro.SetFusedHeading(0, 0);
}

}  // namespace frc973