#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QTableView>
#include <QTextStream>

#include <algorithm>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto ui_tableView = findChild<QTableView*>("tableView_2");

    m_modelLogs = new QStandardItemModel(this);
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
            m_modelLogs->appendRow(items);
            ++lineNo;
        }
        inputFile.close();
    }
    auto errMsg = inputFile.errorString();
    auto err0 = inputFile.error();

    ui_tableView->setModel(m_modelLogs);

    auto ui_button = findChild<QPushButton*>("pushButton");
    connect(ui_button, SIGNAL(clicked()), this, SLOT(showFiltered()));

    setupFiltersTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showFiltered()
{
    auto ui_tableView = findChild<QTableView*>("tableView_2");

    for (int i = 0; i < m_modelLogs->rowCount(); ++i)
    {
        ui_tableView->setRowHidden(i, true);
    }

    for (int i = 0; i < m_modelLogs->rowCount(); ++i)
    {
        for (int j = 0; j < 2; j++)
        {
            auto search = m_modelFilters->item(j)->text();
            auto text = m_modelLogs->item(i, 1)->text();

            if (text.contains(search))
            {
                ui_tableView->setRowHidden(i, false);
                auto item = m_modelLogs->item(i, 1);
                if (j == 0)
                {
                    item->setBackground(QBrush(Qt::red));
                    item->setForeground(QBrush(Qt::yellow));
                }
                else
                {
                    item->setBackground(QBrush(Qt::gray));
                }
            }
        }
    }
}

void MainWindow::setupFiltersTable()
{
    m_modelFilters = new QStandardItemModel(this);
    QList<QStandardItem *> items;
    items.append(new QStandardItem("test"));
    QList<QStandardItem *> items2;
    items2.append(new QStandardItem("test2"));
    m_modelFilters->appendRow(items);
    m_modelFilters->appendRow(items2);

    auto tableView = findChild<QTableView*>("tableView");
    tableView->setModel(m_modelFilters);
}
