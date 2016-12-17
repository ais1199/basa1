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
#include <QListWidget>
#include <QSpinBox>
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
    loadobinfo();
    newob=(struct obinf *)malloc(1*sizeof(struct obinf));
    ui->example->setReadOnly(true);
    ui->datalist->setReadOnly(true);
    ui->nplist->setReadOnly(true);
    ui->mainlist->setReadOnly(true);
    ui->spinBox->setMinimum(1);
    connect(ui->createbase,&QPushButton::clicked,this,&MainWindow::createDok);
    connect(ui->finish,&QPushButton::clicked,this,&MainWindow::finnewob);
    connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::updateob);
    connect(ui->adddata,&QPushButton::clicked,this,&MainWindow::addobgect);
    connect(ui->loadbase,&QPushButton::clicked,this,&MainWindow::load);
    connect(ui->freelist,&QPushButton::clicked,this,&MainWindow::fpl);
    connect(ui->delob,&QPushButton::clicked,this,&MainWindow::fsp);
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
                vector<part>*curp=&(cur->parts);
                part pp;
                while(f.readLine(buf,128))
                {
                    if(buf[0]!=' ')break;
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
    }
    else
    {
        ui->status->setText("список баз пуст");
    }

}

void MainWindow::updmlist()
{
    int i,j,d;
    vector<obinf*> m=*obbase;
    int dop=m.size();
    vector<part> pa;
    part pp;
    obinf* bas;
    ui->mainlist->clear();
    QString wr;
    for(i=0;i<dop;i++)
    {
        bas=m[i];
        wr=QString(bas->name)+QString(":\n");
        ui->mainlist->insertPlainText(wr);
        pa=bas->parts;
        d=pa.size();
        for(j=0;j<d;j++)
        {
            pp=pa[j];
            wr=QString("  ")+QString(pp.name)+QString("(")+QString(pp.tipe)+QString(")\n");
            ui->mainlist->insertPlainText(wr);
        }
    }
}

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
    int dop=uk.size();
    for(j=0;j<dop;j++)
    {
        pp=uk[j];
        s+=pp.size;
    }
    newob->size=s;
}
//реакция на кнопку "Добавить Объект"
void MainWindow::finnewob()
{
    newob->name=makechar(ui->newob->text());
    givesize();

    QString n=currentdir+QString("/ob.txt");
    QFile f(n);
    char*intt;
    if(zeroobinf!=dada.fo(newob->name))
    {
        ui->status->setText(QString("такой объект уже есть в списке"));
    }
    else
    {
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
            int dop=pp.size();
            for(ii=0;ii<dop;ii++)
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
            obbase->push_back(newob);//___________________________chtnging is heare!
            //ui->olist->addItem();
            ui->status->setText(QString("нет ошибок"));
            ui->nplist->clear();
            ui->newob->clear();
            updmlist();
        }
        else
        {
            ui->status->setText(QString("Не удолось обновить фаил."));
        }
        f.close();
        newob=(struct obinf *)malloc(1*sizeof(struct obinf));
    }

}
//реакция на кнопку "добавить подобъект"
void MainWindow::updateob()//--------------------------------тут еще туча изменений
{
    part pp,ii;
    vector<part> v=newob->parts;
    pp.tipe=makechar(ui->newobtipe->text());
    pp.name=makechar(ui->newobname->text());
    pp.size=sizeofob(pp.tipe);
    int i;
    int dop=v.size();
    for(i=0;i<dop;i++)
    {
        ii=v[i];
        if(0==strcmp(ii.name,pp.name))break;
    }
    if(i==dop)
    {
        if(pp.size==0)
        {
           free(pp.tipe);
           free(pp.name);
           ui->status->setText(QString("такого объекта не существует"));
        }
        else
        {
            newob->parts.push_back(pp);
            ui->status->setText(QString("ошибок нет"));
            ui->newobname->clear();
            tdp();
            connect(ui->delob,&QPushButton::clicked,this,&MainWindow::fsp);
        }

    }
    else
    {
        ui->status->setText(QString("в создаваемом объекте уже есть элемент с таким именем"));
    }
}
//обновление списка того, что есть в создаваемой величине
void MainWindow::tdp()
{
    int i,dop;
    dop=newob->parts.size();
    vector<part> pp=newob->parts;
    ui->nplist->clear();
    QString wtp;
    part ogo;
    for(i=0;i<dop;i++)
    {
        ogo=pp[i];
        wtp=QString(ogo.name)+QString(" (")+QString(ogo.tipe)+QString(")\n");
        ui->nplist->insertPlainText(wtp);
    }
}
//free newobj parts list
void MainWindow::fpl()
{
    newob->parts.resize(0);
    ui->nplist->clear();
    ui->status->setText("нет ошибок");
}
//free pointed part in newobjlist
void MainWindow::fsp()
{
    int i,j,dop;
    dop=newob->parts.size();
    vector<part> *pp=&(newob->parts);
    part ou;
    char*u=makechar(ui->namembr->text());
    for(i=0;i<dop;i++)
    {
        ou=(*pp)[i];
        if(0==strcmp(u,ou.name))break;
    }
    if(i==dop)
    {
        ui->status->setText("такого подобъекта нет");//почему-то выводит именно это, а в остальном воркает

    }
    else
    {
        ui->status->setText("нет ошибок");
        ui->namembr->clear();
        for(j=i;j<dop-1;j++)
        {
            (*pp)[j]=(*pp)[j+1];
        }
        newob->parts.resize(dop-1);
        tdp();
    }
}

