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
#include <QDialog>
#include <QFileDialog>
//Запуск виджета в исходном виде.
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    printf("MWStart\n");
    ui->setupUi(this);
    QDir d;
    currentdir=d.currentPath()+QString("/debug/dops");
    dada.baza.resize(0);
    obbase=&(dada.baza);
    zeroobinf=dada.zerobase;
    loadobinfo();
    printf("afterloading\n");
    newob=(struct obinf *)malloc(1*sizeof(struct obinf));
    ui->example->setReadOnly(true);
    ui->datalist->setReadOnly(true);
    ui->datalist2->setReadOnly(true);

    ui->nplist->setReadOnly(true);
    ui->mainlist->setReadOnly(true);
    ui->spinBox->setMinimum(1);
    ui->spinBox2->setMinimum(1);
    dada.wasfound.resize(0);
    rbres=true;
    connect(ui->createbase,&QPushButton::clicked,this,&MainWindow::createDok);
    connect(ui->finish,&QPushButton::clicked,this,&MainWindow::finnewob);
    connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::updateob);
    connect(ui->adddata,&QPushButton::clicked,this,&MainWindow::addobgect);
    connect(ui->loadbase,&QPushButton::clicked,this,&MainWindow::load);
    connect(ui->freelist,&QPushButton::clicked,this,&MainWindow::fpl);
    connect(ui->delob,&QPushButton::clicked,this,&MainWindow::fsp);
    connect(ui->radioButton,SIGNAL(clicked(bool)),this,SLOT(radioreaction()));
    connect(ui->radioButton_2,SIGNAL(clicked(bool)),this,SLOT(radioreaction2()));

}
void MainWindow::radioreaction()
{
    rbres=true;
}
void MainWindow::radioreaction2()
{
    rbres=false;
}

//Загрузка информации об уже созданных типах
void MainWindow::loadobinfo()
{
    printf("loaddatabase\n");
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
    printf("tutok?\n");
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
                cur->parts=vector<part>();
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
                //cur->parts=vector<part>();
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
                    printf("eee\n");
                    cur->parts.push_back(pp);
                    printf("da ladno, chto ne tak!?\n");
                }
            }
        }
        updmlist();
    }
    else
    {
        ui->status->setText("список баз пуст");
    }
    f.close();

}
//----------------------------выписывает в большое окно список того что есть
void MainWindow::updmlist()
{
    printf("159\n");
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
    printf("187\n");
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
    printf("205\n");
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
    vector<part> pp=newob->parts;
    part pa;
    int dop=pp.size();
    int i;
    for(i=0;i<dop;i++)
    {
        pa=pp[i];
        free(pa.name);
        free(pa.tipe);
    }
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
        ou=(*pp)[i];
        free(ou.name);
        free(ou.tipe);
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
    QString st= QString(ui->nbplase->text());
    QString*st2= new QString(ui->nbtipe->text());
    QString dir=QFileDialog::getExistingDirectory(this,"Место сохранения","");
    QString*st1= new QString(dir+QString("/")+st);
    ui->Curbase->setText(*st1);
    ui->Curbasetipe->setText(*st2);
    ui->example->clear();
    wrex(cot);
    nwba=0;
    curbast.resize(0);
    ui->status2->setText("нет ошибок");
    connect(ui->serch,&QPushButton::clicked,this,&MainWindow::serch);
    connect(ui->del1,&QPushButton::clicked,this,&MainWindow::delone);
    connect(ui->opensecond,&QPushButton::clicked,this,&MainWindow::open2);
    connect(ui->spinBox,SIGNAL(valueChanged(int)),this,SLOT(pa(int)));

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
    int t=curbast.size();
    ui->lim1->setText(QString(dada.toChar(t)));
    ui->spinBox->setMaximum(t);
    if(ui->spinBox->value()==t)
    {
        showdata(t,true);
    }
    else
    {
        ui->spinBox->setValue(t);

    }
    connect(ui->savenew,&QPushButton::clicked,this,&MainWindow::save);
    connect(ui->sas1,&QPushButton::clicked,this,&MainWindow::saveas1);
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
        char *u;
        part pp=urur[n];
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
    QString c=ui->Curbase->text()+QString(".txt");
    dada.pinf(c,curbast,cot);
    ui->status2->setText("сохранено");
}

void MainWindow::saveas1()
{
    QString c=QFileDialog::getSaveFileName(this,"сохранить первую базу","")+QString(".txt");
    dada.pinf(c,curbast,cot);
    ui->status2->setText("сохранено");
}

