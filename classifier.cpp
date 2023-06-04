/*=======================================================================================
=========================================================================================
        =                                                                              =
        =            Proyect:       Email Classifier                                   =
        =            File name:     classifier.cpp                                     =
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
 * @Last Modified time: 2021-12-19 23:01:25
 */
/*------------------  FUNCTIONS  -----------------*/

#include "include/classifier.h"
#include "qdebug.h"

#include <QSet>
#include <QStringList>

/*------------------------------------------------*/

/**
 * @brief      Constructs a new instance.
 */
Classifier::Classifier(QString corpusTestFile, QString reservedWords, QStringList learnFiles)
{
    set_Data("");
    readInputFiles(learnFiles);
    generateClassProbability();
    classifyFile(corpusTestFile, reservedWords);
    QString outputFile = "outputs/classification.csv";
    QString resume = "outputs/resume.csv";
    storeFile(outputFile, resume);
}

/**
 * @brief      Constructs a new instance.
 *
 * @param      argv  The arguments array
 * @param      argc  The count of arguments
 */
Classifier::Classifier(char *argv[], int &argc)
{
    set_Data("");
    readInputFiles(argv, argc);
    generateClassProbability();
    QString input = argv[2];
    QString stopWords = argv[3];
    classifyFile(input, stopWords);
    QString outputFile = "outputs/classification.csv";
    QString resume = "outputs/resume.csv";
    storeFile(outputFile, resume);
}

/**
 * @brief      Destroys the object.
 */
Classifier::~Classifier(void)
{
}

/**
 * @brief      Gets the input files.
 *
 * @return     The input files.
 */
std::vector<QString> Classifier::get_InputFiles(void) const
{
    return _inputFiles;
}

/**
 * @brief      Gets the learned data.
 *
 * @return     The learned data.
 */
std::vector<Vocabulary> Classifier::get_Class(void) const
{
    return _class;
}

/**
 * @brief      Gets the data.
 *
 * @return     The data.
 */
QString Classifier::get_Data(void) const
{
    return _data;
}

/**
 * @brief      Sets the input files.
 *
 * @param[in]  newInputFiles  The new input files
 */
void Classifier::set_InputFiles(std::vector<QString> newInputFiles)
{
    _inputFiles = newInputFiles;
}

/**
 * @brief      Sets the learned data.
 *
 * @param[in]  newClass  The new learned data
 */
void Classifier::set_Class(std::vector<Vocabulary> newClass)
{
    _class = newClass;
}

/**
 * @brief      Sets the data.
 *
 * @param[in]  newData  The new data
 */
void Classifier::set_Data(QString newData)
{
    _data = newData;
}

/**
 * @brief      Preprocess, calculates the probabilities and classifies the given
 *             input file.
 *
 * @param      inputFile      The input file with the testCorpus
 * @param      stopWordsFile  The stop words file for preprocessing use
 */
void Classifier::classifyFile(QString &inputFile, QString &stopWordsFile)
{
    Vocabulary voc;
    std::vector<QString> stopWord;
    stopWord = voc.loadStopWord(stopWordsFile);
    QString tmp;
    preProcess(stopWord, inputFile);
    std::string helper = "outputs/preProcesserHelper.txt";
    std::ifstream file(helper, std::ios::in);
    std::ifstream originalFile(inputFile.toStdString(), std::ios::in);
    Chrono myChrono;
    myChrono.startChrono();
    if (file.fail() || originalFile.fail()) {
        qDebug() << "\nError 404, preProcesserHelper.txt file not found in /outputs.\n";
        exit(1);
    }
    std::string originalReader = "";
    while (!file.eof()) {
        QVector<QString> sentence;
        std::string tmp = "";
        while (!file.eof()) {
            file >> tmp;
            if (tmp == "preprocesserendl") {
                break;
            }
            sentence.push_back(QString::fromStdString(tmp));
        }
        std::getline(originalFile, originalReader);
        if (originalReader[originalReader.length() - 1] == '\r') {
            originalReader[originalReader.length() - 1] = ' ';
        }
        _data += QString::fromStdString(originalReader);
        classify(sentence);
    }
    file.close();
    originalFile.close();
    myChrono.stopChrono();
    qDebug() << "\nElapsed Classifying time: " << myChrono.get_Seconds(5) << " seconds.\n";
}

