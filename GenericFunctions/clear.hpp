#ifndef GENERICFUNCTIONS_CLEAR_HPP
#define GENERICFUNCTIONS_CLEAR_HPP

#include <QGridLayout>
void clear(QGridLayout* Layout)
{
    QLayoutItem *child;
    while ((child = Layout->takeAt(0)) != 0)
    {
        Layout->removeWidget(child->widget());
        delete child->widget();
    }
    delete child;
}
#endif

