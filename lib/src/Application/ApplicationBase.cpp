#include "ApplicationBase.h"

#include "sdl/SDL.h"

namespace lib {

ApplicationBase::ApplicationBase(int argc, char* argv[]) {
}

ApplicationBase::~ApplicationBase() {
}

bool ApplicationBase::Initialize() {
    m_sdl = std::make_unique<SDL>();
    m_sdl->Initalize();

    return OnInitialize();
}

bool ApplicationBase::Update() {
    m_sdl->BeginFrame();
    bool isContinue = OnUpdate();
    m_sdl->EndFrame();
    if (m_sdl->IsEnd()) {
        isContinue = false;
    }
    return isContinue;
}

bool ApplicationBase::Finazlie() {
    m_sdl->FInalize();
    m_sdl.reset();
    return OnFinalize();
}

void ApplicationBase::Run() {
    bool isSuccess = Initialize();
    if (!isSuccess) {
        return;
    }

    while (isSuccess) {
        isSuccess = Update();
    }

    Finazlie();
}
}  // namespace lib
