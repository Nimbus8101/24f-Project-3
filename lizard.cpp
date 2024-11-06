/***************************************************************/
/*                                                             */
/* lizard.cpp                                                  */
/*                                                             */
/* To compile, you need all the files listed below             */
/*   lizard.cpp                                                */
/*                                                             */
/* Be sure to use the -lpthread option for the compile command */
/*   g++ -g -Wall -std=c++11 lizard.cpp -o lizard -pthread     */
/*                                                             */
/* Execute with the -d command-line option to enable debugging */
/* output.  For example,                                       */
/*   ./lizard -d                                               */
/*                                                             */
/***************************************************************/

#include <iostream>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <semaphore>

using namespace std;

/*
 * This is a stub file.  It contains very little code and what
 * it does contain may need to be altered or removed.  It is
 * only provided for a starting point.
 *
 * The comments are probably useful.
 */


/*
 * Define "constant" values here
 */


/*
 * Make this 1 to check for lizards travelling in both directions
 * Leave it 0 to allow bidirectional travel
 */
#define UNIDIRECTIONAL       0

/*
 * Set this to the number of seconds you want the lizard world to
 * be simulated.  
 * Try 30 for development and 120 for more thorough testing.
 */
#define WORLDEND             30

/*
 * Number of lizard threads to create
 */
#define NUM_LIZARDS          20

/*
 * Number of cat threads to create
 */
#define NUM_CATS             2

/*	
 * Maximum lizards crossing at once before alerting cats
 */
#define MAX_LIZARD_CROSSING  4

/*
 * Maximum seconds for a lizard to sleep
 */
#define MAX_LIZARD_SLEEP     3

/*
 * Maximum seconds for a cat to sleep
 */
#define MAX_CAT_SLEEP        3

/*
 * Maximum seconds for a lizard to eat
 */
#define MAX_LIZARD_EAT       5

/*
 * Number of seconds it takes to cross the driveway
 */
#define CROSS_SECONDS        2


/*
 * Declare global variables here
 */
mutex mtx;

int numCrossing;



/**************************************************/
/* Please leave these variables alone.  They are  */
/* used to check the proper functioning of your   */
/* program.  They should only be used in the code */
/* I have provided.                               */
/**************************************************/
int numCrossingSago2MonkeyGrass;
int numCrossingMonkeyGrass2Sago;
int debug;
int running;
/**************************************************/



/**
 * This class models a cat that sleep, wakes-up, checks on lizards in the driveway
 * and goes back to sleep. If the cat sees enough lizards it "plays" with them.
 */
class Cat {
	
	int       _id;        // the Id of the cat
	thread*   _catThread; // the thread simulating the cat
	
	public:
		Cat (int id);
		int getId();
		void run();
		void wait();
    
    private:
		void sleepNow();

        static void catThread (Cat *aCat); 
};

/**
 * Constructs a cat.
 *
 * @param id - the Id of the cat 
 */
Cat::Cat (int id)
{
	_id = id;
}

/**
 * Returns the Id of the cat.
 *
 * @return the Id of a cat
 */
int Cat::getId()
{
	return _id;
}


/**
 * Launches a cat thread.
 * 
 * Status: Incomplete - Make changes to this code.
 */
void Cat::run() 
{
	 // launch the thread to simulate the cat's behavior	 

}

/**
  * Waits for a cat to finish running.
  *
  * Status: Incomplete - Make changes to this code.
  */
void Cat::wait()
{
	 // wait for the thread to terminate
}


/**
 * Simulate a cat sleeping for a random amount of time
 * @return N/A
 * Status: Completed - No need to change any of this code.
 */
void Cat::sleepNow()
{
	int sleepSeconds;

	sleepSeconds = 1 + (int)(random() / (double)RAND_MAX * MAX_CAT_SLEEP);

	if (debug)
    {
		cout << "[" << _id << "] cat sleeping for " << sleepSeconds << " seconds" << endl;
		cout << flush;
    }

	sleep( sleepSeconds );

	if (debug)
    {
		cout << "[" << _id << "] cat awake" << endl;
		cout << flush;
    }
}

/**
  *
  * This simulates a cat that is sleeping and occasionally checking on
  * the driveway on lizards.
  * 
  * @param aCat - a cat that is being run concurrently
  * 
  * @return - N/A
  *
  * Status: Incomplete - Make changes as you see are necessary.
  */
void Cat::catThread (Cat *aCat)
{
	
	if (debug)
    {
		cout << "[" << aCat->getId() << "] cat is alive\n";
		cout << flush;
    }

	while(running)
    {
		aCat->sleepNow();



		/*
	     * Check for too many lizards crossing
	     */
		if (numCrossingSago2MonkeyGrass + numCrossingMonkeyGrass2Sago > MAX_LIZARD_CROSSING){
            cout << "\tThe cats are happy - they have toys.\n";
            exit( -1 );
		}
    }
}



