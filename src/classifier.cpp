/*=======================================================================================
=========================================================================================
	=                                                                              =
	=            Proyect:       Email Classifier                                   =
	=            File name:     classifier.cpp                                     =
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
* @Last Modified by:   ADRIAN
* @Last Modified time: 2021-12-19 23:01:25
*/
/*------------------  FUNCTIONS  -----------------*/

#include "../include/classifier.hpp"

/*------------------------------------------------*/

/**
 * @brief      Constructs a new instance.
 */
Classifier::Classifier (void) {
	set_Data("");
}

/**
 * @brief      Constructs a new instance.
 *
 * @param      argv  The arguments array
 * @param      argc  The count of arguments
 */
Classifier::Classifier (char* argv[], int& argc) {
	set_Data("");
	readInputFiles(argv, argc);
	generateClassProbability();
	std::string input = argv[2];
	std::string stopWords = argv[3];
	classifyFile(input, stopWords);
	std::string outputFile = "../outputs/classification.csv";
	std::string resume = "../outputs/resume.csv";
	storeFile(outputFile, resume);
}

/**
 * @brief      Destroys the object.
 */
Classifier::~Classifier (void) {
}

/**
 * @brief      Gets the input files.
 *
 * @return     The input files.
 */
std::vector<std::string> Classifier::get_InputFiles (void) const {
	return inputFiles_;
}

/**
 * @brief      Gets the learned data.
 *
 * @return     The learned data.
 */
std::vector<Vocabulary> Classifier::get_Class (void) const {
	return class_;
}

/**
 * @brief      Gets the data.
 *
 * @return     The data.
 */
std::string Classifier::get_Data (void) const {
	return data_;
}

/**
 * @brief      Sets the input files.
 *
 * @param[in]  newInputFiles  The new input files
 */
void Classifier::set_InputFiles (std::vector<std::string> newInputFiles) {
	inputFiles_ = newInputFiles;
}

/**
 * @brief      Sets the learned data.
 *
 * @param[in]  newClass  The new learned data
 */
void Classifier::set_Class (std::vector<Vocabulary> newClass) {
	class_ = newClass;
}

/**
 * @brief      Sets the data.
 *
 * @param[in]  newData  The new data
 */
void Classifier::set_Data (std::string newData) {
	data_ = newData;
}

/**
 * @brief      Preprocess, calculates the probabilities and classifies the given
 *             input file.
 *
 * @param      inputFile      The input file with the testCorpus
 * @param      stopWordsFile  The stop words file for preprocessing use
 */
void Classifier::classifyFile (std::string& inputFile, std::string& stopWordsFile) {
	Vocabulary voc;
	std::vector<std::string> stopWord;
	stopWord = voc.loadStopWord(stopWordsFile);
	std::string tmp;
	preProcess(stopWord, inputFile);
	std::string helper = "../outputs/preProcesserHelper.txt";
	std::ifstream file(helper, std::ios::in);
	std::ifstream originalFile(inputFile, std::ios::in);
	Chrono myChrono;
	myChrono.startChrono();
	if (file.fail() || originalFile.fail()) {
		std::cout << std::endl << "Error 404, preProcesserHelper.txt file not found in /outputs." << std::endl;
		exit(1);
	}
	std::string originalReader = "";
	while (!file.eof()) {
		std::vector<std::string> sentence; 
		std::string tmp = "";
		while (!file.eof()) {
			file >> tmp;
			if (tmp == "preprocesserendl") {
				break;
			}
			sentence.push_back(tmp);
		}
		std::getline(originalFile, originalReader);
		if (originalReader[originalReader.length() -1] == '\r') {
			originalReader[originalReader.length() -1] = ' ';
		}
		data_ += originalReader;
		classify(sentence);
	}
	file.close();
	originalFile.close();
	myChrono.stopChrono();
	std::cout << std::endl << "Elapsed Classifying time: " << myChrono.get_Seconds(5) << " seconds." << std::endl;
}

/**
 * @brief      Classifies a given sentence into the correct type and stores the
 *             information into data var.
 *
 * @param[in]  sentence  The sentence which is going to be classifyed
 */
void Classifier::classify (std::vector<std::string> sentence) {
	std::vector<float> prob;
	prob.resize(inputFiles_.size());
	for (unsigned i = 0; i < prob.size(); i++) {
		prob[i] = 0.0;
	}
	std::set<Token>::iterator it;
	for (unsigned i = 0; i < sentence.size(); i++) {
		it = learnedData_.find(sentence[i]);
		for (unsigned j = 0; j < prob.size(); j++) {
			prob[j] += it -> get_MultiClass(j);
		}
	}
	data_ += ", ";
	unsigned selection = 0;
	for (unsigned i = 0; i < prob.size(); i++) {
		prob[i] += class_[i].get_ClassProbability();
		if (prob[selection] < prob[i]) {
			selection = i;
		}
		data_ += std::to_string(prob[i]);
		data_ += ", ";
	}
	resume_.push_back(class_[selection].get_Type());
	data_ += class_[selection].get_Type();
	data_ += ".\r";
}

