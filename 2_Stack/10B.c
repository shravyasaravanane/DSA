#include <iostream>
#include <stack>
#include <string>
using namespace std;
bool isOperator(char c)
{
    return c=='+'||c=='-'||c=='*'||c=='/'||c=='^';
}
string postToPre(string post_exp)
{
    stack<string> s;
    for(int i=0;i<(int)post_exp.length();i++)
    {
        if(isOperator(post_exp[i]))
        {
            string op1=s.top();
            s.pop();
            string op2=s.top();
            s.pop();
            s.push(post_exp[i]+op2+op1);
        }
        else
            s.push(string(1,post_exp[i]));
    }
    return s.top();
}
int main()
{
    string post_exp;
    cin>>post_exp;
    cout<<postToPre(post_exp);
    return 0;
}