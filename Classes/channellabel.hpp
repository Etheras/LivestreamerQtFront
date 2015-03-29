#ifndef CLASSES_CHANNELLABEL_HPP
#define CLASSES_CHANNELLABEL_HPP

#include <QPixmap>
#include <QLabel>
#include <QMouseEvent>
class QString;
class ChannelLabel : public QLabel
{
Q_OBJECT
public:
    explicit ChannelLabel(QString URl = "", QString PrevieW = "", QString TitlE = "", QString NamE = "", QString GamE = "", int ViewerS = 0, QWidget *Parent = 0){URL = URl; Preview = PrevieW; Title = TitlE; Name = NamE; Game = GamE; Viewers = ViewerS; this->setParent(Parent);}
    void setURL(QString URl){URL=URl;}
    QString getURL(){return URL;}
    void setPreview(QPixmap PrevieW){Preview = PrevieW;  this->setMouseTracking(true); this->setPixmap(Preview); this->setScaledContents(true);this->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);}
    QPixmap getPreview(){return Preview;}
    void setTitle(QString TitlE){Title = TitlE;}
    QString getTitle(){return Title;}
    void setName(QString NamE){Name = NamE;}
    QString getName(){return Name;}
    void setGame(QString GamE){Game = GamE;}
    QString getGame(){return Game;}
    void setViewers(int ViewerS){Viewers = ViewerS;}
    int getViewers(){return Viewers;}
private:
    QPixmap Preview;
    QString Game, Name, Title, URL;
    int Viewers;

signals:
    void onClick(QPoint, Qt::MouseButton, QString, QString, QString, QString, int);

protected:
    void mousePressEvent(QMouseEvent* event) {emit onClick(event->globalPos(), event->button(), Title, URL, Name, Game, Viewers);}
};
#endif

