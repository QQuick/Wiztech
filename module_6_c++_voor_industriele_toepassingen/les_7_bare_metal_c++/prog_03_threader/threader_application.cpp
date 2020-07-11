#include <iostream>
#include <vector>
#include <mutex>
namespace st = std;

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
    for (auto multiplier = 1; multiplier <= 10; multiplier++) {
        consoleMutex.lock ();
        auto answer = float ();
        
        while (true) {
            st::cout << multiplier << " x " << baseNumber << " = ";
            st::cin >> answer;
            
            if (answer == baseNumber) {
                break;
            }
            else {
                st::cout << "Bijna goed, probeer 't nog eens...";
            }
        }
        
        consoleMutex.unlock ();
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
    
    return 0;
}