//определяет размер типа по его имени
int MainWindow::sizeofob(char*name)
{
    int i;
    vector<obinf*> zu=*(obbase);
    obinf*cu;
    int dop=zu.size();
    for(i=0;i<dop;i++)
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
    char*ii=makechar(ui->nbtipe->text());
    cot=dada.fo(ii);
    if(cot==zeroobinf)exit(252);
    QString*st1= new QString(ui->nbplase->text());
    QString*st2= new QString(ui->nbtipe->text());
    ui->Curbase->setText(*st1);
    ui->Curbasetipe->setText(*st2);
    ui->example->clear();
    wrex(cot);
    nwba=0;
    curbast.resize(0);
    ui->status2->setText("нет ошибок");
}
//выводит подсказку для нового объекта
void MainWindow::wrex(obinf*inf)
{
    vector<part> pp=inf->parts;
    QString wr=QString(inf->name)+QString(":\n");
    ui->example->insertPlainText(wr);
    part pa;
    //char*u;
    char a[]="int";
    char b[]="char";
    int i;
    obinf*nana;
    int dop=pp.size();
    for(i=0;i<dop;i++)
    {
        pa=pp[i];
        if(0==strcmp(a,pa.tipe))
        {
            wr=QString(pa.name)+QString("(int)\n");
            ui->example->insertPlainText(wr);
        }
        else
        {
            if(0==strcmp(b,pa.tipe))
            {
                wr=QString(pa.name)+QString("(char)\n");
                ui->example->insertPlainText(wr);
            }
            else
            {
                nana=dada.fo(pa.tipe);
                if(nana!=zeroobinf)
                {
                    wrex(nana);

                }
            }
        }
    }
}



