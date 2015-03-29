#ifndef CLASSES_NAVIGATIONBUTTON_HPP
#define CLASSES_NAVIGATIONBUTTON_HPP

#include <QPushButton>
class QString;
class NavigationButton : public QPushButton
{
Q_OBJECT
public:
	explicit NavigationButton(QWidget *Parent = 0):QPushButton(Parent){}
	void setURL(QString URl){URL=URl;}
	QString getURL(){return URL;}
private:
	QString URL;

signals:
	void onClick(QString);

protected:
	void mousePressEvent(QMouseEvent*) {emit onClick(URL);}
};

#endif
