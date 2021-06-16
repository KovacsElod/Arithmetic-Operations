#include <iostream>

using namespace std;

class NagyEgesz
{
    int* szamjegyek;
    int n;
    int elojel;
    public:
        NagyEgesz();
        NagyEgesz(int elo,int dim,const int* szamj);
        NagyEgesz(const NagyEgesz&);
        NagyEgesz(int szam);
        NagyEgesz(long szam);
        ~NagyEgesz();
        NagyEgesz operator +(NagyEgesz &);
        NagyEgesz operator -(NagyEgesz &);
        NagyEgesz operator /(NagyEgesz &);
        NagyEgesz operator *(NagyEgesz &);
        NagyEgesz& operator =(const NagyEgesz&);
        NagyEgesz& operator+=(const NagyEgesz&);
        NagyEgesz& operator-=(const NagyEgesz&);
        NagyEgesz& operator++();
        NagyEgesz operator++(int);
        NagyEgesz& operator--();
        NagyEgesz operator--(int);
        class NullavalValoOsztas{};
        ostream& kiir(ostream&) const;
};

NagyEgesz::NagyEgesz()
{
    n=1;
    elojel=0;
    szamjegyek=new int[1];
    szamjegyek[0]=0;
}

NagyEgesz::NagyEgesz(int elo,int dim, const int* szamj)
{
    elojel=elo;
    n=dim;
    szamjegyek=new int[n];
    for(int i=0; i<n; i++)
        szamjegyek[i]=szamj[i];
}

NagyEgesz::NagyEgesz(const NagyEgesz &x)
{
    elojel=x.elojel;
    n=x.n;
    szamjegyek=new int[n];
    for(int i=0; i<n; i++)
        szamjegyek[i]=x.szamjegyek[i];
}

NagyEgesz::~NagyEgesz()
{
    delete[] szamjegyek;
}

NagyEgesz::NagyEgesz(int szam)
{
    if (szam>0)
        elojel=1;
    else if(szam<0)
    {
        elojel=-1;
        szam=0-szam;
    }
    else
        {
            elojel=0;
            n=1;
            szamjegyek=new int[1];
            szamjegyek[0]=0;
            return;
        }
    int i=0;
    int szam2=szam;
    while(szam2>0)
    {
        szam2/=10;
        i++;
    }
    n=i;
    szamjegyek=new int[i-1];
    i=0;
    while(szam!=0)
    {
        szamjegyek[n-i-1]=szam%10;
        szam/=10;
        i++;
    }
}

NagyEgesz::NagyEgesz(long szam)
{
    if (szam>0)
        elojel=1;
    else if(szam<0)
    {
        elojel=-1;
        szam=0-szam;
    }
    else
        elojel=0;
    int i=0;
    int szam2=szam;
    while(szam2>0)
    {
        szam2/=10;
        i++;
    }
    n=i;
    szamjegyek=new int[i-1];
    i=0;
    while(szam!=0)
    {
        szamjegyek[n-i-1]=szam%10;
        szam/=10;
        i++;
    }
}

NagyEgesz& NagyEgesz::operator=(const NagyEgesz& x)
{
    if(this!=&x)
    {
        delete[] szamjegyek;
        elojel=x.elojel;
        n=x.n;
        szamjegyek=new int[n];
        for(int i=0; i<n; i++)
            szamjegyek[i]=x.szamjegyek[i];
    }
    return *this;
}

