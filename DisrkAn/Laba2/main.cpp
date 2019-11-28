#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <time.h>

const int OUT_OF_RANGE = 1;
const int DOES_NOT_EXIST = 2;
const int KEY_EXIST = 3;
const int FILE_ERROR = 4;
const int BLACK = 5;
const int RED = 6;
const int MAX_KEY_SIZE = 257;

struct TDict{
    char Key[MAX_KEY_SIZE];
    unsigned long long Value;
};

struct TRBNode{
    TDict Dict;
    int Color;
    TRBNode* Left;
    TRBNode* Right;
    TRBNode* Father;
};

class TRBtree{
public:

    TRBtree(){
        Nil = new TRBNode;
        Nil->Color = BLACK;
        Nil->Left = nullptr;
        Nil->Right = nullptr;
        Root = Nil;
    }

    TRBtree(TDict dic){
        Nil = new TRBNode;
        Nil->Color = BLACK;
        Nil->Left = nullptr;
        Nil->Right = nullptr;

        Root = new TRBNode;
        Root->Color = BLACK;
        Root->Left = Nil;
        Root->Right = Nil;
        Root->Father = Nil;
        Root->Dict = dic;

        Nil->Father = Root;
    }

    void Add(TDict dic){
        if (Root == Nil){
            TRBNode* node = new TRBNode;
            node->Color = BLACK;
            node->Dict = dic;
            node->Left = Nil;
            node->Right = Nil;
            node->Father = Nil;
            Root = node;
            return;
        }
        TRBNode* x = Root;
        TRBNode* y = nullptr;
        while (x != Nil){
            y = x;
            if(strcmp(dic.Key, x->Dict.Key) < 0){
                x = x->Left;
            }
            else if (strcmp(dic.Key, x->Dict.Key) > 0){
                x = x->Right;
            }
            else{
                throw KEY_EXIST;
                break;
            }
        }
        if (x == Nil){
            TRBNode* z = new TRBNode;
            z->Dict = dic; // important
            z->Father = y;
            if (y == Nil){
                Root = z;
            }
            else if (strcmp(dic.Key, y->Dict.Key) < 0){
                y->Left = z;
            }
            else if (strcmp(dic.Key, y->Dict.Key) > 0){
                y->Right = z;
            }
            z->Left = Nil;
            z->Right = Nil;
            z->Color = RED;
            FixInsertiont(z);
        }
    }

    void Erase(TDict dic){
        if(Root == Nil) throw DOES_NOT_EXIST;
        if(strcmp(Root->Dict.Key, dic.Key) == 0){
            if(Root->Right == Nil && Root->Left == Nil){
                delete Root;
                Root = Nil;
                return;
            }
        }
        TRBNode* buf = Root;
        int color = RED;

        while(buf != Nil){
            if(strcmp(dic.Key, buf->Dict.Key) > 0){
                buf = buf->Right;
            }
            else if (strcmp(dic.Key, buf->Dict.Key) < 0){
                buf = buf->Left;
            }
            else{ // found
                break;
            }

            if (buf == Nil) throw DOES_NOT_EXIST;
        }

        TRBNode* y = buf;
        TRBNode* x = Nil;
        color = y->Color;

        if(buf->Left == Nil){
            x = buf->Right;
            Transparent(buf, buf->Right);
        }
        else if(buf->Right == Nil){
            x = buf->Left;
            Transparent(buf, buf->Left);
        }
        else{
            y = MaxLeft(buf->Right);
            color = y->Color;
            x = y->Right;
            if(y->Father == buf){
                x->Father = y;
            }
            else{
                Transparent(y, y->Right);
                y->Right = buf->Right;
                y->Right->Father = y;
            }
            Transparent(buf, y);
            y->Left = buf->Left;
            y->Left->Father = y;
            y->Color = buf->Color;
        }
        delete buf;
        if (color == BLACK) FixErase(x);
    }

    unsigned long long Find(TDict dic){
        TRBNode* buf = Root;
        if(Root == Nil) throw DOES_NOT_EXIST;
        while(buf != Nil){
            if(strcmp(dic.Key, buf->Dict.Key) > 0){
                buf = buf->Right;
            }
            else if ((strcmp(dic.Key, buf->Dict.Key) < 0)) {
                buf = buf->Left;
            }
            else{
                return buf->Dict.Value;
            }

            if (buf == Nil){
                throw DOES_NOT_EXIST;
            } 
        }
        return buf->Dict.Value;
    }

