/*=======================================================================================
=========================================================================================
    =                                                                              =
    =            Proyect:       Chrono Class                                       =
    =            File name:     Chrono.hpp                                         =
    =            Author:        Adrián Epifanio Rodríguez Hernández                =
    =            Date:          16/04/2020                                         =
    =            Language:      C++                                                =
    =            Email:         alu0101158280@ull.edu.es                           =
    =            Place:         Universidad De La Laguna                           =
    =                           Escuela Superior de Ingeniería y Tecnología        =
    =            GitHub:        AdrianEpi                                          =
    =                           https://github.com/AdrianEpi                       =
    =            Description:   Header file fo the Chrono class                    =
    =                                                                              =
=========================================================================================
=======================================================================================*/
/*------------  FUNCTIONS DECLARATION  ------------*/

#pragma once

/*-------------------------------------------------*/
/*------------  LIBRARY DECLARATION  ------------*/

#include <chrono> 
#include <ctime>
#include <string>
#include <iostream>
#include <iomanip>

/*------------------------------------------------*/

/**
 * @brief      This class describes a chrono.
 */
class Chrono {
	
	private:
		// Attribs 
		std::chrono::time_point<std::chrono::system_clock> startClock_;
		std::chrono::time_point<std::chrono::system_clock>  endClock_;
		int totalTime_;
		time_t startTime_;
		time_t endTime_;

	public:
		// Builder & Destroyer
		Chrono ();
		~Chrono ();

		// Getters & Setters
		std::chrono::time_point<std::chrono::system_clock> get_StartClock (void) const;
		std::chrono::time_point<std::chrono::system_clock> get_EndClock (void) const;
		int get_TotalTime (void) const;
		std::string get_StartTime (void) const;
		std::string get_EndTime (void) const;

		void set_StartClock (std::chrono::time_point<std::chrono::system_clock> startClock);
		void set_EndClock (std::chrono::time_point<std::chrono::system_clock> endClock);
		void set_TotalTime (int totalTime);
		void set_StartTime (void);
		void set_EndTime (void);

		// Functions
		void restartChrono (void);
		void startChrono (void);
		void stopChrono (void);
		void pauseChrono (void);
		void resumeChrono (void);

		// Return Time Functions
		float get_Seconds (void);
		float get_Seconds (int decimalAmmount);
		float get_MilliSeconds (void);
		float get_MilliSeconds (int decimalAmmount);
		float get_MicroSeconds (void);
};