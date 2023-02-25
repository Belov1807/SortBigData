#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFile>
#include <QDebug>
#include <QDateTime>
#include <QFileInfo>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createSourceDataFile();

    /*QMultiMap<int, QPair<long int, QString> > dataDictionary;
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
    dataFile2.close();*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createSourceDataFile()
{
    qint64 timeStart = QDateTime::currentMSecsSinceEpoch();

    QFile dataFile("../data/data.txt");
    dataFile.open(QFile::WriteOnly);

    qsrand(QDateTime::currentMSecsSinceEpoch());
    int randomeLineSize = (qrand() % ((40 + 1) - 1) + 1);

    int fileSizeInMb = 0;

    while (fileSizeInMb < 1000)
    {
        QFileInfo fileInfo(dataFile);
           fileSizeInMb = fileInfo.size() / 1000000;
           QString *randomLine = new QString();

        for (int i = 0; i < randomeLineSize; i ++)
        {
            char symbol = (qrand() % ((122 + 1) - 65) + 65);

            randomLine->append(symbol);

        }
        dataFile.write(randomLine->toUtf8() + '\n');
        dataFile.flush();
        delete randomLine;
        randomeLineSize = (qrand() % ((40 + 1) - 1) + 1);
    }


    dataFile.close();

    qint64 timeFinish = QDateTime::currentMSecsSinceEpoch();

    qint64 leadTime = timeFinish - timeStart;

    QTime time(0, 0);
    time = time.addMSecs(leadTime);

    qDebug() << "Время выполнения = " << time.toString("mm") << " минут, "<< time.toString("ss") << " секунд, ";
}
