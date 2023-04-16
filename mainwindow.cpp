#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbfacade.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    layout = new QGridLayout(this);
    layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    ui->scrollAreaWidgetContents->setLayout(layout);
    setWidgetsGray();

    translationDB = new DBFacade();
}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::setWidgetsGray()
{
    QPalette readOnlyPalette = ui->textEdit->palette();
    QColor mainWindowBgColor = palette().color(QPalette::Window);
    readOnlyPalette.setColor(QPalette::Base, mainWindowBgColor);

    ui->scrollArea->setStyleSheet("QScrollArea { border: 1px silver }");

    ui->line->setStyleSheet("border: silver");
    ui->line_2->setStyleSheet("border: silver");
    ui->line_3->setStyleSheet("border: silver");
    ui->line_4->setStyleSheet("border: silver");
    ui->line_5->setStyleSheet("border: silver");
    ui->line_6->setStyleSheet("border: silver");
    ui->line_7->setStyleSheet("border: silver");
    ui->line_8->setStyleSheet("border: silver");
    ui->line_9->setStyleSheet("border: silver");

    ui->textBrowser->setPalette(readOnlyPalette);
    ui->textBrowser_2->setPalette(readOnlyPalette);
    ui->textBrowser_3->setPalette(readOnlyPalette);
    ui->textBrowser_4->setPalette(readOnlyPalette);
    ui->textBrowser_5->setPalette(readOnlyPalette);
    ui->textBrowser_6->setPalette(readOnlyPalette);
    ui->textBrowser_7->setPalette(readOnlyPalette);
    ui->textBrowser_8->setPalette(readOnlyPalette);
    ui->textBrowser_9->setPalette(readOnlyPalette);
    ui->textBrowser_10->setPalette(readOnlyPalette);
    ui->textBrowser_11->setPalette(readOnlyPalette);
    ui->textBrowser_12->setPalette(readOnlyPalette);
    ui->textBrowser_13->setPalette(readOnlyPalette);
    ui->textBrowser_14->setPalette(readOnlyPalette);
    ui->textBrowser_15->setPalette(readOnlyPalette);
    ui->textBrowser_16->setPalette(readOnlyPalette);
    ui->textBrowser_17->setPalette(readOnlyPalette);
    ui->textBrowser_18->setPalette(readOnlyPalette);
    ui->textBrowser_19->setPalette(readOnlyPalette);
    ui->textBrowser_20->setPalette(readOnlyPalette);
    ui->textBrowser->setStyleSheet("border: silver");
    ui->textBrowser_2->setStyleSheet("border: silver");
    ui->textBrowser_3->setStyleSheet("border: silver");
    ui->textBrowser_4->setStyleSheet("border: silver");
    ui->textBrowser_5->setStyleSheet("border: silver");
    ui->textBrowser_6->setStyleSheet("border: silver");
    ui->textBrowser_7->setStyleSheet("border: silver");
    ui->textBrowser_8->setStyleSheet("border: silver");
    ui->textBrowser_9->setStyleSheet("border: silver");
    ui->textBrowser_10->setStyleSheet("border: silver");
    ui->textBrowser_11->setStyleSheet("border: silver");
    ui->textBrowser_12->setStyleSheet("border: silver");
    ui->textBrowser_13->setStyleSheet("border: silver");
    ui->textBrowser_14->setStyleSheet("border: silver");
    ui->textBrowser_15->setStyleSheet("border: silver");
    ui->textBrowser_16->setStyleSheet("border: silver");
    ui->textBrowser_17->setStyleSheet("border: silver");
    ui->textBrowser_18->setStyleSheet("border: silver");
    ui->textBrowser_19->setStyleSheet("border: silver");
    ui->textBrowser_20->setStyleSheet("border: silver");
}



void MainWindow::on_pushButton_clicked()
{

}




