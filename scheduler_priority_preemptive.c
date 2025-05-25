#include <stdio.h>
#include "process.h"

void schedule_priority_preemptive(Process *plist, int n) {
    int current_time = 0, completed = 0;
    int idx = -1;
    int highest_priority = 1e9;

    printf("\n=== Priority Scheduling (Preemptive) Gantt Chart ===\n");

    while (completed < n) {
        idx = -1;
        highest_priority = 1e9;

        for (int i = 0; i < n; i++) {
            if (plist[i].arrival_time <= current_time && !plist[i].finished && plist[i].remaining_time > 0) {
                if (plist[i].priority < highest_priority) {
                    highest_priority = plist[i].priority;
                    idx = i;
                } else if (plist[i].priority == highest_priority) {
                    if (plist[i].arrival_time < plist[idx].arrival_time) {
                        idx = i;
                    }
                }
            }
        }

        if (idx == -1) {
            current_time++;
            continue;
        }

        if (plist[idx].start_time == -1)
            plist[idx].start_time = current_time;

        printf("| P%d (%d) ", plist[idx].pid, current_time);

        plist[idx].remaining_time--;
        current_time++;

        if (plist[idx].remaining_time == 0) {
            plist[idx].end_time = current_time;
            plist[idx].turnaround_time = plist[idx].end_time - plist[idx].arrival_time;
            plist[idx].waiting_time = plist[idx].turnaround_time - plist[idx].burst_time;
            plist[idx].finished = 1;
            completed++;
        }
    }

    printf("|\n");

    // 평균 시간 계산
    int total_wait = 0, total_turn = 0;
    for (int i = 0; i < n; i++) {
        total_wait += plist[i].waiting_time;
        total_turn += plist[i].turnaround_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_wait / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turn / n);
}