#include <iostream>
#include <stdexcept>
#include <vector>
#include "specker_move_state.hpp"
#include "specker_player.hpp"

using namespace std;

class Game {
    private:
    int Heaps=0, Players=0, i=0, j=0;
    int *c;
    vector<Player*> plr;

    public:
    Game(int heaps, int players);
    ~Game();

    void addHeap(int coins) throw(logic_error);
    void addPlayer(Player *player) throw(logic_error);
    void play(ostream &out) throw(logic_error);
};

Game::Game(int heaps, int players) {
    Heaps=heaps;
    Players=players;
    c = new int[Heaps];
    for(int i=0; i<Heaps; i++) c[i]=0;
    plr.clear();
}

Game::~Game() {
    Heaps=Players=0;
}

void Game::addHeap(int coins) throw(logic_error) {
    if(i>=Heaps) throw logic_error("max heaps");
    c[i]=coins;
    i++;
}

void Game::addPlayer(Player *player) throw(logic_error) {
    if(j>=Players) throw logic_error("max players");
    plr.push_back(player);
    j++;
}

void Game::play(ostream &out) throw(logic_error) {
    State st(Heaps, c);
    out << "State: " << st << endl;
    for(int i=0; i<Players; i++) {
        out << *plr[i] << " " << plr[i]->play(st) << endl;        
        st.next(plr[i]->play(st));
        out << "State: " << st << endl;
        if(st.winning()) {
            out << *plr[i] << " wins" << endl;
            break;
        }
        if(i==Players-1) i=-1;
    }
}

int main() {
    Game specker(3,4);
    specker.addHeap(10);
    specker.addHeap(20);
    specker.addHeap(17);
    specker.addPlayer(new SneakyPlayer("Tom"));
    specker.addPlayer(new SpartanPlayer("Mary"));
    specker.addPlayer(new GreedyPlayer("Alan"));
    specker.addPlayer(new RighteousPlayer("Robin"));
    specker.play(cout);
}