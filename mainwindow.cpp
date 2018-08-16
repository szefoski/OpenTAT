#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>
#include <QtDebug>
#include <QFile>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QTableView>
#include <QTextStream>

#include <algorithm>

const int FilterTableColumnBg = 1;
const int FilterTableColumnFg = 2;

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
            auto lineNoItem = new QStandardItem(QString::number(lineNo));
            lineNoItem->setTextAlignment(Qt::AlignmentFlag::AlignRight);
            items.append(lineNoItem);
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

    ui_tableView->resizeColumnToContents(0);

    setupFiltersTable();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showFiltered()
{
    auto ui_tableView = findChild<QTableView*>("tableView_2");
    auto ui_tableFilters = findChild<QTableView*>("tableView");

    const QColor hlClr = Qt::red; // highlight color to set
    const QColor txtClr = Qt::white; // highlighted text color to set

    QPalette p = palette();
    p.setColor(QPalette::Highlight, hlClr);
    p.setColor(QPalette::HighlightedText, txtClr);
    ui_tableFilters->setPalette(p);

    for (int i = 0; i < m_modelLogs->rowCount(); ++i)
    {
        ui_tableView->setRowHidden(i, true);
    }

    for (int i = 0; i < m_modelLogs->rowCount(); ++i)
    {
        for (int j = 0; j < m_modelFilters->rowCount(); j++)
        {
            auto search = m_modelFilters->item(j)->text();
            auto text = m_modelLogs->item(i, 1)->text();

            if (text.contains(search))
            {
                ui_tableView->setRowHidden(i, false);
                auto itemLog = m_modelLogs->item(i, 1);
                auto itemBg = m_modelFilters->item(j, FilterTableColumnBg);
                auto itemFg = m_modelFilters->item(j, FilterTableColumnFg);

                itemLog->setBackground(itemBg->background());
                itemLog->setForeground(itemFg->background());
                break;
            }
        }
    }
}

void MainWindow::selectedFilter(const QModelIndex &)
{

}

void MainWindow::setupFiltersTable()
{
    m_modelFilters = new QStandardItemModel(this);
    m_modelFilters->setColumnCount(3);

    QStringList headers = {};
    m_modelFilters->setHorizontalHeaderLabels({"Filter", "BG Color", "Font Color"});
    for (int i = 0; i < 5; ++i)
    {
        QList<QStandardItem *> items;

        auto itemFilter = new QStandardItem();
        itemFilter->setSelectable(false);
        items.append(itemFilter);

        auto itemColorBg = new QStandardItem();
        itemColorBg->setSelectable(false);
        itemColorBg->setEditable(false);
        items.append(itemColorBg);

        auto itemColorFg = new QStandardItem();
        itemColorFg->setSelectable(false);
        itemColorFg->setEditable(false);
        items.append(itemColorFg);

        m_modelFilters->appendRow(items);
    }

    auto tableView = findChild<QTableView*>("tableView");
    tableView->setModel(m_modelFilters);
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
}

void MainWindow::on_tableView_entered(const QModelIndex &index)
{
   int a = 0;
}

void MainWindow::on_tableView_viewportEntered()
{
   int a = 0;
   ++a;
   a = a;
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    if (index.column() == FilterTableColumnBg || index.column() == FilterTableColumnFg)
    {
        QFlags<QColorDialog::ColorDialogOption> opt1;
        opt1.setFlag(QColorDialog::DontUseNativeDialog, true);
        opt1.setFlag(QColorDialog::ShowAlphaChannel);
        QColor color = QColorDialog::getColor(Qt::darkGreen, this , "Set Color", opt1);

        if( color.isValid() )
        {
            qDebug() << "Color Choosen : " << color.name();
        }

        m_modelFilters->itemFromIndex(index)->setBackground(color);
        showFiltered();
    }
}
