#ifndef LABEL_H
#define LABEL_H
#include <QLabel>

class Label : public QLabel
{
    Q_OBJECT

public:
    Label();
    void resizeEvent(QResizeEvent* event);
};

#endif // LABEL_H
