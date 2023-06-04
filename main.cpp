#include <QDebug>
#include <QApplication>
#include <QFile>
#include <QFileDialog>
#include <QInputDialog>

/*------------------  FUNCTIONS  -----------------*/

#include "include/vocabulary.h"
#include "include/corpus.h"
#include "include/learner.h"
#include "include/classifier.h"
#include "include/Color.h"

/*------------------------------------------------*/
/*------------------  LIBRARIES  -----------------*/

#include <dirent.h>
#include <sys/types.h>

/*------------------------------------------------*/

void printHelp(void);
void generateVocabulary(QString originFile = nullptr, QString outputFile = nullptr,
                        QString reservedWords = nullptr);
void generateCorpus(QString originFile = nullptr, QString outputPath = nullptr,
                    QString reservedWords = nullptr, QList<QString> corpuses = QList<QString>());
void generateLearner(int &argc, char *argv[]);
void generateLearner();
void generateClassifier(int &argc, char *argv[]);
void generateClassifier();
void calculateError(int &argc, char *argv[]);
void mailGenerator(void);
void generateMail(QString fileName, std::vector<QString> &mail);
void deleteCommas(QString &message);
QString getValidMail(std::vector<QString> &mail);
void storeMail(QString type, std::vector<QString> &mail);
void generateTestMail(void);
void saveToFile(QString fileName, QString data, bool trunc);

/**
 * @brief      Main function of the program, receives the data file as
 *             parameter.
 *
 * @param[in]  argc  The count of arguments
 * @param      argv  The arguments array
 *
 * @return     0 If program finishes correctly
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //    if (argc <= 1) {
    //        printHelp();
    //    }
    //    else {

    std::string flag; //= argv[1];
    std::cout << "Enter Flags:\n";
    std::cin >> flag;
    if (flag == "-h" || flag == "--help") {
        printHelp();
        return (0);
    }
    else if (flag == "-v" || flag == "--vocabulary") {
        generateVocabulary();
    }
    else if (flag == "-co" || flag == "--corpus") {
        generateCorpus();
    }
    else if (flag == "-l" || flag == "--learner") {
        generateLearner();
    }
    else if (flag == "-cl" || flag == "--classify") {
        generateClassifier();
    }
    else if (flag == "-e" || flag == "--error") {
        calculateError(argc, argv);
    }
    else if (flag == "-u" || flag == "--updateDatabase") {
        mailGenerator();
    }
    else if (flag == "-t" || flag == "--generateTest") {
        srand(time(NULL));
        generateTestMail();
    }
    // }

    qDebug() << "\n"
             << "Program finished correclty."
             << "\n";
    return a.exec();
}

/**
 * @brief      Prints help information about how to run and use the program.
 */
void printHelp(void)
{
    QFile file("include/man.txt");

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "\n"
                 << "Error while opening manual file, make sure the file \"man.txt\" is placed on "
                    "the include folder."
                 << "\n";
        qDebug() << "You can also read the instructions at <https://github.com/AdrianEpi/SBlocker> "
                 << "\n"
                 << "\n";
        exit(1);
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        qDebug() << file.readLine() << "\n";
    }
}

/**
 * @brief      Generates the vocabulary from the first input file and stores it
 *             into second file using the stopwords readed from third file
 *
 * @param      argc  The count of arguments
 * @param      argv  The arguments array
 */
// void generateVocabulary(int &argc, char *argv[])
void generateVocabulary(QString originFile, QString outputFile, QString reservedWords)
{
    if (originFile.isEmpty() || outputFile.isEmpty() || reservedWords.isEmpty()) {
        //        qDebug() << "\n"
        //                 << "Error, the program needs 4 arguments to generate the vocabulary:"
        //                 << "\n"
        //                 << "\t bin/textClassifier -v originFile outputFile reservedWordsFile"
        //                 << "\n";
        //        exit(1);
        originFile = QFileDialog::getOpenFileName(nullptr, "Choose origin file.");
        outputFile = QFileDialog::getOpenFileName(nullptr, "Choose output file.");
        reservedWords = QFileDialog::getOpenFileName(nullptr, "Choose reserved words file.");
    }
    QString fileHelper = "outputs/preProcesserHelper.txt";
    Vocabulary vocabulary(originFile, outputFile);
    {
        Chrono chrono;
        chrono.startChrono();
        vocabulary.preProcessData(reservedWords);
        chrono.stopChrono();
        qDebug() << "\n"
                 << "Elapsed pre-processing time: " << chrono.get_Seconds(5) << " seconds."
                 << "\n";
    }
    {
        Chrono chrono;
        chrono.startChrono();
        vocabulary.generateVocabulary(fileHelper, false);
        chrono.stopChrono();
        qDebug() << "\n"
                 << "Elapsed generating vocabulary time: " << chrono.get_Seconds(5) << " seconds."
                 << "\n";
    }
    {
        Chrono chrono;
        chrono.startChrono();
        vocabulary.storeVocabulary(outputFile);
        chrono.stopChrono();
        qDebug() << "\n"
                 << "Elapsed storing vocabulary time: " << chrono.get_Seconds(5) << " seconds."
                 << "\n";
    }
}

