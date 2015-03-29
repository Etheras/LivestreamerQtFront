#ifndef GUI_OPTIONS_HPP
#define GUI_OPTIONS_HPP

#include <QDialog>
#include <QSettings>
#include <QFileDialog>
#include <QDesktopServices>

namespace Ui {
class Options;
}
class NetworkManager;
class Options : public QDialog
{
Q_OBJECT

public:
explicit Options(QWidget *parent, QSettings *SettingS, NetworkManager *ManageR);
~Options();

private slots:
void on_OkCancel_accepted();

void on_PlayerButton_clicked();

void on_LiveStreamerButton_clicked();

void on_OAuthButton_clicked();

void on_ResultsSlider_valueChanged(int value);

private:
Ui::Options *ui;
QSettings* Settings;
NetworkManager *Manager;
};

#endif
