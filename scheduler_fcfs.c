#include <stdio.h>
#include "process.h"

void schedule_fcfs(Process *plist, int n) {
    // 도착 시간(Arrival Time) 기준 정렬
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (plist[i].arrival_time > plist[j].arrival_time) {
                Process tmp = plist[i];
                plist[i] = plist[j];
                plist[j] = tmp;
            }
        }
    }

    int current_time = 0;
    printf("\n=== FCFS Gantt Chart ===\n");

    for (int i = 0; i < n; i++) {
        Process *p = &plist[i];

        // 아직 도착하지 않았다면 도착 시간까지 기다림
        if (current_time < p->arrival_time)
            current_time = p->arrival_time;

        p->start_time = current_time;
        p->end_time = current_time + p->burst_time;
        p->waiting_time = p->start_time - p->arrival_time;
        p->turnaround_time = p->end_time - p->arrival_time;
        p->finished = 1;

        printf("| P%d (%d~%d) ", p->pid, p->start_time, p->end_time);

        current_time = p->end_time;
    }

    printf("|\n");

    // 평균 대기 시간, 반환 시간 계산
    int total_wait = 0, total_turn = 0;
    for (int i = 0; i < n; i++) {
        total_wait += plist[i].waiting_time;
        total_turn += plist[i].turnaround_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_wait / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turn / n);
}