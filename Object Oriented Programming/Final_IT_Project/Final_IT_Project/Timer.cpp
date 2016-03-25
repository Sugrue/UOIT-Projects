#include <iostream>
#include "Timer.h"
#include "GL/glut.h"

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

Timer::Timer(string _name)
	{
		previousTime = glutGet(GLUT_ELAPSED_TIME);
		this->tick();
		name = _name;
	}

// ########################################################################################################################

float Timer::tick()
	{
		currentTime = glutGet(GLUT_ELAPSED_TIME);
		elapsedTime = currentTime - previousTime;
		previousTime = currentTime;
		return elapsedTime;
	}

// ########################################################################################################################

float Timer::getElapsedTimeMS()
	{
		return elapsedTime;
	}

// ========================================================================================================================

float Timer::getElapsedTimeSeconds()
	{
		return (elapsedTime/1000.f);
	}

// ========================================================================================================================

float Timer::getCurrentTime()
	{
		return currentTime;
	}

// ########################################################################################################################

void Timer::print()
	{
		cout << name << ":" << elapsedTime<<std::endl;
	}

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################