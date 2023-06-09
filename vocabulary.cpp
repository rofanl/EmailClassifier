/*=======================================================================================
=========================================================================================
        =                                                                              =
        =            Proyect:       Email Classifier                                   =
        =            File name:     vocabulary.cpp                                     =
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
 * @Last Modified by:   ADRIAN
 * @Last Modified time: 2021-12-19 22:17:18
 */
/*------------------  FUNCTIONS  -----------------*/

#include "include/vocabulary.h"

/*------------------------------------------------*/

/**
 * @brief      Constructs a new instance.
 */
Vocabulary::Vocabulary(void)
{
    set_InputFile("");
    set_OutpuFile("");
    set_VocabularyCounter(0);
    set_Type("");
    set_NTokens(0);
    set_NLines(0);
    set_ClassProbability(0.0);
}

/**
 * @brief      Constructs a new instance.
 *
 * @param[in]  inputFile  The input file
 * @param[in]  outpuFile  The outpu file
 */
Vocabulary::Vocabulary(QString inputFile, QString outpuFile)
{
    set_InputFile(inputFile);
    set_OutpuFile(outpuFile);
    set_VocabularyCounter(0);
    set_Type("");
    set_NTokens(0);
    set_NLines(0);
    set_ClassProbability(0.0);
}

/**
 * @brief      Destroys the object.
 */
Vocabulary::~Vocabulary(void)
{
}

/**
 * @brief      Gets the input file.
 *
 * @return     The input file.
 */
QString Vocabulary::get_InputFile(void) const
{
    return _inputFile;
}

/**
 * @brief      Gets the outpu file.
 *
 * @return     The outpu file.
 */
QString Vocabulary::get_OutpuFile(void) const
{
    return _outpuFile;
}

/**
 * @brief      Gets the VocabularyCounter.
 *
 * @return     The VocabularyCounter.
 */
int Vocabulary::get_VocabularyCounter(void) const
{
    return _vocabularyCounter;
}

/**
 * @brief      Gets the tokens number.
 *
 * @return     The tokens number.
 */
int Vocabulary::get_NTokens(void) const
{
    return _nTokens;
}

/**
 * @brief      Gets the number of lines.
 *
 * @return     The number of lines.
 */
int Vocabulary::get_NLines(void) const
{
    return _nLines;
}

/**
 * @brief      Gets the class probability.
 *
 * @return     The class probability.
 */
float Vocabulary::get_ClassProbability(void) const
{
    return _classProbability;
}

/**
 * @brief      Gets the vocabulary.
 *
 * @return     The vocabulary.
 */
std::set<Token> Vocabulary::get_Vocabulary(void) const
{
    return _vocabulary;
}

/**
 * @brief      Gets the type.
 *
 * @return     The type.
 */
QString Vocabulary::get_Type(void) const
{
    return _type;
}

/**
 * @brief      Sets the input file.
 *
 * @param[in]  newInputFile  The new input file
 */
void Vocabulary::set_InputFile(QString newInputFile)
{
    _inputFile = newInputFile;
}

/**
 * @brief      Sets the outpu file.
 *
 * @param[in]  newOutpuFile  The new outpu file
 */
void Vocabulary::set_OutpuFile(QString newOutpuFile)
{
    _outpuFile = newOutpuFile;
}

/**
 * @brief      Sets the counter.
 *
 * @param[in]  newVocabularyCounter  The new counter
 */
void Vocabulary::set_VocabularyCounter(int newVocabularyCounter)
{
    _vocabularyCounter = newVocabularyCounter;
}

/**
 * @brief      Sets the tokens number.
 *
 * @param[in]  newTokens  The new tokens number
 */
void Vocabulary::set_NTokens(int newTokens)
{
    _nTokens = newTokens;
}

/**
 * @brief      Sets the number of lines.
 *
 * @param[in]  newLines  The new lines number
 */
void Vocabulary::set_NLines(int newLines)
{
    _nLines = newLines;
}

/**
 * @brief      Sets the vocabulary.
 *
 * @param[in]  newVocabulary  The new vocabulary
 */
void Vocabulary::set_Vocabulary(std::set<Token> newVocabulary)
{
    _vocabulary = newVocabulary;
}

/**
 * @brief      Sets the type.
 *
 * @param[in]  newType  The new type
 */
void Vocabulary::set_Type(QString newType)
{
    _type = newType;
}

/**
 * @brief      Sets the class probability.
 *
 * @param[in]  newClassProbability  The new class probability
 */
void Vocabulary::set_ClassProbability(float newClassProbability)
{
    _classProbability = newClassProbability;
}

/**
 * @brief      Assignment operator.
 *
 * @param[in]  newVocabulary  The new vocabulary
 *
 * @return     The result of the assignment
 */
Vocabulary &Vocabulary::operator=(const Vocabulary &newVocabulary)
{
    this->set_Vocabulary(newVocabulary.get_Vocabulary());
    this->set_VocabularyCounter(newVocabulary.get_VocabularyCounter());
    this->set_OutpuFile(newVocabulary.get_OutpuFile());
    this->set_InputFile(newVocabulary.get_InputFile());
    this->set_NTokens(newVocabulary.get_NTokens());
    this->set_NLines(newVocabulary.get_NLines());
    this->set_Type(newVocabulary.get_Type());
    this->set_ClassProbability(newVocabulary.get_ClassProbability());
    return *this;
}

/**
 * @brief      Preprocess the data for the program, erases punctuation signs,
 *             converts all to lowercase and erases reserved words.
 *
 * @param[in]  stopWordFile  The stop word file
 */
