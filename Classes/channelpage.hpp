#ifndef CLASSES_CHANNELPAGE_HPP
#define CLASSES_CHANNELPAGE_HPP

#include "channellabel.hpp"

class QString;
class ChannelPage
{
public:
    ChannelPage(QList<ChannelLabel*>* ChannelS = NULL, QString PreviouS = "", QString CurrenT = "", QString NexT = "", int TotaL = 0){Channels = ChannelS; Previous = PreviouS; Current = CurrenT; Next = NexT; Total=TotaL;}
    void setChannels(QList<ChannelLabel*>* ChannelS){Channels = ChannelS;}
    QList<ChannelLabel*>* getChannels(){return Channels;}
    void setPrevious(QString PreviouS){Previous = PreviouS;}
    QString getPrevious(){return Previous;}
    void setCurrent(QString CurrenT){Current = CurrenT;}
    QString getCurrent(){return Current;}
    void setNext(QString NexT){Next = NexT;}
    QString getNext(){return Next;}
    void setTotal(int TotaL){Total = TotaL;}
    int getTotal(){return Total;}
private:
    QList<ChannelLabel*>* Channels;
    QString Previous, Current, Next;
    int Total;
};

#endif
