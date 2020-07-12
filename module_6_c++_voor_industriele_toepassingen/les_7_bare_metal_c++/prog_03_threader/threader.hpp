// Copyright: GEATEC engineering, 2020
// License: Apache 2

#include <vector>
#include <list>
#include <thread>
#include <chrono>

namespace st = std;

namespace threader {

class Task {
    public:
        virtual void run () = 0;
};

class Batch;

class Scheduler {
    public:
        Scheduler (int nrOfThreads);
        void add (Task &task);
        void fork ();
        void join ();
        
    protected:
        st::vector <Batch> batches;
        int nrOfThreads;
        int threadIndex;
};

class Batch {
    protected:
        st::thread *aThread;
        st::list <Task *> tasks;

        void add (Task &task);
        void fork ();
        void join ();
        void run ();
        
    friend class Scheduler;
};

}
