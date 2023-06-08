#include "GUI/Window.h"
#include <QApplication>
#include <QFile>
#include <QIODevice>

#define сетлокаль std::setlocale(LC_ALL, "")

int main(int argc, char **argv)
{
    сетлокаль;
    QApplication app (argc, argv);

    QFile file("stylesheet.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    app.setStyleSheet(styleSheet);
    Window window;
    window.show();

    return app.exec();
}