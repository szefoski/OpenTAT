#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>
#include <QtDebug>
#include <QFile>
#include <QItemSelectionModel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QStandardItemModel>
#include <QTableView>
#include <QTextStream>

#include <algorithm>

class MySelectionModel : public QItemSelectionModel
{
public Q_SLOTS:
    void select(const QModelIndex & index, QItemSelectionModel::SelectionFlags command) override
    {
        int aaa = 0;
    }

    void select(const QItemSelection & selection, QItemSelectionModel::SelectionFlags command) override
    {

        int aaa = 0;
    }
};

class MyItem : public QStandardItem
{
public:
    MyItem() = default;
    explicit MyItem(const QString &text) : QStandardItem(text) {}
    MyItem(const QIcon &icon, const QString &text) : QStandardItem(icon, text) {}
    //explicit QStandardItem(int rows, int columns = 1) : QStandardItem(rows, columns) {}
    virtual ~MyItem() = default;
};

const int FilterTableColumnExpression = 2;
const int FilterTableColumnBg = 1;
const int FilterTableColumnFg = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto ui_tableLogs = findChild<QTableView*>("tableLogs");

    m_modelLogs = new QStandardItemModel(this);
    ui_tableLogs->verticalHeader()->hide();
    ui_tableLogs->horizontalHeader()->hide();

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
            auto lineNoItem = new MyItem(QString::number(lineNo));
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

    ui_tableLogs->setModel(m_modelLogs);

    auto ui_button = findChild<QPushButton*>("pushButton");
    connect(ui_button, SIGNAL(clicked()), this, SLOT(filterLogs()));

    ui_tableLogs->resizeColumnToContents(0);

    setupFiltersTable();
    ui_tableLogs->setSelectionModel(new MySelectionModel());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void test1()
{
    QString text = "ab";
    QString search = "abc|ab";

    QRegularExpression re(search);
    const auto match = re.match(text, 0, QRegularExpression::PartialPreferFirstMatch);

    bool has = match.hasPartialMatch();
    int a = 0;
}

void MainWindow::filterLogs()
{
    test1();
    auto ui_tableLogs = findChild<QTableView*>("tableLogs");
    auto ui_tableFilters = findChild<QTableView*>("tableFilters");

    const QColor hlClr = Qt::red; // highlight color to set
    const QColor txtClr = Qt::red; // highlighted text color to set

    QPalette p = palette();
    p.setColor(QPalette::Highlight, QColor(0,255,0,0));
    p.setColor(QPalette::HighlightedText, txtClr);
    ui_tableLogs->setPalette(p);

    for (int i = 0; i < m_modelLogs->rowCount(); ++i)
    {
        ui_tableLogs->setRowHidden(i, true);
    }

    for (int i = 0; i < m_modelLogs->rowCount(); ++i)
    {
        const auto text = m_modelLogs->item(i, 1)->text();

        for (int j = 0; j < m_modelFilters->rowCount(); j++)
        {
            const auto expression = m_modelFilters->item(j, FilterTableColumnExpression)->text();

            QRegularExpression re(expression);
            const auto match = re.match(text, 0, QRegularExpression::PartialPreferFirstMatch);

            bool has = match.hasMatch();
            if (has)
            {
                ui_tableLogs->setRowHidden(i, false);
                auto itemLog = m_modelLogs->item(i, 1);
                auto itemBg = m_modelFilters->item(j, FilterTableColumnBg);
                auto itemFg = m_modelFilters->item(j, FilterTableColumnFg);

                itemLog->setBackground(itemBg->background());
                itemLog->setForeground(itemFg->background());
                break;
            }
            else if (j == m_modelFilters->rowCount() -1)
            {
                ui_tableLogs->setRowHidden(i, false);
                auto itemLog = m_modelLogs->item(i, 1);

                itemLog->setBackground(QBrush(Qt::white));
                itemLog->setForeground(QBrush(Qt::black));
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
    //m_modelFilters->setColumnCount(3);

    QStringList headers = {};
    m_modelFilters->setHorizontalHeaderLabels({"Font Color", "BG Color", "Filter"});
    for (int i = 0; i < 5; ++i)
    {
        QList<QStandardItem *> items;

        auto itemColorFg = new QStandardItem();
        itemColorFg->setSelectable(false);
        itemColorFg->setEditable(false);
        items.append(itemColorFg);

        auto itemColorBg = new QStandardItem();
        itemColorBg->setSelectable(false);
        itemColorBg->setEditable(false);
        items.append(itemColorBg);

        auto itemFilter = new QStandardItem();
        itemFilter->setSelectable(false);
        items.append(itemFilter);

        m_modelFilters->appendRow(items);
    }

    auto ui_tableFilters = findChild<QTableView*>("tableFilters");
    ui_tableFilters->setModel(m_modelFilters);
}

void MainWindow::applyFilter(const QModelIndex &index)
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
        filterLogs();
    }
}

void MainWindow::on_tableFilters_doubleClicked(const QModelIndex &index)
{
    applyFilter(index);
}
