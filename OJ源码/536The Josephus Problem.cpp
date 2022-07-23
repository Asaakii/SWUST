#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int p = 0;
    for (int i = 2; i <= n; i++)
        p = (p + 2) % i;
    int s = p + 1;
    cout << s << endl;
    return 0;
}
