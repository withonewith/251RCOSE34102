#include <stdio.h>
#include "process.h"

#define TIME_QUANTUM 4  // 타임 퀀텀 값 조정 가능

void schedule_rr(Process *plist, int n) {
    int current_time = 0;
    int completed = 0;
    int queue[n];
    int front = 0, rear = 0;
    int in_queue[n];

    for (int i = 0; i < n; i++) {
        in_queue[i] = 0;
        if (plist[i].arrival_time == 0) {
            queue[rear++] = i;
            in_queue[i] = 1;
        }
    }

    printf("\n=== Round Robin (Time Quantum = %d) Gantt Chart ===\n", TIME_QUANTUM);

    while (completed < n) {
        if (front == rear) {
            current_time++;
            for (int i = 0; i < n; i++) {
                if (!plist[i].finished && !in_queue[i] && plist[i].arrival_time <= current_time) {
                    queue[rear++] = i;
                    in_queue[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++];
        Process *p = &plist[idx];

        if (p->start_time == -1)
            p->start_time = current_time;

        int exec_time = (p->remaining_time < TIME_QUANTUM) ? p->remaining_time : TIME_QUANTUM;

        printf("| P%d (%d~%d) ", p->pid, current_time, current_time + exec_time);

        p->remaining_time -= exec_time;
        current_time += exec_time;

        // 도중에 도착한 프로세스도 큐에 넣기
        for (int i = 0; i < n; i++) {
            if (!plist[i].finished && !in_queue[i] && plist[i].arrival_time <= current_time) {
                queue[rear++] = i;
                in_queue[i] = 1;
            }
        }

        if (p->remaining_time == 0) {
            p->end_time = current_time;
            p->turnaround_time = p->end_time - p->arrival_time;
            p->waiting_time = p->turnaround_time - p->burst_time;
            p->finished = 1;
            completed++;
        } else {
            queue[rear++] = idx;  // 다시 큐 뒤에 삽입
        }
    }

    printf("|\n");

    // 평균 출력
    int total_wait = 0, total_turn = 0;
    for (int i = 0; i < n; i++) {
        total_wait += plist[i].waiting_time;
        total_turn += plist[i].turnaround_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_wait / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turn / n);
}