#pragma once

#include <iostream>

#include <networktables/NetworkTable.h>

#include "lib/Constants.h"

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
        driverCamera,      /**< The regular camera, no reflection. Pipeline 0 */           
        pipeline_1,         /**< Pipeline 1 */  
        pipeline_2,         /**< Pipeline 2 */ 
        pipeline_3,         /**< Pipeline 3 */ 
        pipeline_4          /**< Pipeline 4 */ 
    };

    /**
     * Sets the limelight sensor pipeline
     */ 
    void SetPipelineMode(PipelineMode mode);

    /**
     * Sets the pipeline to the one with driver camera (pipeline 0)
     */
    void SetCameraDriver();

    /**
     * Gets the pipeline that is currently used
     * @return the current pipeline
     */ 
    double GetPipeline();
    
    /**
     * Gets target X offset in degrees
     * @return target X offset
     */ 
    double GetXOffset();

    /**
     * Gets target Y offset in degrees
     * @return target Y offset
     */ 
    double GetYOffset();

    /**
     * Gets the target area
     * @return the target area
     */ 
    double GetTargetArea();

     /**
      * Gets the distance from the limelight to the target in the horizontal direction
      */
    void GetHorizontalDist(); 

private:
    std::shared_ptr<nt::NetworkTable> m_limelightSensor;

    PipelineMode m_pipelineMode;

    static constexpr double TARGET_HEIGHT = 1; /**< Target's height in inches from ground TODO: UPDATE VALUE*/
    static constexpr double CAMERA_HEIGHT = 1; /**< Camera's Height in inches from ground TODO: UPDATE VALUE*/
    static constexpr double CAMERA_ANGLE = 
            1 * (Constants::PI / 180.0); /**< Camera Angle in degrees wrt ground TODO: UPDATE VALUE*/
            // ### for comp; ### for pbot
    static constexpr double CAMERA_BUMPER_OFFSET = 1; /**< The offset in inches between the camera and the bumper edge TODO: UPDATE VALUE*/
};  
} // namespace frc973
