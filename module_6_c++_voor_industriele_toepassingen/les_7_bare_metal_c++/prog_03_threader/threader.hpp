#include <vector>
#include <thread>
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
        
    protected:
        st::vector <Batch> batches;
        int nrOfThreads;
        int threadIndex = 0;
};

class Batch {
    public:
        Batch (int threadIndex);
        ~Batch ();
    
    protected:
        st::thread *aThread;
        st::vector <Task *> tasks;
        int threadIndex;

        void add (Task &task);
        void run ();
        
    friend class Scheduler;
};

}