void MainWindow::engNgramsGeneration(QStringList words, QStringList& threegrams, QStringList& bigrams, QStringList& unigrams)
{

    QString temp3Gram;
    QString temp2Gram;
    QString temp1Gram;
    QString space = " ";

    if (words.size() > 2) {
        for (int i = 0; i < words.size(); i++) {
            if (i < words.size() - 2) {
                temp3Gram = words[i] + space + words[i+1] + space + words[i+2] + space;
                threegrams.append(temp3Gram);
                temp3Gram.clear();
            }
                if (i < words.size() - 1) {
                    temp2Gram = words[i] + space + words[i+1] + space;
                    bigrams.append(temp2Gram);
                    temp2Gram.clear();
                }
                unigrams << words[i] + space;

        }
    } else if (words.size() == 2){
        temp2Gram = words[0] + space + words[1] + space;
        bigrams << temp2Gram;
        temp2Gram.clear();
        temp1Gram = words[0] + space;
        unigrams << temp1Gram;
        temp1Gram.clear();
        temp1Gram = words[1] + space;
        unigrams << temp1Gram;
        temp1Gram.clear();
    } else if (words.size() == 1) {
        temp1Gram = words[0] + space;
        unigrams << temp1Gram;
        temp1Gram.clear();
    }

}


QStringList MainWindow::splitIntoSentences(QString text)
{
    QRegExp sentenceCap("[^\\.\\?\\!]+[\\.\\?\\!]{0,1}");
    QRegExp StringCap("[^\\n]+");
    int pos1 = 0;
    int pos2 = 0;
    QString string;
    QStringList sentences;

    while ((pos1 = StringCap.indexIn(text,pos1)) != -1){     //убираем перенос строки
       string.append(StringCap.cap(0));                       //заменяем перенос строки на пробел
       string.append(" ");
       pos1 += StringCap.matchedLength();
    }
    string.chop(1);                                                  //убираем последний пробел
    while ((pos2 = sentenceCap.indexIn(string,pos2)) != -1){         //разбиение на предложения
       sentences << (sentenceCap.cap(0));
       pos2 += sentenceCap.matchedLength();
    }
    return sentences;
}

QStringList MainWindow::splitTntoWords(QString sentence)
{   
    QRegExp word("[\\w]+|\\w{1,}\\-{1}\\w{1,}");
    int pos = 0;
    QStringList words;

    while ((pos = word.indexIn(sentence,pos)) != -1){
       words << (word.cap(0));
       pos += word.matchedLength();
    }

    return words;
}

void MainWindow::addNgram(QStringList translationWords,  QMap<QString, int> &translationNgramCount, int n){
    int flag;
    QString translationNgram;
    while(translationWords.size() > n){
         for(int i = 0; i <= n; i++){
             translationNgram.append(translationWords[i]);
             translationNgram.append(" ");
         }

          translationNgram.chop(1);

          if (translationNgramCount.isEmpty()){
              translationNgramCount.insert(translationNgram,1);
          }else{
              QMap<QString, int>::iterator rusNgramIt = translationNgramCount.find(translationNgram);

              if (rusNgramIt != translationNgramCount.end()){
                  translationNgramCount[rusNgramIt.key()]++;
                  flag = 1;
              }

              if (flag != 1){
                  translationNgramCount.insert(translationNgram,1);
              }

          flag = 0;
          }

          translationNgram.clear();
          translationWords.removeFirst();
    }
}

void MainWindow::eraseLowFreqNgrams(QMap<QString, int> &translationNgramCount)
{
    QMap<QString, int>::iterator it = translationNgramCount.begin();
    while (it != translationNgramCount.end()) {

        if(it.value() < 20){
            it = translationNgramCount.erase(it);
        }else{
             ++it;
         }

    }

}

void MainWindow::rusNgramsGeneration(QStringList &translationlessNgrams, QMultiMap<QString, QString> sourseNgramsTranslationSentences, QMap<QString, QMap<QString, int>> &sourseNgramTranslationNgramCount,
                                                QMap<QString, QMap<QString, int>> &sourseNgramTranslationNgramCount2, int n)
{
  //  QRegExp characters("[^\\s\\n\\.\\?\\!\\,\\-]+");
    QRegExp word("[\\w]+|\\w{1,}\\-{1}\\w{1,}");

    int m = 0;
    int appearenceCount = 0;

   QList<QString>::iterator ListIt = translationlessNgrams.begin();
    while (ListIt != translationlessNgrams.end()) {
        QMap<QString, int> translationNgramCount;
        QMap<QString, int> translationNgramCount2;

        QMultiMap<QString, QString>::iterator it = sourseNgramsTranslationSentences.find(*ListIt);
        while (it != sourseNgramsTranslationSentences.end() && it.key() == *ListIt) {
            QStringList translationWords;
            appearenceCount++;
            int pos = 0;
            while ((pos = word.indexIn(it.value(),pos)) != -1){
                translationWords << word.cap(0).toLower();
                pos += word.matchedLength();
            }

            addNgram(translationWords, translationNgramCount, n-1);

            if((n-1) > 0){
               m = n-2;
            }else{
               m = n;
            }

            addNgram(translationWords, translationNgramCount2, m);

            it++;
         }

         translationDB->addToEngNgramsTable(*ListIt, appearenceCount);

         if (appearenceCount > 20){

            eraseLowFreqNgrams(translationNgramCount);
            eraseLowFreqNgrams(translationNgramCount2);

            sourseNgramTranslationNgramCount.insert(*ListIt,translationNgramCount);
            sourseNgramTranslationNgramCount2.insert(*ListIt,translationNgramCount2);

            ListIt++;

          }else{

            ListIt = translationlessNgrams.erase(ListIt++);

          }
          appearenceCount = 0;
    }

}


