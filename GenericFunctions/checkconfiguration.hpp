#ifndef GENERICFUNCTIONS_CHECKCONFIGURATION_HPP
#define GENERICFUNCTIONS_CHECKCONFIGURATION_HPP

#include <QSettings>
#include <QMessageBox>
bool CheckConfiguration(QSettings *Settings)
{
	bool toReturn = false;

	if(Settings->value("LiveStreamer").toString() != "" && Settings->value("Player").toString() != "" && Settings->value("OAuth").toString() != "")
		toReturn = true;
	else
	{
		QMessageBox Warning;
		Warning.setText("You need to configure settings from the options dialog");
		Warning.exec();
	}
	return toReturn;
}

#endif

