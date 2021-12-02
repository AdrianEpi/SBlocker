/*=======================================================================================
=========================================================================================
	=                                                                              =
	=            Proyect:       Email Classifier                                   =
	=            File name:     preProcesser.cpp                                   =
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
/*
* @Authors: Adrian Epifanio
* 			Fabio Ovidio 
* 			Oscar Hernandez 
* @Date:   2021-11-05 08:37:08
* @Last Modified by:   Adrian Epifanio
* @Last Modified time: 2021-12-02 18:32:26
*/
/*------------------  FUNCTIONS  -----------------*/

#include "../include/preProcesser.hpp"

/*------------------------------------------------*/

/**
 * @brief      Constructs a new instance.
 */
PreProcesser::PreProcesser (void) {
	set_InputFile("");
	set_OutputFile("");
	set_Data("");
}

/**
 * @brief      Constructs a new instance.
 *
 * @param[in]  inputFile  The input file
 * @param[in]  outpuFile  The outpu file
 */
PreProcesser::PreProcesser (std::string inputFile, std::string outpuFile) {
	set_InputFile(inputFile);
	set_OutputFile(outpuFile);
	set_Data("");
}

/**
 * @brief      Destroys the object.
 */
PreProcesser::~PreProcesser (void) {
}

/**
 * @brief      Gets the input file.
 *
 * @return     The input file.
 */
std::string PreProcesser::get_InputFile (void) const {
	return inputFile_;
}

/**
 * @brief      Gets the output file.
 *
 * @return     The output file.
 */
std::string PreProcesser::get_OutputFile (void) const {
	return outputFile_;
}

/**
 * @brief      Gets the data.
 *
 * @return     The data.
 */
std::string PreProcesser::get_Data (void) const {
	return data_;
}

/**
 * @brief      Sets the input file.
 *
 * @param[in]  newInputFile  The new input file
 */
void PreProcesser::set_InputFile (std::string newInputFile) {
	inputFile_ = newInputFile;
}

/**
 * @brief      Sets the output file.
 *
 * @param[in]  newOutputFile  The new output file
 */
void PreProcesser::set_OutputFile (std::string newOutputFile) {
	outputFile_ = newOutputFile;
}

/**
 * @brief      Sets the data.
 *
 * @param[in]  newData  The new data
 */
void PreProcesser::set_Data (std::string newData) {
	data_ = newData;
}

/**
 * @brief      Assignment operator.
 *
 * @param[in]  newPreProcesser  The new pre processer
 *
 * @return     The result of the assignment
 */
PreProcesser& PreProcesser::operator= (const PreProcesser& newPreProcesser) {
	this -> set_Data(newPreProcesser.get_Data());
	this -> set_OutputFile(newPreProcesser.get_OutputFile());
	this -> set_InputFile(newPreProcesser.get_InputFile());
	return *this;
}

/**
 * @brief      Converts all the str into Lower Case
 *
 * @param      str   The string
 */
void PreProcesser::convertLowerCase (std::string& str) {
	set_Data(str);
	convertLowerCase();
	str = get_Data();
}

/**
 * @brief      Converts all the data into Lower Case
 */
void PreProcesser::convertLowerCase (void) {
	std::transform(data_.begin(), data_.end(),data_.begin(), ::tolower);
}

/**
 * @brief      Converts all the str into Upper Case
 *
 * @param      str   The string
 */
void PreProcesser::convertUpperCase (std::string& str) {
	set_Data(str);
	convertUpperCase();
	str = get_Data();
}

/**
 * @brief      Converts all the data into Upper Case
 */
void PreProcesser::convertUpperCase (void) {
	std::transform(data_.begin(), data_.end(),data_.begin(), ::toupper);
}

/**
 * @brief      Deletes all the words from the vector in the given file and
 *             stores them into the same file.
 *
 * @param[in]  reservedWords  The reserved words vector
 * @param[in]  fileName       The file name
 */
