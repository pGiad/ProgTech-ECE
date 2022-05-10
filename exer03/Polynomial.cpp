#include <iostream>

using namespace std;

class Polynomial {
    protected:
    int exponMax;  
    class Term {
        protected:
        int exponent;
        int coefficient;
        Term *next;
        Term(int exp, int coeff, Term *n): exponent(exp),
            coefficient(coeff), next(n) {}
        friend class Polynomial;
    };
    Term *head;

    static Polynomial add(const Polynomial &p, const Polynomial &q) {
        Term *termp=p.head;
        Term *termq=q.head;
        Polynomial pol;

        while(termp!=nullptr && termq!=nullptr) {
            if(termp->exponent > termq->exponent) {
                pol.addTerm(termp->exponent, termp->coefficient);
                termp=termp->next;
            }
            else if(termp->exponent < termq->exponent) {
                pol.addTerm(termq->exponent, termq->coefficient);
                termq=termq->next;
            }
            else {
                pol.addTerm(termp->exponent, (termp->coefficient + termq->coefficient));
                termp=termp->next;
                termq=termq->next;
            }

            if(termp==nullptr) {
                while(termq!=nullptr) {
                    pol.addTerm(termq->exponent, termq->coefficient);
                    termq=termq->next;
                }
            }
            else if(termq==nullptr) {
                while(termp!=nullptr) {
                    pol.addTerm(termp->exponent, termp->coefficient);
                    termp=termp->next;
                }
            }
        }
        pol.exponMax=max(p.exponMax, q.exponMax);
        return pol;
    }

    static Polynomial multiply(const Polynomial &p, const Polynomial &q) {
        Polynomial pol;

        for(Term *termp=p.head; termp!=nullptr; termp=termp->next)
            for(Term *termq=q.head; termq!=nullptr; termq=termq->next)
                pol.addTerm(termp->exponent + termq->exponent, termp->coefficient * termq->coefficient);
        pol.exponMax=p.exponMax+q.exponMax;
        return pol;
    }

    static void print(const Polynomial &p) {
        if(p.head==nullptr || (p.head->next==nullptr && p.head->coefficient==0)) { cout << 0; return; }

        Term *t=p.head;
        while(t->coefficient==0 && t->next!=nullptr) t=t->next;
        if(t==nullptr || t->coefficient==0) { cout << 0; return; }
        if(t->exponent==0 && t->coefficient>0) { cout << t->coefficient; return; }
        if(t->exponent==0 && t-> coefficient<0) { cout << "- " << -(t->coefficient); return; }
        if(t->exponent==1 && t->coefficient==1) cout << "x";
        else if(t->exponent==1 && t->coefficient==-1) cout << "- x";
        else if(t->exponent==1) cout << t->coefficient << "x";
        else if(t->coefficient==1) cout << "x^" << t->exponent;
        else if(t->coefficient==-1) cout << "- x^" << t->exponent;
        else if(t->coefficient<0) cout << "- " << -(t->coefficient) << "x^" << t->exponent;
        else cout << t->coefficient << "x^" << t->exponent;

        if(t->next==nullptr) return;
        for(Term *q=t->next; q!=nullptr; q=q->next) {
            if(q->coefficient!=0) {
                if(q->exponent==0 && q->coefficient>0) { cout << " + " << q->coefficient; return; }
                else if(q->exponent==0 && q->coefficient<0) { cout << " - " << -(q->coefficient); return;}
                if(q->exponent==1 && q->coefficient==1) cout << " + x";
                else if(q->exponent==1 && q->coefficient==-1) cout << " - x";
                else if(q->exponent==1 && q->coefficient>0) cout << " + " << q->coefficient << "x";
                else if(q->exponent==1 && q->coefficient<0) cout << " - " << -(q->coefficient) << "x";
                else {
                    if(q->coefficient==1) cout << " + x^" << q->exponent;
                    else if(q->coefficient==-1) cout << " - x^" << q->exponent;
                    else if(q->coefficient>0 && q->coefficient!=1) cout << " + " << q->coefficient << "x^" << q->exponent;
                    else cout << " - " << -(q->coefficient) << "x^" << q->exponent;
                }
            }
        }
    }

    public:
    Polynomial() { head=nullptr; exponMax=0; }
    Polynomial(const Polynomial &p) {
        head=nullptr;
        Term *h=p.head;
        while(h!=nullptr) {
            addTerm(h->exponent, h->coefficient);
            h=h->next;
        }
        exponMax=p.exponMax;
    }
    
    ~Polynomial() {
        Term *t=head;
        while(t!=nullptr) {
            Term *p=t;
            t=t->next;
            delete p;
        }
        exponMax=0;
    }

    Polynomial & operator = (const Polynomial &p) {
        Term *t=head;
        while(t!=nullptr) { 
            Term *p=t;
            t=t->next;
            delete p;
        }
        head=nullptr;
        for(Term *q=p.head; q!=nullptr; q=q->next) addTerm(q->exponent, q->coefficient);
        exponMax=p.exponMax;
        return *this;
    }

    void addTerm(int expon, int coeff) {
        if(coeff==0) return;
        if(head==nullptr) {
            head = new Term(expon, coeff, nullptr);
            exponMax=expon;
            return;
        }
        if(exponMax<expon) {
            Term *newTerm = new Term(expon, coeff, head);
            head=newTerm;
            exponMax=expon;
            return;
        }
        Term *t=head;
        while(t!=nullptr) {
            if(t->exponent==expon) { 
                t->coefficient=t->coefficient+coeff;
                return;
            }
            if(t->next==nullptr) {
                Term *newTerm = new Term(expon, coeff, nullptr);
                t->next=newTerm;
                return;
            }
            if(t->next->exponent<expon) {
                Term *newTerm = new Term(expon, coeff, t->next);
                t->next=newTerm;
                return;
            }
            if(t->exponent>expon) t=t->next;
        }
    }

    double evaluate(double x) {
        Term *t=head;
        double sum=0;
        double product=x;
        while(t!=nullptr) {
            if(t->exponent==0) sum=sum+t->coefficient;
            else if(t->exponent==1) sum=sum+(t->coefficient*x);
            else {
                for(int i=1; i<t->exponent; ++i) product=product*x;
                product=product*(t->coefficient);
                sum=sum+product;
                product=x;
            }
            t=t->next;
        }
        return sum;
    }

    friend Polynomial operator + (const Polynomial &p, const Polynomial &q) { return add(p, q); }

    friend Polynomial operator * (const Polynomial &p, const Polynomial &q) { return multiply(p, q); }

    friend ostream & operator << (ostream &out, const Polynomial &p) { print(p); return out; }
};

/*
int main() {
    Polynomial p;
    p.addTerm(1, 3);
    p.addTerm(2, 1);
    p.addTerm(0, -1);

    Polynomial q(p);
    q.addTerm(1, -3);

    cout << "P(x) = " << p << endl;
    cout << "P(1) = " << p.evaluate(1) << endl;
    cout << "Q(x) = " << q << endl;
    cout << "Q(1) = " << q.evaluate(1) << endl;
    cout << "(P+Q)(x) = " << p+q << endl;
    cout << "(P*Q)(x) = " << p*q << endl;
}*/