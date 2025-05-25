#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "process.h"

#define MAX_PROCESSES 10

void generate_processes(Process *plist, int n) {
    srand(time(NULL)); // 난수 초기화(실행할 때다 다른 값이 나오도록)
    for (int i = 0; i < n; i++) {
        plist[i].pid = i + 1;
        plist[i].arrival_time = rand() % 10; // 0~9
        plist[i].burst_time = (rand() % 8) + 3;  // 3~10
        plist[i].remaining_time = plist[i].burst_time;
        plist[i].io_start_time = rand() % plist[i].burst_time; // 무작위 시점에 I/O
        plist[i].io_burst_time = rand() % 4 + 1; // 1~4
        plist[i].priority = rand() % 10 + 1;     // 1~10
        plist[i].finished = 0;
        plist[i].start_time = -1;
    }
}

void print_process_list(Process *plist, int n) {
    printf("PID\tAT\tBT\tIO@/IO_BT\tPriority\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d/%d\t\t%d\n",
               plist[i].pid, plist[i].arrival_time,
               plist[i].burst_time, plist[i].io_start_time,
               plist[i].io_burst_time, plist[i].priority);
    }
}