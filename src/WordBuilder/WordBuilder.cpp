#include "WordBuilder.h"

WordBuilder::WordBuilder()
{
    this->pword = new QAxObject("Word.Application");

    this->pdoc = pword->querySubObject("Documents")->querySubObject("Add()");

    this->prange = this->pdoc->querySubObject("Range()");

    this->pfont = prange->querySubObject("Font");
    this->pfont->setProperty("Name", "Times New Roman");
    this->pfont->setProperty("Size", "14");

    this->ptable = pdoc->querySubObject("Tables");
}

WordBuilder::~WordBuilder()
{
    delete pword;
}

WordBuilder* WordBuilder::createColontitul()
{
    // alignment -> right
    this->switchAlignment("right");

    // texting
    this->appendText("Начальнику службы РАВ");

    return this;
}

WordBuilder* WordBuilder::createHeader()
{
    // append new lines
    this->insertParagraphs(1);

    // alignment
    this->switchAlignment("center");

    // texting
    this->appendText("ЗАЯВКА");

    // append new lines
    this->insertParagraphs(1);

    // alignment
    this->switchAlignment("left");

    // texting
    this->appendText("          Прошу в целях поддержки техники отделения зенитного ракетного вооружения БУК М1-2 в боеготовом состоянии и обеспечения своевременного ремонта узлов и блоков пополнить ЗИП на изделие 9А319М1.");

    return this;
}

WordBuilder* WordBuilder::createTable(QVector<Spare> spares, quint16 length)
{
    quint16 counter = 1;
    this->insertParagraphs(1);
    this->refreshRange();

    this->ptable = this->ptable->querySubObject("Add(Range, NumRows, NumColumns, DefaultTableBehavior, AutoFitBehavior)",
                                                        this->prange->asVariant(), length, TABLE_COUNT_COLUMNS, 1, 2);
    this->activeParagraph += (length * (TABLE_COUNT_COLUMNS + 1));


    this->insertDataInTable("№ п/п", "Параметры, входящие в комплект", "Единицы измерения", "Положено держать", "Примечание");
    for(Spare &elem: spares) {
        if (elem.getCount().toInt() > 0) {
            this->insertDataInTable(QString::number(counter++), elem.getName(), "шт", elem.getCount(), "");
        }

    }


    return this;
}

WordBuilder* WordBuilder::createFooter()
{
    this->refreshRange();

    this->insertParagraphs(1);


    this->switchAlignment("center");

    this->appendText("__________________________________________________");

    this->insertParagraphs(2);

    this->switchAlignment("left");

    this->appendText("Начальник расчёта_________________________________");

    return this;
}

void WordBuilder::switchAlignment(QString direction)
{
    QStringList directionList;
    directionList << "left" << "center" << "right";

    this->pword->querySubObject("ActiveDocument")
            ->querySubObject("Paragraphs(int)", this->activeParagraph)
            ->querySubObject("Format")
            ->setProperty("Alignment", directionList.indexOf(direction));
}

void WordBuilder::insertParagraphs(quint16 counts)
{
    for(; counts > 0; counts--) {
        this->prange->dynamicCall("InsertParagraphAfter()");
        this->activeParagraph++;
    }
}

void WordBuilder::refreshRange()
{
    this->prange->dynamicCall("SetRange(int, int)", this->startRange, this->stopRange);

    this->startRange = this->stopRange;
    this->stopRange += STEP_RANGE;
}

void WordBuilder::appendText(QString text)
{
    this->refreshRange();
    this->prange->dynamicCall("Text", text.toStdString().c_str());
}

void WordBuilder::insertDataInTable(QString order, QString itemName, QString units, QString count, QString note)
{
    QStringList dataList;
    dataList << order << itemName << units << count << note;

    quint16 coll = 1;

    for (; coll <= 5; coll++) {
        this->ptable->querySubObject("Cell(int, int)", this->currentRow, coll)
                ->querySubObject("Range")
                ->setProperty("Text", dataList.at(coll - 1).toStdString().c_str());
    }
    this->currentRow++;
}

void WordBuilder::saveDocument()
{
    this->pword->dynamicCall("SetVisible", true);
    this->~WordBuilder();
}