NagyEgesz NagyEgesz::operator+(NagyEgesz& x)
{
    int jel;
    int carry=0;
    int k;
    if(n>x.n)
    {
        jel=elojel;
        k=n-x.n;
        if(elojel==x.elojel)
        {
            int* t=new int[n+1];
            for(int i=n-1;i>=k;i--)
            {
                t[i+1]=(x.szamjegyek[i-k]+szamjegyek[i]+carry)%10;
                carry=(x.szamjegyek[i-k]+szamjegyek[i]+carry)/10;
            }
            if(k-1!=0)
                for(int i=k-1;i>=0;i--)
                {
                    t[i+1]=(szamjegyek[i]+carry)%10;
                    carry=(szamjegyek[i]+carry)/10;
                }
            else
                t[1]=szamjegyek[0];
            t[0]=carry;
            NagyEgesz er(jel,n+1,t);
            return er;
        }
        else
        {
            int* t=new int[n];
            for(int i=n-1;i>=k;i--)
            {
                t[i]=(10-x.szamjegyek[i-k]+szamjegyek[i]+carry)%10;
                if(-x.szamjegyek[i-k]+szamjegyek[i]+carry<0)
                    carry=-1;
                else
                    carry=0;
            }
            for(int i=k-1;i>=0;i--)
            {
                t[i]=(10+szamjegyek[i]+carry)%10;
                if(szamjegyek[i]+carry<0)
                    carry=-1;
                else
                    carry=0;
            }
            NagyEgesz er(jel,n,t);
            return er;
        }
    }
    else if(x.n>n)
    {
        jel=x.elojel;
        k=x.n-n;
        if(elojel==x.elojel)
        {
            int* t=new int[x.n+1];
            for(int i=x.n-1;i>=k;i--)
            {
                t[i+1]=(x.szamjegyek[i]+szamjegyek[i-k]+carry)%10;
                carry=(x.szamjegyek[i]+szamjegyek[i-k]+carry)/10;
            }
            if(k-1!=0)
                for(int i=k-1;i>=0;i--)
                {
                    t[i+1]=(x.szamjegyek[i]+carry)%10;
                    carry=(x.szamjegyek[i]+carry)/10;
                }
            else
                t[1]=x.szamjegyek[0];
            t[0]=carry;
            NagyEgesz er(jel,x.n+1,t);
            return er;
        }
        else
        {
            int* t=new int[x.n];
            for(int i=x.n-1;i>=k;i--)
            {
                t[i]=(10+x.szamjegyek[i]-szamjegyek[i-k]+carry)%10;
                if(x.szamjegyek[i]-szamjegyek[i-k]+carry<0)
                    carry=-1;
                else
                    carry=0;
            }
            for(int i=k-1;i>=0;i--)
            {
                t[i]=(10+x.szamjegyek[i]+carry)%10;
                if(x.szamjegyek[i]+carry<0)
                    carry=-1;
                else
                    carry=0;
            }
            NagyEgesz er(jel,x.n,t);
            return er;
        }
    }
    else
    {
        if(elojel==x.elojel)
        {
            int* t=new int[n+1];
            for(int i=n-1;i>=0;i--)
            {
                t[i+1]=(x.szamjegyek[i]+szamjegyek[i]+carry)%10;
                carry=(x.szamjegyek[i]+szamjegyek[i]+carry)/10;
            }
            t[0]=carry;
            NagyEgesz er(jel,n+1,t);
            return er;
        }
        else
        {
            int i=0;
            int* na=new int[n];//a nagyobb szam
            int* ki=new int[n];//kisebb szam
            while(szamjegyek[i]>=x.szamjegyek[i]&&i<n)
                i++;
            if(i==n)
            {
                na=szamjegyek;
                jel=elojel;
                ki=x.szamjegyek;
            }
            else
            {
                ki=x.szamjegyek;
                jel=x.elojel;
                ki=szamjegyek;
            }
            int* t=new int[x.n];
            for(int i=x.n-1;i>=0;i--)
            {
                t[i]=(10+na[i]-ki[i]+carry)%10;
                if(na[i]-ki[i]<0)
                    carry=-1;
                else
                    carry=0;
            }
            NagyEgesz er(jel,x.n,t);
            return er;
        }
    }
}

