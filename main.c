#include <stdio.h>
#include <string.h>
#include "process.h"

#define N 5


extern void generate_processes(Process *plist, int n);
extern void print_process_list(Process *plist, int n);
extern void schedule_fcfs(Process *plist, int n);
extern void schedule_sjf(Process *plist, int n);
extern void schedule_sjf_preemptive(Process *plist, int n);
extern void schedule_priority(Process *plist, int n);
extern void schedule_priority_preemptive(Process *plist, int n);
extern void schedule_rr(Process *plist, int n);


void copy_process_list(Process *dest, Process *src, int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
        dest[i].remaining_time = src[i].burst_time;
        dest[i].start_time = -1;
        dest[i].end_time = 0;
        dest[i].waiting_time = 0;
        dest[i].turnaround_time = 0;
        dest[i].finished = 0;
    }
}

int main() {
    Process plist[N];
    generate_processes(plist, N);

    printf("=== Process List ===\n");
    print_process_list(plist, N);

    Process temp[N];

    printf("\n--- FCFS ---\n");
    copy_process_list(temp, plist, N);
    schedule_fcfs(temp, N);

    printf("\n--- SJF (Non-preemptive) ---\n");
    copy_process_list(temp, plist, N);
    schedule_sjf(temp, N);

    printf("\n--- SJF (Preemptive - SRTF) ---\n");
    copy_process_list(temp, plist, N);
    schedule_sjf_preemptive(temp, N);

    printf("\n--- Priority (Non-preemptive) ---\n");
    copy_process_list(temp, plist, N);
    schedule_priority(temp, N);

    printf("\n--- Priority (Preemptive) ---\n");
    copy_process_list(temp, plist, N);
    schedule_priority_preemptive(temp, N);

    printf("\n--- Round Robin (Time Quantum = 4) ---\n");
    copy_process_list(temp, plist, N);
    schedule_rr(temp, N);

    return 0;
}