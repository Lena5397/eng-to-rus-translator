#include "dbfacade.h"

DBFacade::DBFacade(QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(QDir::toNativeSeparators(QApplication::applicationDirPath()) + "/translationdb.db");

    if(db.open()){
        query = QSqlQuery(db);
        dbMessageBox.setText("База переводов подключена");
        dbMessageBox.exec();
    }else {
        dbMessageBox.setText("База переводов не подключена: "+ db.lastError().databaseText());
        dbMessageBox.exec();

    }

}

bool DBFacade::engNgramSearch(QString ngram)
{

    query.exec("SELECT ngram FROM eng_ngrams WHERE ngram LIKE '" + ngram + "'");

    QSqlRecord rec = query.record();
    int nameCol = rec.indexOf("ngram");
    query.next();

    if (!query.value(nameCol).isNull()){
        return true;
    }else{
        return false;
    }

}



void DBFacade::addToTranslationTable(QString engNgram, QString rusNgram, int translationCount, double coef)
{

      QString stringTranslationCount = QString::number(translationCount);
      QString stringCoef = QString::number(coef,'f',10);

      query.exec("INSERT INTO translations (eng_ngram, rus_ngram, count, coef) VALUES ('" + engNgram + "', '" + rusNgram + "', '" + stringTranslationCount + "', '" + stringCoef + "')");
}



void DBFacade::addToEngNgramsTable(QString engNgram, int appearences)
{

     QString stringTranslationAppearences = QString::number(appearences);

     query.exec("INSERT INTO eng_ngrams (ngram, count) VALUES ('" + engNgram + "', '" + stringTranslationAppearences + "')");
}



void DBFacade::addToExamplesTable(QString engNgram, QString rusNgram, QString engSentence, QString rusSentence)
{
    QSqlQuery queryp;
    queryp.prepare ("INSERT INTO examples (eng_ngram, rus_ngram, eng_sentence, rus_sentence) Values(:en, :rn, :es, :rs)") ;
    queryp.bindValue (":en", engNgram);
    queryp.bindValue (":rn", rusNgram);
    queryp.bindValue (":es", engSentence);
    queryp.bindValue (":rs", rusSentence);
    if (!queryp.exec()){
        qDebug() << "Error could not insert information to database" << queryp.lastError();
    }

}


QStringList DBFacade::rusNgramCapture(QString engNgram)
{

    QStringList rusNgrams;
    QString translationNgram;
    query.exec("SELECT rus_ngram FROM translations WHERE eng_ngram LIKE '" + engNgram + " '");

    QSqlRecord rec = query.record();
    int nameCol3 = rec.indexOf("rus_ngram");
    while(query.next()){
        translationNgram = query.value(nameCol3).toString();
        rusNgrams.append(translationNgram);
        translationNgram.clear();
    }
    return rusNgrams;
}


QMap<QString, QString> DBFacade::examplesCapture(QString engNgram, QString rusNgram)
{

    QString engExample;
    QString rusExample;
    QMap<QString, QString> examplesTemp;

    query.exec("SELECT eng_sentence, rus_sentence FROM examples WHERE rus_ngram LIKE '" + rusNgram + "' AND eng_ngram LIKE '" + engNgram + " '");

    QSqlRecord rec = query.record();
    int nameColEngSent = rec.indexOf("eng_sentence");
    int nameColRusSent = rec.indexOf("rus_sentence");

    while(query.next()){
       engExample = query.value(nameColEngSent).toString();
       rusExample = query.value(nameColRusSent).toString();
       examplesTemp.insert(engExample,rusExample);
       engExample.clear();
       rusExample.clear();
    }

    return examplesTemp;
}