QStringList MainWindow::noTranslationNgramSearch(QStringList ngrams, QMap<QString, int> &ngramCountMap)
{
    QStringList noTranslationNgram;
    if (!ngrams.isEmpty()){

        for(int i = 0; i <= ngrams.size()-1; i++){

            if (i == 0){
                QString ngram_toLower = ngrams[i];
                QString::iterator itQString ;
                itQString = ngram_toLower.begin();
                *itQString =  (*itQString).toLower();
                ngrams[i] = ngram_toLower;
            }

            //если нграмма не найдена добавление в список нграм без перевода
            if(!(translationDB->engNgramSearch(ngrams[i]))){
                noTranslationNgram.append(ngrams[i]);
            }
        }
        for(int i = 0; i <= noTranslationNgram.size()-1; i++){
            // ngramCountMap - key - Нграмма, value - количество найденых совпадений в корпусе
            ngramCountMap.insert(noTranslationNgram[i], 0);
        }
    }

    return noTranslationNgram;

}

void MainWindow::translationSort(QMap<QString, QMap<QString, int>> sourseTransCount, QMultiMap<QString, QMap<QString, QVector<int>>>& sourseTranslationSorted)
{
    typedef Map::const_iterator Iter;
    QMap<QString, QVector <int>> translationCountTemp;
    QVector <int> tempNumbers;
    QVector<Iter> byVal;
    QMap<QString, int> mapTemp;


    QMap<QString, QMap<QString, int>>::const_iterator it = sourseTransCount.constBegin();
    while (it != sourseTransCount.constEnd()) {
        mapTemp = it.value();

        QMap<QString, int>::const_iterator tempIt = mapTemp.cbegin();
        while (tempIt != mapTemp.cend()) {
            byVal.append(tempIt);
            ++tempIt;
        }
        qSort(byVal.begin(), byVal.end(), [] (Iter i0, Iter i1) {
            return i0.value() > i1.value();
        });
        if(byVal.size() > 10){
            for(int i = 0; i <= 9; i++){

                tempNumbers << byVal[i].value() << 0  << 0;
                translationCountTemp.insert(byVal[i].key(), tempNumbers);
                tempNumbers.clear();
            }
        }else{
            for(int i = 0; i <= byVal.size()-1; i++){


                tempNumbers << byVal[i].value() << 0 << 0;
                translationCountTemp.insert(byVal[i].key(), tempNumbers);
                tempNumbers.clear();

            }
        }
        if (!translationCountTemp.isEmpty()){
            sourseTranslationSorted.insert(it.key(),translationCountTemp);
        }
        translationCountTemp.clear();
        byVal.clear();
        ++it;
   }
}

void MainWindow::backTranslation(QString corpora, QMultiMap<QString, QMap<QString, QVector<int>>> &sourseTranslationSorted)
{
    QMultiMap<QString, QMap<QString, QVector<int>>>::iterator engNgramIterator = sourseTranslationSorted.begin();
     while (engNgramIterator != sourseTranslationSorted.end()) {

         QMap<QString, QVector<int>>::iterator rusNgramIterator = engNgramIterator.value().begin();
          while (rusNgramIterator != engNgramIterator.value().end()) {

              QString rusNgramToUpper = rusNgramIterator.key();
              QString::iterator itQStringRus ;
              itQStringRus = rusNgramToUpper.begin();
              *itQStringRus =  (*itQStringRus).toUpper();

              QRegExp rusNgram(" " + rusNgramIterator.key() + " " + "|" + "" + rusNgramToUpper + " ");
              int pos = 0;

              while ((pos = rusNgram.indexIn(corpora,pos)) != -1){
                  rusNgramIterator.value()[1]++;
                  pos += rusNgram.matchedLength();
              }
              ++rusNgramIterator;
          }
          ++engNgramIterator;
     }
}

