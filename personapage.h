#ifndef PERSONAPAGE_H
#define PERSONAPAGE_H

#include <QWizardPage>
#include <QGroupBox>
#include <QGridLayout>
#include <QRadioButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QButtonGroup>
#include <QLabel>
#include <QDateEdit>
#include <QPushButton>
#include <QCheckBox>
#include "squadremodel.h"
#include "arbitrimodel.h"

class PersonaPage : public QWizardPage
{
    Q_OBJECT
private:
    void createButtons();
    void createEditor();
    void createLayout();

    SquadreModel* squadre;
    ArbitriModel* arbitri;

    QGroupBox* buttonGroupBox;

    enum {giocatore, allenatore, arbitro};
    QButtonGroup* radioButtonGroup;
    QRadioButton* giocatoreButton;
    QCheckBox* portiereButton;
    QRadioButton* allenatoreButton;
    QRadioButton* arbitroButton;
    QPushButton* insertButton;

    QLabel* nomeLabel;
    QLabel* cognomeLabel;
    QLabel* numeroLabel;
    QLabel* squadraLabel;
    QLabel* livelloLabel;
    QLineEdit* nomeEdit;
    QLineEdit* cognomeEdit;
    QLabel* dataLabel;
    QDateEdit* dataEdit;
    QSpinBox* numeroEdit;
    QComboBox* squadraEdit;
    QSpinBox* livelloEdit;

    QHBoxLayout* layout;
    QVBoxLayout* radioLayout;
    QGridLayout* editorLayout;

public:
    explicit PersonaPage(SquadreModel* sm, ArbitriModel* am, QWidget *parent = 0);

    int nextId() const;

signals:
    void personaCreata();

private slots:
    void validateData();

public slots:
    void changeEditor();
    void insertPerson();

};

#endif // PERSONAPAGE_H
