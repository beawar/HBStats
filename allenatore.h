#ifndef ALLENATORE_H
#define ALLENATORE_H

#include "tesserato.h"
#include "eccezioni.h"

class Allenatore : public Tesserato
{
private:
    bool ammonizione;
    int dueMinuti;
    bool esclusione;
public:
    static unsigned int max2Minuti;

    Allenatore(const QString& nome="", const QString& cognome="", const QDate& nascita=QDate::currentDate());
    Allenatore(const Allenatore& a);

    virtual bool isAmmonito () const;
    virtual int get2Minuti () const;
    virtual bool isEscluso () const;

    virtual void ammonito (const bool& add =true) throw (Err_Ammonizione);
    virtual void add2Minuti (int x=1) throw (Err_DueMinuti);
    virtual void escluso (const bool& add =true) throw (Err_Esclusione);

    Allenatore& operator =(const Allenatore& a);

    virtual QString getInfo() const;
    virtual void reset();
};



#endif // ALLENATORE_H
