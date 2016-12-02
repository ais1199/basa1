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

//SIZES IS FAILING!!!
//-------------------------------------------ATTENTION!!! A LOT OF WAYS TO CREATE HOROROR
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QDir d;
    currentdir=d.currentPath()+QString("/debug/dops");
    loadobinfo();
    newobj();
    connect(ui->createbase,&QPushButton::clicked,this,&MainWindow::createDok);
    connect(ui->finish,&QPushButton::clicked,this,&MainWindow::finnewob);
    connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::updateob);
    connect(ui->adddata,&QPushButton::clicked,this,&MainWindow::addobgect);
}

void MainWindow::loadobinfo()
{
    QString n=currentdir+QString("/ob.txt");
    QFile f(n);
    obinf*cur=(struct obinf*)malloc(1*sizeof(struct obinf));
    obbase=(struct obinf*)malloc(1*sizeof(struct obinf));
    char*buf1=(char*)malloc(5*sizeof(char));
    strcpy(buf1,"char\0");
    obbase->name=buf1;
    obbase->parts=zeropart;
    obbase->size=sizeof(char*);
    obbase->next=cur;
    buf1=(char*)malloc(4*sizeof(char*));
    strcpy(buf1,"int\0");
    cur->name=buf1;
    cur->parts=zeropart;
    cur->size=sizeof(int);
    cur->next=zeroobinf;
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
                cur->next=(struct obinf*)malloc(1*sizeof(struct obinf));
                cur=cur->next;
                cur->next=zeroobinf;
                cur->parts=zeropart;
                cur->name=(char*)malloc((k-4)*sizeof(char));
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
                part*curp=(struct part*)malloc(1*sizeof(struct part));
                cur->parts=curp;
                curp->size=0;
                while(f.readLine(buf,128))
                {
                    if(buf[0]!=' ')break;
                    if(curp->size)
                    {
                        curp->next=(struct part*)malloc(1*sizeof(struct part));
                        curp=curp->next;
                    }
                    curp->next=zeropart;
                    bb=QString(buf);
                    cc=bb.section("\r",0,0);
                    aa=cc.section("|",2,2);
                    curp->size=aa.toInt(&ok,10);
                    if(curp->size==0)exit(44);//----------------------------------------44

                    bb=cc.section(" ",1,1);
                    aa=bb.section("|",0,0);
                    curp->tipe=makechar(aa);
                    aa=bb.section("|",1,1);
                    curp->name=makechar(aa);

                }
            }
        }
        f.close();
        dada.baza=obbase;
        dada.zerobase=zeroobinf;
        dada.zeroob=zerodata;
        dada.zeropart=zeropart;
    }
    else
    {
        exit(11);//----------------------------------------------------------------------11
    }

}

void MainWindow::newobj()
{
    newob=(struct obinf *)malloc(1*sizeof(struct obinf));
    //newob->parts=(struct part *)malloc(1*sizeof(struct part));
    curpart=zeropart;
    newob->next=zeroobinf;
}

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

void MainWindow::givesize()
{
    int s=0;
    part*uk;
    for(uk=newob->parts;uk!=zeropart;uk=uk->next)
    {
        s+=uk->size;
    }
    newob->size=s;
}

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
        part*cup=newob->parts;
        char i='|';
        char p=' ';
        while(cup!=zeropart)
        {
            f.write(&p,1);
            f.write(cup->tipe,strlen(cup->tipe));
            f.write(&i,1);
            f.write(cup->name,strlen(cup->name));
            f.write(&i,1);
            intt=dada.toChar(cup->size);
            f.write(intt,strlen(intt));
            free(intt);
            f.write(stend,2);
            cup=cup->next;

        }
        f.write(stend,2);

    }
    else
    {
        exit(111);
    }
    f.close();
    obinf*cur=lastobinf();
    cur->next=newob;
    newobj();
}

obinf* MainWindow::lastobinf()
{
    obinf*tata;
    for(tata=obbase;tata->next!=zeroobinf;tata=tata->next)
    {

    }
    return tata;
}

void MainWindow::updateob()
{
    if(curpart==zeropart)
    {
        newob->parts=(struct part *)malloc(1*sizeof(struct part));
        curpart=newob->parts;
    }
    else
    {
        curpart->next=(struct part *)malloc(1*sizeof(struct part));
        curpart=curpart->next;
    }
    curpart->next=zeropart;
    curpart->tipe=makechar(ui->newobtipe->text());
    curpart->name=makechar(ui->newobname->text());
    curpart->size=sizeofob(curpart->tipe);
}

int MainWindow::sizeofob(char*name)
{
    obinf*cu=obbase;
    for(;cu!=zeroobinf;cu=cu->next)
    {
        if(QString(name)==QString(cu->name))
        {
            return cu->size;
        }
    }

    return 0;
}
//-----------------------------------------------------------PART2!!!!!!!!!!!!!!!
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

    nwba=zerodata;
}



void MainWindow::addobgect()
{
    if(nwba==zerodata)
    {
        curbast=(struct ob*)malloc(sizeof(struct ob));
        nwba=curbast;
    }
    else
    {
        nwba->next=(struct ob*)malloc(sizeof(struct ob));
        nwba=nwba->next;        
    }
    nwba->next=zerodata;
    nwba->data=malloc(cot->size);
    reading= QString(ui->data->toPlainText());
    cursor=0;
    cursor2=0;
    putdata(cot->parts,nwba->data);
    tester();
    //save();
    //connect(ui->savenew,&QPushButton::clicked,this,&MainWindow::save);
}

void MainWindow::putdata(part *wp, void *data)
{
    char a[]="int";
    char b[]="char";
    bool ok;
    //void*d;
    //char *u;
    obinf*nana;
    QString s;
    QString c=QString("\n");
    //int*i;
    int prov;
    char *provc;
    //QPlainTextEdit
    if(wp!=zeropart)
    {
        s=reading.section(c,cursor,cursor);
        if(0==strcmp(a,wp->tipe))
        {
            //i=(int*)malloc(sizeof(int));
            *((int*)(data+cursor2))=s.toInt(&ok,10);//remont!!!
            /*data=(int*)i;
            d=data+sizeof(int*);//-------------------тут зарыта фигня!*/
            prov=*((int*)data);
            cursor++;
            cursor+=sizeof(int);
        }
        else
        {
            if(0==strcmp(b,wp->tipe))
            {
                ((char*)(data+cursor2)))=makechar(s);
                provc=((char*)(data+cursor2));
                cursor2+=sizeof(char*);
                cursor++;
            }
            else
            {
                nana=dada.fo(wp->tipe);
                if(nana!=zeroobinf)
                {
                    if(nana->parts!=zeropart) putdata(nana->parts,data);

                }
                //d=data+nana->size;
            }
        }
        putdata(wp->next,data);
    }
}

void MainWindow::save()
{
    QString c=currentdir+QString("/")+ui->nbplase->text()+QString(".txt");
    dada.pinf(c,curbast,cot);
}

void MainWindow::tester()
{
    ob*pi=curbast;
    void*data;
    int i;
    //zi=0;
    char*j;
    while(pi!=zerodata)
    {
        data=pi->data;
        i=*((int*)data);
        //data+=sizeof(int*);

        j=((char*)(data+sizeof(int)));
        pi=pi->next;
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
