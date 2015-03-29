#include "window.hpp"
#include "ui_window.h"

Window::Window(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::Window)
{
	ui->setupUi(this);
}

Window::~Window()
{
	delete ui;
}
