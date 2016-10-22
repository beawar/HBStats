#include "label.h"

Label::Label()
{

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
            if(r.height() <= cRect.height() && r.width() <= cRect.widht() )
                fontSize++;
            else
                resized = true;
        }

        font.setPixelSize(fontSize);
        this->setFont(font);
    }
}
