//
// Created by 温盛章 on 9/1/15.
//

#include "debug.h"
using namespace std;
void DEBUG(string s) {
#ifdef _DEBUG
    cout << s << endl;
#endif
}
