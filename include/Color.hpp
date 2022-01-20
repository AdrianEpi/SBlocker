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

#include <iostream>

/*------------------------------------------------*/

/**
 *
 * Usage example:
 * 
 * std::string test = "message"; 
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
        static std::string writeBlack (const std::string& myString);
        static std::string writeBlue (const std::string& myString);
        static std::string writeCyan (const std::string& myString);
        static std::string writeGreen (const std::string& myString);
        static std::string writeMagenta (const std::string& myString);
        static std::string writeRed (const std::string& myString);
        static std::string writeWhite (const std::string& myString);
        static std::string writeYellow (const std::string& myString);

        // Background color methods
        static std::string paintBlack (const std::string& myString);
        static std::string paintBlue (const std::string& myString);
        static std::string paintCyan (const std::string& myString);
        static std::string paintGreen (const std::string& myString);
        static std::string paintMagenta (const std::string& myString);
        static std::string paintRed (const std::string& myString);
        static std::string paintWhite (const std::string& myString);
        static std::string paintYellow (const std::string& myString);
        -------------------------------*/
        

        /**
         * @brief      Writes the given text with black color.
         *
         * @param[in]  myString  My string
         *
         * @return     The string written with the color.
         */
        static std::string writeBlack (const std::string& myString) {
            return ("\033[30m" + myString + "\033[00m");
        }

        /**
         * @brief      Writes the given text with blue color.
         *
         * @param[in]  myString  My string
         *
         * @return     The string written with the color.
         */
        static std::string writeBlue (std::string& myString) {
            return ("\033[34m" + myString + "\033[00m");
        }

        /**
         * @brief      Paints the given text with cyan color.
         *
         * @param[in]  myString  My string
         *
         * @return     The string written with the color.
         */
        static std::string writeCyan (const std::string& myString) {
            return ("\033[36m" + myString + "\033[00m");
        }

        /**
         * @brief      Writes the given text with green color.
         *
         * @param[in]  myString  My string
         *
         * @return     The string written with the color.
         */
        static std::string writeGreen (const std::string& myString) {
            return ("\033[32m" + myString + "\033[00m");
        }

        /**
         * @brief      Writes the given text with magenta color.
         *
         * @param[in]  myString  My string
         *
         * @return     The string written with the color.
         */
        static std::string writeMagenta (const std::string& myString) {
            return ("\033[35m" + myString + "\033[00m");
        }

        /**
         * @brief      Writes the given text with red color.
         *
         * @param[in]  myString  My string
         *
         * @return     The string written with the color.
         */
        static std::string writeRed (const std::string& myString) {
            return ("\033[31m" + myString + "\033[00m");
        }

        /**
         * @brief      Paints the given text with white color.
         *
         * @param[in]  myString  My string
         *
         * @return     The string written with the color.
         */
        static std::string writeWhite (const std::string& myString) {
            return ("\033[37m" + myString + "\033[00m");
        }

        /**
         * @brief      Writes the given text inn color yellow.
         *
         * @param[in]  myString  My string
         *
         * @return     The string written with the color.
         */
        static std::string writeYellow (const std::string& myString) {
            return ("\033[33m" + myString + "\033[00m");
        }

        /**
         * @brief      Paints the given text with a black background color.
         *
         * @param[in]  myString  My string
         *
         * @return     The string written with the background color.
         */
        static std::string paintBlack (const std::string& myString) {
            return ("\033[40m" + myString + "\033[00m");
        }

        /**
         * @brief      Paints the given text with a blue background color.
         *
         * @param[in]  myString  My string
         *
         * @return     The string written with the background color.
         */
        static std::string paintBlue (const std::string& myString) {
            return ("\033[44m" + myString + "\033[00m");
        }

        /**
         * @brief      Paints the given text with a cyan background color.
         *
         * @param[in]  myString  My string
         *
         * @return     The string written with the background color.
         */
        static std::string paintCyan (const std::string& myString) {
            return ("\033[46m" + myString + "\033[00m");
        }

        /**
         * @brief      Paints the given text with a green background color.
         *
         * @param[in]  myString  My string
         *
         * @return     The string written with the background color.
         */
        static std::string paintGreen (const std::string& myString) {
            return ("\033[42m" + myString + "\033[00m");
        }

        /**
         * @brief      Paints the given text with a magenta background color.
         *
         * @param[in]  myString  My string
         *
         * @return     The string written with the background color.
         */
        static std::string paintMagenta (const std::string& myString) {
            return ("\033[45m" + myString + "\033[00m");
        }

        /**
         * @brief      Paints the given text with a red background color.
         *
         * @param[in]  myString  My string
         *
         * @return     The string written with the background color.
         */
        static std::string paintRed (const std::string& myString) {
            return ("\033[41m" + myString + "\033[00m");
        }

        /**
         * @brief      Paints the given text with a white background color.
         *
         * @param[in]  myString  My string
         *
         * @return     The string written with the background color.
         */
        static std::string paintWhite (const std::string& myString) {
            return ("\033[47m" + myString + "\033[00m");
        }

        /**
         * @brief      Paints the given text with a yellow background color.
         *
         * @param[in]  myString  My string
         *
         * @return     The string written with the background color.
         */
        static std::string paintYellow (const std::string& myString) {
            return ("\033[43m" + myString + "\033[00m");
        }

};
#endif // COLOR_H
