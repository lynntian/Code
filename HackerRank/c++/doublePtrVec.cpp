
#include <iostream>
using namespace std;

int main() {
    unsigned long N;
    unsigned long Q;
    cin >> N; cin >> Q;

    unsigned long** vs = new unsigned long*[N];
    
    for(int i = 0; i < N; i++)
    {
        unsigned long c;
        cin >> c;
        vs[i] = new unsigned long[c];

        for(int j = 0; j < c; j++)
        {
            unsigned long tmp;
            cin >> tmp;
            vs[i][j] = tmp;
        }
    }

    for(int a = 0; a < Q; a++)
    {
        unsigned long x; unsigned long y;
        cin >> x >> y;
        cout << vs[x][y] << endl;
    }

    for(int i = 0; i < N; i ++)
    {
        delete[] vs[i];    
    }
    delete [] vs;
    return 0;
}