/**
 * @brief      Classifies a given sentence into the correct type and stores the
 *             information into data var.
 *
 * @param[in]  sentence  The sentence which is going to be classifyed
 */
void Classifier::classify(QVector<QString> sentence)
{
    std::vector<float> prob;
    prob.resize(_inputFiles.size());
    for (unsigned i = 0; i < prob.size(); i++) {
        prob[i] = 0.0;
    }
    QHash<QString, Token>::iterator it;
    for (QString word : sentence) {

        it = _learnedData.find(word);
        for (unsigned j = 0; j < prob.size(); j++) {
            prob[j] += it->get_MultiClass(j);
        }
    }
    _data += ", ";
    unsigned selection = 0;
    for (unsigned i = 0; i < prob.size(); i++) {
        prob[i] += _class[i].get_ClassProbability();
        if (prob[selection] < prob[i]) {
            selection = i;
        }
        _data += QString::number(prob[i]);
        _data += ", ";
    }
    _resume.push_back(_class[selection].get_Type());
    _data += _class[selection].get_Type();
    _data += ".\r";
}

/**
 * @brief      Generates and adds the class probabilities to each class with the
 *             following formula: ln(classLinesAmmount / totalLinesAmmout)
 */
void Classifier::generateClassProbability(void)
{
    int totalLines = 0;
    for (unsigned i = 0; i < _class.size(); i++) {
        totalLines += _class[i].get_NLines();
    }
    for (unsigned i = 0; i < _class.size(); i++) {
        _class[i].addClassProbability(totalLines);
    }
}

/**
 * @brief      Preprocess the given sentence using the same pre-processing
 *             method as the vocabulary
 *
 * @param      preprocesser  The preprocesser
 * @param      stopWords     The stop words
 * @param      sentence      The sentence
 */
void Classifier::preProcess(std::vector<QString> &stopWords, QString &fileName)
{
    PreProcesser preprocesser;
    QString helper = "outputs/preProcesserHelper.txt";
    preprocesser.loadTestData(fileName);
    preprocesser.convertLowerCase();
    preprocesser.erasePunctuationSigns();
    preprocesser.eraseAllNumbers();
    preprocesser.storeData(helper, 0);
    preprocesser.eraseReservedWords(stopWords, helper);
}

QString Classifier::getTypeOfFile(QString file)
{
    QRegExp rx(R"(_(\w*)(?:\.txt))");
    rx.indexIn(file);
    return rx.cap(1);
}

/**
 * @brief      Reads input learned files and store the tokens into the Class vector.
 *
 * @param      argv  The arguments array
 * @param      argc  The count of arguments
 */
void Classifier::readInputFiles(char *argv[], int &argc)
{
    std::vector<Token> tmpVector;
    for (int k = 4; k < argc; k++) {
        std::string fileName = argv[k];
        _inputFiles.push_back(QString::fromStdString(fileName));
        std::string type = "";
        // ONLY FOR THIS PROGRAM
        if (fileName == "outputs/learned_SPAM.txt") {
            type += "SPAM";
        }
        else {
            type += "HAM";
        }
        std::ifstream file(fileName, std::ios::in);
        if (file.fail()) {
            std::cout << std::endl << "Error 404," << fileName << " file not found." << std::endl;
            exit(1);
        }
        else if (k == 4) {
            std::string reader = "";
            file >> reader >> reader >> reader >> reader >> reader >> reader;
            Vocabulary newVoc;
            newVoc.set_NLines(std::stoi(reader));
            newVoc.set_Type(QString::fromStdString(type));
            _class.push_back(newVoc);
            std::getline(file, reader);
            while (!file.eof()) {
                file >> reader >> reader;
                Token newToken(QString::fromStdString(reader));
                file >> reader >> reader >> reader >> reader;
                newToken.addClassProb(std::stof(reader), QString::fromStdString(type));
                newToken.set_Type(QString::fromStdString(type));
                tmpVector.push_back(newToken);
            }
        }
        else {
            int i = 0;
            std::string reader = "";
            file >> reader >> reader >> reader >> reader >> reader >> reader;
            Vocabulary newVoc;
            newVoc.set_NLines(std::stoi(reader));
            newVoc.set_Type(QString::fromStdString(type));
            _class.push_back(newVoc);
            std::getline(file, reader);
            while (!file.eof()) {
                file >> reader >> reader >> reader >> reader >> reader >> reader;
                tmpVector[i].addClassProb(std::stof(reader), QString::fromStdString(type));
                i++;
            }
        }
        file.close();
    }
    for (unsigned i = 0; i < tmpVector.size(); i++) {
        _learnedData.insert(tmpVector[i].get_Name(), tmpVector[i]);
    }
}

