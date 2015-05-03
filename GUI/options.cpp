#include "options.hpp"
#include "ui_options.h"
#include "Classes/networkmanager.hpp"

#include "GenericVariables/genericvariables.hpp"

Options::Options(QWidget *parent, QSettings *SettingS, NetworkManager *ManageR) :
	QDialog(parent),
	ui(new Ui::Options)
{
	ui->setupUi(this);

	Manager = ManageR;
	Settings = SettingS;
	ui->ResultsSlider->setValue(Settings->value("Results").toInt());
	ui->PlayerPathText->setText(Settings->value("Player_Path").toString());
	ui->LiveStreamerText->setText(Settings->value("LiveStreamer_Path").toString());
	ui->OAuthText->setText(Settings->value("OAuth").toString());
	ui->Maximised->setChecked(Settings->value("Maximised").toBool());
	ui->ResetOnStart->setChecked(Settings->value("Reset_on_Start").toBool());
	ui->PlayerArgumentsText->setText(Settings->value("Player_Arguments").toString());
}

Options::~Options()
{
	delete ui;
}

void Options::on_OkCancel_accepted()
{
	Settings->setValue("Results", ui->ResultsSlider->value());
	Settings->setValue("Player_Path", ui->PlayerPathText->text());
	Settings->setValue("LiveStreamer_Path", ui->LiveStreamerText->text());
	Settings->setValue("OAuth", ui->OAuthText->text());
	Settings->setValue("Maximised", ui->Maximised->isChecked());
	Settings->setValue("Reset_on_Start", ui->ResetOnStart->isChecked());
	Settings->setValue("Player_Arguments", ui->PlayerArgumentsText->text());
	Settings->sync();
	QFile file("404_preview.jpg");
	if (!file.exists())
	{
		if ( file.open(QIODevice::WriteOnly) )
		{
			QPixmap my404_preview = Manager->getIcon(GenericIconRequestURL);
			my404_preview.save(&file);
		}
	}

}

void Options::on_LiveStreamerButton_clicked()
{
	ui->LiveStreamerText->setText(QFileDialog::getOpenFileName(this));
}

void Options::on_OAuthButton_clicked()
{
	QDesktopServices::openUrl(OAuthGenenerationRequestURL);
}

void Options::on_ResultsSlider_valueChanged(int value)
{
	ui->ResultsText->setText(QString::number(value));
}

void Options::on_LiveStreamerDownload_clicked()
{
	QDesktopServices::openUrl(LivestreamerDownloadURL);
}

void Options::on_PlayerPathButton_clicked()
{
	ui->PlayerPathText->setText(QFileDialog::getOpenFileName(this));
}
