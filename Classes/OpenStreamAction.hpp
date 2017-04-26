#ifndef CLASSES_OPENSTREAMACTION_HPP
#define CLASSES_OPENSTREAMACTION_HPP

#include <QAction>
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>
class QString;
class OpenStreamAction : public QAction
{
Q_OBJECT
public:
    explicit OpenStreamAction(const QString Text, QWidget *Parent = 0):QAction(Text, Parent){connect(this, SIGNAL(triggered()), this, SLOT(onTriggered()));}
	void setURL(QString URl){URL=URl;}
    QString getURL(){return URL;}

private:
	QString URL;
    QString Quality;

signals:
    void onClick(QString);

private slots:
    void onTriggered(){emit onClick(URL);}
};

#endif

