#include "intropage.h"
#include "newwizard.h"

IntroPage::IntroPage(SquadreModel* sm, ArbitriModel *am, QWidget *parent) :
    QWizardPage(parent), squadre(sm), arbitri(am)
{
    helpLabel = new QLabel(tr("Crea un nuovo giocatore, allenatore o arbitro"), this);
    helpLabel->setWordWrap(true);
    createButtons();
    createLayouts();

    setLayout(layout);
}

void IntroPage::setLabelText(){
    switch(radioButtonGroup->checkedId()){
    case persona:
        helpLabel->setText(tr("Crea un nuovo giocatore, allenatore o arbitro"));
        update();
        break;
    case squadra:
        helpLabel->setText(tr("Crea una nuova squadra. Per aggiungere giocatori creare successivamente nuovi giocatori"));
        update();
        break;
    case partita:
        helpLabel->setText(tr("Crea una nuova partita tra due squadre."
                              "Sono necessari almeno due arbitri e due squadre per sbloccare questo contenuto"));
        update();
        break;
    }
}

void IntroPage::createButtons(){
    personaRadioButton = new QRadioButton(tr("Persona"), this);
    personaRadioButton->setChecked(true);
    connect(personaRadioButton, SIGNAL(clicked()), this, SLOT(setLabelText()));

    squadraRadioButton = new QRadioButton(tr("Squadra"), this);
    connect(squadraRadioButton, SIGNAL(clicked()), this, SLOT(setLabelText()));

    partitaRadioButton = new QRadioButton(tr("Partita"), this);
    connect(partitaRadioButton, SIGNAL(clicked()), this, SLOT(setLabelText()));

    radioButtonGroup = new QButtonGroup(this);
    radioButtonGroup->addButton(personaRadioButton, persona);
    radioButtonGroup->addButton(squadraRadioButton, squadra);
    radioButtonGroup->addButton(partitaRadioButton, partita);

    if(squadre->isEmpty()){
        personaRadioButton->setEnabled(false);
        partitaRadioButton->setEnabled(false);
    }
}

void IntroPage::createLayouts(){
    mainGroup = new QGroupBox(tr("Crea nuovo:"), this);

    QVBoxLayout* buttonsLayout = new QVBoxLayout;
    buttonsLayout->addWidget(personaRadioButton);
    buttonsLayout->addWidget(squadraRadioButton);
    buttonsLayout->addWidget(partitaRadioButton);
    buttonsLayout->addStretch(1);

    mainGroup->setLayout(buttonsLayout);

    layout = new QVBoxLayout;
    layout->addWidget(mainGroup);
    layout->addWidget(helpLabel);


}

int IntroPage::nextId() const{
    switch(radioButtonGroup->checkedId()){
    case persona:
        return NewWizard::Page_Persona;
    case squadra:
        return NewWizard::Page_Squadra;
    case partita:
        return NewWizard::Page_Partita;
    default:
        return -1;
    }
}
