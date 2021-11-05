/*=======================================================================================
=========================================================================================
	=                                                                              =
	=            Proyect:       Email Classifier                                   =
	=            File name:     corpus.hpp                                         =
	=            Authors:       Adrián Epifanio Rodríguez Hernández                =
	=                           Fabio Ovidio Bianchini Cano                        =
	=            Date:          05/11/2021                                         =
	=            Subject:       Inteligent Systems                                 =
	=            Language:      C++                                                =
	=            Emails:        alu0101158280@ull.edu.es                           =
	=                           alu0101040929@ull.edu.es                           =
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
 * @brief      This class describes a corpus.
 */
class Corpus {

	private:
		// Attributes
		std::string name_;				// The corpus name or data type
		std::string outputFileName_;	// The output file name
		std::string inputFile_;			// The input file name

	public:
		// Builders & Destroyer
		Corpus (void);
		Corpus (std::string name, std::string inputFile);
		~Corpus (void);

		// Getters & Setters
		std::string get_Name (void) const;
		std::string get_OutputFileName (void) const;
		std::string get_InputFile (void) const;

		void set_Name (std::string newName);
		void set_OutputFileName (std::string newOutputFileName);
		void set_InputFile (std::string newInputFile);

		// Functions
		void generateCorpus (std::vector<std::string>& stopWords, PreProcesser& preProcesser);

};