#include "window.h"

#include <QProgressBar>
#include <QSlider>
#include <QApplication>

Window::Window(QWidget *parent) : QWidget(parent)
{

    setFixedSize(300, 300);
    m_button = new QPushButton("", this);
    m_button->setGeometry(10, 10, 120, 30);
    m_button->setCheckable(true);

    connect(m_button, SIGNAL (clicked(bool)), this, SLOT (slotButtonClicked(bool)));
    connect(this, SIGNAL(counterReached()), QApplication::instance(), SLOT(quit()));

    QProgressBar *progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    progressBar->setGeometry(10, 50, 180, 30);

    QSlider *slider = new QSlider(this);
    slider->setOrientation(Qt::Horizontal);
    slider->setRange(0, 100);
    slider->setValue(0);
    slider->setGeometry(10, 80, 180, 30);

    connect(slider, SIGNAL(valueChanged(int)), progressBar, SLOT(setValue(int)));
}

void Window::slotButtonClicked(bool checked)
{
    if (checked)
    {
        m_button->setText("Checked");
    }
    else
    {
        m_button->setText("Hello World!");
    }

    ++m_counter;
    if (m_counter == 10)
    {
        emit counterReached();
    }
}
