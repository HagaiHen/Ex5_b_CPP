#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <stack>

#define MAX_VALUE 1000000000

using namespace std;


namespace ariel {
    
    class Node {

        private:
            string data;
            Node* parent;
            vector<Node*> childs;
            int level;

        public:
            Node(const string &d) : data(d) {}
            string get_data() { return this->data; };
            void set_data(const string &s) { this->data=s; };
            Node * get_parent() { return this->parent; };
            void set_parent(Node *n) { this->parent = n; };
            friend ostream &operator<<(ostream &stream, const Node &n) {
                stream << n.data;
                return stream;
            }
            int get_level() {return this->level; };
            void set_level(int l) {this->level = l; };

            vector<Node*> get_childs() { return this->childs; };

            void add_childs(Node * son) {
                this->childs.push_back(son);
            }

            

    };

    class LevelIter {
        private:
            Node * curr;
            vector<Node*> s;

        public:
            LevelIter() : curr(nullptr) {}
            LevelIter (Node* root) : curr(root) { //roll all over the nodes and adding all childs 
                vector<Node*> tmp;
                tmp.push_back(this->curr);
                this->s.push_back(this->curr);
                while (tmp.size() > 0) {
                        this->curr = tmp.front();
                        tmp.erase(tmp.begin());
                        for (size_t i = 0; i < curr->get_childs().size(); i++) { //get all the childs and adding them
                            s.push_back(this->curr->get_childs()[i]);
                            tmp.push_back(this->curr->get_childs()[i]);
                        }
                }

                //to avoid duplicates, the curr and the first element in the list are identical
                this->curr = root;
                this->s.erase(this->s.begin());
            }

            Node* get_curr () {
                return this->curr;
            }

            LevelIter& operator++() { //simply roll all over the vector
                if (this->s.size() == 0) {
                    this->curr = nullptr;
                    return *this;
                    //cout << "hhh" << endl;
                }

                this->curr = this->s.front();
                this->s.erase(this->s.begin());
                return *this;

            }

            LevelIter operator++(int) {
                
                LevelIter it = *this;
                ++(*this);
                return it;
            }

            LevelIter& operator--() {
                curr--;
                return *this;
            }

            LevelIter operator--(int) {
                LevelIter it = *this;
                --(*this);
                return it;
            }

            LevelIter& operator[](int index) {
                this->curr = this->curr + index;
                return *this;
            }

            LevelIter* operator->() {
                return this;
            }

            string operator*() {
                return this->curr->get_data();
            }

            bool operator==(const LevelIter& other) const {
                return this->curr == other.curr;
            }

            bool operator!=(const LevelIter& other) const {
                return !(this->curr == other.curr);
            }

            friend ostream &operator<<(ostream &stream, const LevelIter &it) {
                stream << it.curr;
                return stream;
            }

            int size() {
                return this->curr->get_data().size();
            }         


    };

    class RevLevelIter {
        private:
            Node * curr;
            vector<Node*> s;

        public:
            RevLevelIter() : curr(nullptr) {}
            RevLevelIter (Node* root) : curr(root) {
                vector<Node*> tmp;
                tmp.push_back(this->curr);
                this->s.push_back(this->curr);
                while (tmp.size() > 0) {
                    this->curr = tmp.front();
                    tmp.erase(tmp.begin());                    
                    for (int i = curr->get_childs().size() - 1; i >= 0; i--) {
                        s.push_back(this->curr->get_childs()[(size_t)i]);
                        tmp.push_back(this->curr->get_childs()[(size_t)i]);
                    }
                }

                //using the stack for reverse
                stack<Node*> stack;
                for (size_t i =0; i < this->s.size(); i++) {
                    stack.push(this->s[i]);
                }
                size_t size = stack.size();
                this->s.clear();
                for (size_t i =0; i < size; i++) {
                    s.push_back(stack.top());
                    stack.pop();
                }
                //remove dup, the curr and the first element in vector are identicals
                this->s.erase(this->s.begin());

            }

            RevLevelIter& operator++() { //simply roll all over the vector
                if (this->s.size() == 0) {
                    this->curr = nullptr;
                    return *this;
                }
                
                this->curr = this->s.front();
                this->s.erase(this->s.begin());
                return *this;
            }

            RevLevelIter operator++(int) {
                RevLevelIter it = *this;
                ++(*this);
                return it;
            }

            RevLevelIter& operator--() {
                curr--;
                return *this;
            }

            RevLevelIter operator--(int) {
                RevLevelIter it = *this;
                --(*this);
                return it;
            }

            RevLevelIter& operator[](int index) {
                this->curr = this->curr + index;
                return *this;
            }

            RevLevelIter* operator->() {
                return this;
            }

            string operator*() {
                return this->curr->get_data();
            }

            bool operator==(const RevLevelIter& other) const {
                return curr == other.curr;
            }

            bool operator!=(const RevLevelIter& other) const {
                return !(this->curr == other.curr);
            }

            friend ostream &operator<<(ostream &stream, const RevLevelIter &it) {
                stream << it.curr;
                return stream;
            }

            int size() {
                return this->curr->get_data().size();
            }         


    };

    class PreOrderIter {
        private:
            Node * curr;
            vector<Node*> s;

        public:
            PreOrderIter() : curr(nullptr) {}
            PreOrderIter (Node* root) : curr(root) {
                stack<Node*> Stack;
                vector<string> PreOrder;
                Stack.push(this->curr);
                while (!Stack.empty()) {
                    Node* tmp = Stack.top();
                    Stack.pop();
                    this->s.push_back(tmp); //add to the final list
                    for (int i = tmp->get_childs().size() - 1; i >= 0; i--) { //push all the childs from right to left
                        Stack.push(tmp->get_childs()[(size_t)i]);
                    }      
                }

                //initial the current
                this->curr = root;
                this->s.erase(this->s.begin());
            }