NagyEgesz NagyEgesz::operator-(NagyEgesz& x)
{
    int jel;
    int carry=0;
    int k;
    if(n>x.n)
    {
        jel=elojel;
        k=n-x.n;
        if(elojel!=x.elojel)
        {
            int* t=new int[n+1];
            for(int i=n-1;i>=k;i--)
            {
                t[i+1]=(x.szamjegyek[i-k]+szamjegyek[i]+carry)%10;
                carry=(x.szamjegyek[i-k]+szamjegyek[i]+carry)/10;
            }
            if(k-1!=0)
                for(int i=k-1;i>=0;i--)
                {
                    t[i+1]=(szamjegyek[i]+carry)%10;
                    carry=(szamjegyek[i]+carry)/10;
                }
            else
                t[1]=szamjegyek[0];
            t[0]=carry;
            int j=0;
            while(szamjegyek[j]==0&&j!=n)
                j++;
            if(j==n)
            {
                NagyEgesz er(0);
                return er;
            }
            int dim=n+1;
            if(j>0)
            {
                dim=n+1-j;
                for(int i=0;i<n+1-j;i++)
                {
                    t[i]=t[i+j];
                }
            }
            NagyEgesz er(jel,dim,t);
            return er;

        }
        else
        {
            int* t=new int[n];
            for(int i=n-1;i>=k;i--)
            {
                t[i]=(10-x.szamjegyek[i-k]+szamjegyek[i]+carry)%10;
                if(-x.szamjegyek[i-k]+szamjegyek[i]+carry<0)
                    carry=-1;
                else
                    carry=0;
            }
            for(int i=k-1;i>=0;i--)
            {
                t[i]=(10+szamjegyek[i]+carry)%10;
                if(szamjegyek[i]+carry<0)
                    carry=-1;
                else
                    carry=0;
            }
            int j=0;
            while(t[j]==0&&j!=n)
                j++;
            if(j==n)
            {
                NagyEgesz er(0);
                return er;
            }
            int dim=n;
            if(j>0)
            {
                dim=n-j;
                for(int i=0;i<n-j;i++)
                {
                    t[i]=t[i+j];
                }
            }
            NagyEgesz er(jel,dim,t);
            return er;
        }
    }
    else if(x.n>n)
    {
        jel=-x.elojel;
        k=x.n-n;
        if(elojel!=x.elojel)
        {
            int* t=new int[x.n+1];
            for(int i=x.n-1;i>=k;i--)
            {
                t[i+1]=(x.szamjegyek[i]+szamjegyek[i-k]+carry)%10;
                carry=(x.szamjegyek[i]+szamjegyek[i-k]+carry)/10;
            }
            if(k-1!=0)
                for(int i=k-1;i>=0;i--)
                {
                    t[i+1]=(x.szamjegyek[i]+carry)%10;
                    carry=(x.szamjegyek[i]+carry)/10;
                }
            else
                t[1]=x.szamjegyek[0];
            t[0]=carry;
            int j=0;
            while(t[j]==0&&j!=n)
                j++;
            if(j==n)
            {
                NagyEgesz er(0);
                return er;
            }
            int dim=x.n+1;
            if(j>0)
            {
                dim=x.n-j+1;
                for(int i=0;i<dim;i++)
                {
                    t[i]=t[i+j];
                }
            }
            NagyEgesz er(jel,dim,t);
            return er;
        }
        else
        {
            int* t=new int[x.n];
            for(int i=x.n-1;i>=k;i--)
            {
                t[i]=(10+x.szamjegyek[i]-szamjegyek[i-k]+carry)%10;
                if(x.szamjegyek[i]-szamjegyek[i-k]+carry<0)
                    carry=-1;
                else
                    carry=0;
            }
            for(int i=k-1;i>=0;i--)
            {
                t[i]=(10+x.szamjegyek[i]+carry)%10;
                if(x.szamjegyek[i]+carry<0)
                    carry=-1;
                else
                    carry=0;
            }
            int j=0;
            while(t[j]==0&&j!=n)
                j++;
            if(j==n)
            {
                NagyEgesz er(0);
                return er;
            }
            int dim=x.n;
            if(j>0)
            {
                dim=x.n-j;
                for(int i=0;i<dim;i++)
                {
                    t[i]=t[i+j];
                }
            }
            NagyEgesz er(jel,dim,t);
            return er;
        }
    }
    else
    {
        if(elojel!=x.elojel)
        {
            int* t=new int[n+1];
            for(int i=n-1;i>=0;i--)
            {
                t[i+1]=(x.szamjegyek[i]+szamjegyek[i]+carry)%10;
                carry=(x.szamjegyek[i]+szamjegyek[i]+carry)/10;
            }
            t[0]=carry;
            jel=elojel;
            int j=0;
            while(t[j]==0&&j!=n)
                j++;
            if(j==n)
            {
                NagyEgesz er(0);
                return er;
            }
            int dim=n+1;
            if(j>0)
            {
                dim=n+1-j;
                for(int i=0;i<dim;i++)
                {
                    t[i]=t[i+j];
                }
            }
            NagyEgesz er(jel,dim,t);
            return er;
        }
        else
        {
            int i=0;
            int* na=new int[n];//a nagyobb szam
            int* ki=new int[n];//kisebb szam
            while(szamjegyek[i]>=x.szamjegyek[i]&&i<n)
                i++;
            if(i==n)
            {
                na=szamjegyek;
                jel=elojel;
                ki=x.szamjegyek;
            }
            else
            {
                ki=x.szamjegyek;
                jel=-x.elojel;
                ki=szamjegyek;
            }
            int* t=new int[x.n];
            for(int i=x.n-1;i>=0;i--)
            {
                t[i]=(10+na[i]-ki[i]+carry)%10;
                if(na[i]-ki[i]<0)
                    carry=-1;
                else
                    carry=0;
            }
            int j=0;
            while(t[j]==0&&j!=n)
                j++;
            if(j==n)
            {
                NagyEgesz er(0);
                return er;
            }
            int dim=x.n;
            if(j>0)
            {
                dim=x.n-j;
                for(int i=0;i<dim;i++)
                {
                    t[i]=t[i+j];
                }
            }
            NagyEgesz er(jel,dim,t);
            return er;
        }
    }
}

