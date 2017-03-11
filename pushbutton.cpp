#include "pushbutton.h"

PushButton::PushButton(QWidget *parent) :
    QPushButton(parent)
{
}

PushButton::PushButton(const QIcon &icon, const QString& s, QWidget *parent):
    QPushButton(icon, s, parent) {}

PushButton::PushButton(const QString& s, QWidget *parent):
    QPushButton(s, parent) {}


void PushButton::mousePressEvent(QMouseEvent *e){
    if(e->button() == Qt::RightButton){
        if(e->modifiers() == Qt::ShiftModifier){
            emit rightModClicked();
        }
        else{
            emit rightClicked();
        }
    }
    else if(e->button() == Qt::LeftButton && e->modifiers() == Qt::ShiftModifier){
        emit leftModClicked();
    }
    else{
        QPushButton::mousePressEvent(e);
    }
}

void PushButton::mouseDoubleClickEvent(QMouseEvent *e){
//    if(e->button() == Qt::RightButton){
//        emit rightDoubleClicked();
//    }
//    else if(e->button() == Qt::LeftButton){
//        emit leftDoubleClicked();
//    }
//    else{
//        QPushButton::mouseDoubleClickEvent(e);
//    }
}


