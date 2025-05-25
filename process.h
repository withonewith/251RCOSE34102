#ifndef PROCESS_H
#define PROCESS_H

typedef struct {
    int pid;              // Process ID
    int arrival_time;     // Arrival Time
    int burst_time;       // CPU Burst Time
    int remaining_time;   // Remaining Burst Time (for preemptive)
    int io_start_time;    // I/O 요청 시점 (고정값)
    int io_burst_time;    // I/O 수행 시간
    int priority;         // 낮을수록 우선순위 높음

    int start_time;       // 실제 CPU 처음 배정 시각
    int end_time;         // 종료 시각
    int waiting_time;
    int turnaround_time;

    int finished;         // 완료 여부 (0 or 1)
} Process;

#endif