void MainWindow::writeToTranslationTable(QMultiMap<QString, QMap<QString, QVector<int>>> &sourseTranslationSorted)
{
    auto iteratorFlag = 0;
    QRegExp punctuation("[^\\w\\s\\-]|\\W{2,}");
    QRegExp word("\\w+");


    QMultiMap<QString, QMap<QString, QVector<int>>>::iterator engNgramIterator = sourseTranslationSorted.begin();
    while (engNgramIterator != sourseTranslationSorted.end()) {
        int engWordCount = 0;
        int pos = 0;
        while ((pos = word.indexIn(engNgramIterator.key(),pos)) != -1){
            engWordCount++;
            pos += word.matchedLength();
        }

        QMap<QString, QVector<int>>::iterator rusNgramIterator = engNgramIterator.value().begin();

        double coefSum(0.0);
        int countSum = 0;
        while (rusNgramIterator != engNgramIterator.value().end()) {
            auto pos = 0;

            /* Удаляем n-граммы содержащие знаки отличные от букв, пробелов и "-"
             * */
            if ((pos = punctuation.indexIn(rusNgramIterator.key(),pos)) != -1){
                iteratorFlag = 1;
            }

            /* Если есть хотя бы один обратный перевод, считаем коэффициент
             * */

            if (rusNgramIterator.value()[1] != 0 && iteratorFlag == 0){
                double coef = static_cast<double>(rusNgramIterator.value()[0]) / rusNgramIterator.value()[1];
                coefSum += coef;

                ++rusNgramIterator;
            }else{
                engNgramIterator.value().erase(rusNgramIterator++);
            }

            iteratorFlag = 0;
        }

        /* Считаем сердний коэффициент
         * Записываем в базу переводы с коэффициентом выше среднего
         * */

        if (engNgramIterator.value().size() != 0){
           auto averageCoef = coefSum/engNgramIterator.value().size();

           QMap<QString, QVector<int>>::iterator coefIterator = engNgramIterator.value().begin();

           while (coefIterator != engNgramIterator.value().end()) {


               double coef = static_cast<double>(coefIterator.value()[0]) / coefIterator.value()[1];

               int pos = 0;
               int rusWordCount = 0;
               while ((pos = word.indexIn(coefIterator.key(),pos)) != -1){
                   rusWordCount++;
                   pos += word.matchedLength();
               }

               if(engWordCount > rusWordCount){
                   coef /= 5;
               }

               if(engWordCount < rusWordCount){
                   coef /= 10;
               }

               if(coef > averageCoef){
                   countSum += coefIterator.value()[0];
                   translationDB->addToTranslationTable(engNgramIterator.key(),coefIterator.key(), coefIterator.value()[0], coef);
                   ++coefIterator;
               }else{
                   engNgramIterator.value().erase(coefIterator++);
               }

           }

        }

        ++engNgramIterator;
     }
}

void MainWindow::fillingStructure(QRegExp rusNgram, QStringList translationlessNgrams, QMultiMap<QString, QString> sourseNgramsTranslationSentences, sourse_translation_examples &setTemp)
{
    for(int i = 0; i <= translationlessNgrams.size()-1; i++){
        if(setTemp.engNgramm == translationlessNgrams[i]){
            int flag10 = 0;
            auto it = sourseNgramsTranslationSentences.find(setTemp.engNgramm);
            while (it != sourseNgramsTranslationSentences.end() && it.key() == setTemp.engNgramm && flag10 < 10){

                int pos = 0;
                if((pos = rusNgram.indexIn(it.value(),pos)) != -1){
                     setTemp.examples.insert(it.value(), "");
                     flag10++;
                }
                it++;
            }

        }
    }
}


