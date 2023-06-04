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
#include "preProcesser.h"
#include "Chrono.h"
#include "token.h"

/*------------------------------------------------*/
/*------------------  LIBRARIES  -----------------*/

#include <cstring>
#include <set>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <QString>

/*------------------------------------------------*/

/**
 * @brief      This class describes a vocabulary and 
 */
class Vocabulary {

	private:
		// Attributes
        QString _inputFile;			// Input file path
        QString _outpuFile;			// Output file where the vocabulary will be stored
        int _vocabularyCounter;			// Number of different words in the vocabulary
        int _nTokens;					// Number of words in the text
        int _nLines;					// Number of lines readed from file;
        std::set<Token> _vocabulary;	// Set with all the vocabulary
        QString _type;				// The vocabulary type (if aplicable)
        float _classProbability;		// The class probability (if aplicable)

	public:
		// Builders & Destroyer
		Vocabulary (void);
        Vocabulary (QString inputFile, QString outpuFile);
		~Vocabulary (void);

		// Getters & Setters
        QString get_InputFile (void) const;
        QString get_OutpuFile (void) const;
		int get_VocabularyCounter (void) const;
		int get_NTokens (void) const;
		int get_NLines (void) const;
		std::set<Token> get_Vocabulary (void) const;
        QString get_Type (void) const;
		float get_ClassProbability (void) const;

        void set_InputFile (QString newInputFile);
        void set_OutpuFile (QString newOutpuFile);
		void set_VocabularyCounter (int newVocabularyCounter);
		void set_NTokens (int newNTokens);
		void set_NLines (int newNLines);
		void set_Vocabulary (std::set<Token> newVocabulary);
        void set_Type (QString newType);
		void set_ClassProbability (float newClassProbability);

		// Operators Overload
		Vocabulary& operator= (const Vocabulary& newVocabulary);

		// Functions
        void preProcessData (QString& stopWordFile);
        std::vector<QString> loadStopWord (QString& inputFile);
        void generateVocabulary (QString& inputFile, bool tokenized);
		void calculateProbabilities (void);
		void addClassProbability (int size);

		// Write
        void readVocabulary (QString& inputFile);
        void storeVocabulary (QString& outputFile);
        void readLearnedData (QString& inputFile);
};
