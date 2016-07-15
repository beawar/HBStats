#include "tesserato.h"

Tesserato::Tesserato() {}

Tesserato::Tesserato(const QString& nome, const QString& cognome, const QDate& nascita)
  : nome(nome), cognome(cognome), dataNascita(nascita), checked(false) {}

Tesserato::Tesserato(const Tesserato &t)
    : nome(t.nome), cognome(t.cognome), dataNascita(t.dataNascita), checked(t.checked){}

QString Tesserato::getNome() const{
  return nome;
}

QString Tesserato::getCognome() const{
  return cognome;
}

QDate Tesserato::getData() const{
  return dataNascita;
}

void Tesserato::setNome(const QString& _nome){
  nome=_nome;
}

void Tesserato::setCognome(const QString &_cognome){
   cognome=_cognome;
}

void Tesserato::setData(const QDate &nascita){
  dataNascita=nascita;
}

void Tesserato::modifica(const Tesserato &t){
    if(*this != t){
        if(nome != t.nome){
            setNome(t.nome);
        }
        if(cognome != t.cognome){
            setCognome(t.cognome);
        }
        if(dataNascita != t.dataNascita){
            setData(t.dataNascita);
        }
    }
}

Tesserato& Tesserato::operator =(const Tesserato& t){
    nome = t.nome;
    cognome = t.cognome;
    dataNascita = t.dataNascita;
    checked = t.checked;
    return *this;
}

bool Tesserato::operator ==(const Tesserato& t) const{
    return nome==t.nome && cognome==t.cognome && dataNascita==t.dataNascita;
}

bool Tesserato::operator !=(const Tesserato& t) const{
    return !(operator ==(t));
}

bool Tesserato::operator <(const Tesserato& t) const{
    if(cognome<t.cognome){
        return true;
    }
    else if(cognome==t.cognome && nome<t.nome){
        return true;
    }
    else if(cognome==t.cognome && nome==t.nome && dataNascita<t.dataNascita){
        return true;
    }
    else{
        return false;
    }
}

bool Tesserato::operator <=(const Tesserato& t) const{
    return (operator <(t)) || (operator ==(t));
}

bool Tesserato::operator >(const Tesserato& t) const{
    return !(operator <=(t));
}

bool Tesserato::operator >=(const Tesserato& t)const{
    return !(operator <(t));
}

void Tesserato::setChecked(const bool & b){
    checked = b;
}

bool Tesserato::isChecked() const{
    return checked;
}

QString Tesserato::getInfo() const{
    QString info;
    info.append(getCognome() + " ");
    info.append(getNome() + " ");
    return info;
}
