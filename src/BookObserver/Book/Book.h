#ifndef BOOK_H
#define BOOK_H

#include <QString>

class Book
{
public:
    Book(QString name="<book_name>", QString isbn="<isbn_number>", QString count="<book_count>");
    QString getName();
    QString getISBN();
    QString getCount();
private:
    QString name;
    QString isbn;
    QString count;
};

#endif // BOOK_H
