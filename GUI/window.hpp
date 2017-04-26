#ifndef GUI_WINDOW_HPP
#define GUI_WINDOW_HPP

#include <QMainWindow>
#include <QDesktopWidget>
#include <QActionGroup>
#include <QSignalMapper>
#include <QSettings>
#include <QDebug>
#include <QShortcut>

namespace Ui {
class Window;
}

class NetworkManager;
class channelInfoClass;

class Window : public QMainWindow
{
Q_OBJECT

public:
explicit Window(QWidget *parent = 0);
~Window();

private slots:
void on_actionExit_triggered();

void on_actionReset_triggered();

void on_actionOptions_triggered();

void on_actionAbout_triggered();

void on_CustomURLButton_clicked();

void on_actionLiveStreamerLog_triggered();

void on_actionLTF_Log_triggered();

void on_Previous_onClick(const QString &URL);

void on_Refresh_onClick(const QString &URL);

void on_Next_onClick(const QString &URL);

void startStream(QPoint point, Qt::MouseButton button, QString Title, QString URL, QString Name, QString Game, int viewers, QString Quality);

void openChat(QString URL);

void openStream(QString URL);

private:
Ui::Window *ui;
QSettings *Settings;
NetworkManager *Manager;
};

#endif
