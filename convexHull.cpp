#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef pair<LL, LL> PLL;
typedef vector<PLL> VPLL;

#define FOR(i, b, e) for(int i = b; i <= e; i++)
#define SIZE(x) ((int)(x).size())

#define PB push_back
#define ST first
#define ND second

LL det(const PLL &a, const PLL &b, const PLL &c)
{
    return a.ST * b.ND + b.ST * c.ND + c.ST * a.ND
            - a.ND * b.ST - b.ND * c.ST - c.ND * a.ST;
}

vector<PLL> hull(vector<PLL> v)
{
    if(SIZE(v) < 2)
        return v;
    sort(v.begin(), v.end());
    vector<PLL> r = {v.front()};
    int minLen = 1;
    FOR(t, 1, 2)
    {
        for(auto &i : v)
            if(i != r.back())
            {
                // zamienic '>= 0' na '> 0' zeby dla trzech wspoliniowych punktow
                // na otoczce srodkowy tez byl zawarty w wyniku
                while(SIZE(r) > minLen && det(r[SIZE(r) - 2], r.back(), i) >= 0)
                    r.pop_back();
                r.push_back(i);
            }
        minLen = SIZE(r);
        reverse(v.begin(), v.end());
        r.pop_back();
    }

    // W wersji z '> 0' zeby dla wszystkich punktow na jednej linii
    // srodkowe nie byly powielone dwukrotie trzeba dodac
    /*
    if(SIZE(r) == 2 * SIZE(v) - 2)
        r.erase(r.begin() + SIZE(v), r.end());
    */

    return r;
}

int main()
{
    int n;
    cin >> n;

    VPLL v;
    FOR(i, 1, n)
    {
        int x, y;
        cin >> x >> y;
        v.PB({x, y});
    }

    VPLL h = hull(v);

    cout << SIZE(h) << endl;
    for(auto i : h)
        cout << i.ST << ' ' << i.ND << endl;
}


