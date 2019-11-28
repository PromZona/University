#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <time.h>
using namespace std;

const int MAX_INPUT = 257;
const int SIZE = 5;
const char CHECK[SIZE] = "DICT";

struct TRBtree{
    char *key;
    unsigned long long value;
    char color;
    TRBtree *right;
    TRBtree *left;
    TRBtree *p;

    TRBtree(char *k, unsigned long long v, char c){
        int len = strlen(k) + 1;
        key = new char [len];
        for (int i = 0; i < len ; i++){
            key[i] = k[i];
        }
        value = v;
        color = c;
    }
    ~TRBtree(){
        delete [] key;
    }
};
TRBtree *nil;
TRBtree *root;

void LeftRotate(TRBtree *x){
    TRBtree *y;
    y = x->right;
    x->right = y->left;
    if( y->left != nil){
        y->left->p = x;
    }
    y->p = x->p;
    if(x->p == nil){
        root = y;
    }
    else if(x->p->left == x){
        x->p->left = y;
    }
    else x->p->right = y;
    y->left = x;
    x->p = y;
}

void RightRotate(TRBtree *x){
    TRBtree *y;
    y = x->left;
    x->left = y->right;
    if( y->right != nil){
        y->right->p = x;
    }
    y->p = x->p;
    if(x->p == nil){
        root = y;
    }
    else if(x->p->left == x){
        x->p->left = y;
    }
    else x->p->right = y;
    y->right = x;
    x->p = y;
}

TRBtree *RBSearch(char *word){
    TRBtree *r = root;
    int cmp;
    while(r != nil){
        cmp = strcmp(word,r->key);
        if(cmp < 0){
            r = r->left;
        }
        else if(cmp > 0){
            r = r->right;
        }
        else if(cmp == 0){
            return r ;
        }
    }
    return r;
}

void RBInsertFixup(TRBtree *node){

    TRBtree *y;
    while( node!=root && node->p->color == 'R'){
        if(node->p == node->p->p->left){
            y = node->p->p->right;
            if( y->color == 'R'){
                node->p->color = 'B';
                node->p->p->color = 'R';
                y->color = 'B';
                node=node->p->p;
            }
            else{
                if(node == node->p->right){
                    node = node->p;
                    LeftRotate(node);
                }
                node->p->color = 'B';
                node->p->p->color ='R';
                RightRotate(node->p->p);
            }
        }
        else{
            y = node->p->p->left;
            if(  y->color == 'R'){
                node->p->color = 'B';
                node->p->p->color = 'R';
                y->color = 'B';
                node=node->p->p;
            }
            else{
                if(node == node->p->left){
                    node = node->p;
                    RightRotate(node);
                }
                node->p->color = 'B';
                node->p->p->color ='R';
                LeftRotate(node->p->p);
            }
        }
    }
    root->color = 'B';
}

void RBInsert(char *word, unsigned long long number){
    if(root == nil){
        TRBtree *node = new TRBtree(word, number,'B');
        node->p = nil;
        node->right = nil;
        node->left = nil;
        //cout << "OK" << '\n';
        root = node;
    }
    else{
        TRBtree *r = root;
        TRBtree *y = NULL;
        int cmp;
        while(r != nil){
            y = r;
            cmp = strcmp(word,r->key);
            if(cmp < 0){
                r = r->left;
            }
            else if(cmp > 0){
                r = r->right;
            }
            else if(cmp == 0){
                cout << "Exist" << '\n';
                break;
            }
        }
        if(r == nil){
            TRBtree *node = new TRBtree(word, number,'R');
            node->p = y;
            node->right = nil;
            node->left = nil;
            if(cmp < 0){
                y->left = node;
            }
            else if(cmp > 0){
                y->right = node;
            }
            RBInsertFixup(node);
            //cout << "OK\n";
        }
    }
}

void RBDeleteFixup(TRBtree *node){
    while( node != root && node->color == 'B') {
        if(node == node->p->left) {
            TRBtree *bro = node->p->right;
            if( bro->color == 'R') {
                bro->color = 'B';
                node->p->color = 'R';
                LeftRotate(node->p);
                bro = node->p->right;
            }
            if(  bro->left->color == 'B' && bro->right->color == 'B') {
                bro->color = 'R';
                node = node->p;
            }
            else {
                if( bro->right->color == 'B') {
                    bro->left->color = 'B';
                    bro->color = 'R';
                    RightRotate(bro);
                    bro = node->p->right;
                }
                bro->color = node->p->color;
                node->p->color = 'B';
                bro->right->color = 'B';
                LeftRotate(node->p);
                node = root;
            }
        }
        else {
            TRBtree *bro = node->p->left;
            if( bro->color == 'R') {
                bro->color = 'B';
                node->p->color = 'R';
                RightRotate(node->p);
                bro = node->p->left;
            }
            if(  bro->right->color == 'B' && bro->left->color == 'B') {
                bro->color = 'R';
                node = node->p;
            }
            else {
                if(  bro->left->color == 'B') {
                    bro->right->color = 'B';
                    bro->color = 'R';
                    LeftRotate(bro);
                    bro = node->p->left;
                }
                bro->color = node->p->color;
                node->p->color = 'B';
                bro->left->color = 'B';
                RightRotate(node->p);
                node = root;
            }
        }
    }
    node->color = 'B';
}

void RBTransplant(TRBtree *tree1, TRBtree *tree2){

    if( tree1->p == nil){
        root = tree2;
    }
    else if(tree1->p->left == tree1){
        tree1->p->left = tree2;
    }
    else tree1->p->right = tree2;
    tree2->p = tree1->p;

}

