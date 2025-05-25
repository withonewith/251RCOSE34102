#include <stdio.h>
#include "process.h"

void schedule_sjf_preemptive(Process *plist, int n) {
    int current_time = 0, completed = 0;
    int shortest = -1;
    int min_remaining = 1e9;

    printf("\n=== SJF (Preemptive - SRTF) Gantt Chart ===\n");

    while (completed < n) {
        shortest = -1;
        min_remaining = 1e9;

        // 현재 시간에 실행 가능한 프로세스 중에서 남은 시간이 가장 짧은 프로세스를 찾는다
        for (int i = 0; i < n; i++) {
            if (plist[i].arrival_time <= current_time && !plist[i].finished && plist[i].remaining_time > 0) {
                if (plist[i].remaining_time < min_remaining) {
                    min_remaining = plist[i].remaining_time;
                    shortest = i;
                } else if (plist[i].remaining_time == min_remaining) {
                    if (plist[i].arrival_time < plist[shortest].arrival_time) {
                        shortest = i;
                    }
                }
            }
        }

        if (shortest == -1) {
            current_time++;  // 실행할 프로세스가 없으면 idle
            continue;
        }

        if (plist[shortest].start_time == -1)
            plist[shortest].start_time = current_time;

        printf("| P%d (%d) ", plist[shortest].pid, current_time);

        plist[shortest].remaining_time--;
        current_time++;

        if (plist[shortest].remaining_time == 0) {
            plist[shortest].end_time = current_time;
            plist[shortest].turnaround_time = plist[shortest].end_time - plist[shortest].arrival_time;
            plist[shortest].waiting_time = plist[shortest].turnaround_time - plist[shortest].burst_time;
            plist[shortest].finished = 1;
            completed++;
        }
    }

    printf("|\n");

    // 평균 시간 출력
    int total_wait = 0, total_turn = 0;
    for (int i = 0; i < n; i++) {
        total_wait += plist[i].waiting_time;
        total_turn += plist[i].turnaround_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_wait / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turn / n);
}