NagyEgesz& NagyEgesz::operator+=(const NagyEgesz& x)
{
    return *this=*this+const_cast<NagyEgesz&>(x);
}

NagyEgesz& NagyEgesz::operator-=(const NagyEgesz& x)
{
    return *this=*this-const_cast<NagyEgesz&>(x);
}

NagyEgesz NagyEgesz::operator*(NagyEgesz& x)
{
    int jel;
    if((x.n==1&&x.szamjegyek[0]==0)||(n==1&&szamjegyek[0]==0))
    {
        int y[1]={0};
        NagyEgesz er(0,1,y);
        return er;
    }
    int t[n+x.n+1]={0};
    int ind1=0;
    int ind2=0;
    for(int i=n-1;i>=0;i--)
    {
        int carry=0;
        int sz1=szamjegyek[i];
        ind2=0;
        for(int j=x.n-1;j>=0;j--)
        {
            int sz2=x.szamjegyek[j];
            int sum=sz1*sz2+t[n+x.n-ind1-ind2-1]+carry;
            carry=sum/10;
            t[n-ind1+x.n-ind2-1]=sum%10;
            ind2++;
        }
        if(carry>0)
            t[n-ind1+x.n-ind2-1]+=carry;
        ind1++;
    }
    int i=n+x.n;
    while(i>=0&&t[i]==0)
        i--;
    if(i==-1)
    {
        jel=0;
        t[0]={0};
        NagyEgesz er(0,1,t);
        return er;
    }
    i=0;
    while(t[i]==0&&i<n+x.n-1)
    {
        i++;
    }
    for(int j=0;j<n+x.n-i;j++)
    {
        t[j]=t[j+i];
    }
    int dim=n+x.n-i;
    NagyEgesz er(jel,dim,t);
    return er;
}



