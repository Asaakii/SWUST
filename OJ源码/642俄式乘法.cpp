#include <iostream>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    int s = n * m;
    while (n != 1)
    {
        if (n % 2 != 0)
            cout << m << "+";
        m *= 2;
        n /= 2;
    }
    cout << m << "=" << s << endl;
    return 0;
}
