#ifndef WORDBUILDER_H
#define WORDBUILDER_H

#define STEP_RANGE 500
#define TABLE_COUNT_COLUMNS 5

#include <QString>
#include <QAxObject>
#include "../Database/Database.h"


class WordBuilder {

public:
    WordBuilder();
    WordBuilder* createColontitul();
    WordBuilder* createHeader();
    WordBuilder* createTable(QVector<Spare> spares, quint16 length);
    WordBuilder* createFooter();
    void saveDocument();
    ~WordBuilder();

private:
    QAxObject* pword;
    QAxObject* pdoc;
    QAxObject* prange;
    QAxObject* pfont;
    QAxObject* ptable;
    quint16 startRange = 0;
    quint16 stopRange = STEP_RANGE;
    quint16 activeParagraph = 1;
    quint16 currentRow = 1;

    void switchAlignment(QString direction);
    void insertParagraphs(quint16 counts);
    void refreshRange();
    void appendText(QString text);
    void insertDataInTable(QString order, QString itemName, QString units, QString count, QString note);
};

#endif // WORDBUILDER_H
