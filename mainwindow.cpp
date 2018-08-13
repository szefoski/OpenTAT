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

    QFile inputFile("/home/daniel/Downloads/logs.txt");
    QFileDevice::FileError err = QFileDevice::NoError;
    const bool exists = inputFile.exists();
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QList<QStandardItem *> items;
            items.append(new QStandardItem(line));
            model->appendRow(items);
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
        auto text = model->item(i)->text();
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
