#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleCell(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, vector<int>& numOverworked, int day, int slot);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

  int numDays = avail.size();
  int numWorkers = avail[0].size();

  sched = DailySchedule(numDays, vector<Worker_T>(dailyNeed, INVALID_ID));
  vector<int> numOverworked(numWorkers, 0);

  return scheduleCell(avail, dailyNeed, maxShifts, sched, numOverworked, 0, 0);

}

bool scheduleCell(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, vector<int>& numOverworked, int day, int slot){

  if(day == avail.size()){
    return true;
  }

  for(int worker = 0; worker < avail[0].size(); worker++){
    
    if(avail[day][worker] == 1 && numOverworked[worker] < maxShifts){
      bool alreadySched = false;
      for(int j = 0; j < slot; j++){
        if(sched[day][j] == worker){
          alreadySched = true;
          break;
        }
      }

      if(alreadySched == false){
        sched[day][slot] = worker;
        numOverworked[worker]++;

        int nextDay = day;
        int nextSlot = slot + 1;

        if(nextSlot == dailyNeed){
          nextDay++;
          nextSlot = 0;
        }

        if(scheduleCell(avail, dailyNeed, maxShifts, sched, numOverworked, nextDay, nextSlot) == true){
          return true;
        }

        sched[day][slot] = INVALID_ID;
        numOverworked[worker]--;

      }
    }
  }

  return false;
}



