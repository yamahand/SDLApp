#include "Application.h"

Application::Application(int argc, char* argv[])
{
}

Application::~Application()
{
}

bool Application::Initialize()
{
	return OnInitialize();
}

bool Application::Update()
{
	return OnUpdate();
}

bool Application::Finazlie()
{
	return OnFinalize();
}


void Application::Run()
{
	bool isSuccess = Initialize();
	if (!isSuccess) {
		return;
	}

	while (isSuccess) {
		isSuccess = Update();
	}

	Finazlie();
}


