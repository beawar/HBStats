#include "statsamescreen.h"

StatSameScreen::StatSameScreen(QWidget *parent) : QWidget(parent){}

StatSameScreen::StatSameScreen(Stat* s1, Stat* s2){
    setObjectName("stat_same_screen");
    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(s1);
    mainLayout->addWidget(s2);

    setLayout(mainLayout);
}
