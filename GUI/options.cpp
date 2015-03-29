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
    ui->PlayerText->setText(Settings->value("Player").toString());
    ui->LiveStreamerText->setText(Settings->value("LiveStreamer").toString());
    ui->OAuthText->setText(Settings->value("OAuth").toString());
    ui->Maximised->setChecked(Settings->value("Maximised").toBool());
    ui->ResetOnStart->setChecked(Settings->value("ResetOnStart").toBool());
}

Options::~Options()
{
    delete ui;
}

void Options::on_OkCancel_accepted()
{
    Settings->setValue("Results", ui->ResultsSlider->value());
    Settings->setValue("Player", ui->PlayerText->text());
    Settings->setValue("LiveStreamer", ui->LiveStreamerText->text());
    Settings->setValue("OAuth", ui->OAuthText->text());
    Settings->setValue("Maximised", ui->Maximised->isChecked());
    Settings->setValue("ResetOnStart", ui->ResetOnStart->isChecked());
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

void Options::on_PlayerButton_clicked()
{
    ui->PlayerText->setText(QFileDialog::getOpenFileName(this));
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
