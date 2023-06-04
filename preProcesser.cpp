/*=======================================================================================
=========================================================================================
        =                                                                              =
        =            Proyect:       Email Classifier                                   =
        =            File name:     preProcesser.cpp                                   =
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
 * @Last Modified by:   Adrian Epifanio
 * @Last Modified time: 2021-12-02 18:32:26
 */
/*------------------  FUNCTIONS  -----------------*/

#include "include/preProcesser.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

/*------------------------------------------------*/

/**
 * @brief      Constructs a new instance.
 */
PreProcesser::PreProcesser(void)
{
    set_InputFile("");
    set_OutputFile("");
    set_Data("");
}

/**
 * @brief      Constructs a new instance.
 *
 * @param[in]  inputFile  The input file
 * @param[in]  outpuFile  The outpu file
 */
PreProcesser::PreProcesser(QString inputFile, QString outpuFile)
{
    set_InputFile(inputFile);
    set_OutputFile(outpuFile);
    set_Data("");
}

/**
 * @brief      Destroys the object.
 */
PreProcesser::~PreProcesser(void)
{
}

/**
 * @brief      Gets the input file.
 *
 * @return     The input file.
 */
QString PreProcesser::get_InputFile(void) const
{
    return inputFile_;
}

/**
 * @brief      Gets the output file.
 *
 * @return     The output file.
 */
QString PreProcesser::get_OutputFile(void) const
{
    return outputFile_;
}

/**
 * @brief      Gets the data.
 *
 * @return     The data.
 */
QString PreProcesser::get_Data(void) const
{
    return _data;
}

/**
 * @brief      Sets the input file.
 *
 * @param[in]  newInputFile  The new input file
 */
void PreProcesser::set_InputFile(QString newInputFile)
{
    inputFile_ = newInputFile;
}

/**
 * @brief      Sets the output file.
 *
 * @param[in]  newOutputFile  The new output file
 */
void PreProcesser::set_OutputFile(QString newOutputFile)
{
    outputFile_ = newOutputFile;
}

/**
 * @brief      Sets the data.
 *
 * @param[in]  newData  The new data
 */
void PreProcesser::set_Data(QString newData)
{
    _data = newData;
}

/**
 * @brief      Assignment operator.
 *
 * @param[in]  newPreProcesser  The new pre processer
 *
 * @return     The result of the assignment
 */
PreProcesser &PreProcesser::operator=(const PreProcesser &newPreProcesser)
{
    this->set_Data(newPreProcesser.get_Data());
    this->set_OutputFile(newPreProcesser.get_OutputFile());
    this->set_InputFile(newPreProcesser.get_InputFile());
    return *this;
}

/**
 * @brief      Converts all the str into Lower Case
 *
 * @param      str   The string
 */
void PreProcesser::convertLowerCase(QString &str)
{
    set_Data(str);
    convertLowerCase();
    str = get_Data();
}

/**
 * @brief      Converts all the data into Lower Case
 */
void PreProcesser::convertLowerCase(void)
{
    _data = _data.toLower();
}

/**
 * @brief      Converts all the str into Upper Case
 *
 * @param      str   The string
 */
void PreProcesser::convertUpperCase(QString &str)
{
    set_Data(str);
    convertUpperCase();
    str = get_Data();
}

/**
 * @brief      Converts all the data into Upper Case
 */
void PreProcesser::convertUpperCase(void)
{
    _data = _data.toUpper();
}

/**
 * @brief      Deletes all the words from the vector in the given file and
 *             stores them into the same file.
 *
 * @param[in]  reservedWords  The reserved words vector
 * @param[in]  fileName       The file name
 */
