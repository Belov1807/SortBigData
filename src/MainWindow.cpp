#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFile>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QMultiMap<int, QPair<long int, QString> > dataDictionary;
    long int counter = 0;

    QFile dataFile("data/data.txt");
    dataFile.open(QFile::ReadOnly);
    QString line = dataFile.readLine();

    while (!line.isEmpty())
    {
        line.remove('\n');
        dataDictionary.insert(line.count(), qMakePair(counter, line));
        line = dataFile.readLine();
        counter ++;
    }

    dataFile.close();

    QFile dataFile2("data/data2.txt");
    dataFile2.open(QFile::WriteOnly);

    auto iterator = dataDictionary.begin();

    for (int i = 0; i < dataDictionary.size(); i ++)
    {
        dataFile2.write(iterator.value().second.toUtf8() + '\n');
        dataFile2.flush();

        iterator ++;
    }
    dataFile2.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}
