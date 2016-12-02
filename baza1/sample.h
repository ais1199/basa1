#ifndef SAMPLE_H
#define SAMPLE_H

#include <QString>
#include <QFile>
//int square(int x);

struct ob
{
    void*data;
    ob*next;
};

struct part
{
    char*tipe;
    char*name;
    int size;
    part*next;
};

struct obinf
{
    char * name;
    int size;
    part*parts;
    obinf*next;
};

class Sample
{
public:
    Sample();
    void pinf(QString,ob*,obinf*);
    void pinfrec(part*);
    char* toChar(int);
    obinf* fo(char*);
    obinf* baza;
    obinf* zerobase;
    void*whattoput;
    ob*zeroob;
    part*zeropart;
    int pointer;
    QFile*f;
};

#endif // SAMPLE_H
