// Copyright: GEATEC engineering, 2020
// License: Apache 2

#include <iostream>
namespace st = std;

#include "threader.hpp"

namespace threader {
    
// ====== Scheduler methods

Scheduler::Scheduler (int nrOfThreads):
    nrOfThreads (nrOfThreads),
    threadIndex (0)
{
    batches.reserve (nrOfThreads);
    for (auto threadIndex = 0; threadIndex < nrOfThreads; threadIndex++) {
        batches.emplace_back ();
    }
}

void Scheduler::add (Task &task) {
    batches [threadIndex++] .add (task);
    threadIndex %= nrOfThreads;
}

void Scheduler::fork () {
    for (auto &batch: batches) {
        batch.fork ();
    }
}

void Scheduler::join () {
    for (auto &batch: batches) {
        batch.join ();
    }
}

// ====== Batch methods    
    
void Batch::add (Task &task) {
    tasks.push_back (&task);
}

void Batch::fork () {
    aThread = new st::thread (&Batch::run, this);
}

void Batch::join () {
    aThread->join ();
    delete aThread;
}

void Batch::run () {
    for (auto task: tasks) {
        task->run ();
    }
}
    
}
