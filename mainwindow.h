#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <QDir>
#include <QResource>
#include <QLineEdit>
#include <QTextEdit>
#include <QTextCodec>
#include <QTextStream>
#include <QFileDialog>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QThread>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlQuery>
#include <QSqlRecord>
 #include <QSqlDatabase>
#include <QVariant>
#include <QScrollArea>
#include <QWidget>
#include <QGroupBox>
#include <QGridLayout>
#include <dynamicbutton.h>
#include <dynamicbutton.h>

class DBFacade;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    struct sourse_translation_examples
    {
        QString engNgramm;
        QString rusNgramm;
        int count;
        QMap <QString, QString> examples;
    };



private slots:

    void setWidgetsGray();

    void on_pushButton_clicked();

    void on_actionOpen_3_triggered();

    void slotGetExaples();

    void clearWidgets();

    void learn(QString tn);

    void on_translateButton_clicked();

    void on_textEdit_textChanged();

    void translationSearchPart(QStringList translationless_ngrams, int n, QMap<QString, int>& ngramCount, QString corporaPart,
                               QMultiMap<QString, QString>& eng3gramRusSentence, QMultiMap<QString, QString>& eng2gramRusSentence, QMultiMap<QString, QString>& eng1gramRusSentence);

    void engNgramsGeneration(QStringList words, QStringList &threegrams, QStringList &bigrams, QStringList &unigrams);

    QStringList splitIntoSentences(QString text);

    QStringList splitTntoWords(QString sentence);

    void translationSearch(QStringList translationless3Grams,
                         QStringList translationless2Grams,
                         QStringList translationless1Grams,
                         QMap<QString, int>& ngramCountMap,
                         QMultiMap<QString, QString>& eng3gramRusSentence,
                         QMultiMap<QString, QString>& eng2gramRusSentence,
                         QMultiMap<QString, QString>& eng1gramRusSentence);

    void backTranslationSearch(QMultiMap<QString, QMap<QString, QVector<int>>> &sourseTranslationSorted);

    void examplesSearch(QVector <sourse_translation_examples>& setVec);

    void examplesSearchPart(sourse_translation_examples& setVec, QString corporaPart);

    QStringList noTranslationNgramSearch(QStringList ngrams, QMap<QString, int> &ngramCountMap);

    void addNgram(QStringList translationWords,  QMap<QString, int> &translationNgramCount, int n);

    void eraseLowFreqNgrams(QMap<QString, int> &translationNgramCount);

    void rusNgramsGeneration(QStringList &translationlessNgrams, QMultiMap<QString, QString> map, QMap<QString, QMap<QString, int>> &sourseNgramTranslationNgramCount,
                                QMap<QString, QMap<QString, int>> &sourseNgramTranslationNgramCount3_2, int n);

    void translationSort(QMap<QString, QMap<QString, int>> sourseTransCount, QMultiMap<QString, QMap<QString, QVector<int>>> &sourseTranslationSorted);

    void backTranslation(QString corpora, QMultiMap<QString, QMap<QString, QVector<int>>> &sourseTranslationSorted);

    void writeToTranslationTable(QMultiMap<QString, QMap<QString, QVector<int>>> &sourseTranslationSorted);

    void fillingStructure(QRegExp rusNgram, QStringList translationlessNgrams, QMultiMap<QString, QString> sourseNgramsTranslationSentences, sourse_translation_examples &setTemp);

    void fillingExamplesStructures(QVector <sourse_translation_examples> &setVec,
                                   QStringList translationless3grams,
                                   QStringList translationless2grams,
                                   QStringList translationless1grams,
                                   QMultiMap<QString, QString> sourse3gramsTranslationSentences,
                                   QMultiMap<QString, QString> sourse2gramsTranslationSentences,
                                   QMultiMap<QString, QString> sourse1gramsTranslationSentences,
                                   QMultiMap<QString, QMap<QString, QVector<int>>> &sourseTranslationSorted);

private:
    Ui::MainWindow *ui;

    QGridLayout *layout;

    QMessageBox messageBox;

    QTextStream textStream;

    typedef QMap<QString, int> Map;

    DBFacade* translationDB;


};
#endif // MAINWINDOW_H