void PreProcesser::eraseReservedWords(std::vector<QString> &reservedWords, QString &fileName)
{
    QFile file(fileName);
    QTextStream ts(&file);
    _data = "";
    if (!file.open(QIODevice::ReadOnly)) {
        std::cout << std::endl
                  << "Error 404, file not found in eraseReservedWords function." << std::endl;
        exit(1);
    }
    QString aux = "";
    while (!ts.atEnd()) {
        ts >> aux;
        bool push = true;
        for (unsigned i = 0; i < reservedWords.size(); i++) {
            if (aux == reservedWords[i]) {
                push = false;
                break;
            }
        }
        if (push) {
            _data += ' ' + aux;
        }
    }
    file.close();
    storeData(fileName, 0);
}

/**
 * @brief      Deletes all the words from the vector in the given string and
 *             returns it
 *
 * @param[in]  reservedWords  The reserved words vector
 * @param[in]  sentence       The sentence
 *
 * @return     The string without the reserved words.
 */
QString PreProcesser::eraseReservedWords(QString &sentence, std::vector<QString> &reservedWords)
{
    QString result = "";
    QString tmp = "";
    for (unsigned j = 0; j < sentence.length(); j++) {
        if (sentence[j] != ' ' && sentence[j] != '\t') {
            tmp += sentence[j];
        }
        else {
            bool push = true;
            for (unsigned i = 0; i < reservedWords.size(); i++) {
                if (tmp == reservedWords[i]) {
                    push = false;
                    break;
                }
            }
            if (push) {
                result += tmp + " ";
            }
            tmp = "";
        }
    }
    return result;
}

/**
 * @brief      Erases all punctuation sings into readed data.
 *
 * @param      str   The string
 */
void PreProcesser::erasePunctuationSigns(QString &str)
{
    set_Data(str);
    erasePunctuationSigns();
    str = get_Data();
}

/**
 * @brief      Erases all punctuation sings into readed data.
 */
void PreProcesser::erasePunctuationSigns(void)
{
    for (unsigned i = 0; i < _data.length(); i++) {
        if (!_data[i].isLetter() && !_data[i].isDigit() && _data[i] != '\n' && _data[i] != '\r') {
            _data[i] = ' ';
        }
    }
}

/**
 * @brief      Erases all URLs into data var, an URL is defined as a '.' between
 *             letters without spaces.
 *
 * @param      str   The string
 */
void PreProcesser::eraseURLs(QString &str)
{
    set_Data(str);
    eraseURLs();
    str = get_Data();
}

/**
 * @brief      Erases all URLs into data var, an URL is defined as a '.' between
 *             letters without spaces. (Careful with float numbers)
 */
void PreProcesser::eraseURLs(void)
{
    for (unsigned i = 0; i < _data.length(); i++) {
        if (_data[i] == '.' && _data[i + 1] != ' ') {
            unsigned k = i;
            while (_data[k] != ' ') {
                _data[k] = ' ';
                k--;
            }
            while (_data[i] != ' ') {
                _data[i] = ' ';
                i++;
            }
        }
    }
}

/**
 * @brief      Erases all Hashtags into data var.
 *
 * @param      str   The string
 */
void PreProcesser::eraseHashtags(QString &str)
{
    set_Data(str);
    eraseHashtags();
    str = get_Data();
}

/**
 * @brief      Erases all Hashtags into data var.
 *
 */
void PreProcesser::eraseHashtags(void)
{
    for (unsigned i = 0; i < _data.length(); i++) {
        if (_data[i] == '#') {
            _data[i] = ' ';
            while (_data[i] != ' ') {
                _data[i] = ' ';
                i++;
            }
        }
    }
}

/**
 * @brief      Erases all numbers and characters form a readen number till next
 *             space.
 *
 * @param      str   The string
 */
void PreProcesser::eraseNumbers(QString &str)
{
    set_Data(str);
    eraseNumbers();
    str = get_Data();
}

/**
 * @brief      Erases all numbers and characters form a readen number till next
 *             space.
 */
void PreProcesser::eraseNumbers(void)
{
    if (_data[0].isDigit()) {
        unsigned i = 0;
        while (_data[i] != ' ') {
            _data[i] = ' ';
            i++;
        }
    }
    for (unsigned i = 1; i < _data.length(); i++) {
        if (_data[i].isDigit() && _data[i - 1] == ' ') {
            while (_data[i] != ' ') {
                _data[i] = ' ';
                i++;
            }
        }
    }
}

