/*=======================================================================================
=========================================================================================
	=                                                                              =
	=            Proyect:       Email Classifier                                   =
	=            File name:     main.cpp                                           =
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
* @Last Modified time: 2021-12-19 15:30:22
*/
/*------------------  FUNCTIONS  -----------------*/

#include "../include/vocabulary.hpp"
#include "../include/corpus.hpp"
#include "../include/learner.hpp"
#include "../include/classifier.hpp"

/*------------------------------------------------*/
/*------------------  LIBRARIES  -----------------*/

#include <dirent.h>
#include <sys/types.h>

/*------------------------------------------------*/

void printHelp (void);
void generateVocabulary (int& argc, char* argv[]);
void generateCorpus (int& argc, char* argv[]);
void generateLearner (int& argc, char* argv[]);
void generateClassifier (int& argc, char* argv[]);
void calculateError (int& argc, char* argv[]);
void mailGenerator (void);
std::string generateMail (std::string fileName);
void deleteCommas (std::string& message);



/**
 * @brief      Main function of the program, receives the data file as
 *             parameter.
 *
 * @param[in]  argc  The count of arguments
 * @param      argv  The arguments array
 *
 * @return     0 If program finishes correctly
 */
int main (int argc, char* argv[]) {
	if (argc <= 1) {
		//printHelp();
		mailGenerator();
	}
	else {
		std::string flag = argv[1];
		if (flag == "-h" || flag == "--help") {
			printHelp();
			return(0);
		}
		else if (flag == "-v" || flag == "--vocabulary") {
			generateVocabulary(argc, argv);
		}
		else if (flag == "-co" || flag == "--corpus") {
			generateCorpus(argc, argv);
		}
		else if (flag == "-l" || flag == "--learner") {
			generateLearner(argc, argv);
		}
		else if (flag == "-cl" || flag == "--classify") {
			generateClassifier(argc, argv);
		}
		else if (flag == "-e" || flag == "--error") {
			calculateError(argc, argv);
		}

	}
	
	std::cout << std::endl << "Program finished correclty." << std::endl;
	return 0;
}	


/**
 * @brief      Prints help information about how to run and use the program.
 */
void printHelp (void) {
	const std::string MAN = "../include/man.txt";
	std::ifstream file(MAN, std::ios::in);
	if (file.fail()) {
		std::cout << std::endl << "Error while opening manual file, make sure the file \"man.txt\" is placed on the include folder." << std::endl;
		std::cout << "You can also read the instructions at <https://github.com/AdrianEpi/Text-Classifier> " << std::endl << std::endl;
		exit(1);
	} 
	std::string reader;
	while (!file.eof()) {
		std::getline(file, reader);
		std::cout << reader << std::endl;
	}
}

/**
 * @brief      Generates the vocabulary from the first input file and stores it
 *             into second file using the stopwords readed from third file
 *
 * @param      argc  The count of arguments
 * @param      argv  The arguments array
 */
void generateVocabulary (int& argc, char* argv[]) {
	if (argc != 5) {
		std::cout << std::endl << "Error, the program needs 4 arguments to generate the vocabulary:" << std::endl << "\t bin/textClassifier -v originFile outputFile reservedWordsFile" << std::endl;
		exit(1);
	}
	std::string originFile = argv[2];
	std::string outputFile = argv[3];
	std::string reservedWords = argv[4];
	std::string fileHelper = "../outputs/preProcesserHelper.txt";
	Vocabulary vocabulary(originFile, outputFile);
	{
		Chrono chrono;
		chrono.startChrono();
		vocabulary.preProcessData(reservedWords);
		chrono.stopChrono();
		std::cout << std::endl << "Elapsed pre-processing time: " << chrono.get_Seconds(5) << " seconds." << std::endl;
	}
	{
		Chrono chrono;
		chrono.startChrono();
		vocabulary.generateVocabulary(fileHelper, false);
		chrono.stopChrono();
		std::cout << std::endl << "Elapsed generating vocabulary time: " << chrono.get_Seconds(5) << " seconds." << std::endl;
	}
	{
		Chrono chrono;
		chrono.startChrono();
		vocabulary.storeVocabulary(outputFile);
		chrono.stopChrono();
		std::cout << std::endl << "Elapsed storing vocabulary time: " << chrono.get_Seconds(5) << " seconds." << std::endl;
	}
}

/**
 * @brief      Generates one corpus per each type of data received as argument
 *             in console line. The data type must be the first column of the
 *             csv or data file and it should be followed by a ',' on the data
 *             file but not in the command line.
 *
 * @param      argc  The count of arguments
 * @param      argv  The arguments array
 */
void generateCorpus (int& argc, char* argv[]) {
	if (argc < 4) {
		std::cout << std::endl << "Error, the program needs at least 3 arguments to generate the corpus:" << std::endl << "\t bin/textClassifier -co originFile reservedWordsFile CORPUS1 CORPUS2 CORPUS3 . . ." << std::endl;
		std::cout << std::endl << "Each \"CORPUS\" represents one data type that wants to be separated into different corpus." << std::endl;
		exit(1);
	}
	std::string originFile = argv[2];
	std::string reservedWords = argv[3];
	PreProcesser preProcesser;
	Vocabulary voc;
	std::vector<std::string> stopWords = voc.loadStopWord(reservedWords);
	for (int i = 4; i < argc; i++) {
		std::string tmp = argv[i];
		Corpus newCorpus(tmp, originFile);
		newCorpus.generateCorpus(stopWords, preProcesser);
	}
}

