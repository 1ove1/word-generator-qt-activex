#include "BookObserver.h"

BookObserver::BookObserver()
{
    this->subscribers = new QVector<Book>();
}

BookObserver::~BookObserver()
{
    delete this->subscribers;
}

void BookObserver::subscribe(Book *obj)
{
    this->subscribers->append(*obj);
}

QVector<Book> BookObserver::getAllBooks()
{
    QVector<Book> copy;
    for(Book &elem: *(this->subscribers)) {
        copy.append(elem);
    }
    return copy;
}

quint16 BookObserver::getLength()
{
    return this->subscribers->length();
}
