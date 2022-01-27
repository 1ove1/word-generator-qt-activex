#include "Book.h"


Book::Book(QString name, QString isbn, QString count)
{
    this->name = name;
    this->isbn = isbn;
    this->count = count;
}

QString Book::getName()
{
    return this->name;
}

QString Book::getISBN()
{
    return this->isbn;
}

QString Book::getCount()
{
    return this->count;
}