ostream& NagyEgesz::kiir(ostream& s) const
{
    int j=0;
    while(szamjegyek[j]==0&&j!=n)
        j++;
    if(j==n)
    {
        s<<0<<endl;
        return s;
    }
    if(elojel==-1)
        s<<"-";
    for(int i=j; i<n; i++)
        s<<szamjegyek[i];
    s<<endl;
    return s;
}

NagyEgesz NagyEgesz::operator/(NagyEgesz& x)
{
    int jel=x.elojel*elojel;
    if(x.n==1&&x.szamjegyek[0]==0)
        throw NullavalValoOsztas();
    if((n==1&&szamjegyek[0]==0)||n<x.n)
    {
        int y[1]={0};
        NagyEgesz er(0,1,y);
        return er;
    }
    NagyEgesz t;
    int db=0;
    elojel=x.elojel=1;
    t=*this-x;
    if(t.elojel<0)
    {
        NagyEgesz er(0);
        return er;
    }
    else if(t.elojel==0)
    {
        int y[1]={1};
        NagyEgesz er(jel,1,y);
        return er;
    }
    else
    {
        db++;
        while(t.elojel>0)
        {
            t=t-x;
            db++;
        }
        NagyEgesz s(db);
        NagyEgesz er(jel,s.n,s.szamjegyek);
        return er;
    }
}

NagyEgesz& NagyEgesz::operator ++()
{
    int g[1]={1};
    NagyEgesz t(elojel,1,g);
    if(elojel<0)
        *this-=t;
    else
        *this+=t;
    return *this;
}

NagyEgesz NagyEgesz::operator ++(int)
{
    NagyEgesz er(elojel,n,szamjegyek);
    int g[1]={1};
    NagyEgesz t(elojel,1,g);
    if(elojel<0)
        *this-=t;
    else
        *this+=t;
    return er;
}

NagyEgesz& NagyEgesz::operator --()
{
    int g[1]={1};
    NagyEgesz t(elojel,1,g);
    if(elojel>0)
        *this-=t;
    else
        *this+=t;
    return *this;
}

NagyEgesz NagyEgesz::operator --(int)
{
    NagyEgesz er(elojel,n,szamjegyek);
    int g[1]={1};
    NagyEgesz t(elojel,1,g);
    if(elojel>0)
        *this-=t;
    else
        *this+=t;
    return er;
}


ostream& operator<<(ostream& s,const NagyEgesz &e)
{
    return e.kiir(s);
}

int main()
{
    NagyEgesz x;
    long a;
    int t[]={1,2,3};
    a=1242334;
    NagyEgesz y(a);
    cout<<y;
    NagyEgesz y2(100);
    cout<<y2;
    NagyEgesz y3(-9000);
    cout<<y3;
    cout<<y2-y3;
    //y2-=y3;
    cout<<y2;
    NagyEgesz y4(87);
    NagyEgesz y5(253);
    cout<<y4-y5;
    NagyEgesz y6(909);
    cout<<y6;
    cout<<y5*y6;
    NagyEgesz y7;
    try
    {
        cout<<y6/y7;
    }
    catch (NagyEgesz::NullavalValoOsztas)
    {
        cout<<"HIBA: 0-val valo osztas nem lehetseges"<<endl;
    }
    //cout<<y4/y5;
    //cout<<y6;
    //y7=++y6;
    cout<<y7;
    //cout<<y6;
    y7=y6++;
    cout<<y7;
    cout<<y6;
    //cout<<y6;
    y7=--y6;
    cout<<y7;
    cout<<y6;
    y7=y6--;
    cout<<y7;
    cout<<y6;
}

