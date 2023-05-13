#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

/* Student structure used to track names, averages, and letter grades */
struct Student
{
    string name; //name
    double avg;  //grade average
    string grade;//assigned overall grade
};

/* Creates a vector of Students from a file */
vector<Student> createVector(string filename)
{
    ifstream fin(filename); //reads from filename
    string line; //takes line from fin
    string word; //takes word from ss
    Student stu; //Student obj for storage
    double average; //average grade
    stringstream ss; //takes substrings of line

    //creating vector
    getline(fin, line);
    ss << line;
    ss >> word;
    vector<Student> v (stoi(word)); //first value of file = vector size
    ss.clear(); //clears ss

    //adding students and averages to vector
    int n = 0;
    int count = 0;
    while(n < v.size())
    {
        //getting name
        getline(fin, line);
        v[n] = stu;
        v[n].name = line; //assign stu.name at index n --> name

        //getting average
        getline(fin, line);
        ss.str(line);
        while(count < 4) //grabs all four test grades
        {
            ss >> word; //ss gives each seperate test grade to word
            average += stod(word);
            count++;
        }
        average = (average/4); //we take the average of all tests
        v[n].avg = average; //assign stu.avg at index n --> average

        n++; //increment n
        ss.clear(); //clears ss
        count = 0; //resets count
        average = 0; //resets average
    }
    return v; //returns a vector
}

/* Uses the BubbleSort algorithm to sort students by their averages */
void bubbleSort(vector<Student> &v)
{
    Student small; //small holds small Student object
    for(int i = 0; i < v.size()-1; i++)
    {
        for(int j = i+1; j < v.size(); j++)
        {
            if(v[j].avg < v[i].avg)
            {
                small = v[j];
                v[j] = v[i];
                v[i] = small;
            }
        }
    }
}

/* Assigns grades to students according to their place in the bell curve */
void assignGrades(vector<Student> &v)
{
    vector<Student> vC = v; //vC is a copy of v
    bubbleSort(vC); //sorts vC, in ascending order

    int a, b, c, d, f;
    int num = vC.size(); //size will be a multiple of 10 (10, 20, 30, etc.)
    a = 0.1*num; //top 10%
    b = 0.2*num; //next 20%
    c = 0.4*num; //middle 40%
    d = 0.2*num; //lower 20%
    f = 0.1*num; //bottom 10%

    //assigns grades to students
    for(int i = 0; i < vC.size(); i++)
    {
        if(f != 0)
        {
            vC[i].grade = "F";
            f--;
        }
        else if(d != 0)
        {
            vC[i].grade = "D";
            d--;
        }
        else if(c != 0)
        {
            vC[i].grade = "C";
            c--;
        }
        else if(b != 0)
        {
            vC[i].grade = "B";
            b--;
        }
        else
        {
            vC[i].grade = "A";
            a--;
        }
    }
    
    //double for loop will find the names in original vector, v, and match the grades from vC
    string name;
    for(int i = 0; i < vC.size(); i++)
    {
        name = v[i].name; //name is given student at vector v index i
        for(int j = 0; j < vC.size(); j++)
        {
            if(name == vC[j].name) //finds the same name in vC
                v[i].grade = vC[j].grade; //assigns vC grade to v grade
        }
    }
}

/* Displays students grades from a vector, v */
void getGrades(vector<Student> v)
{
    for(int i = 0; i < v.size(); i++)
    {
        cout << v[i].name << " - " << v[i].grade << endl;
    }
}

/* MAIN */
int main()
{
    //creates a vector of Students from file
    string filename;
    cin >> filename;
    vector<Student> list = createVector(filename);

    //sorts the vector, assigns grades, and displays them to terminal
    assignGrades(list);
    getGrades(list);
}