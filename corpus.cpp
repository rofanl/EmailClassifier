/*=======================================================================================
=========================================================================================
        =                                                                              =
        =            Proyect:       Email Classifier                                   =
        =            File name:     corpus.cpp                                         =
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
 * @Last Modified time: 2021-12-02 18:32:44
 */
/*------------------  FUNCTIONS  -----------------*/

#include "include/corpus.h"
#include "qdebug.h"

/*------------------------------------------------*/

/**
 * @brief      Constructs a new instance.
 */
Corpus::Corpus(void)
{
    set_Name("");
    set_OutputFileName("");
    set_InputFile("");
}

/**
 * @brief      Constructs a new instance.
 *
 * @param[in]  name       The name
 * @param[in]  inputFile  The input file
 */
Corpus::Corpus(QString name, QString inputFile)
{
    set_Name(name);
    set_OutputFileName("outputs/corpus_" + name + ".txt");
    set_InputFile(inputFile);
}

/**
 * @brief      Destroys the object.
 */
Corpus::~Corpus(void)
{
}

/**
 * @brief      Gets the name.
 *
 * @return     The name.
 */
QString Corpus::get_Name(void) const
{
    return _name;
}

/**
 * @brief      Gets the output file name.
 *
 * @return     The output file name.
 */
QString Corpus::get_OutputFileName(void) const
{
    return _outputFileName;
}

/**
 * @brief      Gets the input file.
 *
 * @return     The input file.
 */
QString Corpus::get_InputFile(void) const
{
    return _inputFile;
}

/**
 * @brief      Sets the name.
 *
 * @param[in]  newName  The new name
 */
void Corpus::set_Name(QString newName)
{
    _name = newName;
}

/**
 * @brief      Sets the output file name.
 *
 * @param[in]  newOutputFileName  The new output file name
 */
void Corpus::set_OutputFileName(QString newOutputFileName)
{
    _outputFileName = newOutputFileName;
}

/**
 * @brief      Sets the input file.
 *
 * @param[in]  newInputFile  The new input file
 */
void Corpus::set_InputFile(QString newInputFile)
{
    _inputFile = newInputFile;
}

/**
 * @brief      Generates and stores the corpus data.
 *
 * @param      stopWords     The stop words
 * @param[in]  preProcesser  The pre processer
 */
void Corpus::generateCorpus(std::vector<QString> &stopWords, PreProcesser &preProcesser)
{
    Chrono myChrono;
    int dataLines;
    myChrono.startChrono();
    QString outputFile = "outputs/preProcesserHelper.txt";
    QString dataType = get_Name() + ",";
    dataLines = preProcesser.loadData(_inputFile, dataType);
    preProcesser.convertLowerCase();
    preProcesser.erasePunctuationSigns();
    preProcesser.eraseAllNumbers();
    preProcesser.storeData(outputFile, 0);
    preProcesser.eraseReservedWords(stopWords, outputFile);
    preProcesser.storeData(_outputFileName, dataLines);
    myChrono.stopChrono();

    qDebug() << "\nElapsed time for corpus " << _name << ": " << myChrono.get_Seconds(5)
             << " seconds\n.";
}
