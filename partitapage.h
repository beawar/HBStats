#ifndef PARTITAPAGE_H
#define PARTITAPAGE_H

#include <QWizardPage>
#include <QListView>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QSpinBox>
#include <QLabel>
#include <QRadioButton>
#include "checklist.h"
#include "squadremodel.h"
#include "arbitrimodel.h"
#include "tabs.h"

class PartitaPage : public QWizardPage
{
    Q_OBJECT
private:
    enum {maxGiocatori = 14, maxAllenatori = 2};
    void createView();
    void createLayout();
    Squadra* homeTeam() const;
    Squadra* guestTeam() const;

    SquadreModel* squadre;
    ArbitriModel* arbitri;

    QVBoxLayout* layout;

    QLabel* numbersSquadra1;
    QLabel* numbersSquadra2;
    QCheckBox* selectAllSquadra1;
    QCheckBox* selectAllSquadra2;

    QGroupBox* squadra1Group;
    QGroupBox* squadra2Group;
    QGroupBox* arbitriGroup;
    QGroupBox* radioGroup;

    QRadioButton* nomeButton;
    QRadioButton* numeroButton;

    QComboBox* squadra1ComboBox;
    QComboBox* squadra2ComboBox;
    QComboBox* arbitro1ComboBox;
    QComboBox* arbitro2ComboBox;

    QLabel* categoriaLabel;
    QComboBox* categoria;

    QListView* squadra1List;
    QListView* squadra2List;

    Vettore<CheckList*> checkArray;

    CheckList* squadra1;
    CheckList* squadra2;

private slots:
    void updateList();
    void updateCheckBox();
    void checkItemS1(QModelIndex index);
    void checkItemS2(QModelIndex index);
    void checkAllS1(bool c);
    void checkAllS2(bool c);
    void sort();

public:
    enum Team {home, guest};
    enum Type {gioc, all};
    explicit PartitaPage(SquadreModel* sm, ArbitriModel* am, QWidget *parent = 0);

    int nextId() const;
    bool validatePage() const;

    int getNumberOf(Team team, Type type);

    Arbitro::Categoria getCategoria() const;
signals:

public slots:

};

#endif // PARTITAPAGE_H
