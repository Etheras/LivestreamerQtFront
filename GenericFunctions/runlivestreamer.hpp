#ifndef GENERICFUNCTIONS_RUNLIVESTREAMER_HPP
#define GENERICFUNCTIONS_RUNLIVESTREAMER_HPP

#include <QProcess>
class QString;
void runLivestreamer(QString URL, QString LiveStreamerPath, QString PlayerPath, QString PlayerArguments = "", QString OAuth = "", QString Quality = "best")
{
	QProcess* LiveStreamerProcess = new QProcess();
	QStringList Arguments;
	Arguments << "-p=" + PlayerPath + " " + PlayerArguments << URL << Quality << "--twitch-oauth-token=" + OAuth;
	LiveStreamerProcess->setStandardOutputFile("LiveStreamer.log", QIODevice::Truncate);
	LiveStreamerProcess->start(LiveStreamerPath, Arguments, QIODevice::ReadOnly);
}
#endif
