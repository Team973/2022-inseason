#pragma once

#include <networktables/NetworkTableInstance.h>

#include <iostream>

#include "frc/smartdashboard/SmartDashboard.h"
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
     * Limelight LED Modes.
     */
    enum class LightMode {
        standard, /**< The light mode decided by the pipeline. */
        on,       /**< The light mode that forces LEDs on. */
        off,      /**< The light mode that forces LEDs off. */
        blink     /**< The light mode that forces LEDs to blink. */
    };

    /**
     * Limelight Pipeline Modes.
     */
    enum class PipelineMode {
        driverCamera, /**< The regular camera, no reflection. Pipeline 0 */
        pipeline_1,   /**< Pipeline 1 */
        pipeline_2,   /**< Pipeline 2 */
        pipeline_3,   /**< Pipeline 3 */
        pipeline_4    /**< Pipeline 4 */
    };

    /**
     * Set Limelight light mode.
     */
    void SetLightMode(LightMode mode);

    /**
     * Sets the limelight sensor pipeline
     * @param mode the pipeline that the limelight will be in
     */
    void SetPipelineMode(PipelineMode mode);

    /**
     * Sets the pipeline to the one with driver camera (pipeline 0)
     */
    void SetCameraDriver();

    void SetVisionCamera();

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
     * Gets the delay of finding the target
     * @return the target latency
     */
    double GetTargetLatency();

    /**
     * Checks if limelight sees a target.
     * @return if on target.
     */
    bool isTargetValid();

    /**
     * Checks if the limelight is dead or not
     * @return if the limelight is dead
     */
    bool IsLimelightDead();

    /**
     * Gets the distance from the limelight to the target in the horizontal direction
     */
    double GetHorizontalDist();

private:
    std::shared_ptr<nt::NetworkTable> m_limelightSensor;

    LightMode m_lightMode;
    PipelineMode m_pipelineMode;

    double m_previousLatency;

    static constexpr double TARGET_HEIGHT =
        31.0; /**< Target's height in inches from ground TODO: UPDATE VALUE - current cf*/
    static constexpr double CAMERA_HEIGHT = 20.0; /**< Camera's Height in inches from ground TODO: UPDATE VALUE*/
    static constexpr double CAMERA_ANGLE =
        33.0; /**< Camera Angle in degrees wrt ground TODO: UPDATE VALUE - current cf*/
              // ### for comp; ### for pbot
    static constexpr double CAMERA_BUMPER_OFFSET =
        1; /**< The offset in inches between the camera and the bumper edge TODO: UPDATE VALUE - current cf*/
};
}  // namespace frc973