class Lizard {
	int     _id;      // the Id of the lizard
	thread* _aLizard; // the thread simulating the lizard

	public:
		Lizard(int id);
		int getId();
        void run();
        void wait();

    private:
		void sago2MonkeyGrassIsSafe();
		void crossSago2MonkeyGrass();
		void madeIt2MonkeyGrass();
		void eat();
		void monkeyGrass2SagoIsSafe();
		void crossMonkeyGrass2Sago();
		void madeIt2Sago();
		void sleepNow();

        static void lizardThread(Lizard *aLizard);
	
};


/**
 * Constructs a lizard.
 * @param id - the Id of the lizard 
 */
Lizard::Lizard (int id){
	_id = id;
}

/**
 * Returns the Id of the lizard.
 * @return the Id of a lizard
 */
int Lizard::getId(){
	return _id;
}

/**
 * Launches a lizard thread.
 * Status: Incomplete - Make changes to this code.
 */
void Lizard::run() 
{
	 // launch the thread to simulate the lizard's behavior
    _aLizard = new thread ( lizardThread, this); 
}

/**
  * Waits for a lizard to finish running.
  *
  * Status: Incomplete - Make changes to this code.
  */
void Lizard::wait(){
	 // wait for the thread to terminate
	if (_aLizard != NULL) {
        _aLizard->join();
    } 
}

/**
 * Simulate a lizard sleeping for a random amount of time
 * Status: Completed - No need to change any of this code.
 */
void Lizard::sleepNow()
{
	int sleepSeconds;

	sleepSeconds = 1 + (int)(random() / (double)RAND_MAX * MAX_LIZARD_SLEEP);

	if (debug){
        cout << "[" << _id << "] sleeping for " << sleepSeconds << " seconds" << endl;
        cout << flush;
    }

	sleep( sleepSeconds );

	if (debug){
        cout << "[" << _id << "] awake" << endl;
        cout << flush;
    }
}

/**
 * Returns when it is safe for this lizard to cross from the sago
 * to the monkey grass.   Should use some synchronization 
 * facilities (lock/semaphore) here.
 * Status: Incomplete - Make changes as you see are necessary.
 */
void Lizard::sago2MonkeyGrassIsSafe(){
	if (debug){
		cout << "[" << _id << "] checking  sago -> monkey grass" << endl;
		cout << flush;
    }

	while(numCrossingSago2MonkeyGrass + numCrossingMonkeyGrass2Sago >= MAX_LIZARD_CROSSING){
    sleep(0);
  }


	if (debug)
    {
		cout << "[" << _id << "] thinks  sago -> monkey grass  is safe" << endl;
		cout << flush;
    }
}


/**
 * Delays for 1 second to simulate crossing from the sago to
 * the monkey grass. 
 * Status: Incomplete - Make changes as you see are necessary.
 */
void Lizard::crossSago2MonkeyGrass(){
	if (debug){
        cout << "[" << _id << "] crossing  sago -> monkey grass" << endl;
        cout << flush;
    }

	/*
	 * One more crossing this way
	 */
  mtx.lock();
	numCrossingSago2MonkeyGrass++;
  mtx.unlock();

	/*
     * Check for lizards cross both ways
     */
	if (numCrossingMonkeyGrass2Sago && UNIDIRECTIONAL){
		cout << "\tCrash!  We have a pile-up on the concrete." << endl;
		cout << "\t" << numCrossingSago2MonkeyGrass << " crossing sago -> monkey grass" << endl;
		cout << "\t" << numCrossingMonkeyGrass2Sago << " crossing monkey grass -> sago" << endl;
		exit( -1 );
    }

	/*
     * It takes a while to cross, so simulate it
     */
	sleep( CROSS_SECONDS );

    /*
     * That one seems to have made it
     */
    mtx.lock();
    numCrossingSago2MonkeyGrass--;
    mtx.unlock();
}


/**
 * Tells others they can go now
 * Status: Incomplete - Make changes as you see are necessary.
 */
void Lizard::madeIt2MonkeyGrass()
{
	/*
     * Whew, made it across
     */
	if (debug){
		cout << "[" << _id << "] made the  sago -> monkey grass  crossing" << endl;
		cout << flush;
    }





}


/**
 * Simulate a lizard eating for a random amount of time
 * Status: Completed - No need to change any of this code.
 */
void Lizard::eat(){
	int eatSeconds;

	eatSeconds = 1 + (int)(random() / (double)RAND_MAX * MAX_LIZARD_EAT);

	if (debug)
    {
		cout << "[" << _id << "] eating for " << eatSeconds << " seconds" << endl;
		cout << flush;
    }

	/*
     * Simulate eating by blocking for a few seconds
     */
	sleep( eatSeconds );

	if (debug)
    {
        cout << "[" << _id << "] finished eating" << endl;
        cout << flush;
    }
}

