#ifndef DBFACADE_H
#define DBFACADE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QFile>
#include <QMessageBox>
#include <QDir>
#include <QResource>
#include <QTextEdit>
#include <QTextCodec>
#include <QTextStream>
#include <QDebug>
#include <QApplication>

class DBFacade : public QObject
{
    Q_OBJECT
public:
    explicit DBFacade(QObject *parent = nullptr);


    bool engNgramSearch(QString ngram);
    void addToTranslationTable(QString eng_ngram, QString rus_ngram, int translation_count, double revers_coef);
    void addToEngNgramsTable(QString eng_ngram, int appearences);
    void addToExamplesTable(QString eng_ngram, QString rus_ngram, QString eng_sentence, QString rus_sentence);
  //  QMultiMap<QString, QString> english_ngram_search(QStringList ngrams_for_search);
    QStringList rusNgramCapture(QString eng_ngram);
    QMap<QString, QString> examplesCapture(QString eng_ngram, QString rus_ngram);

protected:
    QSqlDatabase db;
    QSqlQuery query;

private:
    QMessageBox dbMessageBox;





};

#endif // DBFACADE_H
