/*=======================================================================================
=========================================================================================
	=                                                                              =
	=            Proyect:       Email Classifier                                   =
	=            File name:     learner.hpp                                        =
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
#include "corpus.hpp"
#include "token.hpp"

/*------------------------------------------------*/
/*------------------  LIBRARIES  -----------------*/

#include <cstring>
#include <set>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ostream>

/*------------------------------------------------*/

/**
 * @brief      This class describes a learner.
 */
class Learner {

	private:
		// Attributes
		std::vector<Vocabulary> learners_;			// The learner for each data type
		std::vector<std::string> inputCorpusFiles_;	// The input corpus file name
		std::string vocabularyFile_;				// The vocabulary file name

	public:
		// Builders & Destroyer
		Learner (void);
		Learner (char* argv[], int& argc);
		~Learner (void);

		// Getters & Setters
		std::vector<Vocabulary> get_Learners (void) const;
		std::vector<std::string> get_InputCorpusFiles (void) const;
		std::string get_VocabularyFile (void) const;

		void set_Learners (std::vector<Vocabulary> newLearners);
		void set_InputCorpusFiles (std::vector<std::string> newInputCorpusFiles);
		void set_VocabularyFile (std::string newVocabularyFile);

		// Write
		void learnAndStoreData (void);

};