    void SaveOrLoad(){
        char command[MAX_KEY_SIZE];
        char path[MAX_KEY_SIZE];
        std::cin >> command >> path;
        if(command[0] == 'S'){
            std::ofstream os(path);
            if(!(os.is_open())){
                throw FILE_ERROR;
            }
            os << "DronDict\n";
            Serialize(Root, os);
            os.close();
        }
        else{
            std::ifstream is(path);
            if(!(is.is_open())){
                throw FILE_ERROR;
            }
            char buf[10];
            is >> buf;
            if(strcmp(buf, "DronDict") != 0){
                throw FILE_ERROR;
            }
            DeleteTree(Root);
            Root = Deserialize(is);
            Root->Father = Nil; 
            ReconnectFather(Root);
            is.close();      
        }
    }

    void Serialize(TRBNode* root, std::ofstream& os){
        if (Root == Nil){
            return;
        }
        os << root->Dict.Key << '\t';
        os << root->Dict.Value << '\t';
        os << root->Color << '\t';

        bool has_left = (root->Left != Nil);
        bool has_right = (root->Right != Nil);

        os << has_left << '\t';
        os << has_right << '\n';

        if (has_left){
            Serialize(root->Left, os);
        }
        if (has_right){
            Serialize(root->Right, os);
        }
    }

    TRBNode* Deserialize(std::ifstream& is){
        TRBNode* root = nullptr;
        TDict buf;
        if (!(is >> buf.Key)){
            return Nil;
        }
        is >> buf.Value;

        int color = BLACK;
        is >> color;

        bool hasleft = false;
        bool hasright = false;

        is >> hasleft;
        is >> hasright;
        
        root = new TRBNode;
        root->Dict = buf;
        root->Color = color;

        if (hasleft){
            root->Left = Deserialize(is);
        }
        else{
            root->Left = Nil;
        }

        if (hasright){
            root->Right = Deserialize(is);
        }
        else{
            root->Right = Nil;
        }
        return root;
    }

    void Delete(){
        DeleteTree(Root);
        delete Nil;
    }

    TRBNode* Root;
    TRBNode* Nil;
private:
    void LeftRotate(TRBNode* x){
        TRBNode* y;
        y = x->Right;
        x->Right = y->Left;
        if (y->Left != Nil){
            y->Left->Father = x;
        }
        y->Father = x->Father;
        if (x->Father == Nil){
            Root = y;
        }
        else if(x->Father->Left == x){
            x->Father->Left = y;
        }
        else{
            x->Father->Right = y;
        }
        y->Left = x;
        x->Father = y;
    }

    void RightRotate(TRBNode* x){
        TRBNode* y;
        y = x->Left;
        x->Left = y->Right;
        if(y->Right != Nil){
            y->Right->Father = x;
        }
        y->Father = x->Father;
        if(x->Father == Nil){
            Root = y;
        }
        else if (x->Father->Left == x){
            x->Father->Left = y;
        }
        else{
            x->Father->Right = y;
        }
        y->Right = x;
        x->Father = y;
    }

    void DeleteTree(TRBNode* node){  
        if (node == Nil) return;  
        DeleteTree(node->Left);  
        DeleteTree(node->Right);   
        delete node;  
    }  

    void FixInsertiont(TRBNode* z){
        while (z != Root && z->Father->Color == RED){
            if (z->Father == z->Father->Father->Left){ // if left
                TRBNode* y = z->Father->Father->Right;
                if (y->Color == RED){
                    z->Father->Color = BLACK;
                    y->Color = BLACK;
                    z->Father->Father->Color = RED;
                    z = z->Father->Father;
                    if (z->Father == nullptr) break;
                }
                else{
                    if (z == z->Father->Right){
                        z = z->Father;
                        LeftRotate(z);
                    }
                    z->Father->Color = BLACK;
                    z->Father->Father->Color = RED;
                    RightRotate(z->Father->Father);
                }   
            }
            else{ // right
                TRBNode* y = z->Father->Father->Left;
                if (y->Color == RED){
                    z->Father->Color = BLACK;
                    y->Color = BLACK;
                    z->Father->Father->Color = RED;
                    z = z->Father->Father;
                    if (z->Father == nullptr) break;
                }
                else{
                    if (z == z->Father->Left){
                        z = z->Father;
                        RightRotate(z);
                    }
                    z->Father->Color = BLACK;
                    z->Father->Father->Color = RED;
                    LeftRotate(z->Father->Father);
                }
            }
        }
        Root->Color = BLACK;
    }

