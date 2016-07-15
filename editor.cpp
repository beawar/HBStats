#include "editor.h"

Editor::Editor(SquadreModel*sm, QWidget *parent) :
    QDialog(parent), squadre(sm)
{   
    createMainEditor();
    if(squadre){
        createTesseratoEditor();
        createSquadraEditor();
    }

    layouts = new QStackedLayout;
    layouts->addWidget(tesseratoWidget);
    layouts->addWidget(squadraWidget);

    QHBoxLayout* editorLayout = new QHBoxLayout;
    editorLayout->addWidget(listView);
    editorLayout->addLayout(layouts);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(radioGroup);
    mainLayout->addLayout(editorLayout);
    mainLayout->addLayout(pushLayout);
    pushLayout->setAlignment(mainLayout, Qt::AlignRight);

    setLayout(mainLayout);
    setWindowTitle(tr("Editor"));
    setMinimumSize(sizeHint());
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    updateList(squadreComboBox->currentIndex());

}

void Editor::createMainEditor(){
    QRadioButton* tesseratoRadio = new QRadioButton(tr("Tesserati"), this);
    tesseratoRadio->setChecked(true);
    QRadioButton* squadraRadio = new QRadioButton(tr("Squadre"), this);

    radioButtonGroup = new QButtonGroup(this);
    radioButtonGroup->addButton(tesseratoRadio, id_tesserato);
    radioButtonGroup->addButton(squadraRadio, id_squadra);
    connect(radioButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(updateLayout()));

    editButton = new QPushButton(tr("Modifica"), this);
    editButton->setEnabled(false);
    removeButton = new QPushButton(tr("Elimina"), this);
    removeButton->setEnabled(false);
    okButton = new QPushButton(tr("Ok"), this);

    connect(editButton, SIGNAL(clicked()), this, SLOT(modifica()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(rimuovi()));
    connect(okButton, SIGNAL(clicked()), this, SLOT(close()));

    listView = new QListView(this);
    connect(listView, SIGNAL(clicked(QModelIndex)),this, SLOT(itemSelected(QModelIndex)));

    QHBoxLayout* radioLayout = new QHBoxLayout;
    radioLayout->addWidget(tesseratoRadio);
    radioLayout->addWidget(squadraRadio);

    radioGroup = new QGroupBox(tr("Scegli cosa modificare:"), this);
    radioGroup->setLayout(radioLayout);

    pushLayout = new QHBoxLayout;
    pushLayout->addWidget(editButton);
    pushLayout->addWidget(removeButton);
    pushLayout->addWidget(okButton);
}

void Editor::createTesseratoEditor(){
    squadraLabel = new QLabel(tr("Squadra:"), this);
    squadreComboBox = new QComboBox(this);
    squadreComboBox->setModel(squadre);
    connect(squadreComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateList(int)));

    for(int i=0; i<squadre->size(); ++i){
        checkArray.push_back(new CheckList(squadre->at(i), false, this));
    }
    tesserati = checkArray[squadreComboBox->currentIndex()];

    nomeTLabel = new QLabel(tr("Nome:"), this);
    nomeTEdit = new QLineEdit(this);

    cognomeTLabel = new QLabel(tr("Cognome:"), this);
    cognomeTEdit = new QLineEdit(this);

    dataTLabel = new QLabel(tr("Data di nascita:"), this);
    dataTEdit = new QDateEdit(this);
    dataTEdit->setMaximumDate(QDate::currentDate());
    dataTEdit->setDisplayFormat("dd/MM/yyyy");

    numeroLabel = new QLabel(tr("Numero:"), this);
    numeroEdit = new QSpinBox(this);
    numeroEdit->setRange(1, 99);

    QGridLayout* gridTLayout = new QGridLayout;
    gridTLayout->addWidget(squadraLabel, 1, 1);
    gridTLayout->addWidget(squadreComboBox, 1, 2);
    gridTLayout->addWidget(nomeTLabel, 2, 1);
    gridTLayout->addWidget(nomeTEdit, 2, 2);
    gridTLayout->addWidget(cognomeTLabel, 3, 1);
    gridTLayout->addWidget(cognomeTEdit, 3, 2);
    gridTLayout->addWidget(dataTLabel, 4, 1);
    gridTLayout->addWidget(dataTEdit, 4, 2);
    gridTLayout->addWidget(numeroLabel, 5, 1);
    gridTLayout->addWidget(numeroEdit, 5, 2);

    tesseratoWidget = new QWidget(this);
    tesseratoWidget->setLayout(gridTLayout);
}

void Editor::createSquadraEditor(){
    nomeSLabel = new QLabel(tr("Nome:"), this);
    nomeSLabel->setAlignment(Qt::AlignLeft);
    nomeSEdit = new QLineEdit(this);

    societaLabel = new QLabel(tr("Società:"), this);
    societaLabel->setAlignment(Qt::AlignLeft);
    societaEdit = new QLineEdit(this);

    penalitaLabel = new QLabel(tr("Penalità:"), this);
    penalitaLabel->setAlignment(Qt::AlignLeft);
    penalitaEdit = new QSpinBox(this);
    penalitaEdit->setRange(0, +99);

    QGridLayout* gridSLayout = new QGridLayout;
    gridSLayout->addWidget(nomeSLabel, 1, 1);
    gridSLayout->addWidget(nomeSEdit, 1, 2);
    gridSLayout->addWidget(societaLabel, 2, 1);
    gridSLayout->addWidget(societaEdit, 2, 2);
    gridSLayout->addWidget(penalitaLabel, 3, 1);
    gridSLayout->addWidget(penalitaEdit, 3, 2);

    squadraWidget = new QWidget(this);
    squadraWidget->setLayout(gridSLayout);
}