void MainWindow::fillingExamplesStructures(QVector <sourse_translation_examples> &setVec,
                                            QStringList translationless3grams,
                                            QStringList translationless2grams,
                                            QStringList translationless1grams,
                                            QMultiMap<QString, QString> sourse3gramsTranslationSentences,
                                            QMultiMap<QString, QString> sourse2gramsTranslationSentences,
                                            QMultiMap<QString, QString> sourse1gramsTranslationSentences,
                                            QMultiMap<QString, QMap<QString, QVector<int>>> &sourseTranslationSorted)
{


    QMultiMap<QString, QMap<QString, QVector <int>>>::const_iterator engNgramIterator = sourseTranslationSorted.constBegin();
    while (engNgramIterator != sourseTranslationSorted.constEnd()) {

        QMap<QString,QVector <int>>::const_iterator rusNgramIterator = engNgramIterator.value().constBegin();
         while (rusNgramIterator != engNgramIterator.value().constEnd()) {

             sourse_translation_examples setTemp;
             setTemp.engNgramm = engNgramIterator.key();
             setTemp.rusNgramm = rusNgramIterator.key();
             setTemp.count = 0;

             QString rusNgramtoUpper = setTemp.rusNgramm;
             QString::iterator itQString ;
             itQString = rusNgramtoUpper.begin();
             *itQString =  (*itQString).toUpper();
             QRegExp rusNgram(" " + setTemp.rusNgramm + "|" + rusNgramtoUpper + "");

             fillingStructure(rusNgram, translationless3grams, sourse3gramsTranslationSentences, setTemp);
             fillingStructure(rusNgram, translationless2grams, sourse2gramsTranslationSentences, setTemp);
             fillingStructure(rusNgram, translationless1grams, sourse1gramsTranslationSentences, setTemp);


             if(!setTemp.examples.isEmpty()){
                 setVec.push_back(setTemp);
             }


           ++rusNgramIterator;
        }

        ++engNgramIterator;
    }
}


void MainWindow::translationSearchPart(QStringList translationlessNgrams, int n, QMap<QString, int>& ngramCount, QString corporaPart,
                                        QMultiMap<QString, QString>& eng3GramRusSentence, QMultiMap<QString, QString>& eng2GramRusSentence, QMultiMap<QString, QString>& eng1GramRusSentence)
{
    QRegExp translationSentence("<seg>([^\\n]+)</seg>");

    for(int i = 0; i <= translationlessNgrams.size()-1; i++){
        auto ngrCountIt = ngramCount.find(translationlessNgrams[i]);

        if (ngrCountIt.value() < 10000) {
            QString ngramToUpper = translationlessNgrams[i];
            QString::iterator itQString ;
            itQString = ngramToUpper.begin();
            *itQString =  (*itQString).toUpper();

            QRegExp sourseSentence(" " + translationlessNgrams[i] + "|" + ngramToUpper + "");
            int pos = 0;

            while ((pos = sourseSentence.indexIn(corporaPart,pos)) != -1){
                pos += sourseSentence.matchedLength();

                if ((pos = translationSentence.indexIn(corporaPart,pos)) != -1){
                    QString sentenceTemp = translationSentence.cap(1);
                    pos += translationSentence.matchedLength();

                    if(n == 3){
                        eng3GramRusSentence.insert(translationlessNgrams[i],sentenceTemp);
                    }else if(n == 2){
                        eng2GramRusSentence.insert(translationlessNgrams[i],sentenceTemp);
                    }else if(n == 1){
                        eng1GramRusSentence.insert(translationlessNgrams[i],sentenceTemp);
                    }

                    ngrCountIt.value()++;
                }

            }

        }

    }

}


void MainWindow::translationSearch(QStringList translationless3Grams,
                                   QStringList translationless2Grams,
                                   QStringList translationless1Grams,
                                   QMap<QString, int>& ngramCountMap,
                                   QMultiMap<QString, QString>& eng3GramRusSentence,
                                   QMultiMap<QString, QString>& eng2GramRusSentence,
                                   QMultiMap<QString, QString>& eng1GramRusSentence)
{


    QFile* corporaFile = new QFile("");    // Пропишите путь до файла corp1.txt здесь

    corporaFile->open(QIODevice::ReadOnly | QIODevice::Text);
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    textStream.setDevice(corporaFile);
    textStream.setCodec(codec);

           while (!corporaFile->atEnd()){
             QString corporaPart = textStream.read(10000000);
             translationSearchPart(translationless3Grams, 3, ngramCountMap, corporaPart, eng3GramRusSentence, eng2GramRusSentence, eng1GramRusSentence);
             translationSearchPart(translationless2Grams, 2, ngramCountMap, corporaPart, eng3GramRusSentence, eng2GramRusSentence, eng1GramRusSentence);
             translationSearchPart(translationless1Grams, 1, ngramCountMap, corporaPart, eng3GramRusSentence, eng2GramRusSentence, eng1GramRusSentence);
           }

    textStream.flush();
    textStream.seek(0);

    corporaFile->close();
}


