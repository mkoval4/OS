/******************************************************************************
* Maksym Koval
* October 30, 2018
* CS3305A - Operating Systems
* The following class evaluates memory availability and proceeds to create
* threads for multiprocessing
******************************************************************************/

#include "simulate.h"

int memory, max_memory;
FILE *fp;
pthread_t thread_exec[NUMBER_OF_THREADS];

void simulate(int memory_value, linked_stack_t *stack)
{
    //used to loop through creation and joining
    int i, j;
    
    //open the output file
    fp = fopen(SYSTEM_OUTPUT, "w");

    //Start the simulation with full memory availability
    memory = max_memory = memory_value;
    
    //Loop while stack is not empty 
    while(stack->size != 0){

        //create threads
        for(i=0; i < NUMBER_OF_THREADS && stack->size != 0; i++){    
            pthread_create(&thread_exec[i], NULL, thread_function, stack);
        }
       
       //join the remaining processes
       for(j = 0; j < i; j++){
           pthread_join(thread_exec[j], NULL);
       }
    }
}

void *thread_function(void *stack){

    job_t* job;

    /* Because of multithreading and parallism the while loop in simulate 
    * will not always have the most up to date stack->size value
    * due to this being the case we may get threads that are 
    * created although the stack is empty but the variable has not  
    * yet been updated. After hours of debuggin I realized it is 
    * cruicial to make sure we are not trying to pop off an an empty stack. 
    */ 
    if (((linked_stack_t*)stack)->head != NULL){
        
        //get job off the stack
        job = pop(((linked_stack_t*)stack));

        //check if the job needs to be discarded
        if((job->required_memory) > max_memory){

            //print the process cannot be executed
            print_exceed_memory(fp, job->number);
            
        //check if the job does not currently have enough memory
        }else if((job->required_memory) > memory){

            //print the process cannot be executed at this time push job back on stack
            print_insufficient_memory(fp, job->number);
            push(((linked_stack_t*)stack), job);
    
        //we can run the job
        }else{
            //print starting job
            print_starting(fp, (int)job->number);

            //allocate memory
            memory = memory - job->required_memory;
            print_allocate_memory(fp, memory, job->required_memory);

            //sleep
            sleep(job->required_time);

            //print job completion 
            print_completed(fp, job->number);

            //deallocate memory 
            memory = memory + job->required_memory;
            print_deallocate_memory(fp, memory, job->required_memory);
        }    
    }
}