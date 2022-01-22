#include "lib/sensors/Limelight.h"

namespace frc973 {

Limelight::Limelight(const char *name) {
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

void Limelight::GetHorizontalDist() {
    // TODO: calculate horizontal distance from limelight to goal
}
    
} // namespace frc973
