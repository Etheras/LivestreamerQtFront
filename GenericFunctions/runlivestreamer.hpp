#ifndef GENERICFUNCTIONS_RUNLIVESTREAMER_HPP
#define GENERICFUNCTIONS_RUNLIVESTREAMER_HPP

#include <QProcess>
class QString;
void runLivestreamer(QString LiveStreamerPath, QString PlayerPath, QString OAuth, QString url, QString Quality = "best")
{
    QProcess* LiveStreamerProcess = new QProcess();
    QStringList Arguments;
    Arguments << "-p=" + PlayerPath << "--twitch-oauth-token=" + OAuth  << url << Quality;
    LiveStreamerProcess->setStandardOutputFile("LiveStreamer.log", QIODevice::Truncate);
    LiveStreamerProcess->start(LiveStreamerPath, Arguments, QIODevice::ReadOnly);
}
#endif

