#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QXmlStreamWriter>
#include <QXmlStreamAttribute>
#include <QString>
#include <QMessageBox>
#include "../BookObserver/BookObserver.h"

class XMLParser
{
public:
    XMLParser();
    static BookObserver* readXML(QString pathToXml);
//    static void writeXML(QString pathToXml, Book itm);
};

#endif // XMLPARSER_H
