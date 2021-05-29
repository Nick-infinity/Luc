
/*
 *********************************************************
 * @authors Nikhil Gupta   Email:nikhilg.me@gmail.com    *
 * @date    2021-05-29 17:04:35 IST                      *
 * @version ${1.0.0}                                     *
 *********************************************************
 */

/*
* 
* Description
*
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class A
{
public:
    double a;
};

bool c(A *a1, A *b1)
{
    return a1->a > b1->a;
}
int main()
{
    vector<A *> v;
    for (int i = 0; i < 5; i++)
    {
        A *p = new A();
        p->a = 1 - i;
        v.push_back(p);
    }
    sort(v.begin(), v.end(), c);
}