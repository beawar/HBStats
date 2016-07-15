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

class PersonaPage : public QWizardPage
{
    Q_OBJECT
private:
    void createButtons();
    void createEditor();
    void createLayout();

    SquadreModel* squadre;

    QGroupBox* buttonGroupBox;

    enum {giocatore, allenatore};
    QButtonGroup* radioButtonGroup;
    QRadioButton* giocatoreButton;
    QCheckBox* portiereButton;
    QRadioButton* allenatoreButton;
    QPushButton* insertButton;

    QLabel* nomeLabel;
    QLabel* cognomeLabel;
    QLabel* numeroLabel;
    QLabel* squadraLabel;
    QLineEdit* nomeEdit;
    QLineEdit* cognomeEdit;
    QLabel* dataLabel;
    QDateEdit* dataEdit;
    QSpinBox* numeroEdit;
    QComboBox* squadraEdit;

    QHBoxLayout* layout;
    QVBoxLayout* radioLayout;
    QGridLayout* editorLayout;

public:
    explicit PersonaPage(SquadreModel* sm, QWidget *parent = 0);

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
