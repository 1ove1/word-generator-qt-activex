#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <QPushButton>
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include "ui_MainWindow.h"
#include "XMLParser/XMLParser.h"
#include "BookObserver/BookObserver.h"
#include "WordBuilder/WordBuilder.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void updateTree();
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    BookObserver *observer;
    QString pathToXml;

    QTreeWidgetItem* addRoot(QString name, QString data);
    void addChiled(QString name, QString isbn, QString count);
    void openOrCreateXml();
};
#endif // MAINWINDOW_H
