#include "src/auto/AutoMode.h"

namespace frc973 {
AutoMode::AutoMode(std::vector<Command *> cmdList) : m_cmdList(cmdList), m_currIndex(0), m_needsInit(true) {
}

void AutoMode::Run() {
    if (IsCompleted()) {
        return;
    }

    if (m_needsInit) {
        m_cmdList[m_currIndex]->Init();
        m_needsInit = false;
    }

    m_cmdList[m_currIndex]->Run();

    if (m_cmdList[m_currIndex]->IsCompleted()) {
        m_cmdList[m_currIndex]->PostExecute();
        m_currIndex++;
        m_needsInit = true;
    }
}

bool AutoMode::IsCompleted() {
    return m_currIndex == static_cast<unsigned int>(m_cmdList.size());
}
}  // namespace frc973