void MainWindow::saveas2()
{
    QString c=QFileDialog::getSaveFileName(this,"сохранить вторую базу","")+QString(".txt");
    dada.pinf(c,second,cot);
    ui->status2->setText("сохранено");
}
//загрузить базу
void MainWindow::load()
{
    //QString*st1= new QString(ui->nbplase->text());
    QString c=QFileDialog::getOpenFileName(this,"открыть основной фаил","","*.txt");
    QFile f(c);
    char buf[128];
    if(f.open(QIODevice::ReadOnly))
    {
        f.readLine(buf,128);
        f.close();
        if(dada.fo(buf)!=zeroobinf)
        {
            QString*st2= new QString(buf);
            ui->Curbase->setText(c);
            ui->Curbasetipe->setText(*st2);
            curbast.resize(0);
            dada.loading(c,&curbast);
            cot=dada.fo(buf);

            connect(ui->savenew,&QPushButton::clicked,this,&MainWindow::save);
            connect(ui->sas1,&QPushButton::clicked,this,&MainWindow::saveas1);

            connect(ui->spinBox,SIGNAL(valueChanged(int)),this,SLOT(pa(int)));
            connect(ui->serch,&QPushButton::clicked,this,&MainWindow::serch);
            connect(ui->del1,&QPushButton::clicked,this,&MainWindow::delone);
            connect(ui->opensecond,&QPushButton::clicked,this,&MainWindow::open2);
            wrex(cot);
            int tarabara=curbast.size();

            ui->spinBox->setMaximum(tarabara);
            if(ui->spinBox->value()!=tarabara)ui->spinBox->setValue(tarabara);
            else
            {
                showdata(1,true);
            }
            ui->lim1->setText(QString(dada.toChar(curbast.size())));
            ui->status2->setText("нет ошибок");
        }
    }
    else
    {
        ui->status2->setText("ошибка загрузки");
    }
    f.close();
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
    int i=nomber-1;
    int limit;
    if(i<0)i=0;
    if(where)
    {
        limit=curbast.size();
        if(limit)
        {
            ui->datalist->clear();
            if(i>=limit)
            {
                i=limit-1;
            }
            cursor2=0;
            cursor=0;
            ui->lim1->setText(QString(dada.toChar(limit)));
            ui->datalist->insertPlainText(QString("\n"));
            pd(0,cot,curbast[i],true);
        }
        else
        {
            ui->datalist->clear();
            ui->lim1->setText(QString("0"));
            ui->spinBox->setMaximum(1);

        }
    }
    else
    {
        limit=second.size();
        if(limit)
        {
            ui->datalist2->clear();
            if(i>=limit)i=limit-1;
            cursor2=0;
            cursor=0;
            ui->lim2->setText(QString(dada.toChar(limit)));
            ui->datalist2->insertPlainText(QString("\n"));
            pd(0,cot,second[i],false);

        }
        else
        {
            ui->datalist->clear();
            ui->lim1->setText(QString("0"));
            ui->spinBox2->setMaximum(1);

        }
    }
    ui->status3->setText("нет ошибок");

}
//----------------------------------------------------------рекурсивная функция для вывода данных
void MainWindow::pd(int n, obinf *inf, void *data,bool where)
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
        else
        {
            ui->datalist2->insertPlainText(d);

        }
        if(0==strcmp(a,pp.tipe))
        {
            i=*((int*)(data+cursor2));
            bb=QString(dada.toChar(i))+c;
            if(where)ui->datalist->insertPlainText(bb);
            else
            {
                ui->datalist2->insertPlainText(bb);
            }
            cursor2+=sizeof(int);
        }
        else
        {
            if(0==strcmp(b,pp.tipe))
            {
                u=*((char**)(data+cursor2));
                u=u;
                bb=QString(u)+c;
                if(where)ui->datalist->insertPlainText(bb);
                else
                {
                    ui->datalist2->insertPlainText(bb);
                }
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
//-----------------------------------начать поиск
void MainWindow::serch()
{
    char*u=makechar(ui->log->text());
    dada.st=cot;
    int pat=1;
    if(rbres)
    {
        dada.sp=&curbast;
    }
    else
    {
        dada.sp=&second;
    }
    pat=dada.interpritator(u);

    int i;

    if(pat>0)
    {
        int dop=dada.wasfound.size();
        ui->lim2->setText(QString(dada.toChar(dop)));
        ui->spinBox2->setMaximum(dop);
        if(rbres)
        {
            second.resize(0);
            for(i=0;i<dop;i++)
            {
                second.push_back(curbast[((dada.wasfound)[i])]);
            }
            ui->obrab->setText(QString("Обработка основной \nбазы"));

        }
        else
        {
            vector<void*> nosta=second;
            second.resize(0);
            for(i=0;i<dop;i++)
            {
                second.push_back(nosta[((dada.wasfound)[i])]);
            }

        }
        connect(ui->del2,&QPushButton::clicked,this,&MainWindow::dellist);
        connect(ui->spinBox2,SIGNAL(valueChanged(int)),this,SLOT(ha(int)));
        connect(ui->V,&QPushButton::clicked,this,&MainWindow::obiedin);
        connect(ui->A,&QPushButton::clicked,this,&MainWindow::peresek);
        connect(ui->sas2,&QPushButton::clicked,this,&MainWindow::saveas2);


        ui->spinBox2->setMaximum(dop);
        if(dop==ui->spinBox2->value())
        {
            showdata(1,false);//--------------------------------где-то тут зарыта еще одна собака

        }
        else
        {
            ui->spinBox2->setValue(dop);

        }
    }
    else
    {
        if(pat==0)
        {
            ui->datalist2->clear();
            ui->lim2->setText(QString("0"));
            second.resize(0);
        }
        else
        {
            ui->status3->setText("ошибка в строке поиска");

        }
    }
}
//------------------------реакция на изменение во втором
void MainWindow::ha(int aa)
{
    if(aa<1)aa=1;
    showdata(aa,false);


}
//-------------------------реакция на кнопку единичного удаления
void MainWindow::delone()
{
    int n=ui->spinBox->value()-1;
    delel(n);
    int s=curbast.size();
    if(n>=s)n=s-1;
    ui->spinBox->setMaximum(n+1);
    if(ui->spinBox->value()==n+1)
    {
        showdata(n+1,true);
    }
    else
    {
        ui->spinBox->setValue(n+1);
    }
}
//---------------------------------функция удаления элемента
void MainWindow::delel(int p)
{
    int i;
    int s=curbast.size()-1;
    //free(curbast[p]);//----------------------------очень скользкий момент
    for(i=p;i<s;i++)
    {
        curbast[i]=curbast[i+1];
    }
    curbast.resize(s);
}
//-------------------------------реакция на кнопку "удалить список"
void MainWindow::dellist()
{
    int i,j;

    int s=curbast.size();
    int s2=second.size();
    //int n;
    j=0;
    for(i=0;i<s2;i++)
    {
        for(j=0;j<s;j++)
        {
            if(curbast[j]==second[i])
            {
                delel(j);
                s=curbast.size();
                break;
            }
        }
    }
    ui->spinBox->setMaximum(s);
    if(ui->spinBox->value()==s)
    {
        showdata(s,true);
    }
    else
    {
        ui->spinBox->setValue(s);
    }
}
//--------------------------открыть допбазу
void MainWindow::open2()
{
    QString c=QFileDialog::getOpenFileName(this,"открыть второй фаил","","*.txt");
    QFile f(c);
    char buf[128];
    if(f.open(QIODevice::ReadOnly))
    {
        f.readLine(buf,128);
        f.close();
        if(dada.fo(buf)==cot)
        {
            second.resize(0);
            dada.loading(c,&second);
            connect(ui->spinBox2,SIGNAL(valueChanged(int)),this,SLOT(ha(int)));
            connect(ui->serch,&QPushButton::clicked,this,&MainWindow::serch);
            connect(ui->del1,&QPushButton::clicked,this,&MainWindow::delone);
            connect(ui->V,&QPushButton::clicked,this,&MainWindow::obiedin);
            connect(ui->A,&QPushButton::clicked,this,&MainWindow::peresek);

            connect(ui->sas2,&QPushButton::clicked,this,&MainWindow::saveas2);

            ui->spinBox2->setMaximum(second.size());
            ui->spinBox2->setValue(second.size());
            ui->lim2->setText(QString(dada.toChar(curbast.size())));
            ui->status3->setText("нет ошибок");
            ui->obrab->setText(QString("Обработка второй \nбазы"));

        }
    }
    else
    {
        ui->status3->setText("ошибка загрузки");
    }
    f.close();

}
//---------------------------------реакция на кнопку "объединить"
void MainWindow::obiedin()
{
   int i,j,c;
   int s=curbast.size();
   int s2=second.size();
   for(i=0;i<s;i++)
   {
       for(j=0;j<s2;j++)
       {
           c=0;
           if(dada.chekidentity(0,&c,cot,second[j],curbast[i]))//сравниваетм содержимое. если равно
           {
               second[j]=curbast[i];
               break;
           }

       }
       if(j==s2)
       {
           second.push_back(curbast[i]);
       }
   }
   s2=second.size();
   ui->spinBox2->setMaximum(s2);
   if(s2==ui->spinBox2->value())showdata(s2,false);
   else
   {
       ui->spinBox2->setValue(s2);
   }
   ui->obrab->setText(QString("Обработка основной \nбазы"));
}

void MainWindow::peresek()
{
    int i,j,c;
    int s=curbast.size();
    int s2=second.size();
    vector<void*>vena=second;
    second.resize(0);
    for(i=0;i<s;i++)
    {
        for(j=0;j<s2;j++)
        {
            c=0;
            if(dada.chekidentity(0,&c,cot,vena[j],curbast[i]))//сравниваетм содержимое. если равно
            {
                second.push_back(curbast[i]);
            }

        }
    }
    s2=second.size();
    ui->spinBox2->setMaximum(s2);
    if(s2==ui->spinBox2->value())showdata(s2,false);
    else
    {
        ui->spinBox2->setValue(s2);
    }
    ui->obrab->setText(QString("Обработка основной \nбазы"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
