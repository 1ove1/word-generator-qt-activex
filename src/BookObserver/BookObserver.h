#ifndef BOOKOBSERVER_H
#define BOOKOBSERVER_H

#include <QVector>
#include "Book/Book.h"

class BookObserver
{
public:
    BookObserver();
    ~BookObserver();
    void subscribe(Book *obj);
    QVector<Book> getAllBooks();
    quint16 getLength();
private:
    QVector<Book> *subscribers;
};

#endif // BOOKOBSERVER_H
