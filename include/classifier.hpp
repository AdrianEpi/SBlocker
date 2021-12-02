/*=======================================================================================
=========================================================================================
	=                                                                              =
	=            Proyect:       Email Classifier                                   =
	=            File name:     classifier.hpp                                     =
	=            Authors:       Adrián Epifanio Rodríguez Hernández                =
	=                           Fabio Ovidio Bianchini Cano                        =
	=                           Óscar Hernández Díaz                               =
	=            Date:          05/11/2021                                         =
	=            Subject:       Inteligent Systems                                 =
	=            Language:      C++                                                =
	=            Emails:        alu0101158280@ull.edu.es                           =
	=                           alu0101040929@ull.edu.es                           =
	=                           alu0101127163@ull.edu.es                           =
	=            Place:         Universidad De La Laguna                           =
	=                           Escuela Superior de Ingeniería y Tecnología        =
	=                                                                              =
=========================================================================================
=======================================================================================*/
/*------------------  FUNCTIONS  -----------------*/

#pragma once
#include "vocabulary.hpp"
#include "Chrono.hpp"

/*------------------------------------------------*/
/*------------------  LIBRARIES  -----------------*/

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <vector>
#include <fstream>
#include <ctype.h>
#include <algorithm>

/*------------------------------------------------*/

/**
 * @brief      This class describes a classifier.
 */
class Classifier {

	private:
		// Attributes
		std::vector<std::string> inputFiles_;	// Input files vector
		std::vector<Vocabulary> class_;			// Class/vocabulary vector
		std::string data_;						// Output data will be stored here
		std::set<Token> learnedData_;			// Dicctionary with all the tokens and it respectives probabilities and class
		std::vector<std::string> resume_;		// Vector where the output resume class will be stored

	public:
		// Builders & Destroyer
		Classifier (void);
		Classifier (char* argv[], int& argc);
		~Classifier (void);

		// Getters & Setters
		std::vector<std::string> get_InputFiles (void) const;
		std::vector<Vocabulary> get_Class (void) const;
		std::string get_Data (void) const;

		void set_InputFiles (std::vector<std::string> newInputFiles);
		void set_Class (std::vector<Vocabulary> newClass);
		void set_Data (std::string newData);

		// Functions
		void classifyFile (std::string& inputFile, std::string& stopWords);
		void classify (std::vector<std::string> sentence);
		void generateClassProbability (void);
		void preProcess (std::vector<std::string>& stopWords, std::string& sentence);

		// Read & Write
		void readInputFiles (char* argv[], int& argc);
		void storeFile (std::string& outputFile, std::string& resumeFile);
};