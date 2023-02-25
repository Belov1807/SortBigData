#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFile>
#include <QDebug>
#include <QDateTime>
#include <QFileInfo>
#include <QThread>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QThread* thread = QThread::create(std::bind(&MainWindow::createSourceDataFile, this));
    thread->start();

    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));


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
    qint64 timeStart = QDateTime::currentSecsSinceEpoch();

    QFile dataFile("../data/data.txt");
    dataFile.open(QFile::WriteOnly);

    qsrand(QDateTime::currentMSecsSinceEpoch());
    int randomeLineSize = (qrand() % ((40 + 1) - 1) + 1);

    int finishFileSizeInMb = 1000;
    int currentFileSizeInMb = 0;
    int oldCurrentFileSizeInMb = 0;
    int percent = 0;
    int oldPercent = 0;

    qint64 currentTime = QDateTime::currentSecsSinceEpoch();
    qint64 oldCurrentTime = 0;

    while (currentFileSizeInMb < finishFileSizeInMb)
    {
        QFileInfo fileInfo(dataFile);

        oldCurrentFileSizeInMb = currentFileSizeInMb;
        currentFileSizeInMb = fileInfo.size() / 1000000;
        if (oldCurrentFileSizeInMb != currentFileSizeInMb)
            ui->label_7->setText(QString("%0 Мб из %1 Мб").arg(currentFileSizeInMb).arg(finishFileSizeInMb));

        oldPercent = percent;
        percent = (currentFileSizeInMb * 100) / finishFileSizeInMb;
        if (oldPercent != percent)
            ui->progressBar->setValue(percent);

        oldCurrentTime = currentTime;
        currentTime = QDateTime::currentSecsSinceEpoch();

        if (oldCurrentTime != currentTime)
        {

            int leadTime = currentTime - timeStart;
            double middleSpeed = (double)currentFileSizeInMb / (double)leadTime;

            int lost = (finishFileSizeInMb -  currentFileSizeInMb) / middleSpeed;
            QTime lostTime(0, 0);
            lostTime = lostTime.addSecs(lost);
            ui->label_5->setText(QString("%0 минут, %1 секунд").arg(lostTime.toString("mm")).arg(lostTime.toString("ss")));

            ui->label_9->setText(QString("%0 мб/сек").arg(middleSpeed));
            QTime time(0, 0);
            time = time.addSecs(leadTime);
            ui->label_3->setText(QString("%0 минут, %1 секунд").arg(time.toString("mm")).arg(time.toString("ss")));

        }
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
}
