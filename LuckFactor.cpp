
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
#include <iomanip>
using namespace std;

class Person
{
public:
    static int count;
    double luck;
    double skills_talent;
    double score;
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

    //generate random number for luckRank and skillRank
    double generateRandom(int lower, int upper) //[lower,upper]
    {

        double num = ((double)rand() *
                      (upper - lower)) /
                         (double)RAND_MAX +
                     lower;

        return num;
    }
};

//set static count
int Person::count = 0; // set initial count to 0

class Averages
{
public:
    double luckAverage;
    double luckRankAverage;
    double skillAverage;
    double skillRankAverage;
    double scoreAverage;
    double rankAverage;

    Averages(double luckAverage,
             double luckRankAverage,
             double skillAverage,
             double skillRankAverage,
             double scoreAverage, double rankAverage)
    {
        this->luckAverage = luckAverage;
        this->luckRankAverage = luckRankAverage;
        this->skillAverage = skillAverage;
        this->skillRankAverage = skillRankAverage;
        this->scoreAverage = scoreAverage;
        this->rankAverage = rankAverage;
    }
};

double generateScore(Person *p1, double luckShare, double skillShare) // generate score from luck and sill_talent
{
    double luck = p1->luck;
    double skills = p1->skills_talent;
    double score = luck * (luckShare / 100) + skills * (skillShare / 100);
    return score;
}

bool compareLuck(Person *p1, Person *p2) // decreasing
{

    return p1->luck > p2->luck;
}

bool compareSkills(Person *p1, Person *p2) // decreasing
{
    return p1->skills_talent > p2->skills_talent;
}

bool compareScore(Person *p1, Person *p2) // sort int decreasing order of score
{

    return p1->score > p2->score;
}

void sortOnLuck(vector<Person *> &persons)
{
    sort(persons.begin(), persons.end(), compareLuck);
    for (int i = 0; i < persons.size(); i++)
    {
        persons[i]->luckRank = i + 1;
    }
}

void sortOnSkills(vector<Person *> &persons)
{
    sort(persons.begin(), persons.end(), compareSkills);
    for (int i = 0; i < persons.size(); i++)
    {
        persons[i]->skillsRank = i + 1;
    }
}

void calculateScore(vector<Person *> &persons, double luckShare, double skillShare)
{

    for (int i = 0; i < persons.size(); i++)
    {
        double finalScore = generateScore(persons[i], luckShare, skillShare);

        persons[i]->score = finalScore;
    }
}

void sortOnScore(vector<Person *> &persons)
{
    sort(persons.begin(), persons.end(), compareScore);
    for (int i = 0; i < persons.size(); i++)
    {
        persons[i]->finalRank = i + 1;
    }
}

// to nicely display information
void display(vector<Person *> &persons, int avgCount, vector<Averages *> &averagesList)
{
    int field_one_width = 8, field_two_width = 12;
    // cout << "Sno.  "
    //      << "Index  "
    //      << "LuckRank "
    //      << "Luck "
    //      << "SkillRank "
    //      << "Skills "
    //      << "Final_Rank "
    //      << "Score " << endl
    //      << endl;
    double luckAverage = 0;
    double luckRankAverage = 0;
    double skillAverage = 0;
    double skillRankAverage = 0;
    double scoreAverage = 0;
    double rankAverage = 0;
    for (int i = 0; i < persons.size(); i++)
    {
        Person *p = persons[i];
        if (i < avgCount)
        {
            luckAverage = luckAverage + p->luck;
            luckRankAverage = luckRankAverage + p->luckRank;
            skillAverage = skillAverage + p->skills_talent;
            skillRankAverage = skillRankAverage + p->skillsRank;
            scoreAverage = scoreAverage + p->score;
            rankAverage = rankAverage + p->finalRank;
        }
        // cout << setprecision(4) << i + 1 << setw(field_one_width) << p->index << setw(field_one_width) << p->luckRank << setw(9) << p->luck << setw(field_one_width) << p->skillsRank << setw(field_one_width) << p->skills_talent << setw(field_one_width) << p->finalRank << setw(field_two_width) << p->score << endl;
    }

    cout << endl
         << "AVERAGES: " << endl;
    cout << setprecision(4) << "luckAverage " << luckAverage / avgCount << endl
         << "luckRankAverage " << luckRankAverage / avgCount << endl
         << "skillAverage " << skillAverage / avgCount << endl
         << "skillRankAverage " << skillRankAverage / avgCount << endl
         << "scoreAverage " << scoreAverage / avgCount << endl
         << "rankAverage " << rankAverage / avgCount << endl;

    Averages *averages = new Averages(luckAverage / avgCount, luckRankAverage / avgCount, skillAverage / avgCount, skillRankAverage / avgCount, scoreAverage / avgCount, rankAverage / avgCount);
    averagesList.push_back(averages);
}

void printAverages_Average(vector<Averages *> &averageList)
{
    int avgCount = averageList.size();

    double luckAverage = 0;
    double luckRankAverage = 0;
    double skillAverage = 0;
    double skillRankAverage = 0;
    double scoreAverage = 0;
    double rankAverage = 0;

    for (int i = 0; i < averageList.size(); i++)
    {
        Averages *p = averageList[i];

        luckAverage = luckAverage + p->luckAverage;
        luckRankAverage = luckRankAverage + p->luckRankAverage;
        skillAverage = skillAverage + p->skillAverage;
        skillRankAverage = skillRankAverage + p->skillRankAverage;
        scoreAverage = scoreAverage + p->scoreAverage;
        rankAverage = rankAverage + p->rankAverage;
    }
    cout << endl
         << "FINAL AVERAGES: " << endl;
    cout << setprecision(4) << "luckAverage " << luckAverage / avgCount << endl
         << "luckRankAverage " << luckRankAverage / avgCount << endl
         << "skillAverage " << skillAverage / avgCount << endl
         << "skillRankAverage " << skillRankAverage / avgCount << endl
         << "scoreAverage " << scoreAverage / avgCount << endl
         << "rankAverage " << rankAverage / avgCount << endl;
}
void calculateScore(int totalPersons, double luckShare, int avgCount, vector<Averages *> &averageList)

{
    double skillShare = 100 - luckShare;
    int lower = 0, upper = 100;
    vector<Person *> persons;

    for (int i = 0; i < totalPersons; i++)
    {
        Person *p = new Person(lower, upper);
        persons.push_back(p);
    }

    sortOnLuck(persons);
    sortOnSkills(persons);
    calculateScore(persons, luckShare, skillShare);
    sortOnScore(persons);
    display(persons, avgCount, averageList);
}

int main()
{
    srand(time(0));
    vector<Averages *> averageList;
    int NUMBER_OF_RECORDS_PER_RUN = 15000;
    int LUCK_SHARE_PER_RUN = 5;
    int AVG_COUNT_PER_RUN = 10;
    int NUMBER_OF_RUNS = 0;
    for (int i = 0; i < NUMBER_OF_RUNS; i++)
    {
        calculateScore(NUMBER_OF_RECORDS_PER_RUN, LUCK_SHARE_PER_RUN, AVG_COUNT_PER_RUN, averageList);
    }
    if (NUMBER_OF_RUNS > 0)
    {
        printAverages_Average(averageList);
    }
}