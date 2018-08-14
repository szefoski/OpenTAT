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
    void showFiltered();
    void selectedFilter(const QModelIndex&);
private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_tableView_entered(const QModelIndex &index);

    void on_tableView_viewportEntered();

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    void setupFiltersTable();
    Ui::MainWindow *ui = nullptr;
    QStandardItemModel* m_modelLogs = nullptr;
    QStandardItemModel* m_modelFilters = nullptr;
};

#endif // MAINWINDOW_H
