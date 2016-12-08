#ifndef SAMPLE_H
#define SAMPLE_H

#include <QString>
#include <QFile>
#include <vector>
using namespace std;
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
    //part*next;
};

struct obinf
{
    char * name;
    int size;
    vector<part> parts;
};

class Sample
{
public:
    Sample();
    void pinf(QString,vector<void*>,obinf*);
    void pinfrec(int,obinf*);
    char* toChar(int);
    obinf* fo(char*);
    vector<obinf*> baza;
    //obinf*curobinf;
    obinf* zerobase;
    int place;
    void*whattoput;
    //ob*zeroob;
    //part*zeropart;
    int pointer;
    QFile*f;
};

#endif // SAMPLE_H
