#include "sample.h"
//#include <QFile>

/*int square(int x)
{
}
*/
Sample::Sample()
{

}

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
    p=urur;
    for(s=n;s>0;s=s/10)
    {
        *p=3*16+s%10;
        p++;
    }
    *p='\0';
    return urur;
}

obinf* Sample::fo(char *name)
{
    obinf*s;
    for(s=baza;s!=zerobase;s=s->next)
    {
        if(0==strcmp(name,s->name))return s;
    }
    return zerobase;
}

void Sample::pinf(QString fname,ob* what,obinf*inf)
{
    f=new QFile(fname);
    ob*start=what;
    part*curs=inf->parts;
    char e[]="\r\n";
    if(f->open(QIODevice::WriteOnly))
    {
        f->write(inf->name,strlen(inf->name));
        f->write(e,2);
        for(;start!=zeroob;start=start->next)
        {
            whattoput=start->data;
            pinfrec(curs);
        }

    }
    else
    {
        exit(100);
    }
    f->close();
}
void Sample::pinfrec(part*curs)
{
    char a[]="int";
    char b[]="char";
    char*buf;
    int per;
    char p[]="\r\n";
    obinf*nana;
    if(curs!=zeropart)
            {
                if(0==strcmp(a,curs->tipe))
                {
                    per=*((int*)whattoput);
                    buf=toChar(per);
                    f->write(buf,strlen(buf));
                    free(buf);
                    f->write(p,2);
                    whattoput+=curs->size;
                }
                else
                {
                    if(0==strcmp(b,curs->tipe))
                    {
                        buf=((char*)whattoput);
                        f->write(buf,strlen(buf));
                        f->write(p,2);
                        whattoput+=curs->size;
                    }
                    else
                    {
                        nana=fo(curs->tipe);
                        if(nana->parts!=zeropart&&nana!=zerobase) pinfrec(nana->parts);
                    }
                }
                if(curs->next!=zeropart)pinfrec(curs->next);
            }
}
