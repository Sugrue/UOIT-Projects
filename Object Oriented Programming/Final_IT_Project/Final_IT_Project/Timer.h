#ifndef _TIMER_H_
#define _TIMER_H_

#include <string>
using namespace std;

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

class Timer // this lets us keep track of the elapsed time in our program easily so we can use it in things like physics calculations 
{
public:
	
	Timer(string _name);
	float tick();						// update the timer clock
	float getElapsedTimeMS();			// delta time in milliseconds 
	float getElapsedTimeSeconds();		// delta time in seconds
	float getCurrentTime();
	void print();

private:

	float currentTime;
	float previousTime;
	float elapsedTime;
	string name;
};

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

#endif
