#include "Application.h"


namespace app {

Application::Application(int argc, char* argv[])
    : ApplicationBase(argc, argv) {
}

Application::~Application() {
}

bool Application::OnInitialize() {
    return true;
}
bool Application::OnUpdate() {
    return true;
}
bool Application::OnFinalize() {
    return true;
}

}