#include <iostream>
#include <fstream>
#include <cassert>
#include <stack>
#include <string>

using namespace std;

int main() {
    
    fstream myIn;
    stack<string> oriStack;
    stack<string> revStack;
    string name;
    
    myIn.open("names.dat");
    assert(myIn);
    
    while(getline(myIn,name)) {
        oriStack.push(name);
        revStack.push(oriStack.top());
    }
    
    myIn.close();
    
    while (!oriStack.empty()) {
        cout << oriStack.top() << endl;
        oriStack.pop();
    }
    
    return 0;
}