void MainWindow::backTranslationSearch(QMultiMap<QString, QMap<QString, QVector<int>>> &sourseTranslationSorted)
{


    QFile* corporaFile = new QFile("");           // Пропишите путь до файла corp2.txt здесь
    corporaFile->open(QIODevice::ReadOnly | QIODevice::Text);
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    textStream.setDevice(corporaFile);
    textStream.setCodec(codec);

    while (!corporaFile->atEnd()){
      QString corporaPart = textStream.read(10000000);
      backTranslation(corporaPart, sourseTranslationSorted);
}

    textStream.flush();
    textStream.seek(0);

    corporaFile->close();
}


void MainWindow::examplesSearch(QVector <sourse_translation_examples>& setVec)
{
    QFile* corporaFile = new QFile("");                      // Пропишите путь до файла corp2.txt здесь
    corporaFile->open(QIODevice::ReadOnly | QIODevice::Text);
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    textStream.setDevice(corporaFile);
    textStream.setCodec(codec);

    while (!corporaFile->atEnd()){
        QString corporaPart = textStream.read(10000000);

        for (int i = 0; i < setVec.size(); i++){

            examplesSearchPart(setVec[i], corporaPart);
        }

    }

    textStream.flush();
    textStream.seek(0);

    corporaFile->close();
}


void MainWindow::examplesSearchPart(sourse_translation_examples& set, QString corporaPart)
{
     QRegExp engSentCap("<seg>([^\\n]+)</seg>");
     QString engNgrammChopped = set.engNgramm;
     engNgrammChopped.chop(1);

     QString engNgramToUpper = engNgrammChopped;
     QString::iterator itQString ;
     itQString = engNgramToUpper.begin();
     *itQString =  (*itQString).toUpper();

     QRegExp engNgram(engNgrammChopped + "|" + engNgramToUpper);
     auto examplesIt = set.examples.begin();
     while (examplesIt != set.examples.end()) {

        if(!examplesIt.key().isEmpty() && examplesIt.value().isEmpty()){
        QRegExp rusSentence(QRegExp::escape(examplesIt.key()));

        int pos = 0;
        if ((pos = rusSentence.indexIn(corporaPart,pos)) != -1){
            pos -= 120;

            if ((pos = engSentCap.indexIn(corporaPart,pos)) != -1){
                auto tempEngSent = engSentCap.cap(1);
                pos += engSentCap.matchedLength();
                int posInSent = 0;

                if ((posInSent = engNgram.indexIn(tempEngSent,posInSent)) != -1){
                    examplesIt.value() = tempEngSent;
                    translationDB->addToExamplesTable(set.engNgramm, set.rusNgramm, tempEngSent, examplesIt.key());

                }else if((pos = engSentCap.indexIn(corporaPart,pos)) != -1){
                    auto tempEngSent = engSentCap.cap(1);
                    pos += engSentCap.matchedLength();
                    posInSent = 0;

                    if ((posInSent = engNgram.indexIn(tempEngSent,posInSent)) != -1){
                        examplesIt.value() = tempEngSent;
                        translationDB->addToExamplesTable(set.engNgramm, set.rusNgramm, tempEngSent, examplesIt.key());
                    }else if((pos = engSentCap.indexIn(corporaPart,pos)) != -1){
                        auto tempEngSent = engSentCap.cap(1);
                        pos += engSentCap.matchedLength();
                        posInSent = 0;

                        if ((posInSent = engNgram.indexIn(tempEngSent,posInSent)) != -1){
                            examplesIt.value() = tempEngSent;
                            translationDB->addToExamplesTable(set.engNgramm, set.rusNgramm, tempEngSent, examplesIt.key());

                        }
                     }
                 }
             }
         }
     }
     examplesIt++;
  }

}


