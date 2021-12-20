# Variables
TIME =$(LOGPATH)$(shell date)
# Object Vars
OBJECTS = main.o vocabulary.o preProcesser.o Chrono.o token.o corpus.o learner.o classifier.o
# Compilation flags
CFLAGS = -c -std=c++17 -Wall

SBlocker: $(OBJECTS)
	g++ $(OBJECTS) -o SBlocker
	mv SBlocker ../bin

main.o: ../src/main.cpp
	g++ $(CFLAGS) ../src/main.cpp

vocabulary.o: ../src/vocabulary.cpp ../include/vocabulary.hpp
	g++ $(CFLAGS) ../src/vocabulary.cpp

preProcesser.o: ../src/preProcesser.cpp ../include/preProcesser.hpp
	g++ $(CFLAGS) ../src/preProcesser.cpp

Chrono.o: ../src/Chrono.cpp ../include/Chrono.hpp
	g++ $(CFLAGS) ../src/Chrono.cpp

token.o: ../src/token.cpp ../include/token.hpp
	g++ $(CFLAGS) ../src/token.cpp

corpus.o: ../src/corpus.cpp ../include/corpus.hpp
	g++ $(CFLAGS) ../src/corpus.cpp

learner.o: ../src/learner.cpp ../include/learner.hpp
	g++ $(CFLAGS) ../src/learner.cpp

classifier.o: ../src/classifier.cpp ../include/classifier.hpp
	g++ $(CFLAGS) ../src/classifier.cpp



.PHONY: clean
clean:
	rm -rf ../build/*.o
	rm -rf ../bin/*

help:
	../bin/SBlocker --help

generateMails:
	../bin/SBlocker --updateDatabase


fullRun:
	make clean
	make
	make runVocabulary
	make runCorpus
	make runLearner
	make runClassifier
	make runTestPercentage

runTestPercentage:
	../bin/SBlocker --error ../outputs/resume.csv ../inputs/resumeExpected.csv

runClassifier:
	../bin/SBlocker --classify ../inputs/mail-test-row.csv ../inputs/stopWords.txt ../outputs/learned_SPAM.txt ../outputs/learned_HAM.txt

runLearner:
	../bin/SBlocker --learner ../outputs/vocabulary.txt SPAM HAM

runCorpus:
	../bin/SBlocker --corpus ../inputs/mail-train.csv ../inputs/stopWords.txt SPAM HAM

runVocabulary:
	../bin/SBlocker --vocabulary ../inputs/mail-train.csv ../outputs/vocabulary.txt ../inputs/stopWords.txt

runGenerateTest:
	../bin/SBlocker --generateTest

runLog:
	echo "\n\n\nExecuted ${TIME}" >> ../outputs/runDetails.txt
	make fullRun >> ../outputs/runDetails.txt
	echo "You can find full output at outputs/runDetails.txt"
