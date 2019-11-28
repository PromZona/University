#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
int main() {
    ofstream fout;
    vector <string> A;
    fout.open("test1.txt");
    srand(time(NULL));
    unsigned long long value;
    string input2;
    for (long long j = 0; j < 8000; ++j) {
	string input;
        for (int i = 0; i < 256; ++i) {
            char a = 'a' + rand()%('z'-'a');
            input += a;
        }
        value = rand();
        fout << '+' << ' ' << input << ' ' << value << '\n';
        A.push_back(input);
    }
    for(long long i = 0; i < A.size(); i++){
            fout << A[i] << '\n';
    }
return 0;
}