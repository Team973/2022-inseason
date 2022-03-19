#include "lib/sensors/Limelight.h"

namespace frc973 {

Limelight::Limelight(const char *name)
        : m_limelightSensor(nt::NetworkTableInstance::GetDefault().GetTable(name))
        , m_lightMode(LightMode::standard)
        , m_pipelineMode(PipelineMode::driverCamera)
        , m_previousLatency(0.0) {
}

void Limelight::SetLightMode(LightMode mode) {
    switch (mode) {
        case LightMode::standard:
            m_limelightSensor->PutNumber("ledMode", 0);
            break;
        case LightMode::on:
            m_limelightSensor->PutNumber("ledmode", 3);
            break;
        case LightMode::off:
            m_limelightSensor->PutNumber("ledmode", 1);
            break;
        case LightMode::blink:
            m_limelightSensor->PutNumber("ledmode", 2);
            break;
    }
}

void Limelight::SetPipelineMode(PipelineMode mode) {
    switch (mode) {
        case PipelineMode::driverCamera:
            m_limelightSensor->PutNumber("pipeline", 0);
            break;
        case PipelineMode::pipeline_1:
            m_limelightSensor->PutNumber("pipeline", 1);
            break;
        case PipelineMode::pipeline_2:
            m_limelightSensor->PutNumber("pipeline", 2);
            break;
        case PipelineMode::pipeline_3:
            m_limelightSensor->PutNumber("pipeline", 3);
            break;
        case PipelineMode::pipeline_4:
            m_limelightSensor->PutNumber("pipeline", 4);
            break;
        default:
            m_limelightSensor->PutNumber("pipeline", 0);
            break;
    }
}

void Limelight::SetCameraDriver() {
    SetPipelineMode(PipelineMode::driverCamera);
}

void Limelight::SetVisionCamera() {
    SetPipelineMode(PipelineMode::pipeline_2);
}

double Limelight::GetPipeline() {
    return m_limelightSensor->GetNumber("pipeline", 97.3);
}

double Limelight::GetXOffset() {
    return m_limelightSensor->GetNumber("tx", 0.0);
}

double Limelight::GetYOffset() {
    return m_limelightSensor->GetNumber("ty", 0.0);
}

double Limelight::GetTargetArea() {
    return m_limelightSensor->GetNumber("ta", 0.0);
}

double Limelight::GetTargetLatency() {
    double min = 11;
    return m_limelightSensor->GetNumber("tl", 0.0) + min;
}

bool Limelight::isTargetValid() {
    return m_limelightSensor->GetNumber("tv", 0.0);
}

bool Limelight::IsLimelightDead() {
    if (GetTargetLatency() == m_previousLatency) {
        m_previousLatency = GetTargetLatency();
        return true;
    } else {
        m_previousLatency = GetTargetLatency();
        return false;
    }
}

double Limelight::GetHorizontalDist() {
    double y_calc = TARGET_HEIGHT - CAMERA_HEIGHT;
    double angle_calc = (CAMERA_ANGLE + GetYOffset()) * Constants::RAD_PER_DEG;

    double x_calc = y_calc / (std::tan(angle_calc));

    return x_calc;
}

double Limelight::GetHorizontalDistWithComp(double pitch, double turretAngle) {
    double y_calc = TARGET_HEIGHT - CAMERA_HEIGHT;
    double angle_calc = (CAMERA_ANGLE + GetYOffset() + ((pitch + 3.7) * std::cos(turretAngle * Constants::RAD_PER_DEG))) * Constants::RAD_PER_DEG;
    double x_calc = y_calc / (std::tan(angle_calc));

    return x_calc;
}

}  // namespace frc973
