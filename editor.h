#ifndef EDITOR_H
#define EDITOR_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QRadioButton>
#include <QButtonGroup>
#include <QGroupBox>
#include <QLabel>
#include <QSpinBox>
#include <QDateEdit>
#include <QStackedLayout>
#include <QItemSelection>
#include "arbitrimodel.h"
#include "squadremodel.h"
#include "checklist.h"
#include "vettore.h"


class Editor : public QDialog
{
    Q_OBJECT
private:
    enum {id_tesserato, id_squadra, id_arbitro};
    SquadreModel* squadre;
    ArbitriModel* arbitri;
    CheckList* tesserati;

    void createMainEditor();
    void createTesseratoEditor();
    void createSquadraEditor();
    void createArbitroEditor();

    QListView* listView;
    QGroupBox* radioGroup;
    QButtonGroup* radioButtonGroup;

    QPushButton* editButton;
    QPushButton* removeButton;
    QPushButton* okButton;

    QLabel* squadraLabel;
    QComboBox* squadreComboBox;
    QLabel* nomeTLabel;
    QLineEdit* nomeTEdit;
    QLabel* cognomeTLabel;
    QLineEdit* cognomeTEdit;
    QLabel* dataTLabel;
    QDateEdit* dataTEdit;
    QLabel* numeroLabel;
    QSpinBox* numeroEdit;

    QLabel* nomeSLabel;
    QLineEdit* nomeSEdit;
    QLabel* societaLabel;
    QLineEdit* societaEdit;
    QLabel* penalitaLabel;
    QSpinBox* penalitaEdit;

    QLabel* nomeALabel;
    QLineEdit* nomeAEdit;
    QLabel* cognomeALabel;
    QLineEdit* cognomeAEdit;
    QLabel* dataALabel;
    QDateEdit* dataAEdit;
    QLabel* livelloLabel;
    QSpinBox* livelloEdit;

    QStackedLayout* layouts;
    QVBoxLayout* mainLayout;
    QHBoxLayout* pushLayout;
    QWidget* tesseratoWidget;
    QWidget* squadraWidget;
    QWidget* arbitroWidget;

    Vettore<CheckList*> checkArray;

public:
    explicit Editor(SquadreModel* sm, ArbitriModel* am, QWidget *parent = 0);

signals:
    void squadraChanged(); //
    void dataChanged(bool);

private slots:
    void modifica();
    void modificaTesserato();
    void modificaSquadra();
    void modificaArbitro();
    void rimuovi();
    void rimuoviTesserato();
    void rimuoviSquadra();
    void rimuoviArbitro();
    void updateList(int);
    void updateLayout();
    void itemSelected(QModelIndex);

public slots:

};

#endif // EDITOR_H