/**
 * @brief      Generates and adds the class probabilities to each class with the
 *             following formula: ln(classLinesAmmount / totalLinesAmmout)
 */
void Classifier::generateClassProbability (void) {
	int totalLines = 0;
	for (unsigned i = 0; i < class_.size(); i++) {
		totalLines += class_[i].get_NLines();
	}
	for (unsigned i = 0; i < class_.size(); i++) {
		class_[i].addClassProbability(totalLines);
	}
}

/**
 * @brief      Preprocess the given sentence using the same pre-processing
 *             method as the vocabulary
 *
 * @param      preprocesser  The preprocesser
 * @param      stopWords     The stop words
 * @param      sentence      The sentence
 */
void Classifier::preProcess (std::vector<std::string>& stopWords, std::string& fileName) {
	PreProcesser preprocesser;
	std::string helper = "../outputs/preProcesserHelper.txt";
	preprocesser.loadTestData(fileName);
	preprocesser.convertLowerCase();
	preprocesser.erasePunctuationSigns();
	preprocesser.eraseAllNumbers();
	preprocesser.storeData(helper, 0);
	preprocesser.eraseReservedWords(stopWords, helper);
}

/**
 * @brief      Reads input learned files and store the tokens into the Class vector.
 *
 * @param      argv  The arguments array
 * @param      argc  The count of arguments
 */
void Classifier::readInputFiles (char* argv[], int& argc) {
	std::vector<Token> tmpVector;
	for (int k = 4; k < argc; k++) {
		std::string fileName = argv[k];
		inputFiles_.push_back(fileName);
		std::string type = "";	
		// ONLY FOR THIS PROGRAM
		if (fileName == "../outputs/learned_SPAM.txt") {
			type += "SPAM";
		}	
		else {
			type += "HAM";
		}
		std::ifstream file(fileName, std::ios::in);
		if (file.fail()) {
			std::cout << std::endl << "Error 404," << fileName << " file not found." << std::endl;
			exit(1);
		}
		else if (k == 4) {
			std::string reader = "";
			file >> reader >> reader >> reader >> reader >> reader >> reader;
			Vocabulary newVoc;
			newVoc.set_NLines(std::stoi(reader));
			newVoc.set_Type(type);
			class_.push_back(newVoc);
			std::getline(file, reader);
			while (!file.eof()) {
				file >> reader >> reader;
				Token newToken(reader);
				file >> reader >> reader >> reader >> reader;
				newToken.addClassProb(std::stof(reader), type);
				newToken.set_Type(type);
				tmpVector.push_back(newToken);
			}
		}
		else {
			int i = 0;
			std::string reader = "";
			file >> reader >> reader >> reader >> reader >> reader >> reader;
			Vocabulary newVoc;
			newVoc.set_NLines(std::stoi(reader));
			newVoc.set_Type(type);
			class_.push_back(newVoc);
			std::getline(file, reader);
			while (!file.eof()) {
				file >> reader >> reader >> reader >> reader >> reader >> reader;
				tmpVector[i].addClassProb(std::stof(reader), type);
				i++;
			}
		}
		file.close();
	}
	for (unsigned i = 0; i < tmpVector.size(); i++) {
		learnedData_.insert(tmpVector[i]);
	}
}

/**
 * @brief      Stores the output data into the classified file and the resume
 *             file. The classify file format is:
 *             <Description>, <ProbSentClassA>, ..., <ProbSentClassN>, <Class>.
 *             <Description>, <ProbSentClassA>, ..., <ProbSentClassN>, <Class>.
 *             <Description>, <ProbSentClassA>, ..., <ProbSentClassN>, <Class>.
 *
 * @param      outputFile  The output file
 * @param      resumeFile  The resume file
 */
void Classifier::storeFile (std::string& outputFile, std::string& resumeFile) {
	std::fstream file(outputFile, std::ios::out | std::ios::trunc);
	if (file.fail()) {
		std::cout << "Error while storing data \"" << outputFile << "\" is not valid document." << std::endl;
		exit(1);
	} 
	else { 
		bool isDecimal = false;
		for (unsigned i = 0; i < data_.length(); i++) {
			/*----------  Fixing decimales to 2 digits  ----------*/
			// file << data_; // If dont want to trunc decimals
			
			if (isDecimal && std::isdigit(data_[i]) && std::isdigit(data_[i - 2])) {
				if (data_[i] != ',') {
					file << data_[i];
					i++;
				}
				while (data_[i] != ',' && data_[i] != '.') {
					i++;
				}
				file << data_[i];
				isDecimal = false;
			}
			else {
				isDecimal = false;
				file << data_[i];
				if (data_[i] == '.') {
					isDecimal = true;
				}
			}
		}
	}
	file.close();
	std::fstream resume(resumeFile, std::ios::out | std::ios::trunc);
	if (resume.fail()) {
		std::cout << "Error while storing data \"" << resumeFile << "\" is not valid document." << std::endl;
		exit(1);
	} 
	else {
		for (unsigned i = 0; i < resume_.size(); i++) {
			resume << resume_[i] << std::endl;
		}
		resume.close();
	}
}
