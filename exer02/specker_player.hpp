#include <iostream>
#include <string>

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


class GreedyPlayer: public Player {         //GREEDY PLAYER
    public:
    GreedyPlayer(const string &n);
    ~GreedyPlayer() override;

    const string & getType() const override;
    Move play(const State &s) override;
}; 

class SpartanPlayer: public Player {            //SPARTAN PLAYER
    public:
    SpartanPlayer(const string &n);
    ~SpartanPlayer() override;

    const string & getType() const override;
    Move play(const State &s) override;
};

class SneakyPlayer: public Player {         //SNEAKY PLAYER
    public:
    SneakyPlayer(const string &n);
    ~SneakyPlayer() override;

    const string &getType() const override;
    Move play(const State &s) override;
};

class RighteousPlayer: public Player {          //RIGHTEOUS PLAYER
    public:
    RighteousPlayer(const string &n);
    ~RighteousPlayer() override;

    const string & getType() const override;
    Move play(const State &s) override;
};