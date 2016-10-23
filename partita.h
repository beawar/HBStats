#ifndef PARTITA_H
#define PARTITA_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QButtonGroup>
#include <vector>
#include "squadra.h"
#include "arbitro.h"
#include "linepartita.h"
using std::vector;

class Partita : public QWidget
{
    Q_OBJECT
private:
    enum {maxGiocatori = 14, maxAllenatori = 2};
    void resizeArrays();
    void createHomeLayout();
    void createGuestLayout();

    QVBoxLayout* mainLayout;

    Squadra* homeTeam;
    Squadra* guestTeam;

    Arbitro* arbitro1;
    Arbitro* arbitro2;
    Arbitro::Categoria categoria;

    int goalHome;
    int goalGuest;

    int currentPortiereHome;
    int currentPortiereGuest;

    int numPlS1;
    int numAllS1;
    int numPlS2;
    int numAllS2;

    LinePartita* homeLines[maxGiocatori+maxAllenatori];
    QButtonGroup* homePortiere;

    LinePartita* guestLines[maxGiocatori+maxAllenatori];
    QButtonGroup* guestPortiere;

    QGroupBox* homeGroup;
    QGroupBox* guestGroup;

    QLabel* punteggio;


public:
    explicit Partita(Squadra* home, Squadra* guest, int numPlS1, int numAllS1, int numPlS2, int numAllS2, Arbitro* a1, Arbitro* a2, Arbitro::Categoria cat, QWidget *parent = 0);

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
