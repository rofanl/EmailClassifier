/*=======================================================================================
=========================================================================================
	=                                                                              =
	=            Proyect:       Email Classifier                                   =
	=            File name:     learner.hpp                                        =
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
#include "corpus.h"
#include "token.h"

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
 * @brief      This class describes a learner.
 */
class Learner {

	private:
		// Attributes
		std::vector<Vocabulary> learners_;			// The learner for each data type
        std::vector<QString> inputCorpusFiles_;	// The input corpus file name
        QString vocabularyFile_;				// The vocabulary file name

	public:
		// Builders & Destroyer
		Learner (void);
		Learner (char* argv[], int& argc);
        Learner (QString vocFile, QStringList corpuses);
		~Learner (void);

		// Getters & Setters
		std::vector<Vocabulary> get_Learners (void) const;
        std::vector<QString> get_InputCorpusFiles (void) const;
        QString get_VocabularyFile (void) const;

		void set_Learners (std::vector<Vocabulary> newLearners);
        void set_InputCorpusFiles (std::vector<QString> newInputCorpusFiles);
        void set_VocabularyFile (QString newVocabularyFile);

		// Write
		void learnAndStoreData (void);

};
