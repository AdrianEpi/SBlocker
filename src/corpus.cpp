/*=======================================================================================
=========================================================================================
	=                                                                              =
	=            Proyect:       Email Classifier                                   =
	=            File name:     corpus.cpp                                         =
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
/*
* @Authors: Adrian Epifanio
* 			Fabio Ovidio 
* @Date:   2021-11-05 08:37:08
* @Last Modified by:   Adrian Epifanio
* @Last Modified time: 2021-11-05 09:35:42
*/
/*------------------  FUNCTIONS  -----------------*/

#include "../include/corpus.hpp"

/*------------------------------------------------*/

/**
 * @brief      Constructs a new instance.
 */
Corpus::Corpus (void) {
	set_Name("");
	set_OutputFileName("");
	set_InputFile("");
}

/**
 * @brief      Constructs a new instance.
 *
 * @param[in]  name       The name
 * @param[in]  inputFile  The input file
 */
Corpus::Corpus (std::string name, std::string inputFile) {
	set_Name(name);
	set_OutputFileName("../outputs/corpus_" + name + ".txt");
	set_InputFile(inputFile);
}

/**
 * @brief      Destroys the object.
 */
Corpus::~Corpus (void) {
}

/**
 * @brief      Gets the name.
 *
 * @return     The name.
 */
std::string Corpus::get_Name (void) const {
	return name_;
}

/**
 * @brief      Gets the output file name.
 *
 * @return     The output file name.
 */
std::string Corpus::get_OutputFileName (void) const {
	return outputFileName_;
}

/**
 * @brief      Gets the input file.
 *
 * @return     The input file.
 */
std::string Corpus::get_InputFile (void) const {
	return inputFile_;
}

/**
 * @brief      Sets the name.
 *
 * @param[in]  newName  The new name
 */
void Corpus::set_Name (std::string newName) {
	name_ = newName;
}

/**
 * @brief      Sets the output file name.
 *
 * @param[in]  newOutputFileName  The new output file name
 */
void Corpus::set_OutputFileName (std::string newOutputFileName) {
	outputFileName_ = newOutputFileName;
}

/**
 * @brief      Sets the input file.
 *
 * @param[in]  newInputFile  The new input file
 */
void Corpus::set_InputFile (std::string newInputFile) {
	inputFile_ = newInputFile;
}

/**
 * @brief      Generates and stores the corpus data.
 *
 * @param      stopWords     The stop words
 * @param[in]  preProcesser  The pre processer
 */
void Corpus::generateCorpus (std::vector<std::string>& stopWords, PreProcesser& preProcesser) {
	Chrono myChrono;
	int dataLines;
	myChrono.startChrono();
	std::string outputFile = "../outputs/preProcesserHelper.txt";
	std::string dataType = get_Name() + ",";
	dataLines = preProcesser.loadData(inputFile_, dataType);
	preProcesser.convertLowerCase();
	preProcesser.erasePunctuationSigns();
	preProcesser.eraseAllNumbers();
	preProcesser.storeData(outputFile, 0);
	preProcesser.eraseReservedWords(stopWords, outputFile);
	preProcesser.storeData(outputFileName_, dataLines);
	myChrono.stopChrono();
	std::cout << std::endl << "Elapsed time for corpus " << name_ << ": " << myChrono.get_Seconds(5) << " seconds." << std::endl;
}


