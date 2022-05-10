#include <iostream>

using namespace std;

template <typename T>
class stack {

    private:
    int SIZE;
    T *info;
    int top;

    public:
    
    stack(int size) {
        info=new T[size];
        SIZE=size;
        top=0;
    }

    stack(const stack &s) {
        SIZE=s.SIZE;
        info=new T[SIZE];
        top=s.top;
        for(int i=0; i<s.top; i++) info[i]=s.info[i];
    }

    ~stack() {
        SIZE=top=0;
        delete[] info;
        info=nullptr;
    }

    const stack & operator = (const stack &s) {
        this->~stack();
        SIZE=s.SIZE;
        info=new T[SIZE];
        top=s.top;
        for(int i=0; i<top; i++) info[i]=s.info[i];
    }

    bool empty() {
        return top==0;
    }

    void push(const T &x) {
        info[top]=x;
        top++;
    }

    T pop() {
        return info[--top];
    }

    int size() {
        return top;
    }

    friend ostream & operator << (ostream &out, const stack &s) {
        out << "[";
        if(s.top==0) {
            out << "]";
            return out;
        }
        else {
            out << s.info[0];
            for(int i=1; i<s.top; i++) out << ", " << s.info[i];
            out << "]";
            return out;
        }
    }
};

#ifndef CONTEST

int main() {
  //integers
  stack<int> s(10);
  cout << "s is empty: " << s << endl;
  s.push(42);
  cout << "s has one element: " << s << endl;
  s.push(17);
  s.push(34);
  cout << "s has more elements: " << s << endl;
  cout << "How many? " << s.size() << endl;
  stack<int> t(5);
  t.push(7);
  cout << "t: " << t << endl;
  t=s;
  cout << "popping from s: " << s.pop() << endl;
  s.push(8);
  stack<int> a(s);
  t.push(99);
  a.push(77);
  cout << "s: " << s << endl;
  cout << "t: " << t << endl;
  cout << "a: " << a << endl;
  //doubles
  stack<double> c(4);
  c.push(3.14);
  c.push(1.414);
  cout << "c contains doubles " << c << endl;
  //characters
  stack<char> k(4);
  k.push('$');
  cout << "k contains a character " << k << endl;
}

#endif