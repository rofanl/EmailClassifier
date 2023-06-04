/*=======================================================================================
=========================================================================================
	=                                                                              =
	=            Proyect:       Email Classifier                                   =
	=            File name:     corpus.hpp                                         =
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

/*------------------------------------------------*/

/**
 * @brief      This class describes a corpus.
 */
class Corpus {

	private:
		// Attributes
        QString _name;				// The corpus name or data type
        QString _outputFileName;	// The output file name
        QString _inputFile;			// The input file name

	public:
		// Builders & Destroyer
		Corpus (void);
        Corpus (QString name, QString inputFile);
		~Corpus (void);

		// Getters & Setters
        QString get_Name (void) const;
        QString get_OutputFileName (void) const;
        QString get_InputFile (void) const;

        void set_Name (QString newName);
        void set_OutputFileName (QString newOutputFileName);
        void set_InputFile (QString newInputFile);

		// Functions
        void generateCorpus (std::vector<QString>& stopWords, PreProcesser& preProcesser);

};