/**
 * @brief      Erases all words that contains numbers and all numbers in data.
 */
void PreProcesser::eraseAllNumbers(void)
{
    if (_data[0].isDigit()) {
        unsigned i = 0;
        while (_data[i] != ' ') {
            _data[i] = ' ';
            i++;
        }
    }
    for (unsigned i = 1; i < _data.length(); i++) {
        if (_data[i].isDigit()) {
            if (_data[i - 1] != ' ') {
                unsigned k = i - 1;
                while (_data[k] != ' ' && k > 0) {
                    _data[k] = ' ';
                    k--;
                }
            }
            while (_data[i] != ' ' && i < _data.size()) {
                _data[i] = ' ';
                i++;
            }
        }
    }
}

/**
 * @brief      Erases all words that contains numbers and all numbers in given
 *             string.
 *
 * @param      str   The string
 */
void PreProcesser::eraseAllNumbers(QString &str)
{
    set_Data(str);
    eraseAllNumbers();
    str = get_Data();
}

/**
 * @brief      Loads the data that starts with the dataTpe from input file into
 *             data var.
 *
 * @param      inputFile  The input file
 * @param[in]  dataType   The data type that wants to be loaded (must be the
 *                        first word per line)
 *
 * @return     Data lines included.
 */
int PreProcesser::loadData(QString &inputFile, QString dataType)
{
    _data = "";
    int dataLines = 0;
    QFile file(inputFile);
    QTextStream in(&file);
    if (!file.open(QIODevice::ReadOnly)) {
        std::cout << std::endl << "Error 404, file not found in loadData function." << std::endl;
        exit(1);
    }
    QString aux = "";
    while (!in.atEnd()) {
        in >> aux;
        if (dataType == "") {
            _data += aux + " ";
            aux = in.readLine();
            _data += aux;
            dataLines++;
        }
        else {
            if (aux.length() < dataType.length()) {
                QString spacedName = "";
                while (aux.length() < dataType.length()) {
                    in >> spacedName;
                    aux += " " + spacedName;
                }
            }
            QString readedType = aux.left(dataType.length());
            aux = aux.mid(dataType.length(), aux.length());
            aux = in.readLine();
            if (readedType == dataType) {
                _data += aux;
                dataLines++;
            }
        }
    }
    file.close();
    return dataLines;
}

/**
 * @brief      Loads the test data.
 *
 * @param      inputFile  The input file
 */
void PreProcesser::loadTestData(QString &inputFile)
{
    _data = "";
    const std::string ENDL = " PREPROCESSERENDL "; // Var that is going to be used in classifier to
                                                   // detects the end of a line
    std::ifstream file(inputFile.toStdString(), std::ios::in);
    if (file.fail()) {
        qDebug() << "\n"
                 << "Error 404, file not found in loadTestData function."
                 << "\n";
        exit(1);
    }
    std::string aux = "";
    while (!file.eof()) {
        std::getline(file, aux);
        _data += QString::fromStdString(aux + ENDL);
    }
    file.close();
}

/**
 * @brief      Prints data var.
 */
void PreProcesser::printData(void)
{
    qDebug() << _data;
}

/**
 * @brief      Stores the data into the given file
 *
 * @param      outputFile  The output file
 * @param[in]  dataLines   The data lines
 */
void PreProcesser::storeData(QString &outputFile, int dataLines)
{
    std::fstream file(outputFile.toStdString(), std::ios::out | std::ios::trunc);

    if (file.fail()) {
        qDebug() << "Error while storing data \"" << outputFile << "\" is not valid document"
                 << "\n";
        exit(1);
    }
    else {
        if (dataLines != 0) {
            file << dataLines << "\n";
        }
        file << _data.toStdString();
    }
    file.close();
}
