#include "src/MainWindow.h"

#include <QApplication>
#include <QTextStream>

int main(int argc, char *argv[])
{
#if WIN32
	setlocale(LC_ALL, "Rus");
	QTextStream cin(stdin); cin.setCodec("CP866");
	QTextStream cout(stdout); cout.setCodec("CP1251");
#endif
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
