
/*
 *********************************************************
 * @authors Nikhil Gupta   Email:nikhilg.me@gmail.com    *
 * @date    2021-05-29 15:35:18 IST                      *
 * @version ${1.0.0}                                     *
 *********************************************************
 */

/*
* 
* This program models luck factor in determinig success of a person based on his skill and talent
*
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;

class Person
{
public:
    int luck;
    int skills_talent;
    int luckPosition;
    int skillsPosition;
    int index;

    Person()
    {
        }
};

int generateRandom(int lower, int upper) //[lower,upper]
{

    int num = (rand() %
               (upper - lower + 1)) +
              lower;

    return num;
}

main()
{
    srand(time(0));
}