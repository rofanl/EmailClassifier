/*=======================================================================================
=========================================================================================
    =                                                                              =
    =            Proyect:       Color Class                                        =
    =            File name:     Color.hpp                                          =
    =            Author:        Adrián Epifanio Rodríguez Hernández                =
    =            Date:          27/10/2020                                         =
    =            Language:      C++                                                =
    =            Email:         alu0101158280@ull.edu.es                           =
    =            Place:         Universidad De La Laguna                           =
    =                           Escuela Superior de Ingeniería y Tecnología        =
    =                                                                              =
=========================================================================================
=======================================================================================*/
/*------------------  FUNCTIONS  -----------------*/
#ifndef COLOR_H
#define COLOR_H
#pragma once 

/*------------------------------------------------*/
/*------------------  LIBRARIES  -----------------*/

#include <QString>
#include <iostream>

/*------------------------------------------------*/

/**
 *
 * Usage example:
 * 
 * QString test = "message";
 * std::cout << std::endl << "test: " << Color::writeBlue(test) << std::endl;
 *
 */


/**
 * @brief      This class describes a color.
 */
class Color {

	public:
        // Builder & Destroyer
		Color (void) {};
		~Color (void) {};

        /*----------  Methods  ----------
        // Text color methods
        static QString writeBlack (const QString& myString);
        static QString writeBlue (const QString& myString);
        static QString writeCyan (const QString& myString);
        static QString writeGreen (const QString& myString);
        static QString writeMagenta (const QString& myString);
        static QString writeRed (const QString& myString);
        static QString writeWhite (const QString& myString);
        static QString writeYellow (const QString& myString);

        // Background color methods
        static QString paintBlack (const QString& myString);
        static QString paintBlue (const QString& myString);
        static QString paintCyan (const QString& myString);
        static QString paintGreen (const QString& myString);
        static QString paintMagenta (const QString& myString);
        static QString paintRed (const QString& myString);
        static QString paintWhite (const QString& myString);
        static QString paintYellow (const QString& myString);
        -------------------------------*/
        

        /**
         * @brief      Writes the given text with black color.
         *
         * @param[in]  myString  My string
         *
         * @return     The string written with the color.
         */
        static QString writeBlack (const QString& myString) {
            return ("\033[30m" + myString + "\033[00m");
        }

        /**
         * @brief      Writes the given text with blue color.
         *
         * @param[in]  myString  My string
         *
         * @return     The string written with the color.
         */
        static QString writeBlue (QString& myString) {
            return ("\033[34m" + myString + "\033[00m");
        }

        /**
         * @brief      Paints the given text with cyan color.
         *
         * @param[in]  myString  My string
         *
         * @return     The string written with the color.
         */
        static QString writeCyan (const QString& myString) {
            return ("\033[36m" + myString + "\033[00m");
        }

        /**
         * @brief      Writes the given text with green color.
         *
         * @param[in]  myString  My string
         *
         * @return     The string written with the color.
         */
        static QString writeGreen (const QString& myString) {
            return ("\033[32m" + myString + "\033[00m");
        }

        /**
         * @brief      Writes the given text with magenta color.
         *
         * @param[in]  myString  My string
         *
         * @return     The string written with the color.
         */
        static QString writeMagenta (const QString& myString) {
            return ("\033[35m" + myString + "\033[00m");
        }

        /**
         * @brief      Writes the given text with red color.
         *
         * @param[in]  myString  My string
         *
         * @return     The string written with the color.
         */
        static QString writeRed (const QString& myString) {
            return ("\033[31m" + myString + "\033[00m");
        }

        /**
         * @brief      Paints the given text with white color.
         *
         * @param[in]  myString  My string
         *
         * @return     The string written with the color.
         */
        static QString writeWhite (const QString& myString) {
            return ("\033[37m" + myString + "\033[00m");
        }

        /**
         * @brief      Writes the given text inn color yellow.
         *
         * @param[in]  myString  My string
         *
         * @return     The string written with the color.
         */
        static QString writeYellow (const QString& myString) {
            return ("\033[33m" + myString + "\033[00m");
        }

        /**
         * @brief      Paints the given text with a black background color.
         *
         * @param[in]  myString  My string
         *
         * @return     The string written with the background color.
         */
        static QString paintBlack (const QString& myString) {
            return ("\033[40m" + myString + "\033[00m");
        }

        /**
         * @brief      Paints the given text with a blue background color.
         *
         * @param[in]  myString  My string
         *
         * @return     The string written with the background color.
         */
        static QString paintBlue (const QString& myString) {
            return ("\033[44m" + myString + "\033[00m");
        }

        /**
         * @brief      Paints the given text with a cyan background color.
         *
         * @param[in]  myString  My string
         *
         * @return     The string written with the background color.
         */
        static QString paintCyan (const QString& myString) {
            return ("\033[46m" + myString + "\033[00m");
        }

        /**
         * @brief      Paints the given text with a green background color.
         *
         * @param[in]  myString  My string
         *
         * @return     The string written with the background color.
         */
        static QString paintGreen (const QString& myString) {
            return ("\033[42m" + myString + "\033[00m");
        }

        /**
         * @brief      Paints the given text with a magenta background color.
         *
         * @param[in]  myString  My string
         *
         * @return     The string written with the background color.
         */
        static QString paintMagenta (const QString& myString) {
            return ("\033[45m" + myString + "\033[00m");
        }

        /**
         * @brief      Paints the given text with a red background color.
         *
         * @param[in]  myString  My string
         *
         * @return     The string written with the background color.
         */
        static QString paintRed (const QString& myString) {
            return ("\033[41m" + myString + "\033[00m");
        }

        /**
         * @brief      Paints the given text with a white background color.
         *
         * @param[in]  myString  My string
         *
         * @return     The string written with the background color.
         */
        static QString paintWhite (const QString& myString) {
            return ("\033[47m" + myString + "\033[00m");
        }

        /**
         * @brief      Paints the given text with a yellow background color.
         *
         * @param[in]  myString  My string
         *
         * @return     The string written with the background color.
         */
        static QString paintYellow (const QString& myString) {
            return ("\033[43m" + myString + "\033[00m");
        }

};
#endif // COLOR_H
