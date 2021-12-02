/*=======================================================================================
=========================================================================================
	=                                                                              =
	=            Proyect:       Email Classifier                                   =
	=            File name:     vocabulary.hpp                                     =
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
#include "preProcesser.hpp"
#include "Chrono.hpp"
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
 * @brief      This class describes a vocabulary and 
 */
class Vocabulary {

	private:
		// Attributes
		std::string inputFile_;			// Input file path
		std::string outpuFile_;			// Output file where the vocabulary will be stored
		int vocabularyCounter_;			// Number of different words in the vocabulary
		int nTokens_;					// Number of words in the text
		int nLines_;					// Number of lines readed from file;
		std::set<Token> vocabulary_;	// Set with all the vocabulary
		std::string type_;				// The vocabulary type (if aplicable)
		float classProbability_;		// The class probability (if aplicable)

	public:
		// Builders & Destroyer
		Vocabulary (void);
		Vocabulary (std::string inputFile, std::string outpuFile);
		~Vocabulary (void);

		// Getters & Setters
		std::string get_InputFile (void) const;
		std::string get_OutpuFile (void) const;
		int get_VocabularyCounter (void) const;
		int get_NTokens (void) const;
		int get_NLines (void) const;
		std::set<Token> get_Vocabulary (void) const;
		std::string get_Type (void) const;
		float get_ClassProbability (void) const;

		void set_InputFile (std::string newInputFile);
		void set_OutpuFile (std::string newOutpuFile);
		void set_VocabularyCounter (int newVocabularyCounter);
		void set_NTokens (int newNTokens);
		void set_NLines (int newNLines);
		void set_Vocabulary (std::set<Token> newVocabulary);
		void set_Type (std::string newType);
		void set_ClassProbability (float newClassProbability);

		// Operators Overload
		Vocabulary& operator= (const Vocabulary& newVocabulary);

		// Functions
		void preProcessData (std::string& stopWordFile);
		std::vector<std::string> loadStopWord (std::string& inputFile);
		void generateVocabulary (std::string& inputFile, bool tokenized);
		void calculateProbabilities (void);
		void addClassProbability (int size);

		// Write
		void readVocabulary (std::string& inputFile);
		void storeVocabulary (std::string& outputFile);
		void readLearnedData (std::string& inputFile);
};