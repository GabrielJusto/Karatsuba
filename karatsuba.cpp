

//compilar: g++ karatsuba.cpp -o karatsuba
//executar ./karatsuba  "multiplicador" "multiplicando"

#include <iostream>
#include <string>
#include <math.h>
#include<stdlib.h>
using namespace std;


string concatZero(string s, int n)
{
    for(int i=0; i<n; i++)
        s += "0";
    return s; 
}


void normalize(string* s1, string* s2)
{
    string a = *s1;
    string b = *s2;

    int n = min(b.size(), a.size());
    if(a.size()<b.size())
    {
        for(int i=n; i<b.size(); i++)
            a = "0"+a;
    }
    else
    {
        for(int i=n; i<a.size(); i++)
            b = "0"+b;
    }
    *s1 = a;
    *s2 = b;
}






string _strSum(string a, string b, int size,  string result,  int over)
{
    if(size == 0)
        return result;
    if(size == 1)
    {
        result = to_string((a[size-1]-48) + (b[size-1]-48)+over)+result;
        return result;
    }
    else
    {
        result = to_string((((a[size-1]-48) + (b[size-1]-48)+over)%10))+result;
        if((a[size-1]-48) + (b[size-1]-48)+over > 9)
            over = 1;
        else
            over = 0;

        size--;
        return _strSum(a, b, size, result, over);
    }
}
string strSum(string a, string b,  string result = "",  int over=0)
{ 
    normalize(&a, &b);
    return _strSum(a, b, a.size(), result, over);
}






string _subStr(string a, string b, int size,  string result, int over)
{
    if(size == 0)
        return result;

    int op1, op2;
    op1 = (a[size-1]-48) - over;
    op2 = b[size-1]-48;
    over = 0;

    if ((op1-op2) < 0 || op1 < 0)
    {
        op1 = op1 + 10;
        over = 1;
    }
        
    result = to_string(op1-op2) + result;
    size--;
    return _subStr(a, b, size, result, over);
    
    
}

string strSub(string a, string b,  string result = "", int over = 0)
{
    // string sma;
    // string larg;
    // bool neg;
    // if(stoi(a)<stoi(b))
    // {
    //     sma = a;
    //     larg = b;
    //     neg = true;
    // }
    // else
    // {
    //     sma = b;
    //     larg = a;
    //     neg = false;
    // }
    normalize(&a, &b);
        
    return _subStr(a, b, a.size(), result, over);
}



string karatsuba (string multiplicand , string multiplier)
{

    if(multiplier.size() == 1 && multiplicand.size() == 1)
        return to_string(stoi(multiplicand) * stoi(multiplier));

    int n = max(multiplicand.size(), multiplier.size())/2;
    normalize(&multiplicand, &multiplier);
     
    
    string a = multiplicand.substr(0, multiplicand.size()-n);
    string b = multiplicand.substr(multiplicand.size()-n, n);
    string c = multiplier.substr(0, multiplier.size()-n);
    string d = multiplier.substr(multiplier.size()-n, n);

    

    string ac = karatsuba(a,c);
    string bd = karatsuba(b,d);
    string a_plus_b = strSum(a,b);
    string c_plus_d = strSum(c,d);
    string ac_plus_bd = strSum(ac, bd);
    ac = concatZero(ac,n*2);

    string mid = karatsuba(a_plus_b, c_plus_d);
    mid = concatZero(strSub(mid, ac_plus_bd), n);
    // string ad = karatsuba(a,d);
    // string bc = karatsuba(b,c);
    // string mid = concatZero(strSum(ad,bc), n/2);
    string result = strSum(strSum(ac, mid), bd);
    

    return result;
    
}


int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cout<<"insira dois números como argumento"<<endl;
        return 0;
    }
    string a = argv[1];
    string b = argv[2];


    string kar = karatsuba (a, b);
    cout<<"\n Karatsuba: "<< kar <<endl;


    //test 
    // string result;
    // for(long int i=0; i<pow(10,18); i++)
    // {
    //     for(long int j=0; j<pow(10,3); j++)
    //     {
    //         result = karatsuba(to_string(j), to_string(i));
    //         if(stoi(result) != j*i)
    //         {
    //             cout<<"error"<<endl;
    //             cout<<"i="<<i<<" j="<<j<<endl;
    //         }
    //         cout<<i<<"*"<<j<<"="<<result<<endl;
    //     }
    // }


}