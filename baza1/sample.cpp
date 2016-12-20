#include "sample.h"



Sample::Sample()
{

}
//делает из числа строку
char* Sample::toChar(int n)
{
    int s=n,k;
    char*urur;
    char*p;
    for(k=0;s>0;k++)
    {
        s=s/10;
    }
    urur=(char*)malloc((k+1)*sizeof(char));
    urur[k]='\0';
    p=urur+k-1;
    for(s=n;s>0;s=s/10)
    {
        *p=3*16+s%10;
        if((p-urur)>0)p--;
    }
    //*p='\0';
    return urur;
}
//находит объект по имени
obinf* Sample::fo(char *name)
{
    obinf*s;
    int i;
    for(i=0;name[i]!='\r';i++)
    {
        if(name[i]=='\n'||name[i]=='\0')break;
    }
    name[i]='\0';
    int dop=baza.size();
    for(i=0;i<dop;i++)
    {
        s=baza[i];
        if(0==strcmp(name,s->name))return s;
    }
    return zerobase;
}
//функция для сохранения, которая открывает фаил.
void Sample::pinf(QString fname,vector<void*> what,obinf*inf)
{
    f=new QFile(fname);
    int j=0;
    int s=what.size();
    char e[]="\r\n";
    if(f->open(QIODevice::WriteOnly))
    {
        f->write(inf->name,strlen(inf->name));
        f->write(e,2);
        for(;j<s;j++)
        {
            whattoput=what[j];
            place=0;
            pinfrec(0,inf);
        }
        //f->write(e,2);
    }
    else
    {
        exit(100);
    }
    f->close();
}
//рекурсивная функция. которая записывает в фаил информацию.
void Sample::pinfrec(int n,obinf*curobinf)
{
    char a[]="int";
    char b[]="char";
    char*buf;
    int per;
    char p[]="\r\n";
    obinf*nana;
    vector<part>urur=(curobinf->parts);
    part curp=urur[n];
    int dop=curobinf->parts.size();
    if(n<dop)
            {
                if(0==strcmp(a,curp.tipe))
                {
                    per=*((int*)(whattoput+place));
                    buf=toChar(per);
                    f->write(buf,strlen(buf));
                    free(buf);
                    f->write(p,2);
                    place+=curp.size;
                }
                else
                {
                    if(0==strcmp(b,curp.tipe))
                    {
                        buf=*((char**)(whattoput+place));
                        f->write(buf,strlen(buf));
                        f->write(p,2);
                        place+=curp.size;
                    }
                    else
                    {
                        nana=fo(curp.tipe);
                        if(nana!=zerobase) pinfrec(0,nana);
                    }
                }
                pinfrec(n+1,curobinf);
            }
}
//подготовка для загрузки базы
void Sample::loading(QString fname,vector<void*>*toinput)
{
    f=new QFile(fname);
    char buf[128];
    obinf*tipe;
    //int j=0;
    if(f->open(QIODevice::ReadOnly))
    {
        f->readLine(buf,128);
        tipe=fo(buf);

        while(!f->atEnd())
        {
            whattoput=malloc(tipe->size);
            place=0;
            getdata(0,tipe);
            toinput->push_back(whattoput);
        }
    }

}
//рекурсивная функция загрузки объекта
void Sample::getdata(int n,obinf*inf)
{
    vector<part> urur=inf->parts;
    int s=urur.size();
    if(n<s)
    {
        char a[]="int";
        char b[]="char";
        char buf[128];
        bool ok;
        char *u;
        part pp=urur[n];
        obinf*nana;
        QString aa,bb;
        int j;
        if(0==strcmp(a,pp.tipe)*strcmp(b,pp.tipe))
        {
            f->readLine(buf,128);
            if(buf[0]!='\r')
            {
                if(0==strcmp(a,pp.tipe))
                {
                    aa=QString(buf);
                    bb=aa.section('\r',0,0);
                    *((int*)(whattoput+place))=bb.toInt(&ok,10);
                    //j=*((int*)(whattoput+place));
                    place+=sizeof(int);
                }
                else
                {
                    for(j=0;buf[j]!='\r';j++)
                    {
                        if(buf[j]=='\0'||buf[j]=='\n')break;
                    }
                    buf[j]='\0';
                    u=(char*)malloc((j+1)*sizeof(char));
                    strcpy(u,buf);
                    *((char**)(whattoput+place))=u;
                    //provc=*((char**)(whattoput+place));
                    place+=sizeof(char*);
                }
            }
        }
        else
        {
            nana=fo(pp.tipe);
            if(nana!=zerobase)getdata(0,nana);
        }
        getdata(n+1,inf);
    }
}

