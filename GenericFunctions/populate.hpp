#ifndef GENERICFUNCTIONS_POPULATE_HPP
#define GENERICFUNCTIONS_POPULATE_HPP

#include <QGridLayout>
#include "Classes/networkmanager.hpp"
#include <QProgressBar>
#include "Classes/navigationbutton.hpp"
class QString;
void populate(QString OAuth, QGridLayout *Twitch,  NetworkManager *MyNetManager, QProgressBar *Progress, QWidget *Navigation, int Results = 25, QWidget *Parent = 0, QString URL = "")
{
    if(URL == "")
        URL = FollowRequestURL + "?limit=" + QString::number(Results);
    ChannelPage* Channels = MyNetManager->getJson(URL, OAuth, Progress);
    clear(Twitch);
    QList<ChannelLabel*>* ChannelList = Channels->getChannels();
    int i=0,j=0;
    for(QList<ChannelLabel*>::const_iterator Channel = ChannelList->constBegin(); Channel != ChannelList->constEnd(); ++Channel)
    {
        QObject::connect(*Channel, SIGNAL(onClick(QPoint, Qt::MouseButton, QString, QString, QString, QString, int, QString)), Parent, SLOT(startStream(QPoint, Qt::MouseButton, QString, QString, QString, QString, int, QString)));
        Twitch->addWidget(*Channel, i++/5, j++%5);
    }
    Navigation->findChild<NavigationButton*>("Previous")->setURL(Channels->getPrevious());
    Navigation->findChild<NavigationButton*>("Refresh")->setURL(Channels->getCurrent());
    Navigation->findChild<NavigationButton*>("Next")->setURL(Channels->getNext());
}
#endif

