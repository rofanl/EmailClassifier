/*=======================================================================================
=========================================================================================
	=                                                                              =
	=            Proyect:       Email Classifier                                   =
	=            File name:     token.hpp                                          =
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
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <QString>



/*------------------------------------------------*/

/**
 * @brief      This class describes a token.
 */
class Token {

	private:
		// Attributes
        QString name_;				// The token name
		unsigned ammount_;				// The ammount of times that the token apears in corpus
		float probability_;				// The probability of the token in corpus
		std::vector<float> multiClass_;	// The probability vector for classifier use
        QString type_; 				// The type of the token into specified classes

	public:
		// Builders & Destroyer
		Token (void);
        Token (QString name);
		~Token (void);

		// Getters & Setters
        QString get_Name(void) const;
		unsigned get_Ammount (void) const;
		float get_Probability (void) const;
		float get_MultiClass (unsigned pos) const;
		std::vector<float> get_MultiClass (void) const;
        QString get_Type (void) const;

        void set_Name (QString name);
		void set_Ammount (unsigned ammount);
		void set_Probability (float newProbability);
		void set_MultiClass (std::vector<float> newMultiClass);
        void set_Type (QString newType);

		// Operators overload
		bool operator< (const Token& otherToken) const;
		bool operator<= (const Token& otherToken) const;
        bool operator< (const QString& str) const;
        bool operator<= (const QString& str) const;
		bool operator> (const Token& otherToken) const;
		bool operator>= (const Token& otherToken) const;
        bool operator> (const QString& str) const;
        bool operator>= (const QString& str) const;
		bool operator== (const Token& otherToken) const;
        bool operator== (const QString& str) const;
		Token& operator++ (void);
		Token& operator= (const Token& otherToken);


        // Function
		void incrementate (void);
        void addClassProb (float prob, QString newClass);
		float generateLogProb (const unsigned& vocSize, const unsigned& tokenAmmount);

		// Write
		void printToken (void) const;
};
