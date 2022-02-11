#include "src/auto/commands/SequentialCommand.h"

namespace frc973 {
SequentialCommand::SequentialCommand(std::vector<Command*> cmdList)
        : m_cmdList(cmdList), m_currIndex(0), m_needsInit(true) {
}

void SequentialCommand::Init() {
}

void SequentialCommand::Run() {
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

bool SequentialCommand::IsCompleted() {
    return m_currIndex == static_cast<unsigned int>(m_cmdList.size());
}
void SequentialCommand::PostExecute() {
    return;
}
}
