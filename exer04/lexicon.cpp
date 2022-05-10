#include <iostream>
#include <string>

using namespace std;

class lexicon {
    public:
    lexicon(): root(nullptr) {}
    ~lexicon() { purge(root); }

    void insert(const string &s) {
        if(root==nullptr) root = new node(s, 1, nullptr, nullptr, nullptr);
        else insert(root, s, 1);
    }
    
    int lookup(const string &s) const {
        if(root==nullptr) return 0;
        else return search(s, root);
    }
    
    int depth(const string &s) const {
        if(root==nullptr) return 0;
        else {
            node *t=root;
            if(search(s, t)!=0)  {
                int level=1;
                dsearch(s, root, level);
                return level;
            }
            else return 0;
        }
    }

    void replace(const string &s1, const string &s2) {
        node *t=root;
        find(s1, t);
        if(t==nullptr) return;
        else {
            int newFreq=t->freq;
            if(t->left==nullptr && t->right==nullptr) {
                node *p=t->parent;
                if(p!=nullptr) {
                    if(p->left==t) p->left=nullptr;
                    else p->right=nullptr;
                }
                else {
                    root=nullptr;
                    insert(s2);
                    root->freq=0;
                }
                delete t;
            }
            else if(t->left!=nullptr && t->right!=nullptr) {
                node *p=t->left;
                while(p->right!=nullptr) p=p->right;
                t->word=p->word;
                t->freq=p->freq;
                if(t->left==p) {
                    t->left=p->left;
                    if(p->left!=nullptr) p->left->parent=t;
                    delete p;
                }
                else {
                    p->parent->right=p->left;
                    if(p->left!=nullptr) p->left->parent=p->parent;
                    delete p;
                }
            }
            else {
                if(t->parent!=nullptr) {
                    node *p=t->parent;
                    if(t->left!=nullptr) {
                        if(p->left==t) {
                            p->left=t->left;
                            t->left->parent=p;
                            delete t;
                        }
                        else {
                            p->right=t->left;
                            t->left->parent=p;
                            delete t;
                        }
                    }
                    else {
                        if(p->left==t) {
                            p->left=t->right;
                            t->right->parent=p;
                            delete t;
                        }
                        else {
                            p->right=t->right;
                            t->right->parent=p;
                            delete t;
                        }
                    }
                }
                else {
                    if(t->left!=nullptr) {
                        root=t->left;
                        t->left->parent=nullptr;
                    }
                    else {
                        root=t->right;
                        t->right->parent=nullptr;
                    }
                }
            }
            node *q=root;
            insert(q, s2, newFreq);
        }
    }

    friend ostream & operator << (ostream &out, const lexicon &l) { printInorder(l.root); return out; }

    private:
    struct node {
        int freq;
        string word;
        node *left, *right, *parent;
        node(string s, int f, node *l, node *r, node *p): word(s), freq(f), left(l), right(r), parent(p) {}
    };
    node *root;

    static void purge(node *t) {
        if(t!=nullptr) {
            purge(t->left);
            purge(t->right);
            t->freq=0;
            delete t;
        }
    }

    static void insert(node *t, const string &s, int freq) {
        if(s.compare(t->word)<0) {
            if(t->left==nullptr) {
                t->left = new node(s, freq, nullptr, nullptr, t);
                return;
            }
            else return insert(t->left, s, freq);
        }
        else if(s.compare(t->word)>0) {
            if(t->right==nullptr) {
                t->right = new node(s, freq, nullptr, nullptr, t);
                return;
            }
            else return insert(t->right, s, freq);
        }
        else { t->freq+=freq; return; }
    }

    static int search(string s, node *t) {
        int result=0;
        if(s.compare(t->word)<0) {
            if(t->left==nullptr) return 0;
            else result=search(s, t->left);
        }
        else if(s.compare(t->word)>0) {
            if(t->right==nullptr) return 0;
            else result=search(s, t->right);
        }
        else if(s.compare(t->word)==0) result=t->freq;
        return result;
    }

    static void dsearch(string s, node *t, int &level) {
        if(s.compare(t->word)<0) { 
            level++;
            dsearch(s, t->left, level);
        }
        else if(s.compare(t->word)>0) {
            level++; 
            dsearch(s, t->right, level);
        }
        else return;
    }

    node * find(const string &s, node *&t) {
        while(t!=nullptr) {
            if(t->word==s) break;
            else if(t->word.compare(s)>0) t=t->left;
            else t=t->right;
        }
        return t;
    }

    static void printInorder(node *t) {
        if(t==nullptr) return;
        printInorder(t->left);
        cout << t->word << " " << t->freq << endl;
        printInorder(t->right);
    }
};
/*
int main() {
    lexicon l;
    l.insert("the");
    l.insert("boy");
    l.insert("and");
    l.insert("the");
    l.insert("wolf");
    cout << "The word 'the' is found " << l.lookup("the") << " time(s)" << endl;
    cout << "The word 'and' is found at depth " << l.depth("and") << endl;
    cout << l;
    l.replace("boy", "wolf");
    cout << "After replacement:\n";
    cout << l;
    cout << "Now the word 'and' is found at depth " << l.depth("and") << endl;
}*/