/**
 * @brief      Generates one corpus per each type of data received as argument
 *             in console line. The data type must be the first column of the
 *             csv or data file and it should be followed by a ',' on the data
 *             file but not in the command line.
 *
 * @param      argc  The count of arguments
 * @param      argv  The arguments array
 */
void generateCorpus(QString originFile, QString outputPath, QString reservedWords,
                    QList<QString> corpuses)
{
    if (originFile.isEmpty() || outputPath.isEmpty() || reservedWords.isEmpty()) {
        //        qDebug() << "\n"
        //                 << "Error, the program needs at least 3 arguments to generate the
        //                 corpus:"
        //                 << "\n"
        //                 << "\t bin/textClassifier -co originFile reservedWordsFile CORPUS1
        //                 CORPUS2 "
        //                    "CORPUS3 . . ."
        //                 << "\n";
        //        qDebug() << "\n"
        //                 << "Each \"CORPUS\" represents one data type that wants to be separated
        //                 into "
        //                    "different corpus."
        //                 << "\n";
        //        exit(1);
        originFile = QFileDialog::getOpenFileName(nullptr, "Choose origin file.");
        // outputPath = QFileDialog::getExistingDirectory(nullptr, "Choose output file path.");
        reservedWords = QFileDialog::getOpenFileName(nullptr, "Choose reserved words file.");
        QString corpusesStr =
            QInputDialog::getMultiLineText(nullptr, "Enter corpuses", "Divide by ,");
        corpuses = corpusesStr.split(",");
    }
    PreProcesser preProcesser;
    Vocabulary voc;
    std::vector<QString> stopWords = voc.loadStopWord(reservedWords);
    for (const QString &corpus : qAsConst(corpuses)) {
        Corpus newCorpus(corpus, originFile);
        newCorpus.generateCorpus(stopWords, preProcesser);
    }
}

/**
 * @brief      Calculates the probability of each token in the given corpus as
 *             an argument at the command line and stores it into different
 *             files.
 *
 * @param      argc  The count of arguments
 * @param      argv  The arguments array
 */
void generateLearner(int &argc, char *argv[])
{
    //    if (argc < 3) {
    //        qDebug() << "\n"
    //                 << "Error, the program needs at least 2 arguments to learn data from corpus."
    //                 << "\n"
    //                 << "\t bin/textClassifier -l vocabularyFile Data1 Data2 ... DataX"
    //                 << "\n";
    //        qDebug() << "\n"
    //                 << "Each \"Data\" represents one data learning type that wants generated."
    //                 << "\n";
    //        exit(1);
    //    }
    Learner learner(argv, argc);
}
void generateLearner()
{
    QString vocFile = QFileDialog::getOpenFileName(nullptr, "Choose vocabulary file.");
    QString corpusesStr = QInputDialog::getMultiLineText(nullptr, "Enter corpuses", "Divide by ,");
    QStringList corpuses = corpusesStr.split(",");
    Learner learner(vocFile, corpuses);
}

/**
 * @brief      Classifies the test_curpus into the received class types
 *
 * @param      argc  The count of arguments
 * @param      argv  The arguments array
 */
