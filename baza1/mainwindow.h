#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sample.h"
//#include <vector>
//using namespace std;



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void newobj();
    void finnewob();
    void updateob();
    void loadobinfo();
    void givesize();
    int sizeofob(char*);

    void createDok();

    void tester();

    Sample dada;
    void addobgect();
    int ctsize;
    int curbsize;
    vector<void*>curbast;
    int nwba;
    //ob*zerodata;
    //obinf*fo(char*);
    obinf*cot;
    void putdata(int,obinf*,void*);
    QString reading;
    int cursor;
    int cursor2;

    //void set_int(void *base, int sizes[], int field_index, int value);

    void tdp();
    void showdata(int, bool);
    void pd(int,obinf*,void*,bool);
    void upd();

    void nxt1();
    void prv1();

    void save();
    void load();
    char* makechar(QString);
    obinf *newob;
    vector<obinf*> *obbase;
    obinf *zeroobinf;
    //obinf *lastobinf();
    part*zeropart;
    part *curpart;
    QString currentdir;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void pa(int);


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
