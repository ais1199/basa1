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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
