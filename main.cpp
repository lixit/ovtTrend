#include "ovttrend.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ovtTrend w;
	w.show();

	return a.exec();
}
