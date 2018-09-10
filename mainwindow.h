#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void filterLogs();
    void selectedFilter(const QModelIndex&);
protected:
    void applyFilter(const QModelIndex &index);
private slots:
    void on_tableFilters_doubleClicked(const QModelIndex &index);
private:
    void setupFiltersTable();
    Ui::MainWindow *ui = nullptr;
    QStandardItemModel* m_modelLogs = nullptr;
    QStandardItemModel* m_modelFilters = nullptr;
};

#endif // MAINWINDOW_H
