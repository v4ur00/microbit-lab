#include "ppi.h"
#include "gpiote.h"

void init_PPI() {

    // Set up the PPI-channels 
    for(int i = 0; i <= 4; i++){
        PPI->PPI_CH[i].EEP = (uint32_t)&(GPIOTE->EVENTS_IN[5]);
        PPI->PPI_CH[i].TEP = (uint32_t)&(GPIOTE->TASKS_OUT[i]);
    }
    
    PPI->CHENSET = 0b11111;

};