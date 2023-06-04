/*=======================================================================================
=========================================================================================
        =                                                                              =
        =            Proyect:       Email Classifier                                   =
        =            File name:     learner.cpp                                        =
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
 * @Last Modified time: 2021-12-19 22:28:01
 */
/*------------------  FUNCTIONS  -----------------*/

#include "include/learner.h"
#include "qdebug.h"

#include <QDebug>

/*------------------------------------------------*/

/**
 * @brief      Constructs a new instance.
 */
Learner::Learner(void)
{
    set_VocabularyFile("");
}

/**
 * @brief      Constructs a new instance.
 *
 * @param      argv  The arguments array
 * @param      argc  The count of arguments
 */
Learner::Learner(char *argv[], int &argc)
{
    // Vocabulary file must be in 3rd place as shown in manual
    set_VocabularyFile(argv[2]);
    for (int i = 3; i < argc; i++) {
        Chrono chrono;
        chrono.startChrono();
        QString tmp = "outputs/corpus_";
        tmp += argv[i];
        tmp += ".txt";
        Vocabulary newVoc;
        newVoc.readVocabulary(vocabularyFile_);
        newVoc.generateVocabulary(tmp, true);
        learners_.push_back(newVoc);
        inputCorpusFiles_.push_back(argv[i]);
        chrono.stopChrono();
        std::cout << std::endl
                  << "Elapsed generating tokens and vocabulary time: " << chrono.get_Seconds(5)
                  << " seconds for " << argv[i] << " data type." << std::endl;
    }
    learnAndStoreData();
}

Learner::Learner(QString vocFile, QStringList corpuses)
{
    // Vocabulary file must be in 3rd place as shown in manual
    set_VocabularyFile(vocFile);
    for (const QString &corpus : corpuses) {
        Chrono chrono;
        chrono.startChrono();
        QString tmp = "outputs/corpus_";
        tmp += corpus;
        tmp += ".txt";
        Vocabulary newVoc;
        newVoc.readVocabulary(vocabularyFile_);
        newVoc.generateVocabulary(tmp, true);
        learners_.push_back(newVoc);
        inputCorpusFiles_.push_back(corpus);
        chrono.stopChrono();
        qDebug() << "\nElapsed generating tokens and vocabulary time: " << chrono.get_Seconds(5)
                 << " seconds for " << corpus << " data type.\n";
    }
    learnAndStoreData();
}

/**
 * @brief      Destroys the object.
 */
Learner::~Learner(void)
{
}

/**
 * @brief      Gets the learners.
 *
 * @return     The learners.
 */
std::vector<Vocabulary> Learner::get_Learners(void) const
{
    return learners_;
}

/**
 * @brief      Gets the input corpus files.
 *
 * @return     The input corpus files.
 */
std::vector<QString> Learner::get_InputCorpusFiles(void) const
{
    return inputCorpusFiles_;
}

/**
 * @brief      Gets the vocabulary file.
 *
 * @return     The vocabulary file.
 */
QString Learner::get_VocabularyFile(void) const
{
    return vocabularyFile_;
}

/**
 * @brief      Sets the learners.
 *
 * @param[in]  newLearners  The new learners
 */
void Learner::set_Learners(std::vector<Vocabulary> newLearners)
{
    learners_ = newLearners;
}

/**
 * @brief      Sets the input corpus files.
 *
 * @param[in]  newInputCorpusFiles  The new input corpus files
 */
void Learner::set_InputCorpusFiles(std::vector<QString> newInputCorpusFiles)
{
    inputCorpusFiles_ = newInputCorpusFiles;
}

/**
 * @brief      Sets the vocabulary file.
 *
 * @param[in]  newVocabularyFile  The new vocabulary file
 */
void Learner::set_VocabularyFile(QString newVocabularyFile)
{
    vocabularyFile_ = newVocabularyFile;
}

/**
 * @brief      Generates the proabilities of all the tokens in vocabulary and
 *             stores them in a file called "learned_DATATYPE.txt".
 *             The file format is:
 *             Number of corpus documents: <integer>
 *             Number of words in corpus: <integer>
 *             Word:<string> Frec:<int> LogProb:<float>
 *             Word:<string> Frec:<int> LogProb:<float>
 *             Word:<string> Frec:<int> LogProb:<float>
 */
void Learner::learnAndStoreData(void)
{
    for (unsigned i = 0; i < learners_.size(); i++) {
        Chrono chrono;
        chrono.startChrono();
        std::string fileName = "outputs/learned_";
        fileName += inputCorpusFiles_[i].toStdString();
        fileName += ".txt";
        std::fstream file(fileName, std::ios::out);
        if (file.fail()) {
            std::cout << "Error while storing learned data \"" << fileName
                      << "\" is not valid document" << std::endl;
            exit(1);
        }
        else {
            int tokenAmmount = learners_[i].get_NTokens();
            int vocSize = learners_[i].get_VocabularyCounter();
            std::string data =
                "number of corpus documents: " + std::to_string(learners_[i].get_NLines());
            data += "\nNumber of words in the corpus: " + std::to_string(tokenAmmount);
            for (auto tmp : learners_[i].get_Vocabulary()) {
                std::string line = "\nWord: " + tmp.get_Name().toStdString();
                /*----------  Uncomment this for tab columns  ----------*/
                /*
                while (line.length() < 50) {
                        line += " ";
                }
                data += line + "\t\tFrec: " + std::to_string(tmp.get_Ammount()) + "  \t\tLogProb: "
                + std::to_string(tmp.generateLogProb(vocSize, tokenAmmount));
                */

                /*----------  Comment this for untab columns  ----------*/
                data += line + " Frec: " + std::to_string(tmp.get_Ammount()) +
                        " LogProb: " + std::to_string(tmp.generateLogProb(vocSize, tokenAmmount));
            }
            file << data;
            file.close();
        }
        chrono.stopChrono();

        qDebug() << "\nElapsed time for calculating probabilities: " << chrono.get_Seconds(5)
                 << " seconds for " << inputCorpusFiles_[i] << " data type.\n";
    }
}
