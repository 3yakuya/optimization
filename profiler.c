#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "papi.h"
 
int eventCount = 2;
int events[] = {PAPI_FP_OPS, PAPI_L1_TCM, PAPI_L1_TCH, PAPI_L2_TCM, PAPI_L2_TCH, PAPI_L3_TCM, PAPI_L3_TCH};
 
void fail();
 
void startCounters() {
    int retval;
    if ( (retval = PAPI_start_counters(events, eventCount)) < PAPI_OK) {
	fail(__FILE__, __LINE__, PAPI_strerror(retval));
    }
}
 
void stopCounters(long long results[eventCount]) {
    int retval;
    if( (retval = PAPI_stop_counters(results, eventCount)) < PAPI_OK) {
    	fail(__FILE__, __LINE__, PAPI_strerror(retval));  
    }
}
 
void unloadAdapter() {
    PAPI_shutdown();
}
 
void fail(char *file, int line, char *call){
    printf("%s\tFAILED\nLine # %d\n", file, line);
    printf("Error: %s\n", call);
    printf("\n");
    exit(1);
}

void printCounters(long long results[]) {
	printf("Floating operations: %ld\n", results[0]);
	printf("L1 Cache misses: %ld\n", results[1]);
}