void PreProcesser::eraseReservedWords (std::vector<std::string>& reservedWords, std::string& fileName) {
	std::ifstream file(fileName, std::ios::in);
	data_ = "";
	if (file.fail()) {
		std::cout << std::endl << "Error 404, file not found in eraseReservedWords function." << std::endl;
		exit(1);
	}
	std::string aux = "";
	while (!file.eof()) {
		file >> aux;
		bool push = true;
		for (unsigned i = 0; i < reservedWords.size(); i++) {
			if (aux == reservedWords[i]) {
				push = false;
				break;
			}
		}
		if (push) {
			data_ += ' ' + aux;
		}
	}
	file.close();
	storeData(fileName, 0);
}

/**
 * @brief      Deletes all the words from the vector in the given string and
 *             returns it
 *
 * @param[in]  reservedWords  The reserved words vector
 * @param[in]  sentence       The sentence
 *
 * @return     The string without the reserved words.
 */
std::string PreProcesser::eraseReservedWords (std::string& sentence, std::vector<std::string>& reservedWords) {
	std::string result = "";
	std::string tmp = "";
	for (unsigned j = 0; j < sentence.length(); j++) {
		if (sentence[j] != ' ' && sentence[j] != '\t') {
			tmp += sentence[j];
		}
		else {
			bool push = true;
			for (unsigned i = 0; i < reservedWords.size(); i++) {
				if (tmp == reservedWords[i]) {
					push = false;
					break;
				}
			}
			if (push) {
				result += tmp + " ";
			}
			tmp = "";
		}
	}
	return result;
}

/**
 * @brief      Erases all punctuation sings into readed data.
 *
 * @param      str   The string
 */
void PreProcesser::erasePunctuationSigns (std::string& str) {
	set_Data(str);
	erasePunctuationSigns();
	str = get_Data();
}

/**
 * @brief      Erases all punctuation sings into readed data.
 */
void PreProcesser::erasePunctuationSigns (void) {
	for (unsigned i = 0; i < data_.length(); i++) {
		if (!isalpha(data_[i]) && !isdigit(data_[i]) && data_[i] != '\n' && data_[i] != '\r') {
			data_[i] = ' ';
		}
	}
}

/**
 * @brief      Erases all URLs into data var, an URL is defined as a '.' between
 *             letters without spaces.
 *
 * @param      str   The string
 */
void PreProcesser::eraseURLs (std::string& str) {
	set_Data(str);
	eraseURLs();
	str = get_Data();
}

/**
 * @brief      Erases all URLs into data var, an URL is defined as a '.' between
 *             letters without spaces. (Careful with float numbers)
 */
void PreProcesser::eraseURLs (void) {
	for (unsigned i = 0; i < data_.length(); i++) {
		if (data_[i] == '.' && data_[i + 1] != ' ') {
			unsigned k = i;
			while (data_[k] != ' ') {
				data_[k] = ' ';
				k--;
			}
			while (data_[i] != ' ') {
				data_[i] = ' ';
				i++;
			}
		}
	}
}

/**
 * @brief      Erases all Hashtags into data var.
 *
 * @param      str   The string
 */
void PreProcesser::eraseHashtags (std::string& str) {
	set_Data(str);
	eraseHashtags();
	str = get_Data();
}

/**
 * @brief      Erases all Hashtags into data var.
 *
 */
void PreProcesser::eraseHashtags (void) {
	for (unsigned i = 0; i < data_.length(); i++) {
		if (data_[i] == '#') {
			data_[i] = ' ';
			while (data_[i] != ' ') {
				data_[i] = ' ';
				i++;
			}
		}
	}
}

/**
 * @brief      Erases all numbers and characters form a readen number till next
 *             space.
 *
 * @param      str   The string
 */
void PreProcesser::eraseNumbers (std::string& str) {
	set_Data(str);
	eraseNumbers();
	str = get_Data();
}

/**
 * @brief      Erases all numbers and characters form a readen number till next
 *             space.
 */
