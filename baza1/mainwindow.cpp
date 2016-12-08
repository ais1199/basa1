#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QDir>
#include <QString>
#include <QLineEdit>
#include <QChar>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QPlainTextEdit>

//---------------------------------------------Remaid in vectors
//SIZES IS FAILING!!!

//Запуск виджета в исходном виде.
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QDir d;
    currentdir=d.currentPath()+QString("/debug/dops");
    dada.baza.resize(0);
    obbase=&(dada.baza);
    zeroobinf=dada.zerobase;
    //curbsize=0;
    loadobinfo();
    newob=(struct obinf *)malloc(1*sizeof(struct obinf));
    //newobj();
    connect(ui->createbase,&QPushButton::clicked,this,&MainWindow::createDok);
    connect(ui->finish,&QPushButton::clicked,this,&MainWindow::finnewob);
    connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::updateob);
    connect(ui->adddata,&QPushButton::clicked,this,&MainWindow::addobgect);
}
//Загрузка информации об уже созданных типах
void MainWindow::loadobinfo()
{
    QString n=currentdir+QString("/ob.txt");
    QFile f(n);

    obinf*cur=(struct obinf*)malloc(1*sizeof(struct obinf));
    char*buf1;
    buf1=(char*)malloc(5*sizeof(char));
    strcpy(buf1,"char\0");
    cur->name=buf1;
    cur->size=sizeof(char*);
    obbase->push_back(cur);

    buf1=(char*)malloc(4*sizeof(char*));
    strcpy(buf1,"int\0");
    cur=(struct obinf*)malloc(1*sizeof(struct obinf));
    cur->name=buf1;
    cur->size=sizeof(int);
    obbase->push_back(cur);
    /*cur->next=(struct obinf*)malloc(1*sizeof(struct obinf));
    cur=cur->next;
    buf1=(char*)malloc(6*sizeof(char));
    strcpy(buf1,"obinf\0");
    cur->name=buf1;
    cur->size=sizeof(struct obinf);
    cur->parts=(struct parts*)malloc(1*(sizeof(struct parts)));
    part*p=cur->parts;
    buf1=(char*)malloc(5*sizeof(char));
    strcpy(buf1,"name\0");
    p->name=buf1;
    //buf1=(char*)malloc(5*sizeof(char));
    //strcpy(buf1,"char\0");
    p->tipe=obbase->name;
    p->size=obbase->size;
    p->next=(struct parts*)malloc(1*(sizeof(struct parts)));
    p=p->next;
    p->tipe=obbase->next->name;
    p->size=obbase->next->size;
    buf1=(char*)malloc(5*sizeof(char));
    strcpy(buf1,"size\0");
    p->name=buf1;
    */

    if(f.open(QIODevice::ReadOnly))
    {
        char buf[128];
        int k=0;
        bool ok;
        QString aa,bb,cc,i;
        while(!f.atEnd())
        {
            f.readLine(buf,128);
            bb=QString(buf);
            cc=bb.section("\r",0,0);
            aa=cc.section(" ",0,0);
            if(aa==QString("name"))
            {
                for(k=5;buf[k]!='\r';k++)
                {
                    if(buf[k]==' ')break;
                }
                buf[k]='\0';
                cur=(struct obinf*)malloc(1*sizeof(struct obinf));
                cur->name=(char*)malloc((k-4)*sizeof(char));
                obbase->push_back(cur);
                strcpy(cur->name,(buf+5));
            }

            i=cc.section(" ",1,1);
            if(aa==QString("size"))
            {
                cur->size=i.toInt(&ok,10);
                if(cur->size==0)exit(33);//________________________________________________33
            }
            if(cc==QString("consist"))
            {
                //part*curp=(struct part*)malloc(1*sizeof(struct part));
                vector<part>*curp=&(cur->parts);
                part pp;
                //curp->size=0;
                while(f.readLine(buf,128))
                {
                    if(buf[0]!=' ')break;
                    /*if(curp->size)
                    {
                        curp->next=(struct part*)malloc(1*sizeof(struct part));
                        curp=curp->next;
                    }
                    curp->next=zeropart;*/

                    bb=QString(buf);
                    cc=bb.section("\r",0,0);
                    aa=cc.section("|",2,2);
                    pp.size=aa.toInt(&ok,10);
                    if(pp.size==0)exit(44);//----------------------------------------44

                    bb=cc.section(" ",1,1);
                    aa=bb.section("|",0,0);
                    pp.tipe=makechar(aa);
                    aa=bb.section("|",1,1);
                    pp.name=makechar(aa);
                    curp->push_back(pp);
                }
            }
        }
        f.close();
        //dada.baza=obbase;
        //dada.zerobase=zeroobinf;
        //dada.zeroob=zerodata;
        //dada.zeropart=zeropart;
    }
    else
    {
        exit(11);//----------------------------------------------------------------------11
    }

}

