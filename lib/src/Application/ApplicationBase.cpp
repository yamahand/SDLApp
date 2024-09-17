#include "ApplicationBase.h"

#include <iostream>
#include <functional>

#include "sdl/SDL.h"
#include "Core/Singleton.h"
#include "Core/IntrusivePtr.h"
#include "Core/FileManager.h"
#include "Logger/Logger.h"
#include "Logger/LogLevel.h"
#include "Util/Function.h"
#include "Util/ObservableVariable.h"

namespace lib {

class Hoge : public IntrusiveRefCounter<Hoge> {
public:
    Hoge() {
        std::cout << "Hoge" << std::endl;
        m_value.RegisterCallback(std::bind(&Hoge::Notify, this));
        m_value2.RegisterCallback([this](const int32_t& a, const int32_t& b) { this->Notify(); });

        m_value = 3;
        m_value2 = 3;
    }
    ~Hoge() {
        std::cout << "~Hoge" << std::endl;
    }

    void Notify() {
        LOG_INFO("app", "aaa");
    }

    ObservableVariable<int32_t> m_value = 0;
    ObservableVariable<int32_t> m_value2 = 0;
};

using HogePtr = IntrusivePtr<Hoge>;

ApplicationBase::ApplicationBase(int argc, char* argv[]) {
    LOG_INFO("app", "ApplicationBase");
    LOG_TRACE("app", "ApplicationBase {0}, {1}, {0}", __LINE__, __FILE__);

    ObservableVariable<int> var(10, [](const int& nv, const int& ov) { LOG_INFO("app", "{0} != {1}", nv, ov); });
    var.RegisterCallback([](const int& nv, const int& ov) { LOG_INFO("app", "{0} != {1}", nv, ov); });
    
    var = 10;
    var = 11;
    var = 12;
}

ApplicationBase::~ApplicationBase() {
}

bool ApplicationBase::Initialize() {
    Singleton<SDL>::GetInstance().Initialize();
    Singleton<FileManager>::GetInstance().Initialize();

    auto h = new Hoge;
    HogePtr hogePtr(h);

    hogePtr->m_value = 1;

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