void MainWindow::learn(QString text)
{
    messageBox.setText("Поиск переводов");
    messageBox.exec();

     // Pазделение текста на предложения
     QStringList sentences = splitIntoSentences(text);

     //Цикл для перебора всех предложений текста
     QRegExp anyCharacter("[^\\s]");
     for(int i = 0; i <= sentences.size()-1; i++){
        int pos = 0;
        //Проверка, не является ли искомое предложение пустой сторой
        if ((pos = anyCharacter.indexIn(sentences[i],pos)) != -1){

            //Разделение предложения на слова
            QStringList words = splitTntoWords(sentences[i]);

            if (!words.isEmpty()){
                QStringList threegrams;
                QStringList bigrams;
                QStringList unigrams;

                //Формирование n-грам из слов
                engNgramsGeneration(words, threegrams, bigrams, unigrams);

                // ngramCountMap - key - Нграмма, value - количество найденых совпадений в корпусе
                QMap<QString, int> ngramCountMap;

                //Поиск n-грам, для которых в базе отсутствует перевод
                QStringList translationless3Grams = noTranslationNgramSearch(threegrams, ngramCountMap);
                QStringList translationless2Grams = noTranslationNgramSearch(bigrams, ngramCountMap);
                QStringList translationless1Grams = noTranslationNgramSearch(unigrams, ngramCountMap);

                if (!translationless3Grams.isEmpty() || !translationless2Grams.isEmpty() || !translationless1Grams.isEmpty()){

                    QMultiMap<QString, QString> eng3GramRusSentence;
                    QMultiMap<QString, QString> eng2GramRusSentence;
                    QMultiMap<QString, QString> eng1GramRusSentence;

                    //Поиск переводов n-грам в параллельном корпусе
                    translationSearch(translationless3Grams, translationless2Grams, translationless1Grams,
                                      ngramCountMap, eng3GramRusSentence, eng2GramRusSentence, eng1GramRusSentence);

                    // sourseTransCount1 - содержит переводы 1gram->1gram, 2gram->2gram, 3gram->3gram
                    // sourseTransCount2 - содержит переводы 1gram->2gram, 2gram->1gram, 3gram->2gram
                    QMap<QString, QMap<QString, int>> sourseTransCount1;
                    QMap<QString, QMap<QString, int>> sourseTransCount2;

                    //Создание пар: исходная n-грамма + n-грамма перевода
                    rusNgramsGeneration(translationless3Grams, eng3GramRusSentence, sourseTransCount1, sourseTransCount2, 3);
                    rusNgramsGeneration(translationless2Grams, eng2GramRusSentence, sourseTransCount1, sourseTransCount2, 2);
                    rusNgramsGeneration(translationless1Grams, eng1GramRusSentence, sourseTransCount1, sourseTransCount2, 1);

                    //sourseTranslationSorted - содержит: исходная n-грамма, n-грамма перевода, вектор: [0] кол-во перевдов, [1] кол-во появлений перевода в корпусе.
                    QMultiMap<QString, QMap<QString, QVector<int>>> sourseTranslationSorted;

                    //Сортировка переводов по частоте появления в корпусе
                    translationSort(sourseTransCount1,sourseTranslationSorted);
                    translationSort(sourseTransCount2,sourseTranslationSorted);

                    // Поиск русских n-грамм в корпусе
                    backTranslationSearch(sourseTranslationSorted);

                    writeToTranslationTable(sourseTranslationSorted);

                    QVector <sourse_translation_examples> setVec;

                    fillingExamplesStructures(setVec, translationless3Grams, translationless2Grams, translationless1Grams, eng3GramRusSentence, eng2GramRusSentence, eng1GramRusSentence, sourseTranslationSorted);

                    examplesSearch(setVec);

                }

            }

        }

    }
     messageBox.setText("Поиск завершен");
     messageBox.exec();

}



void MainWindow::on_actionOpen_3_triggered()
{
    QString textForTranslation;

    QFile *file = new QFile("://resource/learnFile.txt");
    file->open(QIODevice::ReadOnly);
    textForTranslation = file->readAll();

     learn(textForTranslation);

}


