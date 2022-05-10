#include <iostream>
#include <string>
//#include "specker_move_state.hpp"

using namespace std;

class Player {          //PLAYER
    protected:
    int s_h, s_c, t_h, t_c;
    string name,type;

    public:
    Player() {}
    Player(const string &n);
    virtual ~Player() {}

    virtual const string & getType() const = 0;
    virtual Move play(const State &s) = 0;

    friend ostream & operator << (ostream &out, const Player &player);
};

Player::Player(const string &n) {
    name=n;
}

class GreedyPlayer: public Player {         //GREEDY PLAYER
    public:
    GreedyPlayer(const string &n) {
        name=n;
        type="Greedy player";
    }

    ~GreedyPlayer() override {
        name='\0';
    }

    const string & getType() const override {
        return type;
    }

    Move play(const State &s) override {
        int best=0;
        int k=s.getHeaps();
        for(int i=0; i<k; i++) best=max(best, s.getCoins(i));
        
        for(int i=0; i<k; i++) {
            if(best==s.getCoins(i)) {
                s_h=i;
                break;
            }
        }
        
        s_c=best;
        t_h=t_c=0;

        return Move(s_h, s_c, t_h, t_c);
    }
};

class SpartanPlayer: public Player {            //SPARTAN PLAYER
    public:
    SpartanPlayer(const string &n) {
        name=n;
        type="Spartan player";
    }

    ~SpartanPlayer() override {
        name='\0';
    }

    const string & getType() const override {
        return type;
    }    

    Move play(const State &s) override {
        int best=0;
        int k=s.getHeaps();
        for(int i=0; i<k; i++) best=max(best, s.getCoins(i));
        
        for(int i=0; i<k; i++){
            if(best==s.getCoins(i)) {
                s_h=i;
                break;
            }
        }

        s_c=1;
        t_h=t_c=0;

        return Move(s_h, s_c, t_h, t_c);
    }
};

class SneakyPlayer: public Player {         //SNEAKY PLAYER
    public:
    SneakyPlayer(const string &n) {
        name=n;
        type="Sneaky player";
    }

    ~SneakyPlayer() override {
        name='\0';
    }

    const string &getType() const override {
        return type;
    }

    Move play(const State &s) override {
        int best=1000000;
        int k=s.getHeaps();
        for(int i=0; i<k; i++) 
        if(s.getCoins(i)!=0) best=min(best, s.getCoins(i));
        
        for(int i=0; i<k; i++) {
            if(best==s.getCoins(i)) {
                s_h=i;
                break;
            }
        }

        s_c=best;
        t_h=t_c=0;

        return Move(s_h, s_c, t_h, t_c);
    }
};

class RighteousPlayer: public Player {          //RIGHTEOUS PLAYER
    public:
    RighteousPlayer(const string &n) {
        name=n;
        type="Righteous player";
    }

    ~RighteousPlayer() override {
        name='\0';
    }

    const string & getType() const override {
        return type;
    }

    Move play(const State &s) override {
        int best1=0;
        int best2=1000000;
        int k=s.getHeaps();
        for(int i=0; i<k; i++) {
            best1=max(best1, s.getCoins(i));
            best2=min(best2, s.getCoins(i));
        }

        for(int i=0; i<k; i++) {
            if(best1==s.getCoins(i)) {
                s_h=i;
                break;
            }
        }
        
        if(best1%2==0) s_c=(best1)/2;
        else s_c=(best1)/2+1;        

        for(int i=0; i<k; i++) {
            if(best2==s.getCoins(i)) {
                t_h=i;
                break;
            }
        }
        
        t_c = s_c - 1;

        return Move(s_h, s_c, t_h, t_c);
    }
};

ostream & operator << (ostream &out, const Player &player) {            //OPERATOR <<
    out << player.type << " " << player.name;
    return out;
}