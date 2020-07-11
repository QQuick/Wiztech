#include "threader.hpp"

namespace threader {
    
// ====== Scheduler methods

Scheduler::Scheduler (int nrOfThreads) {
    for (auto threadIndex = 0; threadIndex < nrOfThreads; threadIndex++) {
        batches.emplace_back (threadIndex);
    }
}

void Scheduler::add (Task &task) {
    batches [threadIndex++] .add (task);
    threadIndex %= nrOfThreads;
}

// ====== Batch methods    
    
Batch::Batch (int threadIndex):
    threadIndex (threadIndex),
    aThread (new st::thread (&Batch::run, this))
{}
    
Batch::~Batch () {
    aThread->join ();
    delete aThread;
}

void Batch::add (Task &task) {
    tasks.push_back (&task);
}

void Batch::run () {
    for (auto task: tasks) {
        task->run ();
    }
}

}