void generateClassifier(int &argc, char *argv[])
{
    if (argc < 4) {
        qDebug() << "\n"
                 << "Error, the program needs at least 3 arguments to classify the test data:"
                 << "\n"
                 << "\t bin/textClassifier -cl corpusTestFile reservedWordsFile LEARNED1 LEARNED2 "
                    "LEARNED3 . . ."
                 << "\n";
        qDebug() << "\n"
                 << "Each \"LEARNED\" is generated with the --learner flag."
                 << "\n";
        exit(1);
    }
    Classifier newClassifier(argv, argc);
}
void generateClassifier()
{
    QString corpusTestFile = QFileDialog::getOpenFileName(nullptr, "Choose corpus test file.");
    QString reservedWords = QFileDialog::getOpenFileName(nullptr, "Choose reserved words file.");
    QStringList learnFiles = QFileDialog::getOpenFileNames(nullptr, "Choose learn files.");

    Classifier newClassifier(corpusTestFile, reservedWords, learnFiles);
}

/**
 * @brief      Calculates the error and success percentage comparing the
 *             expected outputFile and the generated outputFile.
 *
 * @param      argc  The count of arguments
 * @param      argv  The arguments array
 */
void calculateError(int &argc, char *argv[])
{
    if (argc != 4) {
        qDebug()
            << "\n"
            << "Error, the program needs 4 arguments to calculate the success and error percentage:"
            << "\n"
            << "\t bin/textClassifier -e classifiedResume expectedResume"
            << "\n";
        exit(1);
    }
    QString expected = argv[3];
    QString received = argv[2];
    std::vector<QString> expect;
    std::vector<QString> receive;
    QString tmp;
    QFile file1(expected);
    QTextStream ts1(&file1);
    if (!file1.open(QIODevice::WriteOnly)) {
        qDebug() << "\n"
                 << "Error 404," << expected << " file not found."
                 << "\n";
        exit(1);
    }
    else {
        while (!ts1.atEnd()) {
            ts1 >> tmp;
            expect.push_back(tmp);
        }
        file1.close();
    }
    QFile file2(received);
    QTextStream ts2(&file2);
    if (file2.open(QIODevice::WriteOnly)) {
        qDebug() << "\n"
                 << "Error 404," << received << " file not found."
                 << "\n";
        exit(1);
    }
    else {
        // std::getline(file2, tmp); мб эти два коммента нужны, но будем посмтреть
        while (!ts2.atEnd()) {
            // tmp = ts2.readLine();
            ts2 >> tmp;
            receive.push_back(tmp);
        }
        file2.close();
    }

    int size = 0;
    if (expect.size() < receive.size()) {
        size = expect.size();
    }
    else {
        size = receive.size();
    }
    int correct = 0;
    for (int i = 0; i < size; i++) {
        if (expect[i] == receive[i]) {
            correct++;
        }
    }
    float percentage = correct;
    percentage /= size;
    percentage *= 100;
    QString success = "Success percentage: ";
    QString error = "Error percentage: ";
    qDebug() << "\n"
             << Color::writeGreen(success) << correct << " / " << size << " = " << percentage
             << " %.";
    qDebug() << "\n"
             << Color::writeRed(error) << (size - correct) << " / " << size << " = "
             << (100 - percentage) << " %."
             << "\n";
}

/**
 * @brief      Gets the information of all the emails in the inputs/GenerateMails folder and stores
 * it.
 */
void mailGenerator(void)
{
    qDebug() << "Please select the type of emails you are going to load:\n\t1. SPAM\n\t2. No "
                "Spam\n\t0. Cancel"
             << "\n";
    QString type;
    int selection;
    std::cin >> selection;
    std::vector<QString> emails;
    switch (selection) {
    case 0:
        exit(0);
        break;
    case 1:
        type = "SPAM";
        break;
    case 2:
        type = "HAM";
        break;
    default:
        qDebug() << "Wrong email type introduced, aborting program   .   .   ."
                 << "\n";
        exit(1);
    }

    struct dirent *entry;
    DIR *dir = opendir("inputs/GenerateMails/");
    if (dir == NULL) {
        exit(1);
    }
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') {
            qDebug() << "Generating mail from: " << entry->d_name << "\n";
            std::vector<QString> mail;
            QString fileName = "inputs/GenerateMails/";
            fileName += entry->d_name;
            generateMail(fileName, mail);
            QString tmp = getValidMail(mail);
            if (tmp != "") {
                emails.push_back(tmp);
            }
        }
    }
    closedir(dir);
    storeMail(type, emails);
}

/**
 * @brief      Generate and gets the valid EMAIL text from an email file.
 *
 * @param[in]  fileName  The file name
 * @param      mail      The mail
 */
