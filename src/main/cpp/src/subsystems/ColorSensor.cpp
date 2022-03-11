#include "src/subsystems/ColorSensor.h"
#include <frc/DriverStation.h>

namespace frc973 {



ColorSensor::ColorSensor()
        : m_colorSensor{Constants::i2cPort} 
        , m_confidence(0.0){
    m_colorMatcher.AddColorMatch(Constants::kBlueTarget);
    m_colorMatcher.AddColorMatch(Constants::kRedTarget);

}

void ColorSensor::Update() {
    m_detectedColor = m_colorSensor.GetColor();

    /**
     * Run the color match algorithm on our detected color
     */
    double confidence = 0.0;
    frc::Color matchedColor = m_colorMatcher.MatchClosestColor(m_detectedColor, confidence);

    if (matchedColor == Constants::kBlueTarget) {
      m_colorString = "Blue";
    } else if (matchedColor == Constants::kRedTarget) {
      m_colorString = "Red";
    } else {
      m_colorString = "Unknown";
    }
}

void ColorSensor::DashboardUpdate() {
    frc::SmartDashboard::PutNumber("Red", m_detectedColor.red);
    frc::SmartDashboard::PutNumber("Blue", m_detectedColor.blue);
    frc::SmartDashboard::PutNumber("Confidence", m_confidence);
    frc::SmartDashboard::PutString("Detected Color", m_colorString);
}

void ColorSensor::GetColor(){
  std::string gameData;
  gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
  if(gameData.length() > 0)

    switch (gameData[0])
    {
      case 'B' :
      //Blue case code
        break;
      case 'R' :
      //Red case code
        break;
    default:
      //This is corrupt data
      break;
    }
}
};



