#ifndef PARTITA_H
#define PARTITA_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QButtonGroup>
#include "squadra.h"
#include "linepartita.h"

class Partita : public QWidget
{
    Q_OBJECT
private:
    enum {maxGiocatori = 14, maxAllenatori = 2};
    void createHomeLayout();
    void createGuestLayout();

    QVBoxLayout* mainLayout;

    Squadra* homeTeam;
    Squadra* guestTeam;

    int goalHome;
    int goalGuest;

    int currentPortiereHome;
    int currentPortiereGuest;

    LinePartita* homeLines[maxGiocatori+maxAllenatori];
    QButtonGroup* homePortiere;

    LinePartita* guestLines[maxGiocatori+maxAllenatori];
    QButtonGroup* guestPortiere;

    QGroupBox* homeGroup;
    QGroupBox* guestGroup;

    QLabel* punteggio;

public:
    explicit Partita(Squadra* home, Squadra* guest, QWidget *parent = 0);

signals:
    void dataChanged();

private slots:
    void updatePunteggio();
    void tiroHome(int, bool);
    void rigoreHome(int, bool);

    void tiroGuest(int, bool);
    void rigoreGuest(int, bool);

    void cambiaPortiereHome();
    void cambiaPortiereGuest();

    void dataSlot();

public slots:
    void termina();
    void reset();

};

#endif // PARTITA_H
