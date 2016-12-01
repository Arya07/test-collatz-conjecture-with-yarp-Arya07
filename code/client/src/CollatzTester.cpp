/*
 * author: Elisa Maiettini
 * date: 29/11/2016
 */
#include <CollatzTester.hpp>

using namespace std;

 void CollatzTester::testPair(int N, int T){
    cout << "CollatzTester: testing number "<< N << "with threshold " << T <<endl;

    while(N>T){
        if(N%2 == 0){
            N=N/2;
        }else{
            N=3*N+1;
        }
    }
}
