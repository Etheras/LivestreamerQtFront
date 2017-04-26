/*
 *  Developer : Etheras FireFox
 *  License : LGPLv3
*/
#include "GUI/window.hpp"
#include "GenericVariables/genericvariables.hpp"
#include "GenericFunctions/ErrorHandling.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QFile::remove(ErrorsLogPath);
	qInstallMessageHandler(FileMessageOutput);

	QApplication a(argc, argv);
	Window w;
	return a.exec();
}
