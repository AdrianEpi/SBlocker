/*=======================================================================================
=========================================================================================
    =                                                                              =
    =            Proyect:       Chrono Class                                       =
    =            File name:     Chrono.cpp                                         =
    =            Author:        Adrián Epifanio Rodríguez Hernández                =
    =            Date:          16/04/2020                                         =
    =            Language:      C++                                                =
    =            Email:         alu0101158280@ull.edu.es                           =
    =            Place:         Universidad De La Laguna                           =
    =                           Escuela Superior de Ingeniería y Tecnología        =
    =            GitHub:        AdrianEpi                                          =
    =                           https://github.com/AdrianEpi                       =
    =            Description:   Source file of the Chrono Class                    =
    =                                                                              =
=========================================================================================
=======================================================================================*/
/*
* @Author: Adrián Epifanio
* @Date:   2020-04-16 10:49:23
* @Last Modified by:   Adrian Epifanio
* @Last Modified time: 2020-11-14 08:41:10
*/
/*------------  FUNCTIONS DECLARATION  ------------*/

#include "../include/Chrono.hpp"

/*-------------------------------------------------*/


/**
 * @brief      Constructs a new chrono.
 */
Chrono::Chrono () {
}

/**
 * @brief      Destroys the chrono.
 */
Chrono::~Chrono () {
}

/**
 * @brief      Gets the start clock.
 *
 * @return     The start clock.
 */
std::chrono::time_point<std::chrono::system_clock> Chrono::get_StartClock (void) const {
	return startClock_;
}

/**
 * @brief      Gets the end clock.
 *
 * @return     The end clock.
 */
std::chrono::time_point<std::chrono::system_clock> Chrono::get_EndClock (void) const {
	return endClock_;
}

/**
 * @brief      Gets the total time.
 *
 * @return     The total time.
 */
int Chrono::get_TotalTime (void) const {
	return totalTime_;
}

/**
 * @brief      Gets the start time.
 *
 * @return     The start time.
 */
std::string Chrono::get_StartTime (void) const {
	return ctime(&startTime_);

}

/**
 * @brief      Gets the end time.
 *
 * @return     The end time.
 */
std::string Chrono::get_EndTime (void) const {
	return ctime(&endTime_);
}

/**
 * @brief      Sets the start clock.
 *
 * @param[in]  startClock  The start clock
 */
void Chrono::set_StartClock (std::chrono::time_point<std::chrono::system_clock> startClock) {
	startClock_ = startClock;
}

/**
 * @brief      Sets the end clock.
 *
 * @param[in]  endClock  The end clock
 */
void Chrono::set_EndClock (std::chrono::time_point<std::chrono::system_clock> endClock) {
	endClock_ = endClock;
}

/**
 * @brief      Sets the total time.
 *
 * @param[in]  totalTime  The total time
 */
void Chrono::set_TotalTime (int totalTime) {
	totalTime_ = totalTime;
}

/**
 * @brief      Sets the start time.
 */
void Chrono::set_StartTime (void) {
    startTime_ = time(NULL);
}

/**
 * @brief      Sets the end time.
 */
void Chrono::set_EndTime (void) {
	endTime_ = time(NULL);
}

/**
 * @brief      Restarts the clock
 */
void Chrono::restartChrono (void) {
	set_TotalTime(0);
}

/**
 * @brief      Starts the chrono.
 */
void Chrono::startChrono (void) {
	restartChrono();
	set_StartTime();
	startClock_ = std::chrono::system_clock::now();
}

/**
 * @brief      Stops the chrono.
 */
void Chrono::stopChrono (void) {
	set_EndTime();
	endClock_ = std::chrono::system_clock::now();
	totalTime_ += std::chrono::duration_cast<std::chrono::microseconds>(endClock_ - startClock_).count();
}

/**
 * @brief      Pauses the chrono.
 */
void Chrono::pauseChrono (void) {
	stopChrono();
	totalTime_ += std::chrono::duration_cast<std::chrono::microseconds>(endClock_ - startClock_).count();
}

/**
 * @brief      Resumes the chrono
 */
void Chrono::resumeChrono (void) {
	startClock_ = std::chrono::system_clock::now();
}

/**
 * @brief      Gets the time in seconds.
 *
 * @return     The seconds.
 */
float Chrono::get_Seconds (void) {
	float time = totalTime_ / 1000000;
	return time;
}

/**
 * @brief      Gets the time in seconds with some decimals.
 *
 * @param[in]  decimalAmmount  The decimal ammount
 *
 * @return     The seconds.
 */
float Chrono::get_Seconds (int decimalAmmount) {
	float time = totalTime_;
	time /= 1000000;
	std::string aux = std::to_string(time);
	std::string copy = "";
	int counter = 0;
	bool decimals = false;
	for (unsigned i = 0; i < aux.size(); i++) {
		if (aux[i] == '.') {
			decimals = true;
			copy[i] = aux[i];
		}
		else if (counter < decimalAmmount) {
			if (decimals == true) {
				counter++;
			}
			copy[i] = aux[i];
		}
		else {
			break;
		}
	}	
	time = stof(copy);
	return time;
}

/**
 * @brief      Gets the time in milli seconds.
 *
 * @return     The milli seconds.
 */
float Chrono::get_MilliSeconds (void) {
	float time = totalTime_ / 1000;
	return time;
}

/**
 * @brief      Gets the time in milli seconds with some decimals.
 *
 * @param[in]  decimalAmmount  The decimal ammount
 *
 * @return     The milli seconds.
 */
float Chrono::get_MilliSeconds (int decimalAmmount) {
	float time = totalTime_;
	time /= 1000;
	std::string aux = std::to_string(time);
	std::string copy = "";
	int counter = 0;
	bool decimals = false;
	for (unsigned i = 0; i < aux.size(); i++) {
		if (aux[i] == '.') {
			decimals = true;
			copy[i] = aux[i];
		}
		else if (counter < decimalAmmount) {
			if (decimals == true) {
				counter++;
			}
			copy[i] = aux[i];
		}
		else {
			break;
		}
	}	
	time = stof(copy);
	return time;
}

/**
 * @brief      Gets the time in micro seconds.
 *
 * @return     The micro seconds.
 */
float Chrono::get_MicroSeconds (void) {
	return totalTime_;
}

