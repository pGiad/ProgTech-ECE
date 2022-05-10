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