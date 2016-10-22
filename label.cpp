#include "label.h"
#include <QRect>
#include <QFont>

Label::Label(QWidget *parent, Qt::WindowFlags f){
    QLabel(parent, f);
}

Label::Label(const QString &text, QWidget *parent, Qt::WindowFlags f){
    QLabel(text, parent, f);
}

void Label::resizeEvent(QResizeEvent* event){
    QLabel::resizeEvent(event);

    QFont font = this->font();
    QRect cRect = this->contentsRect();

    if( !this->text().isEmpty() ){
        int fontSize = 1;
        bool resized = false;
        while(!resized)
        {
            QFont f(font);
            f.setPixelSize(fontSize);
            QRect r = QFontMetrics(f).boundingRect(this->text());
            if(r.height() <= cRect.height() && r.width() <= cRect.width() )
                fontSize++;
            else
                resized = true;
        }

        font.setPixelSize(fontSize);
        this->setFont(font);
    }

}
