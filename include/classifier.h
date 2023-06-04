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
#include "vocabulary.h"
#include "Chrono.h"

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
#include <QSet>
#include <QHash>

/*------------------------------------------------*/

/**
 * @brief      This class describes a classifier.
 */
class Classifier {

	private:
		// Attributes
        std::vector<QString> _inputFiles;	// Input files vector
        std::vector<Vocabulary> _class;			// Class/vocabulary vector
        QString _data;						// Output data will be stored here
        QHash<QString,Token> _learnedData;			// Dicctionary with all the tokens and it respectives probabilities and class
        std::vector<QString> _resume;		// Vector where the output resume class will be stored

	public:
		// Builders & Destroyer
		Classifier (void);
        Classifier (QString corpusTestFile,QString reservedWords,QStringList learnFiles);
		Classifier (char* argv[], int& argc);
		~Classifier (void);

		// Getters & Setters
        std::vector<QString> get_InputFiles (void) const;
		std::vector<Vocabulary> get_Class (void) const;
        QString get_Data (void) const;

        void set_InputFiles (std::vector<QString> newInputFiles);
		void set_Class (std::vector<Vocabulary> newClass);
        void set_Data (QString newData);

		// Functions
        void classifyFile (QString& inputFile, QString& stopWords);
        void classify (QVector<QString> sentence);
		void generateClassProbability (void);
        void preProcess (std::vector<QString>& stopWords, QString& sentence);
        QString getTypeOfFile(QString file);

		// Read & Write
        void readInputFiles (char* argv[], int& argc);
        void readInputFiles (QStringList learnFiles);
        void storeFile (QString& outputFile, QString& resumeFile);
};
