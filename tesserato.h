#ifndef TESSERATO_H
#define TESSERATO_H

#include <QString>
#include <QDate>
#include "eccezioni.h"

class Tesserato
{
private:
  QString nome;
  QString cognome;
  QDate dataNascita;

  bool checked;

protected:
  Tesserato(const QString& nome, const QString& cognome, const QDate& nascita);
  Tesserato();
  Tesserato(const Tesserato& t);

public:
  virtual ~Tesserato() {}

  QString getNome() const;
  QString getCognome() const;
  QDate getData() const;
  void setNome(const QString& _nome);
  void setCognome(const QString& _cognome);
  void setData(const QDate& nascita);

  virtual void modifica(const Tesserato& t);

  Tesserato& operator =(const Tesserato& t);

  bool operator ==(const Tesserato& t) const;
  bool operator !=(const Tesserato& t) const;
  bool operator <(const Tesserato& t) const;
  bool operator <=(const Tesserato& t) const;
  bool operator >(const Tesserato& t) const;
  bool operator >=(const Tesserato& t) const;

  void setChecked(const bool& b);
  bool isChecked() const;

  virtual QString getInfo() const;
  virtual void ammonito (const bool& add =true) throw (Err_Ammonizione) =0;
  virtual void add2Minuti (int x =1) throw (Err_DueMinuti) =0;
  virtual void escluso (const bool& add =true) throw (Err_Esclusione) =0;
  virtual bool isAmmonito () const =0;
  virtual int get2Minuti () const =0;
  virtual bool isEscluso () const =0;
  virtual void reset() =0;

};

#endif // TESSERATO_H
