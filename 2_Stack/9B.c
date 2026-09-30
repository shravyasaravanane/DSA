#include <iostream>
#include <queue>
using namespace std;
class Stack
{
    queue<int> q;
public:
    void push(int val);
    void pop();
    int top();
};
void Stack::push(int val)
{
    int s=q.size();
    q.push(val);
    for(int i=0;i<s;i++)
    {
        q.push(q.front());
        q.pop();
    }
}
void Stack::pop()
{
    q.pop();
}
int Stack::top()
{
    return q.front();
}
int main()
{
    int n,m,x;
    Stack s;
    cin>>n>>m;
    for(int i=0;i<n;i++)
    {
        cin>>x;
        s.push(x);
    }
    cout<<"top of element "<<s.top()<<endl;
    for(int i=0;i<m;i++)
        s.pop();
    cout<<"top of element "<<s.top()<<endl;
    return 0;
}