void Editor::modifica(){
    if(listView->selectionModel()->currentIndex().isValid()){
        switch(radioButtonGroup->checkedId()){
            case id_tesserato:
                modificaTesserato();
            break;
            case id_squadra:
                modificaSquadra();
            break;
            default:
                break;
        }
        updateList(squadreComboBox->currentIndex());
        emit dataChanged(true);
    }
}

void Editor::modificaTesserato(){
    Squadra* squadra = squadre->at(squadreComboBox->currentIndex());
    int index = listView->selectionModel()->currentIndex().row();
    Giocatore* gioc = dynamic_cast<Giocatore*>(squadra->at(index));
    if(gioc){
        Giocatore g;
        g.setNome(nomeTEdit->text());
        g.setCognome(cognomeTEdit->text());
        g.setData(dataTEdit->date());
        g.setNumero(numeroEdit->value());
        squadra->modificaTesserato(gioc, g);
    }
    else{
        Allenatore* all = dynamic_cast<Allenatore*>(squadra->at(index));
        if(all){
            Allenatore a;
            a.setNome(nomeTEdit->text());
            a.setCognome(cognomeTEdit->text());
            a.setData(dataTEdit->date());
            squadra->modificaTesserato(all, a);
        }
    }
    updateList(squadreComboBox->currentIndex());
}

void Editor::modificaSquadra(){
    int index = listView->selectionModel()->currentIndex().row();
    Squadra nuova;
    nuova.setNome(nomeSEdit->text());
    nuova.setSocieta(societaEdit->text());
    nuova.addPenalita(penalitaEdit->value());
    squadre->modificaSquadra(squadre->at(index), nuova);
    updateList(INT_MIN);
    emit squadraChanged();
}

void Editor::rimuovi(){
    if(listView->selectionModel()->currentIndex().isValid()){
        switch(radioButtonGroup->checkedId()){
            case id_tesserato:
                rimuoviTesserato();
            break;
            case id_squadra:
                rimuoviSquadra();
            break;
            default:
            break;
        }
        emit dataChanged(true);
    }
}

void Editor::rimuoviTesserato(){
    Squadra* squadra = squadre->at(squadreComboBox->currentIndex());
    int index = listView->selectionModel()->currentIndex().row();
    squadra->removeTesserato(squadra->at(index));
    updateList(squadreComboBox->currentIndex());
}

void Editor::rimuoviSquadra(){
    int index = listView->selectionModel()->currentIndex().row();
    squadre->removeSquadra(squadre->at(index));
    updateList(INT_MIN);
    emit squadraChanged();
}

void Editor::updateList(int index){
    switch(radioButtonGroup->checkedId()){
        case id_tesserato:
            checkArray[index]->updateList();
            listView->setModel(tesserati);
            break;
        case id_squadra:
            listView->setModel(squadre);
            break;
        default:
            break;
    }
    connect(listView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(itemSelected(QModelIndex)));
    listView->setCurrentIndex(QModelIndex());
    itemSelected(listView->currentIndex());
    update();
}

void Editor::updateLayout(){

    switch (radioButtonGroup->checkedId()) {
        case id_tesserato:
            layouts->setCurrentWidget(tesseratoWidget);
            itemSelected(listView->currentIndex());
            break;
        case id_squadra:
            layouts->setCurrentWidget(squadraWidget);
            break;
        default:

            break;
    }
    updateList(squadreComboBox->currentIndex());
}

void Editor::itemSelected(QModelIndex current){
    if(!current.isValid()){
        switch (radioButtonGroup->checkedId()) {
            editButton->setEnabled(false);
            removeButton->setEnabled(false);
            case id_tesserato:
                nomeTEdit->clear();
                cognomeTEdit->clear();
                dataTEdit->setDate(QDate::currentDate());
                numeroEdit->clear();
            break;
            case id_squadra:
                nomeSEdit->clear();
                societaEdit->clear();
                penalitaEdit->clear();
                break;
            default:
            break;
        }
    }
    else{
        editButton->setEnabled(true);
        removeButton->setEnabled(true);
        Squadra* squadra = squadre->at(squadreComboBox->currentIndex());
        switch(radioButtonGroup->checkedId()){
            case id_tesserato:
            {
                nomeTEdit->setText(squadra->at(current.row())->getNome());
                cognomeTEdit->setText(squadra->at(current.row())->getCognome());
                dataTEdit->setDate(squadra->at(current.row())->getData());
                Giocatore* g = dynamic_cast<Giocatore*>(squadra->at(current.row()));
                if(g){
                    numeroEdit->setEnabled(true);
                    numeroEdit->setValue(g->getNumero());
                }
                else{
                    numeroEdit->setDisabled(true);
                }
            }
            break;
            case id_squadra:
                nomeSEdit->setText(squadre->at(current.row())->getNome());
                societaEdit->setText(squadre->at(current.row())->getSocieta());
                penalitaEdit->setValue(squadre->at(current.row())->getPenalita());
            break;
            default:
            break;
        }
    }
    update();
}
