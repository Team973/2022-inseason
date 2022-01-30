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
     * Updates the intake subsystem 
     */
    void Update();

    /** 
     * Updates the intake subsystem in Smartdashboard
     */ 
    void DashboardUpdate();
  
private: 
    ctre::phoenix::led::CANdle *m_candle;
    ctre::phoenix::led::RainbowAnimation m_rainbow;
    ctre::phoenix::led::LarsonAnimation m_larson;
    ctre::phoenix::led::FireAnimation m_fire; // fire not work 
    ctre::phoenix::led::RgbFadeAnimation m_rgbFade;
    ctre::phoenix::led::SingleFadeAnimation m_singleFade;
    ctre::phoenix::led::ColorFlowAnimation m_flow;
    ctre::phoenix::led::StrobeAnimation m_strobe;
    ctre::phoenix::led::TwinkleAnimation m_twinkle;
    ctre::phoenix::led::TwinkleOffAnimation m_twinkleOff;
    
};
} // namespace frc973