void RBDelete(char *word){

    TRBtree *node = RBSearch(word);
    if(node == nil){
        cout << "NoSuchWord" << '\n';
    }
    else{
    TRBtree *y = node;
    TRBtree *x;
    char yColor = y->color;


    if(node->left == nil){
        x = node->right;
        RBTransplant(node, node->right);
    }
    else if(node->right == nil){
        x = node->left;
        RBTransplant(node, node->left);
    }
    else {
        y = y->right;
        while(y->left != nil){   // ищем минимальный игрик
            y = y->left;
        }
        yColor = y->color;
        x = y->right;
        if(y->p == node){
            x->p = y;
        }
        else{
            RBTransplant(y, y->right);
            y->right = node->right;
            y->right->p = y;
        }
        RBTransplant(node, y);
        y->left = node->left;
        y->left->p = y;
        y->color = node->color;
    }

    if(yColor == 'B'){
        RBDeleteFixup(x);
    }
  delete node;
  //cout << "OK" << '\n';
  }
}

void RBClean(TRBtree *r){
    if (r == nil){
        return ;
    }
    RBClean(r->left);
    RBClean(r->right);
    delete r;
    }

bool Save(ofstream &output, TRBtree *r){
    if(r == nil) {
       return true;
    }
    int a, b, len = strlen(r->key) + 1;
    output.write((char*) &len, sizeof(int));
    output.write(r->key, len);
    output.write((char*) &(r->value), sizeof(unsigned long long));
    output.write((char*) &(r->color), sizeof(char));
    if(output.bad()){
        return false;
    }
    if(r->left != nil){
        a = 1;
    }
    else{
        a = 0;
    }
    if(r->right != nil){
        b = 1;
    }
    else{
        b = 0;
    }
    output.write((char*) &a, sizeof(int));
    output.write((char*) &b, sizeof(int));
    Save(output, r->left);
    Save(output, r->right);
    return true;
}

bool Load(ifstream &input, TRBtree *p, int l = 0, int r = 0){
    int left, right;
    int len;
    unsigned long long value;
    char color;
    input.read((char*) &len, sizeof(int));
    if( input.eof()){
        return true;
    }
    char *word = new char [len];
    input.read(word, len);
    input.read((char*) &value, sizeof(unsigned long long));
    input.read((char*) &color, sizeof(char));
    input.read((char*) &left, sizeof(int));
    input.read((char*) &right, sizeof(int));

    if(input.bad()){
        return false;
    }
    TRBtree *node = new TRBtree(word, value, color);
    delete [] word;
    node->p = p;
    if(r){
        p->right = node;
    }
    else if(l){
        p->left = node;
    }
    if(left){
        Load(input, node, 1);
    }
    else{
        node->left = nil;
    }
    if(right){
        Load(input, node, 0, 1);
    }
    else{
        node->right = nil;
    }
    root = node;
    return true;
}

void ToLower(char *word) {
    int len = strlen(word);
    for (int i = 0; i < len; i++)
        word[i] = tolower(word[i]);
}

int main(){
    ifstream cin("test1.txt") ;
    ios::sync_with_stdio(false);
    unsigned long long number;
    char input [MAX_INPUT]={'\0'};
    nil = new TRBtree(input, 0, 'B');
    root = nil;
    clock_t start = clock();
    while(cin >> input){
            clock_t start = clock();
            if(input[0] == '+'){
                cin >> input;
                ToLower(input);
                cin >> number;
                RBInsert(input, number);
                std::cout << "OK\n";
            }
            else if(input[0] == '-'){
                cin >> input;
                ToLower(input);
                RBDelete(input);
                std::cout << "OK\n";
            }
            else if(input[0] =='!'){
                cin >> input;
                if( ! strcmp(input, "Save") ){
                    cin >> input;
                    ofstream output;
                    output.open(input, ios::binary);
                    if(!(output.is_open())){
                        cout << "ERROR: Couldn't create file\n";
                    }
                    else{
                    output.write((char*)&CHECK, sizeof(CHECK));
                    if(Save(output, root)){
                        cout << "OK\n";
                    }
                    else{
                        cout << "ERROR: Couldn't write down dictionary\n";
                        }
                    output.close();
                    }
                }
                else if( ! strcmp(input,"Load") ){
                    cin >> input;
                    ifstream inputt;
                    inputt.open(input, ios::binary);
                    if( ! (inputt.is_open()) ){
                        cout << "ERROR: Couldn't open file\n";
                    }
                    else{
                        RBClean(root);
                        root = nil;
                        char *s = new char[SIZE]; //проверка
                        inputt.read(s,SIZE);
                        if(inputt.bad()){
                            cout << "ERROR: Couldn't write dictionary\n";
                            delete [] s;
                            continue;
                        }
                        if(strcmp(s, "DICT")){
                            cout << "ERROR: Isn't dictionary\n";
                            delete [] s;
                            continue;
                        }
                        delete [] s;
                        if(Load(inputt,nil)){
                            cout << "OK\n";
                        }
                        else{
                            cout << "ERROR: Couldn't write dictionary\n";
                        }
                        inputt.close();
                    }
                }
            }
            else{
                ToLower(input);
                TRBtree *FindWord;
                FindWord = RBSearch(input);
                if(FindWord != nil){
                    cout << "OK: " << FindWord->value << '\n';
                }
                else{
                    cout << "NoSuchWord" << '\n';
                }
            }
    }
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    cout<<"Sec:"<< seconds<<endl;
    RBClean(root);
    return 0;
}