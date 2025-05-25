#include <stdio.h>
#include "process.h"

void schedule_sjf(Process *plist, int n) {
    int completed = 0;
    int current_time = 0;
    int is_completed[n];

    for (int i = 0; i < n; i++) is_completed[i] = 0;

    printf("\n=== SJF (Non-preemptive) Gantt Chart ===\n");

    while (completed < n) {
        int idx = -1;
        int min_burst = 1e9;

        for (int i = 0; i < n; i++) {
            if (plist[i].arrival_time <= current_time && !is_completed[i]) {
                if (plist[i].burst_time < min_burst) {
                    min_burst = plist[i].burst_time;
                    idx = i;
                } else if (plist[i].burst_time == min_burst) {
                    // 동일한 burst면 도착시간 빠른 것 우선
                    if (plist[i].arrival_time < plist[idx].arrival_time) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            if (current_time < plist[idx].arrival_time)
                current_time = plist[idx].arrival_time;

            plist[idx].start_time = current_time;
            plist[idx].end_time = current_time + plist[idx].burst_time;
            plist[idx].waiting_time = plist[idx].start_time - plist[idx].arrival_time;
            plist[idx].turnaround_time = plist[idx].end_time - plist[idx].arrival_time;
            plist[idx].finished = 1;

            printf("| P%d (%d~%d) ", plist[idx].pid, plist[idx].start_time, plist[idx].end_time);

            current_time = plist[idx].end_time;
            is_completed[idx] = 1;
            completed++;
        } else {
            // 실행 가능한 프로세스가 없을 경우 시간 증가
            current_time++;
        }
    }

    printf("|\n");

    // 평균 계산
    int total_wait = 0, total_turn = 0;
    for (int i = 0; i < n; i++) {
        total_wait += plist[i].waiting_time;
        total_turn += plist[i].turnaround_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_wait / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turn / n);
}