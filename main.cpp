#include <QApplication>
#include "mainwindow.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("ET-Crypto");

    MainWindow window;
    window.show();

    return app.exec();
}