void MainWindow::clearWidgets()
{

    while (QLayoutItem* item = layout->takeAt(0)) {
        delete item->widget();
        delete item;
    }
    ui->textBrowser->clear();
    ui->textBrowser_2->clear();
    ui->textBrowser_3->clear();
    ui->textBrowser_4->clear();
    ui->textBrowser_5->clear();
    ui->textBrowser_6->clear();
    ui->textBrowser_7->clear();
    ui->textBrowser_8->clear();
    ui->textBrowser_9->clear();
    ui->textBrowser_10->clear();
    ui->textBrowser_11->clear();
    ui->textBrowser_12->clear();
    ui->textBrowser_13->clear();
    ui->textBrowser_14->clear();
    ui->textBrowser_15->clear();
    ui->textBrowser_16->clear();
    ui->textBrowser_17->clear();
    ui->textBrowser_18->clear();
    ui->textBrowser_19->clear();
    ui->textBrowser_20->clear();
}


void MainWindow::on_translateButton_clicked()
{
    clearWidgets();

    QString textForTranslation;
    QStringList rusNgrams;

    textForTranslation = ui->textEdit->toPlainText();

    while(textForTranslation.at(textForTranslation.size() - 1) == " " || textForTranslation.at(textForTranslation.size() - 1) == "\n"){
        textForTranslation.chop(1);
    }

    ui->textEdit->setText(textForTranslation);

    if (translationDB->engNgramSearch(textForTranslation + " ")) {
       rusNgrams = translationDB->rusNgramCapture(textForTranslation);
       int col = 0;
       int row = 0;

       for (int i = 0; i < rusNgrams.size(); i++) {
          DynamicButton *button;
          button = new DynamicButton(this);                                        // Создаем кнопку с переводом
          button->setText(rusNgrams[i]);
          button->setStoredText(rusNgrams[i]);
          button->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed, QSizePolicy::PushButton));

          connect(button, SIGNAL(clicked()), this, SLOT(slotGetExaples()));
          layout->addWidget(button, row, col);                                    //Добавляем кнопку на layout row - ряд, col - колонка

          if (col < 6){                                                           // Когда ряд из шести колонок(col) заполнен, переходем на следующий ряд(row)
            col++;
          }else{
            col = 0;
            row++;
          }
      }

    }else{
        messageBox.setText("Нет переводов для " + textForTranslation + "   =(");
        messageBox.exec();
    }
}



void MainWindow::slotGetExaples()
{
    /* Определяем объект, который вызвал сигнал
     * */
    DynamicButton *button = (DynamicButton*) sender();

    QString engTextForTranslation = ui->textEdit->toPlainText();
    QString translation = button->getText();

   // ПОИСК ПРИМЕРОВ В БД

    QMap<QString, QString> examples = translationDB->examplesCapture(engTextForTranslation, translation);

    for (int j = 0; j < 20; j = j+2) {                                                     // Очищаем QTextBrowser'ы
        QWidget *widget = ui->gridLayout->itemAtPosition(j, 0)->widget();                  //Создаем указатель на Widget находящийся в i-ом раду в 0-ой колонке gridLayout
        QTextBrowser *browser = qobject_cast<QTextBrowser *>( widget );                    //Приводим тип QWidget к типу QTextBrowser
        browser->setText(" ");

        QWidget *widget2 = ui->gridLayout->itemAtPosition(j, 1)->widget();
        QTextBrowser *browser2 = qobject_cast<QTextBrowser *>( widget2 );
        browser2->setText(" ");

    }

    int i = 0;

    QMap<QString, QString>::const_iterator iterator = examples.constBegin();
    while (iterator != examples.constEnd()) {                                               // Заполныем QTextBrowser'ы примерами

        QWidget *widget = ui->gridLayout->itemAtPosition(i, 0)->widget();                  //Создаем указатель на Widget находящийся в i-ом раду в 0-ой колонке gridLayout
        QTextBrowser *browser = qobject_cast<QTextBrowser *>( widget );                    //Приводим тип QWidget к типу QTextBrowser
        browser->setText(iterator.key());

        QWidget *widget2 = ui->gridLayout->itemAtPosition(i, 1)->widget();
        QTextBrowser *browser2 = qobject_cast<QTextBrowser *>( widget2 );
        browser2->setText(iterator.value());

        i = i+2;
        ++iterator;

     }

}



void MainWindow::on_textEdit_textChanged()
{
    QString text_examination;
    text_examination = ui->textEdit->toPlainText();

    if (text_examination.size() > 100){

        ui->textEdit->clear();

    }


}