    void FixErase(TRBNode* x){
        while (x->Color == BLACK && x != Root){ // p — Black and node root
            if (x == x->Father->Left){ //if left
                TRBNode* w = x->Father->Right;
                if (w->Color == RED){ // Brother red
                    w->Color = BLACK;
                    x->Father->Color = RED;
                    LeftRotate(x->Father);
                    w = x->Father->Right;
                }
                if (w->Left->Color == BLACK && w->Right->Color == BLACK){
                    w->Color = RED;
                    x = x->Father;
                } 
                else{
                    if (w->Right->Color == BLACK){
                        w->Left->Color = BLACK;
                        w->Color = RED;
                        RightRotate(w);
                        w = x->Father->Right;
                    }
                    w->Color = x->Father->Color;
                    x->Father->Color = BLACK;
                    w->Right->Color = BLACK;
                    LeftRotate(x->Father);
                    x = Root;
                }
            }
            else{ // p is right
                TRBNode* w = x->Father->Left;
                if (w->Color == RED){ // Brother red
                    w->Color = BLACK;
                    x->Father->Color = RED;
                    RightRotate(x->Father);
                    w = x->Father->Left;
                }
                if (w->Left->Color == BLACK && w->Right->Color == BLACK){
                    w->Color = RED;
                    x = x->Father;
                } 
                else{
                    if (w->Left->Color == BLACK){
                        w->Right->Color = BLACK;
                        w->Color = RED;
                        LeftRotate(w);
                        w = x->Father->Left;
                    }
                    w->Color = x->Father->Color;
                    x->Father->Color = BLACK;
                    w->Left->Color = BLACK;
                    RightRotate(x->Father);
                    x = Root;
                }
            }
        }         
        x->Color = BLACK;
    }

    void ReconnectFather(TRBNode* root){
        if(root == Nil) return;
        root->Left->Father = root;
        root->Right->Father = root;
        ReconnectFather(root->Left);
        ReconnectFather(root->Right);
    }

    TRBNode* MaxLeft(TRBNode* t){
        while(t->Left != Nil){
            t = t->Left;
        }
        return t;
    }

    TRBNode* MaxRight(TRBNode* t){
        while(t->Right != Nil){
            t = t->Right;
        }
        return t;
    }

    void Transparent(TRBNode* u, TRBNode* v){
        if (u->Father == Nil){
            Root = v;
        }
        else if(u == u->Father->Left){
            u->Father->Left = v;
        }
        else{
            u->Father->Right = v;
        }
        v->Father = u->Father;
    }
};

int main(){
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    TRBtree tree;
    char strbuf[257]; 
    TDict bufdict;
    std::ifstream stream("test1.txt");
    clock_t start = clock();
    while (stream >> strbuf) {
        switch (strbuf[0]) {
            case '+':
                stream >> bufdict.Key >> bufdict.Value;
                for(size_t i = 0; i < strlen(bufdict.Key); i++){
                    bufdict.Key[i] = tolower(bufdict.Key[i]);
                }
                try{
                    tree.Add(bufdict);
                    std::cout << "OK\n";
                }
                catch(int a){
                    if (a == KEY_EXIST) std::cout << "Exist\n";
                    else std::cout << "ERROR: Something bad happened\n";
                }
                break;
            case '-':
                stream >> bufdict.Key;
                for(size_t i = 0; i < strlen(bufdict.Key); i++){
                    bufdict.Key[i] = tolower(bufdict.Key[i]);
                }
                try{
                    tree.Erase(bufdict);
                    std::cout << "OK\n";
                }
                catch(int a){
                    if (a == DOES_NOT_EXIST) std::cout << "NoSuchWord\n";
                    else std::cout << "ERROR: Something bad happened\n";
                }
                break;
            case '!':
                try{
                    tree.SaveOrLoad();
                    std::cout << "OK\n";
                }
                catch(int a){
                    std::cout << "ERROR: Work with file completed wrong\n";
                }
                break;
            default:
                strcpy(bufdict.Key, strbuf);
                for(size_t i = 0; i < strlen(bufdict.Key); i++){
                    bufdict.Key[i] = tolower(bufdict.Key[i]);
                }
                try{
                    unsigned long long a = tree.Find(bufdict);
                    std::cout << "OK: " << a << std::endl;
                }
                catch(int a){
                    std::cout << "NoSuchWord\n";
                }
                break;
        }
    }
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout<<"Sec:"<< seconds<<std::endl;
    tree.Delete();
    return 0;
}