void Classifier::readInputFiles(QStringList learnFiles)
{
    // читая первый файл надо заполнить вектор токенами, читая последующие надо обновить
    // существующие токены и добавить недостающие
    QHash<QString, Token> tmpVector;

    for (QString learnfile : learnFiles) {
        std::string fileName = learnfile.toStdString();
        _inputFiles.push_back(learnfile);
        QString type;

        type = getTypeOfFile(QString::fromStdString(fileName));
        std::ifstream file(fileName, std::ios::in);
        if (file.fail()) {
            std::cout << std::endl << "Error 404," << fileName << " file not found." << std::endl;
            exit(1);
        }
        else {
            std::string reader = "";
            file >> reader >> reader >> reader >> reader >> reader;
            Vocabulary newVoc;
            newVoc.set_NLines(std::stoi(reader));
            newVoc.set_Type(type);
            _class.push_back(newVoc);
            file >> reader >> reader >> reader >> reader >> reader >> reader >> reader;
            while (!file.eof()) {
                file >> reader >> reader;
                QString word = QString::fromStdString(reader);
                file >> reader >> reader >> reader >> reader;
                float prob = std::stof(reader);
                if (!tmpVector.contains(word)) {
                    Token newToken(word);
                    newToken.addClassProb(prob, type);
                    newToken.set_Type(type);
                    tmpVector.insert(word, newToken);
                }
                else {
                    tmpVector[word].addClassProb(prob, type);
                }
            }
        }
        file.close();
        _learnedData = tmpVector;
        //        for (Token token : tmpVector)
        //            _learnedData.insert(token);
    }
}

/**
 * @brief      Stores the output data into the classified file and the resume
 *             file. The classify file format is:
 *             <Description>, <ProbSentClassA>, ..., <ProbSentClassN>, <Class>.
 *             <Description>, <ProbSentClassA>, ..., <ProbSentClassN>, <Class>.
 *             <Description>, <ProbSentClassA>, ..., <ProbSentClassN>, <Class>.
 *
 * @param      outputFile  The output file
 * @param      resumeFile  The resume file
 */
void Classifier::storeFile(QString &outputFile, QString &resumeFile)
{
    std::fstream file(outputFile.toStdString(), std::ios::out | std::ios::trunc);
    if (file.fail()) {
        std::cout << "Error while storing data \"" << outputFile.toStdString()
                  << "\" is not valid document." << std::endl;
        exit(1);
    }
    else {
        // bool isDecimal = false;
        //  for (int i = 0; i < _data.length(); i++) {
        /*----------  Fixing decimales to 2 digits  ----------*/
        file << _data.toStdString(); // If dont want to trunc decimals

        //            if (isDecimal && _data[i].isDigit() && _data[i - 2].isDigit()) {
        //                if (_data[i] != ',') {
        //                    file << _data[i].toLatin1();
        //                    i++;
        //                }
        //                while (_data[i] != ',' && _data[i] != '.') {
        //                    i++;
        //                }
        //                file << _data[i].toLatin1();
        //                isDecimal = false;
        //            }
        //            else {
        //                isDecimal = false;
        //                file << _data[i].toLatin1();
        //                if (_data[i] == '.') {
        //                    isDecimal = true;
        //                }
        //            }
        //}
    }
    file.close();
    std::fstream resume(resumeFile.toStdString(), std::ios::out | std::ios::trunc);
    if (resume.fail()) {
        std::cout << "Error while storing data \"" << resumeFile.toStdString()
                  << "\" is not valid document." << std::endl;
        exit(1);
    }
    else {
        for (unsigned i = 0; i < _resume.size(); i++) {
            resume << _resume[i].toStdString() << std::endl;
        }
        resume.close();
    }
}
