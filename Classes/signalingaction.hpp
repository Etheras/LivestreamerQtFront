#ifndef CLASSES_SIGNALINGACTION_HPP
#define CLASSES_SIGNALINGACTION_HPP

#include <QAction>
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>
class QString;
class SignalingAction : public QAction
{
Q_OBJECT
public:
	explicit SignalingAction(const QString Text, QWidget *Parent = 0):QAction(Text, Parent){connect(this, SIGNAL(triggered()), this, SLOT(onTriggered()));}
	void setURL(QString URl){URL=URl;}
	QString getURL(){return URL;}

private:
	QString URL;

signals:
	void onClick(QString);

private slots:
	void onTriggered(){emit onClick(URL);}
};

#endif

