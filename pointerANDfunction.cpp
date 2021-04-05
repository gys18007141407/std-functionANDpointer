#include <functional>
#include <iostream>
#include <vector>

typedef std::function<void()> ss;
std::vector<ss> funcs;

int fun(int a, int b){
    std::cout <<a + b << std::endl;
    return a+b;
}


int main(){

    

    typedef void(*f)();

    f aa[2];


    void* p = (void*)(&fun); // save func address

    //aa[0] = (void(*)())p;
    aa[0] = (void(*)())(&fun);  // save to array

    aa[0]();  // execute directly

    auto q = std::bind((int(*)(int,int))(aa[0]), 1, 2);  // switch func type and bind params

    ss s = q; // assign to another function class

    s();
    q();

    
    
    
    funcs.push_back((void(*)())p);
    funcs.back()();


    // auto xx = std::bind(funcs.back(), 1, 2, 3);   // compile passed, xx() error!!!!, this means function can bind directly
    // auto yy = std::bind((void(*)(int,int))(funcs.back()) , 1, 3); // compile error !!!


    // conclusion : std::function limit many operation, but can wrap any callable object
    //              pointer can switch randomly, but not safe and cannot suit for any callable object such as lambda


    std::vector<void(*)()> funcs2;
    funcs2.push_back((void(*)())&fun);
    funcs2.back()();

    auto xx = std::bind((void(*)(int, int))funcs2.back(), 2, 4);

    xx();

    ss yy = xx;
    yy();
  
//print
// -1771407223
// 3
// 3
// -107992792
// 752151768
// 6
// 6

    return 0;
}