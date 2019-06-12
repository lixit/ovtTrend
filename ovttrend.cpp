#include "ovttrend.h"
#include "ui_ovttrend.h"

ovtTrend::ovtTrend(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::ovtTrend)
{
	ui->setupUi(this);
}

ovtTrend::~ovtTrend()
{
	delete ui;
}
