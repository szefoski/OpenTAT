#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

#include <QPushButton>

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr);

signals:
    void counterReached();
private slots:
void slotButtonClicked(bool checked);

private:
    QPushButton *m_button;
    int m_counter = 0;
};

#endif // WINDOW_H
