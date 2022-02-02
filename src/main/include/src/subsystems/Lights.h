#pragma once

#include "lib/bases/Subsystem.h"
#include "src/RobotInfo.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include "ctre/phoenix/led/CANdle.h"
#include "ctre/phoenix/led/ColorFlowAnimation.h"
#include "ctre/phoenix/led/FireAnimation.h"
#include "ctre/phoenix/led/LarsonAnimation.h"
#include "ctre/phoenix/led/RainbowAnimation.h"
#include "ctre/phoenix/led/RgbFadeAnimation.h"
#include "ctre/phoenix/led/SingleFadeAnimation.h"
#include "ctre/phoenix/led/StrobeAnimation.h"
#include "ctre/phoenix/led/TwinkleAnimation.h"
#include "ctre/phoenix/led/TwinkleOffAnimation.h"

namespace frc973 {
class Lights : public Subsystem {

public:
    /** 
     * Constructs the lights subsystem 
     */
    Lights(ctre::phoenix::led::CANdle *CANdle);

    /**
     * Sets the tower state to either Off, Rainbow, Larson, RgbFade, SingleFade, ColorFlow, Strobe, Twinkle, or TwinkleOff.
     */
    enum class LightsState
    {
        Off,        /**< State for turning the off the lights. */
        Rainbow,    /**< State for setting the lights to the Rainbow animation. */
        Larson,     /**< State for setting the lights to the Larson animation. */
        RgbFade,    /**< State for setting the lights to the RgbFade animation. */
        SingleFade, /**< State for setting the lights to the SingleFade animation. */
        ColorFlow,  /**< State for setting the lights to the ColorFlow animation. */
        Strobe,     /**< State for setting the lights to the Strobe animation. */
        Twinkle,    /**< State for setting the lights to the Twinkle animation. */
        TwinkleOff  /**< State for setting the lights to the TwinkleOff animation. */
    };

    /** 
     * Updates the intake subsystem 
     */
    void Update();

    /** 
     * Updates the intake subsystem in Smartdashboard
     */ 
    void DashboardUpdate();

    /**
     * Where the state of the lights is set to
     * either Off, Rainbow, Larson, RgbFade, SingleFade, ColorFlow, Strobe, Twinkle, or TwinkleOff.
     */
    Lights::LightsState GetLightsState();

    /**
     * Where the state of the lights is set to 
     * either Off, Rainbow, Larson, RgbFade, SingleFade, ColorFlow, Strobe, Twinkle, or TwinkleOff.
     * @param state new lights state
     */
    void SetLightsState(LightsState state);

private: 
    ctre::phoenix::led::CANdle *m_candle;

    ctre::phoenix::led::RainbowAnimation m_rainbow;
    ctre::phoenix::led::LarsonAnimation m_larson;
    ctre::phoenix::led::RgbFadeAnimation m_rgbFade;
    ctre::phoenix::led::SingleFadeAnimation m_singleFade;
    ctre::phoenix::led::ColorFlowAnimation m_flow;
    ctre::phoenix::led::StrobeAnimation m_strobe;
    ctre::phoenix::led::TwinkleAnimation m_twinkle;
    ctre::phoenix::led::TwinkleOffAnimation m_twinkleOff;

    LightsState m_lightsState;
    
};
} // namespace frc973