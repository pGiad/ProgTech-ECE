#include <iostream>

using namespace std;

template <typename T>
class stack {

  private:
    int SIZE;
    struct node {
      T info;
      node *next;
    };
    node *head;

  public:
    stack(int size);
    stack(const stack &s);
    ~stack();

    const stack<T> & operator = (const stack<T> &s) {
      node *p=head;
      node *q=s.head;

      while(q!=nullptr) {
        p->info=q->info;
        q=q->next;
        if(p->next!=nullptr) p=p->next;
        else {
          p->next=new node;
          p=p->next;
        }
      }
      node *t=head;
      while(t->next!=p) t=t->next;
      t->next=nullptr;
      delete p;
    }

    bool empty();
    void push(const T &x);
    T pop();
        int size();

    friend ostream & operator << (ostream &out, const stack<T> &s) {
      node *p=s.head;
      out << "[";
      if(p==nullptr) out << "]";
      else {
        out << p->info;
        while(p->next!=nullptr) {
          p=p->next;
          out << ", " << p->info;
        }
        out << "]";
      }
      return out;
    }
};

template<typename T>
stack<T>::stack(int size) {
  head=nullptr;
  SIZE=size;
}

template<typename T>
stack<T>::stack(const stack &s) {
  head=nullptr;
  SIZE=s.SIZE;
  node *q=s.head;
  while(q!=nullptr) {
    push(q->info);
    q=q->next;
  }
}

template<typename T>
stack<T>::~stack() {
  node *p=head;
  while(p!=nullptr){
    head=p->next;
    p=p->next;
  }
  head=p->next;
  delete head, p;
}

template<typename T>
bool stack<T>::empty() {
  return head==nullptr;
}

template<typename T>
void stack<T>::push(const T &x) {
  T save;
  node *p=new node;
  node *q;
  p->info=x;
  p->next=head;
  head=p;
  while(p->next!=nullptr) {
    q=p;
    p=p->next;
    save=q->info;
    q->info=p->info;
    p->info=save;
  }
}

template<typename T>
T stack<T>::pop() {
  node *p=head, *q=head;
  T result;
  while(p->next!=nullptr) p=p->next;
  result=p->info;
  while(q->next!=p) q=q->next;
  q->next=nullptr;
  delete p;
  return result;
}

template<typename T>
int stack<T>::size() {
  int k=0;
  node *p=head;
  while(p!=nullptr) {
    k++;
    p=p->next;
  }
  delete p;
  return k;
}

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