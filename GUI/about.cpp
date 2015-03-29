#include "about.hpp"
#include "ui_about.h"

About::About(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::About)
{
	ui->setupUi(this);
	this->setWindowFlags(Qt::FramelessWindowHint);
}

About::~About()
{
	delete ui;
}