/*
//подготовка для создания нового типа структур (выполняется всегда);
void MainWindow::newobj()
{

    //newob->parts=(struct part *)malloc(1*sizeof(struct part));
    //curpart=zeropart;
    //newob->next=zeroobinf;
}*/
//делает из КуСтринг обячную строку.
char* MainWindow::makechar(QString text)
{
    int n=text.size();
    QChar *kuchar=text.data();
    char*res=(char*)malloc((n+1)*sizeof(char));
    int i;
    QChar dop;
    for(i=0;i<n;i++)
    {
        dop=kuchar[i];
        res[i]=dop.toLatin1();
    }
    res[n]='\0';
    return res;
}

//определяет размер создаваемого типа структуры
void MainWindow::givesize()
{
    int s=0;
    int j;
    vector<part>uk=newob->parts;
    part pp;
    for(j=0;j<uk.size();j++)
    {
        pp=uk[j];
        s+=pp.size;
    }
    newob->size=s;
}
//реакция на кнопку "Добавить Объект". Не доработано. Могут быть баги!
void MainWindow::finnewob()
{
    newob->name=makechar(ui->newob->text());
    givesize();

    QString n=currentdir+QString("/ob.txt");
    QFile f(n);
    char*intt;
    if(f.open(QIODevice::Append))
    {
        char buff[]="name \0";
        char stend[]="\r\n";
        f.write(buff,strlen(buff));
        f.write(newob->name,strlen(newob->name));
        f.write(stend,2);
        char buf2[]="size \0";
        f.write(buf2,5);
        intt=dada.toChar(newob->size);
        f.write(intt,strlen(intt));
        free(intt);
        f.write(stend,2);
        char cons[]="consist\r\n";
        f.write(cons,9);
        vector<part> pp=newob->parts;
        part cup;
        int ii;
        char i='|';
        char p=' ';
        for(ii=0;ii<pp.size();ii++)
        {
            cup=pp[ii];
            f.write(&p,1);
            f.write(cup.tipe,strlen(cup.tipe));
            f.write(&i,1);
            f.write(cup.name,strlen(cup.name));
            f.write(&i,1);
            intt=dada.toChar(cup.size);
            f.write(intt,strlen(intt));
            free(intt);
            f.write(stend,2);
            //cup=cup->next;
        }
        f.write(stend,2);

    }
    else
    {
        exit(111);
    }
    f.close();
    //obinf*cur=lastobinf();
    obbase->push_back(newob);
    newob=(struct obinf *)malloc(1*sizeof(struct obinf));
    //newobj();
}
/*
//находит хвост цепочки структур обинф.
obinf* MainWindow::lastobinf()
{
    obinf*tata;
    for(tata=obbase;tata->next!=zeroobinf;tata=tata->next)
    {

    }
    return tata;
}*/
//реакция на кнопку "добавить подобъект"
void MainWindow::updateob()
{
    /*if(curpart==zeropart)
    {
        newob->parts=(struct part *)malloc(1*sizeof(struct part));
        curpart=newob->parts;
    }
    else
    {
        curpart->next=(struct part *)malloc(1*sizeof(struct part));
        curpart=curpart->next;
    }*/
    part pp;
    //curpart->next=zeropart;
    pp.tipe=makechar(ui->newobtipe->text());
    pp.name=makechar(ui->newobname->text());
    pp.size=sizeofob(pp.tipe);
    newob->parts.push_back(pp);
}
//определяет размер типа по его имени
int MainWindow::sizeofob(char*name)
{
    int i;
    vector<obinf*> zu=*(obbase);
    obinf*cu;
    for(i=0;i<zu.size();i++)
    {
        cu=zu[i];
        if(QString(name)==QString(cu->name))
        {
            return cu->size;
        }
    }

    return 0;
}
//-----------------------------------------------------------PART2!!!!!!!!!!!!!!!
//записывает имя и тип новой базы. с которой будет вестись работа
void MainWindow::createDok()
{
    //QString n = currentdir+QString("/")+ui->nbplase->text()+QString(".txt");
    //QFile f(n);
    char*ii=makechar(ui->nbtipe->text());
    char r[]="\r\n";
    cot=dada.fo(ii);
    if(cot==zeroobinf)exit(252);
    QString*st1= new QString(ui->nbplase->text());
    QString*st2= new QString(ui->nbtipe->text());
    ui->Curbase->setText(*st1);
    ui->Curbasetipe->setText(*st2);

    nwba=0;
    curbast.resize(0);
}

