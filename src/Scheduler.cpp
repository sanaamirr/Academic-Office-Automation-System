#include <iostream>
#include <fstream>
#include <iomanip>
#include "Classes.h"
#include "Venue.h"
using namespace std ; 
#include "Scheduler.h"
void Scheduler :: ScheduleandExport (Classes **classesArray , int classCount  , Venue ** venues , int venueCount) {
    int totalSlots = 20; 
    ofstream outFile("../data/schedule.txt");

    if (!outFile.is_open()) {
        cerr << "Error: Could not create schedule.txt" << endl;
        return;
    }

    // 1. Initialize the Time Grid
    Classes*** timeGrid = new Classes**[venueCount];
    for (int i = 0; i < venueCount; i++) {
        timeGrid[i] = new Classes*[totalSlots];
        for (int j = 0; j < totalSlots; j++) timeGrid[i][j] = nullptr;
    }

    outFile << "================ EXAM SCHEDULE ================" << endl;
    outFile << left << setw(15) << "Course ID" << setw(30) << "Course Name" 
            << setw(10) << "Slot" << "Venues Assigned" << endl;
    outFile << "---------------------------------------------------------------" << endl;

    // 2. Allocation Loop
    for (int i = 0; i < classCount; i++) {
        bool fullyAssigned = false;

        for (int s = 0; s < totalSlots && !fullyAssigned; s++) {
            int capacityFound = 0;
            int venuesNeeded = 0;
            int tempIndices[50];

            for (int v = 0; v < venueCount; v++) {
                if (timeGrid[v][s] == nullptr) {
                    capacityFound += venues[v]->capacity;
                    tempIndices[venuesNeeded++] = v;

                    if (capacityFound >= classesArray[i]->student_count) {
                        // Found enough space in this slot! Write to file and update grid
                        outFile << left << setw(15) << classesArray[i]->courseID 
                                << setw(30) << classesArray[i]->courseName 
                                << setw(10) << s + 1 ;

                        for (int k = 0; k < venuesNeeded; k++) {
                            int vIdx = tempIndices[k];
                            timeGrid[vIdx][s] = classesArray[i];
                            
                            // Add venue name to the file line
                            outFile << venues[vIdx]->roomID << (k == venuesNeeded - 1 ? "" : ", ");
                        }
                        outFile << endl;

                        classesArray[i]->isAssigned = true;
                        //classesArray[i]->assignedSlot = s ;
                        fullyAssigned = true;
                        break;
                    }
                }
            }
        }

        if (!fullyAssigned) {
            outFile << "!!! FAILED TO ASSIGN: " << classesArray[i]->courseName 
                    << " (Count: " << classesArray[i]->student_count << ")" << endl;
        }
    }

    outFile << "===============================================" << endl;
    outFile.close();
    cout << "Schedule successfully exported to ../data/schedule.txt" << endl;

    // Cleanup timeGrid memory
    for (int i = 0; i < venueCount; i++) delete[] timeGrid[i];
    delete[] timeGrid;
 }