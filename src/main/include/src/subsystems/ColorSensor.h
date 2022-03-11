#pragma once

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/smartdashboard.h>
#include <frc/util/color.h>
#include <ctre/Phoenix.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "lib/bases/Subsystem.h"
#include "rev/ColorSensorV3.h"
#include "rev/ColorMatch.h"
#include "lib/Constants.h"

namespace frc973 {
    class ColorSensor : public Subsystem {
        public: 
            ColorSensor();

            void Update() override; 
        
            void DashboardUpdate() override;

            void GetColor();


        private:
            rev::ColorSensorV3 m_colorSensor;
            rev::ColorMatch m_colorMatcher;
            frc::Color m_detectedColor;
            std::string m_colorString;
            double m_confidence;

    };




}

