/*=======================================================================================
=========================================================================================
	=                                                                              =
	=            Proyect:       Email Classifier                                   =
	=            File name:     preProcesser.hpp                                   =
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
 * @brief      This class describes a pre processer, it makes possible to
 *             preprocess data files before using them.
 */
class PreProcesser {

	private:
		// Attributes
		std::string inputFile_;						// Input file path
		std::string outputFile_;					// Output file path where the preprocessed text will store the data
		std::string data_;							// Full stored data readed from input file

	public:
		// Builders & Destroyer
		PreProcesser (void);
		PreProcesser (std::string inputFile, std::string outpuFile);
		~PreProcesser (void);

		// Getters & Setters
		std::string get_InputFile (void) const;
		std::string get_OutputFile (void) const;
		std::string get_Data (void) const;

		void set_InputFile (std::string newInputFile);
		void set_OutputFile (std::string newOutputFile);
		void set_Data (std::string newData);

		// Operators Overload
		PreProcesser& operator= (const PreProcesser& newPreProcesser);

		// Functions
		void convertLowerCase (std::string& str);
		void convertLowerCase (void);
		void convertUpperCase (std::string& str);
		void convertUpperCase (void);
		void eraseReservedWords (std::vector<std::string>& reservedWords, std::string& fileName);
		std::string eraseReservedWords (std::string& sentence, std::vector<std::string>& reservedWords);
		void erasePunctuationSigns (std::string& str);
		void erasePunctuationSigns (void);
		void eraseURLs (std::string& str);
		void eraseURLs (void);
		void eraseHashtags (std::string& str);
		void eraseHashtags (void);
		void eraseNumbers (std::string& str);
		void eraseNumbers (void);
		void eraseAllNumbers (void);
		void eraseAllNumbers (std::string& str);

		// Read & Write
		int loadData (std::string& inputFile, std::string dataType);
		void loadTestData (std::string& inputFile);
		void printData (void);
		void storeData(std::string& outputFile, int dataLines);

};