#include "ApplicationBase.h"

#include <iostream>

#include "sdl/SDL.h"
#include "Util/Singleton.h"

#include "Core/IntrusiveRefCounter.h"
#include "Core/IntrusivePtr.h"

namespace lib {

class Hoge : public IntrusiveRefCounter<Hoge> {
public:
    Hoge() {
        std::cout << "Hoge" << std::endl;
    }
    ~Hoge() {
        std::cout << "~Hoge" << std::endl;
    }
};

using HogePtr = IntrusivePtr<Hoge>;

ApplicationBase::ApplicationBase(int argc, char* argv[]) {
}

ApplicationBase::~ApplicationBase() {
}

bool ApplicationBase::Initialize() {
    Singleton<SDL>::GetInstance().Initalize();

    auto h          = new Hoge;
    HogePtr HogePtr(h);

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
