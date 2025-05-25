#include <stdio.h>
#include <stdlib.h>
#include "process.h"

#define MAX_IO 3  // 프로세스당 최대 I/O 발생 횟수

typedef struct {
    int time;
    int duration;
    int done;
} IORequest;

void schedule_fcfs(Process *plist, int n) {
    // Arrival Time 기준 정렬
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
    printf("\n=== FCFS with I/O Gantt Chart ===\n");

    for (int i = 0; i < n; i++) {
        Process *p = &plist[i];

        // I/O 요청 시점들을 생성
        IORequest io[MAX_IO];
        int io_count = rand() % MAX_IO + 1;  // 1~MAX_IO
        int used_bursts[MAX_IO] = {0};

        for (int k = 0; k < io_count; k++) {
            int t;
            do {
                t = rand() % (p->burst_time - 1) + 1;  // 최소 1, 최대 burst-1
            } while (used_bursts[t % MAX_IO]);  // 중복 방지
            used_bursts[t % MAX_IO] = 1;
            io[k].time = t;
            io[k].duration = rand() % 4 + 1;  // 1~4
            io[k].done = 0;
        }

        int remaining_burst = p->burst_time;
        int executed = 0;

        if (current_time < p->arrival_time)
            current_time = p->arrival_time;

        p->start_time = current_time;

        while (remaining_burst > 0) {
            // 이번에 실행할 시간 (I/O 요청 발생 전까지만)
            int run_time = 1;

            // I/O 요청이 현재 실행 시점에 있는지 확인
            for (int k = 0; k < io_count; k++) {
                if (!io[k].done && executed == io[k].time) {
                    printf("| P%d (%d~%d) [I/O %ds] ", p->pid, current_time, current_time + run_time, io[k].duration);
                    current_time += run_time + io[k].duration;
                    io[k].done = 1;
                    break;
                }
            }

            // I/O 없으면 그냥 실행
            if (run_time == 1)
                printf("| P%d (%d~%d) ", p->pid, current_time, current_time + run_time);

            current_time += run_time;
            executed += run_time;
            remaining_burst -= run_time;
        }

        p->end_time = current_time;
        p->turnaround_time = p->end_time - p->arrival_time;
        p->waiting_time = p->turnaround_time - p->burst_time;
        p->finished = 1;
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