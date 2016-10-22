#ifndef LABEL_H
#define LABEL_H
#include <QLabel>

class Label : public QLabel
{
    Q_OBJECT

protected:
    void resizeEvent(QResizeEvent* event);
public:
    Label(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    Label(const QString &text, QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());

};

#endif // LABEL_H