int Sample::interpritator(char*text)
{
    char *u=text;
    char*p,*k;
    char a[]="int";
    char b[]="char";
    bool result=true;
    //bool action;
    vector<int>res;
    vector<int>myres;
    vector<int>itsres;
    int i,j;
    int dop,l;

    if (u[0]=='!')
    {
        u++;
        result=false;
    }
    if(u[0]=='(')
    {
        i=-1;
        for(p=u+1;(*p)!='\0';p++)
        {
            if((*p)=='(')i--;
            if((*p)==')')i++;
            if(i==0)break;
        }
        if(i==0)
        {
            if(*(p+1)=='\0')
            {
                (*p)='\0';
                if(interpritator(u+1)<0)return -1;
                res=wasfound;
            }

        }
        else
        {
            j=0;
            return -1;
        }
    }
    else
    {
        p=u;
    }
    char action2;
        for(;(*p)!='\0';p++)
        {
            if((*p)=='&'||(*p)=='|')
            {
                action2=(*p);
                break;
            }
        }
        if((*p)=='\0'&&u[0]!='(')
        {
            obinf*c;
            part pa;
            vector<part> pp;
            i=0;
            char*fi=u;
            char*gi;
            for(c=st;;)
            {
                pp=c->parts;
                dop=pp.size();
                char action;
                for(gi=fi;(*gi)!='\0';gi++)
                {
                    if((*gi)=='.'||(*gi)=='>'||(*gi)=='<'||(*gi)=='!'||(*gi)=='=')
                    {
                        action=(*gi);
                        break;
                    }
                }
                (*gi)='\0';
                for(j=0;j<dop;j++)
                {
                    pa=pp[j];
                    if(strcmp(fi,pa.name)==0)break;
                    i+=pa.size;
                }
                if(j==dop)
                {
                    j=dop;
                    return -1;
                }
                if(action=='.')
                {
                   fi=gi+1;
                   c=fo(pa.tipe);
                }
                else
                {
                    gi++;
                    //res.resize(0);
                    dop=sp->size();

                    char*azaz;
                    if(0==strcmp(pa.tipe,b))
                    {
                        if(action=='=')
                        {

                            for(l=0;l<dop;l++)
                            {
                                azaz=getchar(gi,((*sp)[l]));
                                if(0==strcmp(*((char**)(((*sp)[l])+i)),azaz))
                                {
                                    res.push_back(l);
                                }
                            }

                        }
                        else
                        {
                            gi++;

                            for(l=0;l<dop;l++)
                            {
                                azaz=getchar(gi,((*sp)[l]));

                                if(strcmp(*((char**)(((*sp)[l])+i)),gi))
                                {
                                    res.push_back(l);
                                }
                            }
                        }
                    }
                    else
                    {
                        int the=0;
                        /*for(fi=gi;(*fi)!='\0';fi++)
                        {
                            if((*fi)>='0'&&(*fi)<='9')
                            {
                                the=10*the+(*fi)-'0';
                            }
                        }*/
                        if(action=='=')
                        {
                            for(l=0;l<dop;l++)
                            {
                                the=getint(gi,((*sp)[l]));
                                if(the==(*((int*)(((*sp)[l])+i))))
                                {
                                    res.push_back(l);
                                }
                            }

                        }
                        else
                        {
                            if(action=='>')
                            {
                                if((*gi)=='=')
                                {
                                    gi++;
                                    for(l=0;l<dop;l++)
                                    {
                                        the=getint(gi,((*sp)[l]));

                                        if(the<=(*((int*)(((*sp)[l])+i))))
                                        {
                                            res.push_back(l);
                                        }
                                    }

                                }
                                else
                                {
                                    for(l=0;l<dop;l++)
                                    {
                                        the=getint(gi,((*sp)[l]));

                                        if(the<(*((int*)(((*sp)[l])+i))))
                                        {
                                            res.push_back(l);
                                        }
                                    }
                                }
                            }
                            else
                            {
                                if(action=='<')
                                {
                                    if((*gi)=='=')
                                    {
                                        gi++;
                                        for(l=0;l<dop;l++)
                                        {
                                            the=getint(gi,((*sp)[l]));

                                            if(the>=(*((int*)(((*sp)[l])+i))))
                                            {
                                                res.push_back(l);
                                            }
                                        }

                                    }
                                    else
                                    {
                                        for(l=0;l<dop;l++)
                                        {
                                            the=getint(gi,((*sp)[l]));

                                            if(the>(*((int*)(((*sp)[l])+i))))
                                            {
                                                res.push_back(l);
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    gi++;
                                    for(l=0;l<dop;l++)
                                    {
                                        the=getint(gi,((*sp)[l]));
                                        if(the!=(*((int*)(((*sp)[l])+i))))
                                        {
                                            res.push_back(l);
                                        }
                                    }
                                }
                            }
                        }
                    }

                    break;
                }
            }
        }
        else
        {
            if((*p)!='\0')
            {
                (*p)='\0';
                if(interpritator(p+1)<0)return -1;
                itsres=wasfound;
                if(interpritator(u)<0)return -1;
                myres=wasfound;
                dop=itsres.size();
                l=myres.size();
                if(action2=='&')
                {
                    j=0;
                    i=0;
                    while(i<dop&&j<l)
                    {
                        if(itsres[i]>myres[j])
                        {
                            j++;

                        }
                        else
                        {
                            if(itsres[i]==myres[j])
                            {
                                j++;
                                res.push_back(itsres[i]);
                            }
                            i++;
                        }
                    }
                }
                else
                {
                    j=0;
                    i=0;
                    while(i<dop&&j<l)
                    {
                        if(itsres[i]>myres[j])
                        {
                            res.push_back(myres[j]);
                            j++;

                        }
                        else
                        {
                            if(itsres[i]==myres[j])j++;
                            res.push_back(itsres[i]);
                            i++;
                        }
                    }
                    if(i==dop)
                    {
                        for(;j<l;j++)
                        {
                            res.push_back(myres[j]);
                        }
                    }
                    else
                    {
                        for(;i<dop;i++)
                        {
                            res.push_back(itsres[i]);
                        }
                    }
                }
            }

        }

    wasfound.resize(0);
    free(text);
    if(result)
    {
        wasfound=res;
        result=true;
    }
    else
    {

        dop=sp->size();
        j=0;
        for(i=0;i<dop;i++)
        {
            if(i==res[j])
            {
                j++;
            }
            else
            {
                wasfound.push_back(i);
            }

        }
        result=false;
    }
    dop=wasfound.size();
    if(dop==0)return 0;
    return 1;

}

int Sample::getint(char *text, void *where)
{
    if(text[0]=='.')
    {
        obinf*c;
        part pa;
        vector<part> pp;
        int i=0;
        //char a[]="int";
        char*fi=text+1;
        char*gi;
        int j,dop;
        char a[]="int";
        for(c=st;;)
        {
            pp=c->parts;
            dop=pp.size();
            char action;
            for(gi=fi;(*gi)!='\0';gi++)
            {
                if((*gi)=='.') break;

            }

            (*gi)='\0';
            for(j=0;j<dop;j++)
            {
                pa=pp[j];
                if(strcmp(fi,pa.name)==0)break;
                i+=pa.size;
            }
            if(j==dop)return -1;
            if(0==strcmp(a,pa.tipe))break;
            fi=gi+1;
            c=fo(pa.tipe);
        }
        int res=*((int*)(where+i));
        return res;
    }
    else
    {
        int the=0;
        char *u;
        for(u=text;(*u)!='\0';u++)
        {
            the=10*the+(*u)-'0';
        }
        return the;
    }
}

char* Sample::getchar(char*text,void*where)
{
    if(text[0]=='.')
    {
        obinf*c;
        part pa;
        vector<part> pp;
        int i=0;
        char*fi=text+1;
        char*gi;
        int j,dop;
        char a[]="char";
        for(c=st;;)
        {
            pp=c->parts;
            dop=pp.size();
            char action;
            for(gi=fi;(*gi)!='\0';gi++)
            {
                if((*gi)=='.') break;

            }

            (*gi)='\0';
            for(j=0;j<dop;j++)
            {
                pa=pp[j];
                if(strcmp(fi,pa.name)==0)break;
                i+=pa.size;
            }
            if(j==dop)return text;
            if(0==strcmp(a,pa.tipe))break;
            fi=gi+1;
            c=fo(pa.tipe);
        }
        char* res=*((char**)(where+i));
        return res;
    }
    else
    {
        return text;
    }
}
