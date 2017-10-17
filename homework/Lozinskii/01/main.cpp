#include<iostream>
using namespace std;
int a[100000][100000];

int main ()
{
    for (int i = 0; i < 10000; i++) {
        for (int j = 0; j < 10000; j++)
            a[i][j] = i +j;
    }
    cout << a[500][500];
    
}