void Vocabulary::preProcessData(QString &stopWordFile)
{
    PreProcesser preProcesser;
    QString outputFile = "outputs/preProcesserHelper.txt";
    std::vector<QString> stopWords = loadStopWord(stopWordFile);
    QString empty = "";
    preProcesser.loadData(_inputFile, empty);
    preProcesser.convertLowerCase();
    preProcesser.erasePunctuationSigns();
    preProcesser.eraseAllNumbers();
    preProcesser.storeData(outputFile, 0);
    preProcesser.eraseReservedWords(stopWords, outputFile);
    return;
}

/**
 * @brief      Loads the stop words (reserved words).
 *
 * @param[in]  inputFile  The input file
 *
 * @return     stop words vector
 */
std::vector<QString> Vocabulary::loadStopWord(QString &inputFile)
{
    std::vector<QString> stopWords;
    std::ifstream file(inputFile.toStdString(), std::ios::in);
    if (file.fail()) {
        std::cout << std::endl << "Error 404, stopWords file not found." << std::endl;
        exit(1);
    }
    std::string word = "";
    while (!file.eof()) {
        file >> word;
        stopWords.push_back(QString::fromStdString(word));
    }
    file.close();
    return stopWords;
}

/**
 * @brief      Generates vocabulary file
 *
 * @param      inputFile  The input file
 * @param[in]  tokenize   If want to words to be tokenized or not
 */
void Vocabulary::generateVocabulary(QString &inputFile, bool tokenize)
{
    std::ifstream file(inputFile.toStdString(), std::ios::in);
    if (file.fail()) {
        std::cout << std::endl
                  << "Error 404, generateVocabulary file not found. (" << inputFile.toStdString()
                  << ")" << std::endl;
        exit(1);
    }
    set_NTokens(0);
    set_VocabularyCounter(0);
    std::string word;
    std::set<Token>::iterator it;
    while (!file.eof()) {
        file >> word;
        if (isdigit(word[0])) {
            _nLines = stoi(word);
        }
        else {
            if (!_vocabulary.count(QString::fromStdString(word))) {
                Token newToken(QString::fromStdString(word));
                _vocabulary.insert(newToken);
            }
            else if (tokenize) {
                it = _vocabulary.find(QString::fromStdString(word));
                Token newToken = *it;
                newToken.incrementate();
                _vocabulary.erase(QString::fromStdString(word));
                _vocabulary.insert(newToken);
            }
            _nTokens++;
        }
    }
    file.close();
    set_VocabularyCounter(_vocabulary.size());
}

/**
 * @brief      Calculates and adds the class probability.
 *
 * @param[in]  size  The size
 */
void Vocabulary::addClassProbability(int size)
{

    float prob = _nLines;
    prob /= size;
    prob = std::log(prob);
    set_ClassProbability(prob);
}

/**
 * @brief      Reads a created vocabulary from file.
 *
 * @param      inputFile  The input file
 */
void Vocabulary::readVocabulary(QString &inputFile)
{
    std::ifstream file(inputFile.toStdString(), std::ios::in);
    if (file.fail()) {
        std::cout << std::endl
                  << "Error 404, readVocabulary file not found. (" << inputFile.toStdString() << ")"
                  << std::endl;
        exit(1);
    }
    set_NTokens(0);
    set_VocabularyCounter(0);
    std::string word;
    std::getline(file, word);
    while (!file.eof()) {
        file >> word;
        Token newToken(QString::fromStdString(word));
        newToken.set_Ammount(0);
        _vocabulary.insert(newToken);
        _nTokens++;
    }
    file.close();
    set_VocabularyCounter(_vocabulary.size());
}

/**
 * @brief      Stores the vocabulary into the given file.
 *
 * @param      outputFile  The output file
 */
void Vocabulary::storeVocabulary(QString &outputFile)
{
    std::fstream file(outputFile.toStdString(), std::ios::out | std::ios::trunc);
    if (file.fail()) {
        std::cout << "Error while storing data \"" << outputFile.toStdString()
                  << "\" is not valid document" << std::endl;
        exit(1);
    }
    else {
        file << "Number of words: " << get_VocabularyCounter();
        for (auto i : _vocabulary) {
            file << std::endl << i.get_Name().toStdString();
        }
        // This represents unkown words
        file << std::endl << "<UNK>";
    }
    file.close();
}

/**
 * @brief      Reads a learned data from a file and store the tokens with their
 *             respective probabilities and frecuence in the tokens set.
 *
 * @param      inputFile  The input file
 */
void Vocabulary::readLearnedData(QString &inputFile)
{
    std::ifstream file(inputFile.toStdString(), std::ios::in);
    QString type = "";
    type += inputFile[inputFile.length() - 5];
    set_Type(type);
    if (file.fail()) {
        std::cout << std::endl
                  << "Error 404, readVocabulary file not found. (" << inputFile.toStdString() << ")"
                  << std::endl;
        exit(1);
    }
    set_NTokens(0);
    set_VocabularyCounter(0);
    std::string word;
    std::getline(file, word);
    std::string tmp = "";
    for (unsigned i = 0; i < word.length(); i++) {
        if (isdigit(word[i])) {
            tmp += word[i];
        }
    }
    set_NLines(std::stoi(tmp));
    std::getline(file, word);
    while (!file.eof()) {
        file >> word >> word;
        Token newToken(QString::fromStdString(word));
        newToken.set_Type(type);
        file >> word >> word;
        newToken.set_Ammount(std::stoi(word));
        file >> word >> word;
        newToken.set_Probability(std::stof(word));
        _vocabulary.insert(newToken);
        _nTokens++;
    }
    file.close();
    set_VocabularyCounter(_vocabulary.size());
}
