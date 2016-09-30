#ifndef INTROPAGE_H
#define INTROPAGE_H

#include <QWizardPage>
#include <QRadioButton>
#include <QGroupBox>
#include <QLabel>
#include <QButtonGroup>
#include <QString>
#include <QVBoxLayout>
#include "squadremodel.h"
#include "arbitrimodel.h"

class IntroPage : public QWizardPage
{
    Q_OBJECT
private:
    enum {persona, squadra, partita};

    SquadreModel* squadre;
    ArbitriModel* arbitri;

    void createButtons();
    void createLayouts();

    QVBoxLayout* layout;

    QGroupBox* mainGroup;
    QButtonGroup* radioButtonGroup;
    QRadioButton* personaRadioButton;
    QRadioButton* squadraRadioButton;
    QRadioButton* partitaRadioButton;

    QLabel* helpLabel;
private slots:
    void setLabelText();

public:
    explicit IntroPage(SquadreModel *sm, ArbitriModel *am, QWidget *parent = 0);

    int nextId() const;

signals:

public slots:

};

#endif // INTROPAGE_H