//добавить в базу элемент
void MainWindow::addobgect()
{
    void*n;
    /*if(nwba==0)
    {

        nwba=curbast;
    }
    else
    {
        nwba->next=(struct ob*)malloc(sizeof(struct ob));
        nwba=nwba->next;        
    }*/
    //nwba->next=zerodata;
    n=malloc(cot->size);
    curbast.push_back(n);
    reading= QString(ui->data->toPlainText());
    cursor=0;
    cursor2=0;
    putdata(0,cot,n);
    //tester();
    //save();
    connect(ui->savenew,&QPushButton::clicked,this,&MainWindow::save);
}
//рекурсивная функция записи данных
void MainWindow::putdata(int n,obinf*inf, void *data)
{
    vector<part> urur=inf->parts;
    if(n<urur.size())
    {
        char a[]="int";
        char b[]="char";
        bool ok;
        //void*d;
        char *u;
        part pp=urur[n];
        //vector<part> pp=inf->parts;
        obinf*nana;
        QString s;
        QString c=QString("\n");
        //int*i;
        int prov;
        char *provc;
        //QPlainTextEdit
        s=reading.section(c,cursor,cursor);
        if(0==strcmp(a,pp.tipe))
        {
            *((int*)(data+cursor2))=s.toInt(&ok,10);

            prov=*((int*)data);
            cursor++;
            cursor2+=sizeof(int);
        }
        else
        {
            if(0==strcmp(b,pp.tipe))
            {
                u=(makechar(s));
                *((char**)(data+cursor2))=u;
                provc=*((char**)(data+cursor2));
                cursor2+=sizeof(char*);
                cursor++;
            }
            else
            {
                nana=dada.fo(pp.tipe);
                if(nana!=zeroobinf)
                {
                    putdata(0,nana,data);

                }
                //d=data+nana->size;
            }
        }
        putdata(n+1,inf,data);
    }
}
//реакция на кнопку "сохранить"
void MainWindow::save()
{
    QString c=currentdir+QString("/")+ui->nbplase->text()+QString(".txt");
    dada.pinf(c,curbast,cot);
}
//тестер
void MainWindow::tester()
{
    int k;
    void*data;
    int i;
    //zi=0;
    char*j;
    for(k=0;k<curbast.size();)
    {
        data=curbast[k];
        i=*((int*)data);
        //data+=sizeof(int*);

        j=*((char**)(data+sizeof(int)));
        k++;
    }
}

/**
 * @brief get_int достаёт int из записи в БД
 * @param base указатель на начало записи
 * @param sizes массив размеров полей записи
 * @param field_index индекс нужного поля в БД
 * @return числовое значение нужного поля
 */
/*
int get_int(void *base, int sizes[], int field_index)
{
    int offset = 0;
    for(int i = 0; i < field_index - 1; ++i) {
        offset += sizes[i];
    }
    return *((int*)(base + offset));
}

void set_int(void *base, int sizes[], int field_index, int value)
{
    int offset = 0;
    for(int i = 0; i < field_index - 1; ++i) {
        offset += sizes[i];
    }
    *((int*)(base + offset)) = value;
}

char * get_str(void *base, int sizes[], int field_index)
{
    int offset = 0;
    for(int i = 0; i < field_index - 1; ++i) {
        offset += sizes[i];
    }
    return (base + offset);
}
*/


MainWindow::~MainWindow()
{
    delete ui;
}
