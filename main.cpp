#include <QApplication>
#include <QFont>
#include <QPushButton>

int main(int argc, char **argv)
{
 QApplication app (argc, argv);

 QFont font("Courier");

 QWidget window;
 window.setFixedSize(200, 50);

 QPushButton button(&window);
 button.setText("My Text");
 button.setToolTip("A tooltip");
 button.setFont(font);
 button.setIcon(QIcon::fromTheme("face-smile"));
 button.setGeometry(10, 20, 120, 30);

 window.show();

 return app.exec();
}
