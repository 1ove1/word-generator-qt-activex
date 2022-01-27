#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->openOrCreateXml();

    this->observer = XMLParser::readXML(this->pathToXml);

    this->updateTree();
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(updateTree()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addChiled(QString name, QString isbn, QString count)
{
    QTreeWidgetItem *itm = new QTreeWidgetItem();
    itm->setFlags(itm->flags() | Qt::ItemIsEditable);
    itm->setText(0, name);
    itm->setText(1, isbn);
    itm->setText(2, count);
    this->ui->treeWidget->addTopLevelItem(itm);
}

void MainWindow::updateTree()
{
    this->ui->treeWidget->clear();

    for(Book &elem: this->observer->getAllBooks()) {
        this->addChiled(elem.getName(), elem.getISBN(), elem.getCount());
    }
}

void MainWindow::on_pushButton_clicked()
{
    this->observer->subscribe(new Book(ui->lineEdit->text(),
                         ui->lineEdit_2->text(),
                         ui->spinBox->text()));
//    XMLParser::writeXML(this->pathToXml, itm);
}

void MainWindow::openOrCreateXml()
{
    this->pathToXml = QFileDialog::getOpenFileName(this,
                                                   tr("Open xml"), ".",
                                                   tr("Xml files (*.xml)"));
    if(this->pathToXml == ""){
        this->pathToXml = QFileDialog::getSaveFileName(this,
                                                       tr("Save xml"), ".",
                                                       tr("Xml files (*.xml)"));
    }

    if(this->pathToXml == ""){
        QMessageBox::warning(this,
                             "Ошибка файла",
                             "Не удалось открыть файл",
                             QMessageBox::Ok);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    WordBuilder *bld = new WordBuilder();

    bld->createColontitul()
            ->createHeader()
            ->createTable(this->observer->getAllBooks(), this->observer->getLength())
            ->createFooter()
            ->saveDocument();
}

