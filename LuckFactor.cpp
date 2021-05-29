
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
    static int count;
    int luck;
    int skills_talent;
    int finalRank;
    int luckRank;
    int skillsRank;
    int index;

    Person(int lower, int upper)
    {
        this->count = count + 1; // keep track of index
        this->luck = generateRandom(lower, upper);
        this->skills_talent = generateRandom(lower, upper);
        this->index = count;
    }

    bool compareLuck(Person *p1, Person *p2)
    {

        return (p1->luck < p2->luck);
    }

    bool compareSkills(Person *p1, Person *p2)
    {
        return (p1->skills_talent < p2->skills_talent);
    }

    static void sortOnLuck(vector<Person *> persons)
    {
        sort(persons.begin(), persons.end(), compareLuck);
        for (int i = 0; i < persons.size(); i++)
        {
            persons[i]->luckRank = i + 1;
        }
    }

        static void sortOnSkills(vector<Person *> persons)
    {
        sort(persons.begin(), persons.end(), compareSkills);
        for (int i = 0; i < persons.size(); i++)
        {
            persons[i]->skillsRank = i + 1;
        }
    }
};

//set static count
int Person::count = 0; // set initial count to 0

//generate random number for luckRank and skillRank
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