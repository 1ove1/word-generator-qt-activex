#include "XMLParser.h"

XMLParser::XMLParser()
{

}

BookObserver* XMLParser::readXML(QString pathToXml)
{
    QFile *file = new QFile(pathToXml);
    BookObserver *observer = new BookObserver();;

    if (!file->open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(NULL,
                             "Ошибка откртия файла (чтение)",
                             "Не удалось открыть файл",
                             QMessageBox::Ok);

    }

    QXmlStreamReader xmlFile(file);

    while(!xmlFile.hasError() && !xmlFile.atEnd()) {
        xmlFile.readNext();


        if (xmlFile.isStartElement()) {
            if (xmlFile.name() == "book") {
                QXmlStreamAttributes attr = xmlFile.attributes();
                observer->subscribe(new Book(attr[0].value().toString(),
                                    attr[1].value().toString(),
                                    attr[2].value().toString()
                        ));
            }
        }
    }

    file->close();
    return observer;
}

/*oid XMLParser::writeXML(QString pathToXml, Book itm)
{
    QFile file(pathToXml);

    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(NULL,
                             "Ошибка откртия файла (запись)",
                             "Не удалось открыть файл",
                             QMessageBox::Ok);
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);  // Устанавливаем автоформатирование текста
    xmlWriter.writeStartElement("book");   // Записываем первый элемент с его именем
    xmlWriter.writeAttribute("name", itm.getName());
    xmlWriter.writeAttribute("isbn", itm.getISBN());
    xmlWriter.writeAttribute("count", itm.getCount());
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();
}*/