void PreProcesser::eraseNumbers (void) {
	if (isdigit(data_[0])) {
		unsigned i = 0;
		while (data_[i] != ' ') {
			data_[i] = ' ';
			i++;
		}
	}
	for (unsigned i = 1; i < data_.length(); i++) {
		if (isdigit(data_[i]) && data_[i - 1] == ' ') {
			while (data_[i] != ' ') {
				data_[i] = ' ';
				i++;
			}
		}
	}
}

/**
 * @brief      Erases all words that contains numbers and all numbers in data.
 */
void PreProcesser::eraseAllNumbers (void) {
	if (isdigit(data_[0])) {
		unsigned i = 0;
		while (data_[i] != ' ') {
			data_[i] = ' ';
			i++;
		}
	}
	for (unsigned i = 1; i < data_.length(); i++) {
		if (isdigit(data_[i])) {
			if (data_[i - 1] != ' ') {
				unsigned k = i - 1;
				while (data_[k] != ' ' && k > 0) {
					data_[k] = ' ';
					k--;
				}
			}
			while (data_[i] != ' ' && i < data_.size()) {
				data_[i] = ' ';
				i++;
			}
		}
	}
}

/**
 * @brief      Erases all words that contains numbers and all numbers in given
 *             string.
 *
 * @param      str   The string
 */
void PreProcesser::eraseAllNumbers (std::string& str) {
	set_Data(str);
	eraseAllNumbers();
	str = get_Data();
}

/**
 * @brief      Loads the data that starts with the dataTpe from input file into
 *             data var.
 *
 * @param      inputFile  The input file
 * @param[in]  dataType   The data type that wants to be loaded (must be the
 *                        first word per line)
 *
 * @return     Data lines included.
 */
int PreProcesser::loadData (std::string& inputFile, std::string dataType) {
	data_ = "";
	int dataLines = 0;
	std::ifstream file(inputFile, std::ios::in);
	if (file.fail()) {
		std::cout << std::endl << "Error 404, file not found in loadData function." << std::endl;
		exit(1);
	}
	std::string aux = "";
	while (!file.eof()) {
		file >> aux;
		if (dataType == "" ) {
			data_ += aux + " ";
			std::getline(file, aux);
			data_ += aux;
			dataLines++;
		}
		else {
			if (aux.length() < dataType.length()) {
				std::string spacedName = "";
				while (aux.length() < dataType.length()) {
					file >> spacedName;
					aux += " " + spacedName;
				}
			}
			std::string readedType = aux.substr(0, dataType.length());
			aux = aux.substr(dataType.length(), aux.length());
			std::getline(file, aux);
			if (readedType == dataType) {				
				data_ += aux;
				dataLines++;
			}
		}
		
	}
	file.close();
	return dataLines;
}

/**
 * @brief      Loads the test data.
 *
 * @param      inputFile  The input file
 */
void PreProcesser::loadTestData (std::string& inputFile) {
	data_ = "";
	const std::string ENDL = " PREPROCESSERENDL "; // Var that is going to be used in classifier to detects the end of a line
	std::ifstream file(inputFile, std::ios::in);
	if (file.fail()) {
		std::cout << std::endl << "Error 404, file not found in loadTestData function." << std::endl;
		exit(1);
	}
	std::string aux = "";
	while (!file.eof()) {
		std::getline(file, aux);
		data_ += aux + ENDL;	
	}
	file.close();
}

/**
 * @brief      Prints data var.
 */
void PreProcesser::printData  (void) {
	std::cout << data_;
}

/**
 * @brief      Stores the data into the given file
 *
 * @param      outputFile  The output file
 * @param[in]  dataLines   The data lines
 */
void PreProcesser::storeData(std::string& outputFile, int dataLines) {
	std::fstream file(outputFile, std::ios::out | std::ios::trunc);
	
	if (file.fail()) {
		std::cout << "Error while storing data \"" << outputFile << "\" is not valid document" << std::endl;
		exit(1);
	} 
	else { 
		if (dataLines != 0) {
			file << dataLines << std::endl;
		}
		file << data_;
	}
	file.close();
}