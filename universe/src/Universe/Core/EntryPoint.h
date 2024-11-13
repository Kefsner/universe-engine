#pragma once
#include "Universe.h"

int main()
{
	Universe::Log::Init();

	UE_CORE_INFO("Creating Universe!");
	auto universe = Universe::CreateApplication();

	UE_CORE_INFO("Running Universe!");
	universe->Run();

	UE_CORE_INFO("Closing Universe!");
	delete universe;

	return 0;
}