/**
 * @brief      Calculates the probability of each token in the given corpus as
 *             an argument at the command line and stores it into different
 *             files.
 *
 * @param      argc  The count of arguments
 * @param      argv  The arguments array
 */
void generateLearner (int& argc, char* argv[]) {
	if (argc < 3) {
		std::cout << std::endl << "Error, the program needs at least 2 arguments to learn data from corpus." << std::endl << "\t bin/textClassifier -l vocabularyFile Data1 Data2 ... DataX" << std::endl;
		std::cout << std::endl << "Each \"Data\" represents one data learning type that wants generated." << std::endl;
		exit(1);
	}
	Learner learner(argv, argc);
}

/**
 * @brief      Classifies the test_curpus into the received class types
 *
 * @param      argc  The count of arguments
 * @param      argv  The arguments array
 */
void generateClassifier (int& argc, char* argv[]) {
	if (argc < 4) {
		std::cout << std::endl << "Error, the program needs at least 3 arguments to classify the test data:" << std::endl << "\t bin/textClassifier -cl corpusTestFile reservedWordsFile LEARNED1 LEARNED2 LEARNED3 . . ." << std::endl;
		std::cout << std::endl << "Each \"LEARNED\" is generated with the --learner flag." << std::endl;
		exit(1);
	}
	Classifier newClassifier(argv, argc);
}

/**
 * @brief      Calculates the error and success percentage comparing the
 *             expected outputFile and the generated outputFile.
 *
 * @param      argc  The count of arguments
 * @param      argv  The arguments array
 */
void calculateError (int& argc, char* argv[]) {
	if (argc != 4) {
		std::cout << std::endl << "Error, the program needs 4 arguments to calculate the success and error percentage:" << std::endl << "\t bin/textClassifier -e classifiedResume expectedResume" << std::endl;
		exit(1);
	}
	std::string expected = argv[3];
	std::string received = argv[2];
	std::vector<std::string> expect;
	std::vector<std::string> receive;
	std::string tmp = "";
	std::ifstream file(expected, std::ios::in);
	if (file.fail()) {
		std::cout << std::endl << "Error 404," << expected << " file not found." << std::endl;
		exit(1);
	}
	else {
		while (!file.eof()) {
			file >> tmp;
			expect.push_back(tmp);
		}
		file.close();
	}
	std::ifstream file2(received, std::ios::in);
	if (file2.fail()) {
		std::cout << std::endl << "Error 404," << received << " file not found." << std::endl;
		exit(1);
	}
	else {
		std::getline(file2, tmp);		
		while (!file2.eof()) {
			file2 >> tmp;
			receive.push_back(tmp);
		}
		file2.close();
	}

	int size = 0;
	if (expect.size() < receive.size()) {
		size = expect.size();
	}
	else {
		size = receive.size();
	}
	int correct = 0;
	for (int i = 0; i < size; i++) {
		if (expect[i] == receive[i]) {
			correct++;
		}
	}
	float percentage = correct;
	percentage /= size;
	percentage *= 100;
	std::cout << std::endl << "Success percentage: " << correct << " / " << size << " = " << percentage << " %.";
	std::cout << std::endl << "Error percentage: " << (size - correct) << " / " << size << " = " << (100 - percentage) << " %." << std::endl;
}

void mailGenerator (void) {
	std::cout << "Please select the type of emails you are going to load:\n\t1. SPAM\n\t2. Promotions\n\t3. Notification\n\t4. Social\n\t0. Cancel" << std::endl;
	std::string type;
	int selection;
	std::cin >> selection;
	switch (selection) {
		case 0:
			exit(0);
			break;
		case 1:
			type = "SPAM";
			break;
		case 2:
			type = "Promotion";
			break;
		case 3:
			type = "Notification";
			break;
		case 4:
			type = "Social";
			break;
		default:
			std::cout << "Wrong email type introduced, aborting program   .   .   ." << std::endl;
			exit(1);
	}

	struct dirent *entry;
    DIR *dir = opendir("../inputs/GenerateMails/");
    if (dir == NULL) {
        exit(1);
    }
    while ((entry = readdir(dir)) != NULL) {
        if (entry -> d_name[0] != '.') {
        	std::cout << "Generating mail from: " << entry -> d_name << std::endl;
        	std::string mail = generateMail(entry -> d_name);
        }
    }
    closedir(dir);

}


std::string generateMail (std::string fileName) {
	std::fstream file(fileName, std::ios::out);
	if (!file.fail()) {
		std::string mail = "";
		while (!file.eof()) {
			std::string line;
			std::getline(file, line);
			if (line.length() > 3) {
				mail += " " + line;
			}
		}
		file.close();
		deleteCommas(mail);
		return mail;
	}
}

void deleteCommas (std::string& message) {
	for (unsigned i = 0; i < message.length(); i++) {
		if (message[i] == ',') {
			message[i] = ';';
		}
	}
}