void generateMail(QString fileName, std::vector<QString> &mail)
{
    QFile file(fileName);
    QTextStream in(&file);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Error, file not found"
                 << "\n";
        exit(1);
    }
    while (!in.atEnd()) {
        QString line;
        line = in.readLine();
        if (line.length() > 3) {
            deleteCommas(line);
            mail.push_back(line);
        }
        else {
            mail.push_back(" ");
        }
    }
    file.close();
}

/**
 * @brief      Delete the commas in a message.
 *
 * @param      message  The message
 */
void deleteCommas(QString &message)
{
    for (unsigned i = 0; i < message.length(); i++) {
        if (message[i] == ',') {
            message[i] = ';';
        }
    }
}

/**
 * @brief      Gets the valid mail.
 *
 * @param      mail  The mail
 *
 * @return     The valid mail.
 */
QString getValidMail(std::vector<QString> &mail)
{
    for (unsigned i = 0; i < mail.size(); i++) {
        if (mail[i].contains("Content-Type: text/plain")) {
            while (mail[i] != " ") {
                i++;
            }
            QString realMail = "";
            while (i < mail.size()) {
                if (mail[i][0] == '-') {
                    break;
                }
                else {
                    realMail += " " + mail[i];
                }
                i++;
            }
            return realMail;
        }
    }
    return "";
}

/**
 * @brief      Stores the emails, 80% to learning database and 20% to testing database.
 *
 * @param[in]  type  The type
 * @param      mail  The mail
 */
void storeMail(QString type, std::vector<QString> &mail)
{
    QString learning = "";
    QString testing = "";
    for (unsigned i = 0; i < mail.size(); i++) {
        if (i % 5 == 0) {
            testing += "\n" + type + ", " + mail[i];
        }
        else {
            learning += "\n" + type + ", " + mail[i];
        }
    }
    saveToFile("inputs/mail-train.csv", learning, false);
    saveToFile("inputs/mail-test.csv", testing, false);
}

/**
 * @brief      Generate the test files for the SBlocker program
 */
void generateTestMail(void)
{
    QFile file("inputs/mail-train.csv");
    QTextStream in(&file);
    if (file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error, mail-train file not found"
                 << "\n";
        exit(1);
    }
    std::vector<QString> types;
    std::vector<QString> lines;
    while (!in.atEnd()) {
        QString line = "";
        QString type = "";
        in >> type;
        if (type == "SPAM,") {
            type = "SPAM";
        }
        else {
            type = "HAM";
        }
        line = in.readLine();
        types.push_back(type);
        lines.push_back(line);
    }
    file.close();
    QString mailTest = "";
    QString mailTestRow = "";
    QString resumeExpected = "";
    if (types.size() != lines.size()) {
        qDebug() << "\nAn error ocurred while working with vectors in generateTestMail\n";
        exit(1);
    }
    unsigned counter = types.size() / 5;
    unsigned num = rand() % types.size();
    mailTest += types[num] + ", " + lines[num];
    resumeExpected += types[num];
    mailTestRow += lines[num];
    counter--;
    while (counter > 0) {
        num = rand() % types.size();
        mailTest += "\n" + types[num] + ", " + lines[num];
        resumeExpected += "\n" + types[num];
        mailTestRow += "\n" + lines[num];
        counter--;
    }
    saveToFile("inputs/mail-test.csv", mailTest, true);
    saveToFile("inputs/mail-test-row.csv", mailTestRow, true);
    saveToFile("inputs/resumeExpected.csv", resumeExpected, true);
}

/**
 * @brief      Saves to file.
 *
 * @param[in]  fileName  The file name
 * @param[in]  data      The data
 * @param[in]  trunc     The truncate
 */
void saveToFile(QString fileName, QString data, bool trunc)
{
    if (!trunc) {
        std::ofstream file(fileName.toStdString(), std::ios::app);
        if (file.fail()) {
            qDebug() << "Error while storing in " + fileName + ", not valid document"
                     << "\n";
            exit(1);
        }
        else {
            file << data.toStdString();
        }
        file.close();
    }
    else {
        std::ofstream file(fileName.toStdString(), std::ios::out);
        if (file.fail()) {
            qDebug() << "Error while storing in " + fileName + ", not valid document"
                     << "\n";
            exit(1);
        }
        else {
            file << data.toStdString();
        }
        file.close();
    }
}
