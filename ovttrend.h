#ifndef OVTTREND_H
#define OVTTREND_H

#include <QMainWindow>

namespace Ui {
class ovtTrend;
}

class ovtTrend : public QMainWindow
{
	Q_OBJECT

public:
	explicit ovtTrend(QWidget *parent = nullptr);
	~ovtTrend();

private:
	Ui::ovtTrend *ui;
};

#endif // OVTTREND_H
