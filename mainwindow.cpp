#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QStandardItemModel>
#include <QTableView>
#include <QTextStream>

#include <algorithm>


QStandardItemModel* model = nullptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto ui_tableView = findChild<QTableView*>("tableView_2");

    model = new QStandardItemModel(this);
    ui_tableView->verticalHeader()->hide();
    ui_tableView->horizontalHeader()->hide();

    QFile inputFile("/home/daniel/Downloads/logs.txt");
    QFileDevice::FileError err = QFileDevice::NoError;
    const bool exists = inputFile.exists();
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        int lineNo = 1;
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QList<QStandardItem *> items;
            items.append(new QStandardItem(QString::number(lineNo)));
            items.append(new QStandardItem(line));
            model->appendRow(items);
            ++lineNo;
        }
        inputFile.close();
    }
    auto errMsg = inputFile.errorString();
    auto err0 = inputFile.error();

    ui_tableView->setModel(model);

    auto ui_button = findChild<QPushButton*>("pushButton");
    connect(ui_button, SIGNAL(clicked()), this, SLOT(showFiltered()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showFiltered()
{
    auto ui_tableView = findChild<QTableView*>("tableView_2");
    auto ui_plainTextEdit = findChild<QPlainTextEdit*>("plainTextEdit");

    auto search = ui_plainTextEdit->toPlainText();
    for (int i = 0; i < model->rowCount(); ++i)
    {
        auto text = model->item(i, 1)->text();
        if (search.isEmpty())
        {
            ui_tableView->setRowHidden(i, false);
            continue;
        }

        if (text.contains(search))
        {
            ui_tableView->setRowHidden(i, false);
        }
        else
        {
            ui_tableView->setRowHidden(i, true);
        }
    }

}
