#include "ApplicationBase.h"

#include "sdl/SDL.h"
#include "Util/Singleton.h"

namespace lib {

ApplicationBase::ApplicationBase(int argc, char* argv[]) {
}

ApplicationBase::~ApplicationBase() {
}

bool ApplicationBase::Initialize() {
    Singleton<SDL>::GetInstance().Initalize();

    return OnInitialize();
}

void ApplicationBase::Update() {
    Singleton<SDL>::GetInstance().BeginFrame();
    OnUpdate();
    Singleton<SDL>::GetInstance().EndFrame();
    if (Singleton<SDL>::GetInstance().IsEnd()) {
    }
}

void ApplicationBase::Finazlie() {
    Singleton<SDL>::GetInstance().FInalize();
    return OnFinalize();
}

void ApplicationBase::Run() {
    bool isSuccess = Initialize();
    if (!isSuccess) {
        return;
    }

    while (isSuccess) {
        Update();
    }

    Finazlie();
}
}  // namespace lib
