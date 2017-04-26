#include "ui_window.h"
#include "window.hpp"

#include "GenericVariables/genericvariables.hpp"
#include "GenericFunctions/genericfunctions.hpp"

#include "Classes/networkmanager.hpp"
#include "Classes/OpenChatAction.hpp"
#include "Classes/OpenStreamAction.hpp"

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
	populate(Settings->value("OAuth").toString(), ui->TwitchLayout, Manager, ui->Progress, ui->Navigation, Settings->value("Results").toInt(), this);
}

void Window::on_CustomURLButton_clicked()
{
    runLivestreamer(ui->CustomURLDropDown->currentText() + ui->CustomURLText->text(), Settings->value("LiveStreamer_Path").toString(), Settings->value("Player_Path").toString(), Settings->value("Player_Arguments").toString(), Settings->value("OAuth").toString(), "Best");
}

void Window::startStream(QPoint point, Qt::MouseButton button, QString Title, QString URL, QString Name, QString Game, int Viewers, QString TrueQuality)
{
	if(button == Qt::LeftButton)
	{
        QMenu* LeftClickMenu = new QMenu(this);
        OpenStreamAction* OpenTrueQualityStream = new OpenStreamAction(TrueQuality, LeftClickMenu);
        OpenTrueQualityStream->setURL(URL);
        connect(OpenTrueQualityStream, SIGNAL(onClick(QString)), this, SLOT(openStream(QString)));
        LeftClickMenu->addAction("Choose Viewing Quality");
        LeftClickMenu->addSeparator();
        LeftClickMenu->addAction(OpenTrueQualityStream);
        QMenu* LivestreamerQualities = new QMenu("Livestreamer Qualities", this);
        OpenStreamAction* OpenBestStream = new OpenStreamAction("Best", LivestreamerQualities);
        OpenBestStream->setURL(URL);
        connect(OpenBestStream, SIGNAL(onClick(QString)), this, SLOT(openStream(QString)));
        LivestreamerQualities->addAction(OpenBestStream);
        LivestreamerQualities->addSeparator();
        OpenStreamAction* OpenHighStream = new OpenStreamAction("High", LivestreamerQualities);
        OpenBestStream->setURL(URL);
        connect(OpenHighStream, SIGNAL(onClick(QString)), this, SLOT(openStream(QString)));
        LivestreamerQualities->addAction(OpenHighStream);
        OpenStreamAction* OpenMediumStream = new OpenStreamAction("Medium", LivestreamerQualities);
        OpenBestStream->setURL(URL);
        connect(OpenMediumStream, SIGNAL(onClick(QString)), this, SLOT(openStream(QString)));
        LivestreamerQualities->addAction(OpenMediumStream);
        OpenStreamAction* OpenLowStream = new OpenStreamAction("Low", LivestreamerQualities);
        OpenBestStream->setURL(URL);
        connect(OpenLowStream, SIGNAL(onClick(QString)), this, SLOT(openStream(QString)));
        LivestreamerQualities->addAction(OpenLowStream);
        OpenStreamAction* OpenMobileStream = new OpenStreamAction("Mobile", LivestreamerQualities);
        OpenBestStream->setURL(URL);
        connect(OpenMobileStream, SIGNAL(onClick(QString)), this, SLOT(openStream(QString)));
        LivestreamerQualities->addAction(OpenMobileStream);
        OpenStreamAction* OpenAudioStream = new OpenStreamAction("Audio", LivestreamerQualities);
        OpenBestStream->setURL(URL);
        connect(OpenAudioStream, SIGNAL(onClick(QString)), this, SLOT(openStream(QString)));
        LivestreamerQualities->addAction(OpenAudioStream);
        LivestreamerQualities->addSeparator();
        OpenStreamAction* OpenWorstStream = new OpenStreamAction("Worst", LivestreamerQualities);
        OpenBestStream->setURL(URL);
        connect(OpenWorstStream, SIGNAL(onClick(QString)), this, SLOT(openStream(QString)));
        LivestreamerQualities->addAction(OpenWorstStream);
        LeftClickMenu->addMenu(LivestreamerQualities);
        LeftClickMenu->popup(point);
	}
	else if(button == Qt::RightButton)
	{
		QMenu* RightClickMenu = new QMenu(this);
		RightClickMenu->addAction(Title);
		RightClickMenu->addAction(Name + " playing " + Game + " @ " + QString::number(Viewers) + " viewers");
		RightClickMenu->addSeparator();
        OpenChatAction *OpenChat = new OpenChatAction("Open Chat", RightClickMenu);
		OpenChat->setURL(URL);
		connect(OpenChat, SIGNAL(onClick(QString)), this, SLOT(openChat(QString)));
		RightClickMenu->addAction(OpenChat);
        RightClickMenu->popup(point);
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
    QUrl pathUrl = QUrl::fromLocalFile("LiveStreamerQtFront.log");
	QDesktopServices::openUrl(pathUrl);
}

void Window::on_Previous_onClick(const QString &URL)
{
	populate(Settings->value("OAuth").toString(), ui->TwitchLayout, Manager, ui->Progress, ui->Navigation, Settings->value("Results").toInt(), this, URL);
}

void Window::on_Refresh_onClick(const QString &URL)
{
	populate(Settings->value("OAuth").toString(), ui->TwitchLayout, Manager, ui->Progress, ui->Navigation, Settings->value("Results").toInt(), this, URL);
}

void Window::on_Next_onClick(const QString &URL)
{
	populate(Settings->value("OAuth").toString(), ui->TwitchLayout, Manager, ui->Progress, ui->Navigation, Settings->value("Results").toInt(), this, URL);
}

void Window::openChat(QString URL)
{
	QDesktopServices::openUrl(QUrl(URL + "/chat"));
}

void Window::openStream(QString URL)
{
    runLivestreamer(URL, Settings->value("LiveStreamer_Path").toString(), Settings->value("Player_Path").toString(), Settings->value("Player_Arguments").toString(), Settings->value("OAuth").toString(), "best");
}
