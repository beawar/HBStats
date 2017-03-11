#ifndef LINEPARTITA_H
#define LINEPARTITA_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include "giocatore.h"
#include "portiere.h"
#include "allenatore.h"
#include "arbitro.h"
#include "pushbutton.h"

class LinePartita : public QWidget
{
    Q_OBJECT
private:
    Tesserato* tesserato;

    void createButtons();
    void createLayout();

    QLabel* numeroLabel;
    QLabel* nomeLabel;
    QLabel* goalLabel;
    PushButton* tiroButton;
    PushButton* rigoreButton;
    PushButton* ammoButton;
    PushButton* dueMinButton;
    PushButton* esclButton;

    QHBoxLayout* layout;

private slots:
    void rightclickAmmo();
    void rightclickdueMin();
    void rightclickEscl();
    void rightclickTiro();
    void rightclickModTiro();
    void rightclickRigore();
    void rightclickModRigore();

    void leftclickAmmo();
    void leftclickdueMin();
    void leftclickEscl();
    void leftclickTiro();
    void leftclickModTiro();
    void leftclickRigore();
    void leftclickModRigore();

    void updateGoals();


public:
    explicit LinePartita(Tesserato* t, QWidget *parent = 0);
    void updateTesserato(Tesserato* t);

signals:
    void tiro(int, bool);
    void rigore(int, bool);
    void dataChanged();

public slots:
    void reset();

};

/* LEGENDA CLICK PER TIRI\RIGORI:
 *      - left click = aggiungi segnato;
 *      - left doubleclick = aggiungi sbagliato;
 *      - right click = rimuovi segnato;
 *      - right doubleclick = rimuovi sbagliato;
 *
 * IN GENERALE:
 *      -left click = aggiungi;
 *      -right click = rimuovi;
 */

#endif // LINEPARTITA_H
