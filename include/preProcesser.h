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
#include <QString>

/*------------------------------------------------*/

/**
 * @brief      This class describes a pre processer, it makes possible to
 *             preprocess data files before using them.
 */
class PreProcesser {

	private:
		// Attributes
        QString inputFile_;						// Input file path
        QString outputFile_;					// Output file path where the preprocessed text will store the data
        QString _data;							// Full stored data readed from input file

	public:
		// Builders & Destroyer
		PreProcesser (void);
        PreProcesser (QString inputFile, QString outpuFile);
		~PreProcesser (void);

		// Getters & Setters
        QString get_InputFile (void) const;
        QString get_OutputFile (void) const;
        QString get_Data (void) const;

        void set_InputFile (QString newInputFile);
        void set_OutputFile (QString newOutputFile);
        void set_Data (QString newData);

		// Operators Overload
		PreProcesser& operator= (const PreProcesser& newPreProcesser);

		// Functions
        void convertLowerCase (QString& str);
		void convertLowerCase (void);
        void convertUpperCase (QString& str);
		void convertUpperCase (void);
        void eraseReservedWords (std::vector<QString>& reservedWords, QString& fileName);
        QString eraseReservedWords (QString& sentence, std::vector<QString>& reservedWords);
        void erasePunctuationSigns (QString& str);
		void erasePunctuationSigns (void);
        void eraseURLs (QString& str);
		void eraseURLs (void);
        void eraseHashtags (QString& str);
		void eraseHashtags (void);
        void eraseNumbers (QString& str);
		void eraseNumbers (void);
		void eraseAllNumbers (void);
        void eraseAllNumbers (QString& str);

		// Read & Write
        int loadData (QString& inputFile, QString dataType);
        void loadTestData (QString& inputFile);
		void printData (void);
        void storeData(QString& outputFile, int dataLines);

};
