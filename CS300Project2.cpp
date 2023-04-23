//============================================================================
// Name        : CS300Project2.cpp
// Author      : Kelvin Pichardo Doughty
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Project 2
//============================================================================

#include <cctype>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>

using namespace std;

// Definition of structure course
struct Course
{
    string courseNumber;
    string name;
    vector<string> prerequisites; //vector array of string type
};
bool strcasecmp(string str1, string str2) {
    transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
    transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
    if (str1 == str2) { return true; }
    return false;
}
// Function to split string to list of strings on the basis of given delimiter
vector<string> tokenize(string s, string del = " ")
{
    //vector array of string type you have to define the type of 
    //vector array you want to create between these <>
    vector<string> stringArray;


    int start = 0;
    int end = s.find(del);

    while (end != -1)
    {
        stringArray.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }

    stringArray.push_back(s.substr(start, end - start));

    return stringArray;
}

// Function to load file and store the details into list of courses
vector<Course> LoadDataStructure()
{

    // Creating an object of iftsream class to open file
    ifstream fin("ABCU_Advising_Program_Input.csv");
    if (!fin) { cout << "File not found" << endl; }
    vector<Course> courses;
    string line;

    // This loop runs till we reach the end of the file
    while (getline(fin, line))
    {
        // Course object to store a course details
        Course course;

        // Getting tokenized information which is separated by commas
        vector<string> tokenizedInformation = tokenize(line, ",");

        // if size of the tokenizedInformation if greater
        // then 1 (atleast course number and course name is there)
        if (tokenizedInformation.size() > 1)
        {
            // Storing information on the structure course
            course.courseNumber = tokenizedInformation[0];
            course.name = tokenizedInformation[1];

            // If there are prerequisites then storing them too
            for (int i = 2; i < tokenizedInformation.size(); i++)
            {
                // cout << tokenizedInformation[i] << endl;
                course.prerequisites.push_back(tokenizedInformation[i]);
            }

            // appending the course into list of courses
            courses.push_back(course);
        }
    }

    fin.close();

    cout << "\nCourses Loaded Successfully\n";

    // Returning the list of courses
    return courses;
}

// function to print a course
void printCourse(Course course)
{
    string courseNumber = course.courseNumber;
    string name = course.name;
    vector<string> prerequisites = course.prerequisites;

    cout << "\n";
    // Printing course details
    cout << "Course Number: " << courseNumber << endl;
    cout << "Course Name: " << name << endl;
    cout << "Prerequisites: ";

    for (int i = 0; i < prerequisites.size(); i++)
    {
        cout << prerequisites[i] << " ";
    }

    cout << "\n\n";
}

// Function to print the list of all courses
void printCourseList(vector<Course> courses)
{
    int n = courses.size();

    // Sorting the courses according the course number
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (courses[j].courseNumber > courses[j + 1].courseNumber)
            {
                swap(courses[j + 1], courses[j]);
            }
        }
    }

    // printing the list of all courses
    cout << "\nHere is a sample schedule: \n";
    for (int i = 0; i < n; i++)
    {
        // printCourse(courses[i]);
        cout << courses[i].courseNumber << ", " << courses[i].name << endl;
    }
}

// Function to find a course with associated course number
void searchCourse(vector<Course> courses)
{
    int n = courses.size();
    string courseNumber;
    int f = 0;

    // cout << "\nEnter courseNumber: ";
    cout << "\nWhich course do you want to know about? ";
    cin >> courseNumber;

    // searching and showing details of the course if found
    cout << "\nCourse Details: \n";
    for (int i = 0; i < n; i++)
    {
        // If course found
        // strcasecmp() function ise used to compare two string ignoring case (upper or lower)
        // but the function operates on a byte-by-byte basis
        // therefore c_str() converts the strings into characters
        // strcasecmp() returns an integer 0 if both the string are equal
        if (strcasecmp(courses[i].courseNumber, courseNumber))
        {
            // then printing its details
            f = 1;
            printCourse(courses[i]);
            break;
        }
    }

    // If course is not found displays message to the user
    if (f == 0)
    {
        cout << "Course with given course number not found\n";
    }
}

// Main function or driver code
int main(int argc, char** argv)
{
    // Vector array to store all the courses
    vector<Course> courses;

    // Showing menu to the users
    cout << "WELCOME TO THE COURSE PLANNER" << endl;
    cout << "1.Load Data Structure\n";
    cout << "2.Print Course List\n";
    cout << "3.Print Course\n";
    cout << "4.Exit\n";

    // variable to store user's choice
    int ch;

    do
    {
        // Taking user's choice/input
        // cout << "\nEnter your choice: ";
        cout << "\nWhat would you like to do? ";
        cin >> ch;

        // Performing operation according to user's choice/input
        switch (ch)
        {
        case 1:
            courses = LoadDataStructure();
            break;
        case 2:
            printCourseList(courses);
            break;
        case 3:
            searchCourse(courses);
            break;
        case 4:
            // cout << "Exit\n";
            cout << "\n Thank you for using the course planner!\n";
            break;
        default:
            // cout << "Invalid Choice\n";
            cout << ch << " is not a valid option\n";
        }
    } while (ch <= 4);

    return 0;
}