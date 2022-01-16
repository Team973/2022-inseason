#pragma once

#include <iostream>

#include <networktables/NetworkTableInstance.h>

namespace frc973 {
/**
 * Limelight Camera Class
 */ 
class Limelight {
public:
    /**
     * Construct the Limelight Sensor
     */ 
    Limelight(const char *name);

    /**
     * Limelight Pipeline Modes.
     */
    enum class PipelineMode
    {
        pipeline_0,            
        pipeline_1,       
        pipeline_2,        
        pipeline_3, 
        pipeline_4  
    };

    /**
     * Sets the limelight sensor pipeline
     */ 
    void SetPipelineMode(PipelineMode mode);

private:
    double m_limelightSensor;

    PipelineMode m_pipelineMode;
};  
} // namespace frc973
