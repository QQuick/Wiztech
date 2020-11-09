// Copyright: GEATEC engineering, 2020
// License: Apache 2

#include <iostream>
#include <iomanip>
#include <vector>
#include <mutex>
#include <chrono>
#include <cstdlib>
namespace st = std;
using namespace st::chrono_literals;

#include "threader.hpp"
namespace tr = threader;

auto consoleMutex = st::mutex ();

class TableTask: public tr::Task {
    public:
        TableTask (int baseNumber);
        void run ();
    protected:
        int baseNumber;
};

TableTask::TableTask (int baseNumber):
    baseNumber (baseNumber)
{}

// ====== TableTask methods

void TableTask::run () {
    auto randMaxFloat = float (RAND_MAX);
    
    for (auto multiplier = 1; multiplier <= 10; multiplier++) {
        consoleMutex.lock ();
        
        st::cout <<
            st::setw (2) << multiplier << " x " <<
            st::setw (2) << baseNumber << " = " <<
            st::setw (2) << multiplier * baseNumber << '\n';
            
        consoleMutex.unlock ();
        st::this_thread::sleep_for ((rand () / randMaxFloat) * 20ms);
    }
}

// ===== Main entrypoint

int main () {
    auto tableTasks = st::vector <TableTask> ();

    for (int baseNumber = 1; baseNumber <= 10; baseNumber++) {
        tableTasks.emplace_back (baseNumber);
    }
    
    auto scheduler = tr::Scheduler (3); 
    
    for (auto &tableTask: tableTasks) {
        scheduler.add (tableTask);
    }
    
    st::cout << "Secundary threads started" << '\n';
    scheduler.fork ();
    scheduler.join ();
    st::cout << "Secundary threads finished" << '\n';
    
    return 0;
}
