#include <iostream>
#include <cstring>
#include <cstdlib>
class Polinom
{
    int degree;//степень
    int*koef;//массив коэффицентов
public:
    Polinom(){};//конструктор по умолчанию
    Polinom(const Polinom& pol);//Конструктор копирования
    Polinom(int count);//Конструктор преобразования типа
    ~Polinom(){delete[] koef;}//Деструктор
    int& operator[](int index);//Перегрузка оператора индексирования
    Polinom operator+(Polinom&);//Перегрузка оператора сложения
    Polinom& operator=(Polinom&);//Перегрузка оператора присваивания
    Polinom operator*(Polinom&);//Перегрузка оператора умножения
    int GetDegr(){return degree;}//Получение степени
    int input(int);//Ввод полинома
    Polinom operator+(int&);//Перегрузка оператора сложения целого числа и полинома
    Polinom operator*(int&);//Перегрузка оператора умножения целого числа и полинома
    bool operator==(Polinom&);
    bool operator>=(Polinom&);
    bool operator<=(Polinom&);
    friend std::ostream& operator<<(std::ostream&, Polinom&);//Перегрузка оператора вывода в поток
};
int Polinom::input(int n)
{
    degree=n;
    koef=new int[degree+1]; 
    for(int i=n;i>=0;i--)
        {
            std::cout<<"Enter " << i << " koef "<<'\n';
            std::cin>>koef[i];
            if(koef[i]==-842150451)
            {
                std::cout<<"Ошибка ввода. Введите число\n";
                exit(0);
            }
        }
    system("cls");
    return 0;
}
std::ostream& operator<<(std::ostream& str, Polinom& pol)
{
  int b;
  b=pol.degree;
  while(pol.koef[b]==0&&b>=0)
  b=b-1;
  if(b<0) 
      str<<"Polinom = 0\n";
  else
    {
        if(b==0) 
            str<<pol.koef[0];
   else
    {
        str<<pol.koef[b]<<"x^"<<b;
        b=b-1;
        for(int i=b;i>0;i--)
            {
                if (pol.koef[i]<0) {str<<pol.koef[i];};
                if (pol.koef[i]>0) {str<<"+"<<pol.koef[i];};
                if (pol.koef[i]!=0) {str<<"x^"<<i;};
            };
        if (pol.koef[0]<0) str<<pol.koef[0];
        if (pol.koef[0]>0) str<<"+"<<pol.koef[0];
    }
    }
  return str;
}
Polinom::Polinom(int count)
{
    degree=count;
    koef=new int[degree+1];
}
Polinom::Polinom(const Polinom& pol)
{
    degree=pol.degree;
    koef=new int[degree+1];
    for(int i=degree;i>=0;i--)
        koef[i]=pol.koef[i];
}
int& Polinom::operator [](int index)
{
    static int iErr=-1;
    if(index>=0&&index<=degree)
        return koef[index];
    else
    {
        std::cout<<"Error with index!"<<'\n';
        return iErr;
    }
}
Polinom Polinom::operator+(Polinom& pol)
{
    if(degree==pol.degree)
    {
        Polinom temp(degree);
        for(int i=pol.degree;i>=0;i--)
            temp.koef[i]=koef[i]+pol.koef[i];
        return temp;
    }
    if(degree<pol.degree)
    {
        Polinom temp(pol.degree);
        for(int i=degree;i>=0;i--)
            temp.koef[i]=koef[i]+pol.koef[i];
        for(int i=pol.degree;i>=degree+1;i--)
            temp.koef[i]=pol.koef[i];
        return temp;
    }
    if(degree>pol.degree)
    {
        Polinom temp(degree);
        for(int i=pol.degree;i>=0;i--)
            temp.koef[i]=koef[i]+pol.koef[i];
        for(int i=degree;i>=pol.degree+1;i--)
            temp.koef[i]=koef[i];
        return temp;
    }
    return *this;
}
Polinom Polinom::operator *(Polinom& pol)
{
        Polinom temp;
        temp.degree=degree+pol.degree;
        temp.koef=new int[temp.degree+1];
        for(int i=0;i<=degree;i++)
        {
            for(int j=0;j<=pol.degree;j++)
                {
                    temp.koef[i+j] +=koef[i]*pol.koef[j];
                }
        }
        return temp;
}
Polinom& Polinom::operator =(Polinom& t)
{
    if(this==&t)
        {
            return *this;
        }
    degree=t.degree;
    for(int i=degree;i>=0;i--)
        koef[i]=t.koef[i];
    return *this;
}
Polinom Polinom::operator +(int &n)
{
    Polinom temp(degree);
    for(int i=degree;i>=0;i--)
    {
        temp.koef[i]=koef[i];
        if (i==0) temp.koef[i]=koef[i]+n;
    }
    return temp;
}
Polinom Polinom::operator *(int&n)
{
    Polinom temp(degree);
    for(int i=degree;i>=0;i--)
        temp.koef[i]=koef[i]*n;
    return temp;
}
bool Polinom::operator ==(Polinom&t)
{
    return(t.degree==degree);
}
bool Polinom::operator >=(Polinom&t)
{
    return(degree>=t.degree);
}
bool Polinom::operator <=(Polinom&t)
{
    return(degree<=t.degree);
}
int main()
{
    setlocale(LC_ALL, "Russian");
    int n=-10;
    int k=0;
    std::cout<<"Введите степень первого полинома\n";std::cin>>n;
    if(n==-10)
    {
        std::cout<<"Ошибка ввода. Введите число\n";
        exit(0);
    }
    Polinom p(n);
    p.input(n);
    int m=-10;
    std::cout<<"Введите степень второго полинома\n";std::cin>>m;
    if(m==-10)
    {
        std::cout<<"Ошибка ввода. Введите число\n";
        exit(0);
    }
    Polinom s(m);
    s.input(m);
    std::cout<<"Первый полином: " << p <<'\n';
    std::cout<<"Второй полином: " << s <<'\n';
    if(p.GetDegr()>=s.GetDegr())
        k=p.GetDegr();
    else
        k=s.GetDegr();
    Polinom t(k);
    t=p+s;
    std::cout<<"\n";
    std::cout<<"Сумма полиномов = " << t <<'\n';
    std::cout<<"Введите натуральное число для сложения с первым полиномом\n";std::cin>>n;
    if(n==-10)
    {
        std::cout<<"Ошибка ввода. Введите число\n";
        exit(0);
    }
    t=p+n;
    std::cout<<t<<'\n';
    std::cout<<"\n";
    std::cout<<"Введите натуральное число для сложения со вторым полиномом\n";std::cin>>n;
    if(n==-10)
    {
        std::cout<<"Ошибка ввода. Введите число\n";
        exit(0);
    }
    t=s+n;
    std::cout<<t<<'\n';
    std::cout<<"\n";
    std::cout<<"Введите натуральное число для умножения первого полинома\n";std::cin>>n;
    if(n==-10)
    {
        std::cout<<"Ошибка ввода. Введите число\n";
        exit(0);
    }
    t=p*n;
    std::cout<<t<<'\n';
    std::cout<<"\n";
    std::cout<<"Введите натуральное число для умножения второго полинома\n";std::cin>>n;
    if(n==-10)
    {
        std::cout<<"Ошибка ввода. Введите число\n";
        exit(0);
    }
    t=s*n;
    std::cout<<t<<'\n';
    std::cout<<"\n";
    if(p==s)
        std::cout<<"Полиномы равны\n";
    else if(p>=s)
        std::cout<<"Первый полином больше второго\n";
    else if(p<=s)
        std::cout<<"Первый полином меньше второго\n";
    Polinom x(p.GetDegr()+s.GetDegr());
    x=p*s;
    std::cout<<"\n";
    std::cout<<x<<'\n';
    system("pause");
    return 0;
}