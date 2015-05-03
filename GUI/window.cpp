#include "ui_window.h"
#include "window.hpp"

#include "GenericVariables/genericvariables.hpp"
#include "GenericFunctions/genericfunctions.hpp"

#include "Classes/networkmanager.hpp"
#include "Classes/signalingaction.hpp"

#include "options.hpp"
#include "about.hpp"

Window::Window(QWidget *parent) : QMainWindow(parent), ui(new Ui::Window)
{
	ui->setupUi(this);
	QCoreApplication::setOrganizationName(ApplicationDevName);
	QCoreApplication::setOrganizationDomain(ApplicationDevURL);
	QCoreApplication::setApplicationName(ApplicationTitle);
	//this->setWindowIcon();
	this->setWindowTitle(ApplicationTitle);
	ui->Progress->hide();
	Settings = new QSettings(ApplicationName + ".ini", QSettings::IniFormat, this);
	ui->Progress->setRange(1, Settings->value("Results").toInt());
	Manager = new NetworkManager(this);
	Quality = initQuality(ui->menuQuality->actions(), this);
	if (Settings->value("Maximised").toBool())
		this->showMaximized();
	else
		this->show();
	CheckConfiguration(Settings);
	if (Settings->value("Reset_on_Start").toBool())
		ui->actionReset->trigger();
	QShortcut *ResetShortcut = new QShortcut(QKeySequence(tr("F5")), this);
	connect(ResetShortcut, SIGNAL(activated()), this, SLOT(on_actionReset_triggered()));
}

Window::~Window()
{
	delete Manager;
	delete Settings;
	delete ui;
}

void Window::on_actionExit_triggered()
{
	this->close();
	QApplication::quit();
}

void Window::on_actionReset_triggered()
{
	clear(ui->TwitchLayout);
	populate(Settings->value("OAuth").toString(), ui->TwitchLayout, Manager, ui->Progress, ui->Navigation, Settings->value("Results").toInt(), this);
}

void Window::on_CustomURLButton_clicked()
{
	runLivestreamer(ui->CustomURLDropDown->currentText() + ui->CustomURLText->text(), Settings->value("LiveStreamer_Path").toString(), Settings->value("Player_Path").toString(), Settings->value("Player_Arguments").toString(), Settings->value("OAuth").toString(), Quality->checkedAction()->text());
}

void Window::startStream(QPoint point, Qt::MouseButton button, QString Title, QString URL, QString Name, QString Game, int Viewers)
{
	if(button == Qt::LeftButton)
	{
		runLivestreamer(URL, Settings->value("LiveStreamer_Path").toString(), Settings->value("Player_Path").toString(), Settings->value("Player_Arguments").toString(), Settings->value("OAuth").toString(), Quality->checkedAction()->text());
	}
	else if(button == Qt::RightButton)
	{
		QMenu* RightClickMenu = new QMenu(this);
		RightClickMenu->addAction(Title);
		RightClickMenu->addAction(Name + " playing " + Game + " @ " + QString::number(Viewers) + " viewers");
		RightClickMenu->addSeparator();
		SignalingAction *OpenChat = new SignalingAction("Open Chat", RightClickMenu);
		OpenChat->setURL(URL);
		connect(OpenChat, SIGNAL(onClick(QString)), this, SLOT(openChat(QString)));
		RightClickMenu->addAction(OpenChat);
		RightClickMenu->exec(point);
	}
}

void Window::on_actionOptions_triggered()
{
	Options* options = new Options(this, Settings, Manager);
	options->show();
}

void Window::on_actionAbout_triggered()
{
	About* about = new About(this);
	about->show();
}

void Window::on_actionLiveStreamerLog_triggered()
{
	QUrl pathUrl = QUrl::fromLocalFile("LiveStreamer.log");
	QDesktopServices::openUrl(pathUrl);
}

void Window::on_actionLTF_Log_triggered()
{

	QUrl pathUrl = QUrl::fromLocalFile("LiveStreamerTwitchFollower.log");
	QDesktopServices::openUrl(pathUrl);
}

void Window::on_Previous_onClick(const QString &URL)
{
	clear(ui->TwitchLayout);
	populate(Settings->value("OAuth").toString(), ui->TwitchLayout, Manager, ui->Progress, ui->Navigation, Settings->value("Results").toInt(), this, URL);
}

void Window::on_Refresh_onClick(const QString &URL)
{
	clear(ui->TwitchLayout);
	populate(Settings->value("OAuth").toString(), ui->TwitchLayout, Manager, ui->Progress, ui->Navigation, Settings->value("Results").toInt(), this, URL);
}

void Window::on_Next_onClick(const QString &URL)
{
	clear(ui->TwitchLayout);
	populate(Settings->value("OAuth").toString(), ui->TwitchLayout, Manager, ui->Progress, ui->Navigation, Settings->value("Results").toInt(), this, URL);
}

void Window::openChat(QString URL)
{
	QDesktopServices::openUrl(QUrl(URL + "/chat"));
}