/**
 * Returns when it is safe for this lizard to cross from the monkey
 * grass to the sago.   Should use some synchronization 
 * facilities (lock/semaphore) here.
 * Status: Incomplete - Make changes as you see are necessary.
 */
void Lizard::monkeyGrass2SagoIsSafe()
{
	if (debug){
		cout << "[" << _id << "] checking  monkey grass -> sago" << endl;
		cout << flush;
    }

  while(numCrossingMonkeyGrass2Sago + numCrossingSago2MonkeyGrass >= MAX_LIZARD_CROSSING){
    sleep(0);
  }

	if (debug){
		cout << "[" << _id << "] thinks  monkey grass -> sago  is safe" << endl;
		cout << flush;
    }
}



/**
 * Delays for 1 second to simulate crossing from the monkey
 * grass to the sago.
 * Status: Incomplete - Make changes as you see are necessary.
 */
void Lizard::crossMonkeyGrass2Sago(){
	if (debug){
		cout << "[" << _id << "] crossing  monkey grass -> sago" << endl;
		cout << flush;
    }

    /*
     * One more crossing this way
     */
	numCrossingMonkeyGrass2Sago++;


    /*
     * Check for lizards cross both ways
     */
	if (numCrossingSago2MonkeyGrass && UNIDIRECTIONAL){
		cout << "\tOh No!, the lizards have cats all over them." << endl;
		cout << "\t " << numCrossingSago2MonkeyGrass << " crossing sago -> monkey grass" << endl;
		cout << "\t " << numCrossingMonkeyGrass2Sago << " crossing monkey grass -> sago" << endl;
		exit( -1 );
    }

	/*
     * It takes a while to cross, so simulate it
     */
	sleep( CROSS_SECONDS );

	/*
     * That one seems to have made it
     */
	numCrossingMonkeyGrass2Sago--;
}


/**
 *
 * Tells others they can go now
 * Status: Incomplete - Make changes as you see are necessary.
 */
void Lizard::madeIt2Sago()
{
	/*
     * Whew, made it across
     */
	if (debug){
		cout << "[" << _id << "] made the  monkey grass -> sago  crossing" << endl;
		cout << flush;
    }
}

/**
  * Follows the algorithm provided in the assignment
  * description to simulate lizards crossing back and forth
  * between a sago palm and some monkey grass. 
  * @param aLizard - the lizard to be executed concurrently
  * @return N/A
  * Status: Incomplete - Make changes as you see are necessary.
  */
void Lizard::lizardThread(Lizard *aLizard){	
    if (debug){
        cout << "[" << aLizard->getId() << "] lizard is alive" << endl;
        cout << flush;
    }

	while(running){
    /* 
    * Follow the algorithm given in the assignment
    * using calls to the functions declared above.
    * You'll need to complete the implementation of
    * some functions by filling in the code.  Some  
    * are already completed - see the comments.
    */

    
    aLizard->sleepNow();















    }

}


/*
 * main()
 *
 * Should initialize variables, locks, semaphores, etc.
 * Should start the cat thread and the lizard threads
 * Should block until all threads have terminated
 * Status: Incomplete - Make changes to this code.
 */
int main(int argc, char **argv){
	/*
	 * Declare local variables
     */
    



	/*
     * Check for the debugging flag (-d)
     */
	debug = 0;
	if (argc > 1)
		if (strncmp(argv[1], "-d", 2) == 0)
			debug = 1;


	/*
     * Initialize variables
     */
	numCrossingSago2MonkeyGrass = 0;
	numCrossingMonkeyGrass2Sago = 0;
	running = 1;

  numCrossing = 0;


	/*
     * Initialize random number generator
	 */
	srandom( (unsigned int)time(NULL) );


	/*
     * Initialize locks and/or semaphores
     */

    mutex mtx;
    counting_semaphore<10> semaphore(1);

	/*
     * Create NUM_LIZARDS lizard threads
     */
    vector<Lizard*> allLizards;
    for (int i=0; i < NUM_LIZARDS; i++) {
        allLizards.push_back(new Lizard(i));
    }    
    

    /*
     * Create NUM_CATS cat threads
     */

	/*
	 * Run NUM_LIZARDS and NUM_CATS threads
	 */
    for (int i=0; i < NUM_LIZARDS; i++) {
        allLizards[i]->run();
    }

	/*
     * Now let the world run for a while
     */
	sleep( WORLDEND );


	/*
     * That's it - the end of the world
     */
	running = 0;


    /*
     * Wait until all threads terminate
     */






	/*
     * Delete the locks and semaphores
     */
    

	/*
	 * Delete all cat and lizard objects
	 */



	/*
     * Exit happily
     */
	return 0;
}