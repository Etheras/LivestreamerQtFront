#ifndef GENERICFUNCTIONS_INITQUALITY_HPP
#define GENERICFUNCTIONS_INITQUALITY_HPP

#include <QAction>
class QActionGroup;
QActionGroup *initQuality(QList<QAction*> Qualities, QWidget *Parent = 0)
{
    QActionGroup* toReturn = new QActionGroup(Parent);

    for (QList<QAction*>::const_iterator Quality = Qualities.constBegin(); Quality != Qualities.constEnd(); ++Quality)
    {
        (*Quality)->setActionGroup(toReturn);
    }

    return toReturn;
}
#endif

