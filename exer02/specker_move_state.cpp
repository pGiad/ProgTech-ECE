#include <iostream>
#include <stdexcept>

using namespace std;

class Move {
    public:
    int source_heap, source_coins, target_heap, target_coins;
    /* Take sc coins from heap sh and put tc coins to heap th.*/
    Move(int sh, int sc, int th, int tc);

    int getSource() const;
    int getSourceCoins() const;
    int getTarget() const;
    int getTargetCoins() const;

    friend ostream & operator << (ostream & out, const Move &move);
};

Move::Move(int sh, int sc, int th, int tc) {
    source_heap=sh;
    source_coins=sc;
    target_heap=th;
    target_coins=tc;
}

int Move::getSource() const {
    return source_heap;
}

int Move::getSourceCoins() const {
    return source_coins;
}

int Move::getTarget() const {
    return target_heap;
}

int Move::getTargetCoins() const {
    return target_coins;
}

ostream & operator << (ostream &out, const Move &move) {
    out << "takes " << move.source_coins << " coins from heap " 
        << move.source_heap << " and puts ";

    if(move.target_coins==0) out << "nothing";
    else out << move.target_coins << " coins to heap " 
             << move.target_heap;
    return out;    
}

class State {
    private:
    int *array;
    int maxHeaps;

    public:
    /* State with h heaps, where the i-th heap starts with c[i] coins.*/
    State(int h, const int c[]);
    ~State();

    void next(const Move &move) throw(logic_error);
    bool winning() const;

    int getHeaps() const;
    int getCoins(int h) const throw(logic_error);

    friend ostream & operator << (ostream &out, const State &state);
};

State::State(int h, const int c[]) {
    maxHeaps=h;
    array=new int[maxHeaps];
    for(int i=0; i<h; i++) array[i]=c[i];
}

State::~State() {
    delete[] array;
    array=nullptr;
}

void State::next(const Move &move) throw(logic_error) {
    int i,j,k,m;
    
    i=move.getSource();
    k=move.getSourceCoins();
    j=move.getTarget();
    m=move.getTargetCoins();
    
    if(array[i]==0) throw logic_error("empty heap");
    if(m>=k) throw logic_error("you put too many coins");
    if(k>array[i]) throw logic_error("you took too many coins");
    if(i<0 || i>=maxHeaps || j<0 || j>=maxHeaps) throw logic_error("invalid heap");
    
    array[i]=array[i]-k;
    array[j]=array[j]+m;
}

bool State::winning() const {
    int sum=0;
    for(int i=0; i<maxHeaps; i++) sum=sum+array[i];
    if(sum==0) return true;
    else return false;
}

int State::getHeaps() const {
    return maxHeaps;
}

int State::getCoins(int h) const throw(logic_error) {
    if(h<0 || h>=maxHeaps) throw logic_error("not valid heap");
    else return array[h];
}

ostream & operator << (ostream &out, const State &state) {
    out << state.array[0];
    for(int i=1; i<state.maxHeaps; i++) out << ", " << state.array[i];
    return out;
}