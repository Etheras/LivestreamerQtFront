#ifndef CLASSES_NETWORKMANAGER_HPP
#define CLASSES_NETWORKMANAGER_HPP

#include "Classes/channelpage.hpp"
#include "GUI/window.hpp"
#include "GenericVariables/genericvariables.hpp"

#include <QNetworkAccessManager>
#include <QMessageBox>
#include <QObject>
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QEventLoop>
#include <QTimer>
#include <QProgressBar>

class Window;
class ChannelPage;

class NetworkManager : public QObject
{
Q_OBJECT
public:
NetworkManager(Window* windoW)
{
    window = windoW;
    Manager = new QNetworkAccessManager(this);
}

QByteArray getAnything(QString URL, int timeout = 5, QString OAuth = "")
{
    QByteArray toReturn = NULL;

    QNetworkRequest* request = new QNetworkRequest(QUrl(URL));
    if(OAuth != "")
    {
        request->setRawHeader("Accept", "application/vnd.twitchtv.v3+json");
        request->setRawHeader("Authorization", "OAuth " + OAuth.toUtf8());
    }
    QEventLoop loop;
    QNetworkReply* reply = Manager->get(*request);
    QTimer::singleShot(timeout*1000, &loop, SLOT(quit()));
    connect(reply, SIGNAL(finished()), &loop,  SLOT(quit()));
    loop.exec();
    if (reply->error() == QNetworkReply::NoError)
        toReturn = reply->readAll();
    else
        qWarning() << reply->error() << ":" << reply->errorString();

    return toReturn;
}

ChannelPage* getJson(QString URL, QString OAuth, QProgressBar *Progress)
{
    ChannelPage* toReturn = new ChannelPage();

    Progress->show();
    QPixmap Image;
    QJsonDocument JsonD = QJsonDocument::fromJson(getAnything(URL, 10, OAuth));
    if (JsonD.object()["_total"].toInt() < Progress->maximum()) Progress->setMaximum(JsonD.object()["_total"].toInt());
    QList<ChannelLabel*>* Channels = new QList<ChannelLabel*>();
    for(QJsonArray::const_iterator JsonStreams = JsonD.object()["streams"].toArray().constBegin(); JsonStreams != JsonD.object()["streams"].toArray().constEnd(); ++JsonStreams)
    {
        QJsonObject JsonChannel = (*JsonStreams).toObject();
        ChannelLabel* Channel = new ChannelLabel();
        Image = getIcon(JsonChannel["preview"].toObject()["large"].toString());
        if(Image.isNull())
            Image.load("404_preview.jpg");
        Channel->setPreview(Image);
        Channel->setName(JsonChannel["channel"].toObject()["display_name"].toString());
        Channel->setTitle(JsonChannel["channel"].toObject()["status"].toString());
        Channel->setURL(JsonChannel["channel"].toObject()["url"].toString());
        Channel->setGame(JsonChannel["channel"].toObject()["game"].toString());
        Channel->setViewers(JsonChannel["viewers"].toInt());
        Channels->append(Channel);

        int i = Progress->value();
        Progress->setValue(++i);
    }
    Progress->hide();
    Progress->setValue(1);
    toReturn->setChannels(Channels);
    toReturn->setPrevious(JsonD.object()["_links"].toObject()["prev"].toString());
    toReturn->setCurrent(JsonD.object()["_links"].toObject()["self"].toString());
    toReturn->setNext(JsonD.object()["_links"].toObject()["next"].toString());
    toReturn->setTotal(JsonD.object()["_total"].toInt());

    return toReturn;
}

QPixmap getIcon(QString URL)
{
    QPixmap toReturn;

    toReturn = QPixmap::fromImage(QImage::fromData(getAnything(URL, 5)));

    return toReturn;
}

private:
Window* window;
QNetworkAccessManager* Manager;
};

#endif