            PreOrderIter& operator++() { //simply roll over the vector
                if (this->s.size() == 0) {
                    this->curr = nullptr;
                    return *this;
                }
                this->curr = this->s.front();
                this->s.erase(this->s.begin());
                return *this;
            }

            PreOrderIter operator++(int) {
                PreOrderIter it = *this;
                ++(*this);
                return it;
            }

            PreOrderIter& operator--() {
                curr--;
                return *this;
            }

            PreOrderIter operator--(int) {
                PreOrderIter it = *this;
                --(*this);
                return it;
            }

            PreOrderIter& operator[](int index) {
                this->curr = this->curr + index;
                return *this;
            }

            PreOrderIter* operator->() {
                return this;
            }

            int length() {
                return this->curr->get_data().size();
            }

            char at (size_t i) {
                return this->curr->get_data().at(i);
            }

            string operator*() {
                return this->curr->get_data();
            }

            bool operator==(const PreOrderIter& other) const {
                return curr == other.curr;
            }

            bool operator!=(const PreOrderIter& other) const {
                return !(this->curr == other.curr);
            }

            friend ostream &operator<<(ostream &stream, const PreOrderIter &it) {
                stream << it.curr;
                return stream;
            }

            int size() {
                return this->curr->get_data().size();
            }         


    };

    
    class OrgChart {

        private:
            Node * root;
            unordered_map<string, vector<Node*>> childs;
            int size = 0;

        
        public:

            OrgChart() : root (nullptr) {} //default constructor

            OrgChart& add_root (const string &s) {
                if (s.size() == 0) {
                    throw invalid_argument("invalid name");
                }
                if (!this->root) {
                    this->size += 1;
                    this->root = new Node(s);
                    this->root->set_data(s);
                } else {
                    this->root->set_data(s);
                }
                this->root->set_level(0);
                return *this;
            }
            //Add a child to some father
            OrgChart& add_sub (const string &s1, const string &s2) {
                if (s2.size() == 0) {
                    throw invalid_argument("invalid name");
                }
            	if (this->root == nullptr) {
                    throw invalid_argument("can't add sub before root");
                }
                if (this->get_node(s1) == nullptr) {
                    throw invalid_argument("this node isnt exists");
                }
                this->size += 1;
                Node * n = new Node(s2);
                n->set_parent(this->get_node(s1));
                this->get_node(s1)->add_childs(n);
                int tmp = this->get_node(s1)->get_level();
                n->set_level(++tmp);
                this->childs[s1].push_back(n);
                this->childs[s2];
                return *this;
            }

            LevelIter begin_level_order() const {
                if (this->root == nullptr) {
                    throw invalid_argument("chart is empty!");
                }
                return LevelIter(this->root);
            }

            LevelIter end_level_order() const {
                if (this->root == nullptr) {
                    throw invalid_argument("chart is empty!");
                }
                return LevelIter();
            }

            RevLevelIter begin_reverse_order() const {
                if (this->root == nullptr) {
                    throw invalid_argument("chart is empty!");
                }
                return RevLevelIter(this->root);
            }

            RevLevelIter reverse_order() const {
                if (this->root == nullptr) {
                    throw invalid_argument("chart is empty!");
                }
                return RevLevelIter();
            }
            
            PreOrderIter begin_preorder() const {
                if (this->root == nullptr) {
                    throw invalid_argument("chart is empty!");
                }
                return PreOrderIter(this->root);
            }

            PreOrderIter end_preorder() const {
                if (this->root == nullptr) {
                    throw invalid_argument("chart is empty!");
                }
                return PreOrderIter();
            }

            friend ostream &operator<<(ostream &stream, const OrgChart &tree) {
                string line = "------";
                string enter = "|";
                string space = "    ";
                stream << tree.root->get_data();
                vector<Node*> tmp;
                tmp.push_back(tree.root);
                stream << "\n";
                int currLevel = 1;
                size_t pos = 1;
                while (tmp.size() != tree.size) {   
                    
                    for (auto it = tree.begin_level_order(); it != tree.end_level_order(); ++it) {
                        if (tree.get_node(*it)->get_level() == currLevel) {
                            stream << enter << line;
                            tmp.push_back(tree.get_node(*it));
                            
                        }
                    }
                    stream << "\n";
                    for (size_t i = pos; i < tmp.size(); i++) {
                        stream << tmp[i]->get_data() << space;
                        pos++;
                    }
                    stream << "\n";
                    currLevel++;
                }
                

                return stream;
            }
            
            LevelIter begin() {
                return LevelIter(this->root);
            }
            
            LevelIter end() {
                return LevelIter();
            }

            unordered_map<string, vector<Node*>> * get_childs() { return &this->childs; }; 

            Node * get_root() { return this->root; };

            vector<Node*> get_sub(const string &s) {

                unordered_map<string, vector<Node*>>::iterator it = this->childs.begin();
                while(it != this->childs.end()) {
                    if (it->first == s) {
                        return this->childs[s];
                    }
                    it++;
                }
                throw invalid_argument("No such Node");

            }

            Node * get_node(const string &s)  const {
                if (this->root->get_data() == s) {
                    return this->root;
                } else {
                    for (const auto & [key, val] : this->childs) {
                        for (size_t i = 0; i < val.size(); i++) {
                            if (val[i]->get_data() == s) {
                                return val[i];
                            }
                        }
                    }
                }
                return nullptr;
            }

            ~OrgChart() {
            
                if (root) {
                    for (auto it = begin_level_order(); it != end_level_order(); ++it) {
                        delete it.get_curr();
                    }
                }
            }

            
    };
}
