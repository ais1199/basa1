#include "sample.h"
//#include <QFile>


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
    for(i=0;i<baza.size();i++)
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
    char e[]="\r\n";
    if(f->open(QIODevice::WriteOnly))
    {
        f->write(inf->name,strlen(inf->name));
        f->write(e,2);
        for(;j<what.size();j++)
        {
            whattoput=what[j];
            place=0;
            pinfrec(0,inf);
        }

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
    if(n<curobinf->parts.size())
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
