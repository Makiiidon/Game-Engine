#include "EngineTime.h"

void EngineTime::initialize()
{
	if (sharedInstance == nullptr)
	{
		sharedInstance = new EngineTime();
	}
	else 
	{
		delete sharedInstance;
	}

}

double EngineTime::getDeltaTime()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(EngineTime::sharedInstance->end - EngineTime::sharedInstance->start).count() / 100.0f;
}

EngineTime::~EngineTime()
{
	delete this;
}

void EngineTime::LogFrameStart()
{
	EngineTime::sharedInstance->start = std::chrono::system_clock::now();
}

void EngineTime::LogFrameEnd()
{
	EngineTime::sharedInstance->end = std::chrono::system_clock::now();
}
