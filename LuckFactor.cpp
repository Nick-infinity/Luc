
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

    Person(int lower, int upper, double luckShare)
    {
        double skillShare = 100 - luckShare;
        this->count = count + 1;                                                 // keep track of index
        this->luck = generateRandom(lower, upper) * (luckShare / 100);           // luckshare% of total luck
        this->skills_talent = generateRandom(lower, upper) * (skillShare / 100); // skillshare% of toal skills
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

double generateScore(Person *p1) // generate score from luck and sill_talent
{
    double luck = p1->luck;
    double skills = p1->skills_talent;
    double score = luck + skills;
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

void calculateFinalScore(vector<Person *> &persons)
{

    for (int i = 0; i < persons.size(); i++)
    {
        double finalScore = generateScore(persons[i]);

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
void display(vector<Person *> &persons, int avgCount, vector<Averages *> &averagesList, bool PRINT_AVERAGES,
             bool PRINT_FINAL_AVERAGE, bool PRINT_TABLE, bool SHOW_PARTIAL_TABLE = false,
             int NUMBER_OF_RECORDS_TO_DISPLAY = 11)
{
    int field_one_width = 8, field_two_width = 12;
    if (PRINT_TABLE || SHOW_PARTIAL_TABLE)
    {
        cout << "Sno.  "
             << "Index  "
             << "LuckRank "
             << "Luck "
             << "SkillRank "
             << "Skills "
             << "Final_Rank   "
             << "Score " << endl
             << endl;
    }
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
        if (PRINT_TABLE || SHOW_PARTIAL_TABLE)
        {
            if (PRINT_TABLE)
            {
                cout << setprecision(4) << i + 1 << setw(field_one_width) << p->index << setw(field_one_width) << p->luckRank << setw(9) << p->luck << setw(field_one_width) << p->skillsRank << setw(field_one_width) << p->skills_talent << setw(field_one_width) << p->finalRank << setw(field_two_width) << p->score << endl;
            }

            else
            {
                if (i < NUMBER_OF_RECORDS_TO_DISPLAY)
                {
                    cout << setprecision(4) << i + 1 << setw(field_one_width) << p->index << setw(field_one_width) << p->luckRank << setw(9) << p->luck << setw(field_one_width) << p->skillsRank << setw(field_one_width) << p->skills_talent << setw(field_one_width) << p->finalRank << setw(field_two_width) << p->score << endl;
                }
            }
        }
    }
    if (PRINT_AVERAGES)
    {
        cout << endl
             << "AVERAGES: " << endl;
        cout << setprecision(4) << "luckAverage " << luckAverage / avgCount << endl
             << "luckRankAverage " << luckRankAverage / avgCount << endl
             << "skillAverage " << skillAverage / avgCount << endl
             << "skillRankAverage " << skillRankAverage / avgCount << endl
             << "scoreAverage " << scoreAverage / avgCount << endl
             << "rankAverage " << rankAverage / avgCount << endl;
    }

    if (PRINT_FINAL_AVERAGE)
    {
        Averages *averages = new Averages(luckAverage / avgCount, luckRankAverage / avgCount, skillAverage / avgCount, skillRankAverage / avgCount, scoreAverage / avgCount, rankAverage / avgCount);
        averagesList.push_back(averages);
    }
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
void calculateScore(int totalPersons, double luckShare, int avgCount, vector<Averages *> &averageList, bool PRINT_AVERAGES,
                    bool PRINT_FINAL_AVERAGE, bool PRINT_TABLE, bool SHOW_PARTIAL_TABLE,
                    int NUMBER_OF_RECORDS_TO_DISPLAY)

{
    double skillShare = 100 - luckShare;
    int lower = 0, upper = 100;
    vector<Person *> persons;

    for (int i = 0; i < totalPersons; i++)
    {
        Person *p = new Person(lower, upper, luckShare);
        persons.push_back(p);
    }

    sortOnLuck(persons);
    sortOnSkills(persons);
    calculateFinalScore(persons);
    sortOnScore(persons);
    display(persons, avgCount, averageList, PRINT_AVERAGES, PRINT_FINAL_AVERAGE, PRINT_TABLE, SHOW_PARTIAL_TABLE, NUMBER_OF_RECORDS_TO_DISPLAY);
}

int main()
{
    srand(time(0));
    vector<Averages *> averageList;
    int NUMBER_OF_RECORDS_PER_RUN = 10;   // Total number of records to generate in one run
    int LUCK_SHARE_PER_RUN = 5;           // Percentage of luck in your success score // 100-LUCK = SKILL percentage in success score
    int AVG_COUNT_PER_RUN = 11;           // Number of records from highest score to process for calculation of average
    int NUMBER_OF_RUNS = 1;               // Number of time to repeat the complete process
    bool PRINT_AVERAGES = false;          // Wheather to print averages of every run
    bool PRINT_FINAL_AVERAGE = true;      // Wheather to print final average of NUMBER_OF_RUNS
    bool PRINT_FULL_TABLE = false;        // Wheather to print the complete table record
    bool SHOW_PARTIAL_TABLE = true;       // To display partial records from top
    int NUMBER_OF_RECORDS_TO_DISPLAY = 5; // Number of records to display from top

        for (int i = 0; i < NUMBER_OF_RUNS; i++)
    {
        calculateScore(NUMBER_OF_RECORDS_PER_RUN, LUCK_SHARE_PER_RUN, AVG_COUNT_PER_RUN, averageList, PRINT_AVERAGES,
                       PRINT_FINAL_AVERAGE, PRINT_FULL_TABLE, SHOW_PARTIAL_TABLE, NUMBER_OF_RECORDS_TO_DISPLAY);
    }

    if (NUMBER_OF_RUNS > 0 && PRINT_FINAL_AVERAGE)
    {
        printAverages_Average(averageList);
    }

    /* 

OUTPUT EXPLANATION
luckAverage 4.403  ->     out of LUCK_SHARE_PER_RUN
luckRankAverage 1792 ->   out of NUMBER_OF_RECORDS_PER_RUN
skillAverage 94.41 ->     out of 100- LUCK_SHARE_PER_RUN
skillRankAverage 94.64 -> out of NUMBER_OF_RECORDS_PER_RUN
scoreAverage 98.81 ->     out of 100
rankAverage 25.5 ->       out of NUMBER_OF_RECORDS_PER_RUN
*/
}