//добавить в базу элемент
void MainWindow::addobgect()
{
    void*n;
    n=malloc(cot->size);
    curbast.push_back(n);
    reading= QString(ui->data->toPlainText());
    cursor=0;
    cursor2=0;
    putdata(0,cot,n);
    ui->lim1->setText(QString(dada.toChar(curbast.size())));
    showdata(curbast.size()+1,true);
    connect(ui->savenew,&QPushButton::clicked,this,&MainWindow::save);
    ui->status2->setText("нет ошибок");
}
//рекурсивная функция записи данных
void MainWindow::putdata(int n,obinf*inf, void *data)
{
    vector<part> urur=inf->parts;
    int dop=urur.size();
    if(n<dop)
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
        s=reading.section(c,cursor,cursor);
        if(0==strcmp(a,pp.tipe))
        {
            *((int*)(data+cursor2))=s.toInt(&ok,10);
            cursor++;
            cursor2+=sizeof(int);
        }
        else
        {
            if(0==strcmp(b,pp.tipe))
            {
                u=(makechar(s));
                *((char**)(data+cursor2))=u;
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
            }
        }
        putdata(n+1,inf,data);
    }
}
//реакция на кнопку "сохранить"
void MainWindow::save()
{
    QString c=currentdir+QString("/")+ui->Curbase->text()+QString(".txt");
    dada.pinf(c,curbast,cot);
    ui->status2->setText("сохранено");
}
//тестер
/*
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
*/
//загрузить базу
void MainWindow::load()
{
    QString*st1= new QString(ui->nbplase->text());
    QString c=currentdir+QString("/")+*st1+QString(".txt");
    QFile f(c);
    char buf[128];
    if(f.open(QIODevice::ReadOnly))
    {
        f.readLine(buf,128);
        f.close();
        if(dada.fo(buf)!=zeroobinf)
        {
            QString*st2= new QString(buf);
            ui->Curbase->setText(*st1);
            ui->Curbasetipe->setText(*st2);
            curbast.resize(0);
            dada.loading(c,&curbast);
            cot=dada.fo(buf);

            connect(ui->savenew,&QPushButton::clicked,this,&MainWindow::save);
            showdata(curbast.size(),true);
            ui->lim1->setText(QString(dada.toChar(curbast.size())));
            connect(ui->spinBox,SIGNAL(valueChanged(int)),this,SLOT(pa(int)));
            wrex(cot);
            ui->status2->setText("нет ошибок");
        }
    }
    else
    {
        ui->status2->setText("ошибка загрузки");
    }
}
//------------------------------------функция, реагирующая на изменение
void MainWindow::pa(int point)
{
    showdata(point,true);
    ui->status2->setText("нет ошибок");
}

//_________________________________стартовая функция для того, чтобы показать фрагмент из базы данных
void MainWindow::showdata(int nomber,bool where)
{
    //vector<part> pp=cot->parts;
    int i=nomber-1;
    int limit;
    if(i<0)i=0;
    if(where)
    {
        limit=curbast.size();
        ui->spinBox->setMaximum(limit);
        ui->datalist->clear();
        if(i>=limit)i=limit-1;
        cursor2=0;
        cursor=0;
        ui->spinBox->setValue(nomber);
        ui->datalist->insertPlainText(QString("\n"));
        pd(0,cot,curbast[i],true);
    }

}
//----------------------------------------------------------рекурсивная функция для вывода данных
void MainWindow::pd(int n, obinf *inf, void *data, bool where)
{
    vector<part> urur=inf->parts;
    int dop=urur.size();
    if(n<dop)
    {

        char a[]="int";
        char b[]="char";
        //bool ok;
        char *u;
        part pp=urur[n];
        obinf*nana;
        QString s;
        QString c=QString("\n");
        QString d,bb;
        int i;
        for(i=0;i<cursor;i++)
        {
            d+=QString(" ");
        }
        d=QString(pp.name)+QString(": ");
        if(where)
        {
            ui->datalist->insertPlainText(d);
        }
        if(0==strcmp(a,pp.tipe))
        {
            i=*((int*)(data+cursor2));
            bb=QString(dada.toChar(i))+c;
            if(where)ui->datalist->insertPlainText(bb);
            cursor2+=sizeof(int);
        }
        else
        {
            if(0==strcmp(b,pp.tipe))
            {
                u=*((char**)(data+cursor2));
                bb=QString(u)+c;
                if(where)ui->datalist->insertPlainText(bb);
                cursor2+=sizeof(char*);
            }
            else
            {
                nana=dada.fo(pp.tipe);
                if(nana!=zeroobinf)
                {
                    pd(0,nana,data,where);

                }
            }
        }
        pd(n+1,inf,data,where);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
