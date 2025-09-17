#include "version_1.h"

void init(){
    printf("\ninited\n");
}

void destroy(){
    printf("\ndest\n");
}

void pml_pre(pthread_mutex_t* x) {
    printf("\ncpml_pre\n");
    return ;
}

int pml_pos(int x) {
    printf("\npml_pos\n");
    return x;
}

void pmu_pre(pthread_mutex_t* x) {
    printf("\ncpmu_pre\n");
    return ;
}

int pmu_pos(int x) {
    printf("\npmu_pos\n");
    return x;
}
