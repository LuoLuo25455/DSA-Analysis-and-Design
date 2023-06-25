//============================================================================
// Project     : Project2.cpp
// Author      : Allan Lee
// Version     :
// Copyright   : Your copyright notice
// Description : Project 2 code for ABCU
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	cout << "Welcome to the course planner." << endl;

}

// Constructing basic structure for courses
struct Course{
	string courseNumber;
	string courseTitle;
	vector<string> prereqs;
};

// Loading file data into data structure
void loadDataStructure(vector<Course> courses){
	string fileName;
	// Asking user to input file name
	cin >> "Please enter the file name:" >> fileName;
	// Opening file with name {fileName}
	ifstream inputFile(fileName);
	// Confirming if the file is openable
	if(inputFile.is_open()){
		// Declaring variable for each line
		string line;
		// Infinite loop if line exists
		while(getline(inputFile, line)){
			// Loading course with file data
			Course course;
			// Identifying delimiter
			int index = line.find(",");
			// First section in the csv file is the courseNumber
			course.courseNumber = line.substr(0, index);
			// Pushing back the "cursor" to after the first ",", repeat the previous logic to load courseTitle
			line = line.substr(index + 1);
			index = line.find(",");
			course.courseTitle = line.substr(0, index);
			line = line.substr(index + 1);
			// Infinite loop if line is not empty (if the course has prereqs)
			while(!line.empty()){
				// Identifying delimiter
				index = line.find(",");
				// Loading prereqs one by one into vector prereqs
				course.prereqs.push_back(line.substr(0, index));
				line = line.substr(index + 1);
			}
			// Add the course to the courses vector
			courses.push_back(course);
		}
		// Closing the file
		inputFile.close();
		cout << "Data loaded successfully" << endl;
	}
	else{
		cout << "Failed loading data" << endl;
	}
}

// Printing list of courses
void printCourseList(vector<Course> courses){
	// Using courseNumbers as the leading index
	vector<string> courseNumbers;
	// Sorting courses alphanumerically
	for(Course course : courses){
		courseNumbers.push_back(course.courseNumber);
	}
	sort(courseNumbers.begin(), courseNumbers.end());
	// Matching lines in the unsorted courseList and sorted courseList to output course information
	for(string courseNumber : courseNumbers){
		for(Course course : courses){
			if(course.courseNumber == courseNumber){
				cout << course.courseNumber << "," << course.courseTitle << endl;
			}
		}
	}
}

// Printing course information
void printCourseInfo(vector<Course> courses){
	// Asking user for input
	string courseNumber;
	cin >> "What course would you like to know about?" >> courseNumber;
	// Converting all course number characters to upper cases
	string toupper(courseNumber);
	// Printing out course info, if course is found
	for(Course course : courses){
		if(course.courseNumber == courseNumber){
			cout << course.courseNumber << "," << course.courseTitle << endl;
			cout << "Prerequisites: ";
			if(course.prereqs.empty()){
				cout << "None" << endl;
			}
			else{
				for(string prereqs : course.prereqs){
					cout << prereqs << " ";
				}
				cout << endl;
			}
		}
		else{
			cout << "Course not found" << endl;
		}
	}
}

// printing menu
void menu(){
	vector<Course> courses;
	string fileName;
	int choice;

	while(choice != 4){
		cout << "1. Load Data Structure" << endl;
		cout << "2. Print Course List" << endl;
		cout << "3. Print Course" << endl;
		cout << "4. Exit" << endl;
		cin >> "What would you like to do?" >> choice;

		switch(choice){
		case 1:
			loadDataStructure(courses);
			break;
		case 2:
			printCourseList(courses);
			break;
		case 3:
			printCourseInfo(courses);
			break;
		case 4:
			cout << "Thank you for using the course planner!" << endl;
			break;
		}
		default:
			cout << choice << " is not a valid option" << endl;
	}

}
