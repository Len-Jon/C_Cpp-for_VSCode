#include<iostream>
#include<string>
#include<stdlib.h>
using namespace std;

int main(){
    cout << "Hello, world!\n你好，世界！" << endl;  //因为Windows的编码比较特殊，所以需要用中文字符来检查配置效果
    string s;
    cin >> s;
    cout << s << endl;
    return 0;
}