/* OPERATING SYSTEMS LAB - ALL PROGRAMS */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>


/* ============ PART A : PROCESS MANAGEMENT ============ */


/* PROGRAM 1 : fork() System Call - Basic */
void program1_fork_basic(void)
{
    int x = fork();

    printf("%d returned by fork & my process ID is %d\n", x, getpid());
}


/* PROGRAM 2 : fork() - Parent and Child Process IDs */
void program2_fork_parent_child_pid(void)
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        printf("Process creation failed\n");
    }
    else if (pid == 0)
    {
        printf("Child Process\n");
        printf("Child PID : %d\n", getpid());
        printf("Parent PID : %d\n", getppid());
    }
    else
    {
        printf("Parent Process\n");
        printf("Parent PID : %d\n", getpid());
        printf("Child PID : %d\n", pid);
    }
}


/* PROGRAM 3 : wait() System Call - Parent Waits for Child */
void program3_wait_system_call(void)
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        printf("Process creation failed\n");
    }
    else if (pid == 0)
    {
        printf("Child process started\n");
        printf("Child PID: %d\n", getpid());
        sleep(3);
        printf("Child process completed\n");
    }
    else
    {
        printf("Parent process started\n");
        printf("Parent PID: %d\n", getpid());
        wait(NULL);
        printf("Parent process: Child has completed\n");
    }
}


/* PROGRAM 4 : Orphan Process */
void program4_orphan_process(void)
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        printf("Process creation failed\n");
    }
    else if (pid == 0)
    {
        printf("Child process started\n");
        printf("Child PID: %d\n", getpid());
        printf("Initial Parent PID: %d\n", getppid());
        sleep(5);
        printf("\nAfter parent terminates:\n");
        printf("Child PID: %d\n", getpid());
        printf("New Parent PID: %d\n", getppid());
    }
    else
    {
        printf("Parent process started\n");
        printf("Parent PID: %d\n", getpid());
        sleep(2);
        printf("Parent process terminated\n");
        exit(0);
    }
}


/* PROGRAM 5 : Zombie Process */
void program5_zombie_process(void)
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        printf("Process creation failed\n");
    }
    else if (pid == 0)
    {
        printf("Child process started\n");
        printf("Child PID: %d\n", getpid());
        printf("Child process terminating...\n");
        exit(0);
    }
    else
    {
        printf("Parent process started\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);
        sleep(20);
        printf("Parent process terminating...\n");
    }
}


/* ============ PART B : CPU SCHEDULING ALGORITHMS ============ */


/* PROGRAM 6 : FCFS (First Come First Served) Scheduling */
void program6_fcfs_scheduling(void)
{
    int n, i;
    int bt[20], wt[20], tat[20];
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter burst time for each process:\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    wt[0] = 0;
    for (i = 1; i < n; i++)
    {
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    for (i = 0; i < n; i++)
    {
        tat[i] = wt[i] + bt[i];
    }

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t\t%d\t\t%d\n", i + 1, bt[i], wt[i], tat[i]);
        avg_wt  += wt[i];
        avg_tat += tat[i];
    }

    avg_wt  = avg_wt / n;
    avg_tat = avg_tat / n;

    printf("\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);
}


/* PROGRAM 7 : SJF (Shortest Job First) Scheduling - Non-Preemptive */
void program7_sjf_scheduling(void)
{
    int n, i, j;
    int bt[20], wt[20], tat[20], p[20];
    int temp;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter burst time for each process:\n");
    for (i = 0; i < n; i++)
    {
        p[i] = i + 1;
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (bt[i] > bt[j])
            {
                temp  = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                temp  = p[i];
                p[i]  = p[j];
                p[j]  = temp;
            }
        }
    }

    wt[0] = 0;
    for (i = 1; i < n; i++)
    {
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    for (i = 0; i < n; i++)
    {
        tat[i] = wt[i] + bt[i];
    }

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t\t%d\t\t%d\n", p[i], bt[i], wt[i], tat[i]);
        avg_wt  += wt[i];
        avg_tat += tat[i];
    }

    avg_wt  = avg_wt / n;
    avg_tat = avg_tat / n;

    printf("\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);
}


/* PROGRAM 8 : Priority Scheduling - Non-Preemptive */
struct Process {
    int pid, arrival, burst, priority;
    int completion, turnaround, waiting, done;
};

void program8_priority_scheduling(void)
{
    int n, time = 0, completed = 0;
    float total_waiting = 0, total_turnaround = 0;

    printf("PRIORITY SCHEDULING (NON-PREEMPTIVE)\n");
    printf("Lower priority number = higher priority\n\n");

    printf("Enter number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of processes.\n");
        return;
    }

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        p[i].done = 0;
        printf("\nEnter arrival time, burst time and priority for P%d: ", i + 1);
        if (scanf("%d %d %d", &p[i].arrival, &p[i].burst, &p[i].priority) != 3 ||
            p[i].arrival < 0 || p[i].burst <= 0) {
            printf("Invalid process details.\n");
            return;
        }
    }

    while (completed < n) {
        int selected = -1;

        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].arrival <= time) {
                if (selected == -1 || p[i].priority < p[selected].priority ||
                    (p[i].priority == p[selected].priority && p[i].arrival < p[selected].arrival))
                    selected = i;
            }
        }

        if (selected == -1) {
            time++;
            continue;
        }

        time += p[selected].burst;
        p[selected].completion = time;
        p[selected].turnaround = p[selected].completion - p[selected].arrival;
        p[selected].waiting    = p[selected].turnaround - p[selected].burst;
        p[selected].done = 1;

        total_waiting    += p[selected].waiting;
        total_turnaround += p[selected].turnaround;
        completed++;
    }

    printf("\n\nPID\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n", p[i].pid, p[i].arrival,
               p[i].burst, p[i].priority, p[i].completion,
               p[i].turnaround, p[i].waiting);
    }

    printf("\nAverage Turnaround Time = %.2f\n", total_turnaround / n);
    printf("Average Waiting Time    = %.2f\n", total_waiting / n);
}


/* PROGRAM 9 : Round Robin Scheduling */
void program9_round_robin_scheduling(void)
{
    int n, quantum, time = 0, completed = 0;
    float total_waiting = 0, total_turnaround = 0;

    printf("ROUND ROBIN CPU SCHEDULING\n\n");

    printf("Enter number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of processes.\n");
        return;
    }

    int arrival[n], burst[n], remaining[n], completion[n], waiting[n], turnaround[n];
    int queue[10000], front = 0, rear = 0, added[n];

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for P%d: ", i + 1);
        if (scanf("%d %d", &arrival[i], &burst[i]) != 2 || arrival[i] < 0 || burst[i] <= 0) {
            printf("Invalid process details.\n");
            return;
        }
        remaining[i] = burst[i];
        added[i] = 0;
    }

    printf("Enter time quantum: ");
    if (scanf("%d", &quantum) != 1 || quantum <= 0) {
        printf("Invalid time quantum.\n");
        return;
    }

    printf("\nExecution order: ");

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (!added[i] && arrival[i] <= time) {
                queue[rear++] = i;
                added[i] = 1;
            }
        }

        if (front == rear) {
            time++;
            continue;
        }

        int current = queue[front++];
        int slice = remaining[current] < quantum ? remaining[current] : quantum;

        printf("P%d ", current + 1);
        time += slice;
        remaining[current] -= slice;

        for (int i = 0; i < n; i++) {
            if (!added[i] && arrival[i] <= time) {
                queue[rear++] = i;
                added[i] = 1;
            }
        }

        if (remaining[current] > 0) {
            queue[rear++] = current;
        } else {
            completion[current] = time;
            turnaround[current] = completion[current] - arrival[current];
            waiting[current]    = turnaround[current] - burst[current];
            total_turnaround += turnaround[current];
            total_waiting    += waiting[current];
            completed++;
        }
    }

    printf("\n\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, arrival[i], burst[i],
               completion[i], turnaround[i], waiting[i]);
    }

    printf("\nAverage Turnaround Time = %.2f\n", total_turnaround / n);
    printf("Average Waiting Time    = %.2f\n", total_waiting / n);
}


/* ============ PART C : INTER-PROCESS COMMUNICATION ============ */


/* PROGRAM 10 : pipe() System Call - Unnamed Pipe */
void program10_pipe_system_call(void)
{
    int fd[2];
    pid_t pid;
    char write_msg[] = "Hello from Parent Process!";
    char read_msg[100];

    if (pipe(fd) == -1)
    {
        perror("Pipe failed");
        return;
    }

    pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        return;
    }

    if (pid > 0)
    {
        close(fd[0]);
        write(fd[1], write_msg, strlen(write_msg) + 1);
        close(fd[1]);
        wait(NULL);
    }
    else
    {
        close(fd[1]);
        read(fd[0], read_msg, sizeof(read_msg));
        printf("Child received: %s\n", read_msg);
        close(fd[0]);
    }
}


/* PROGRAM 11 : FIFO (Named Pipe) */
void program11_fifo_named_pipe(void)
{
    char *fifo = "/tmp/myfifo";
    char write_msg[] = "Hello through Named Pipe!";
    char read_msg[100];

    mkfifo(fifo, 0666);

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        return;
    }

    if (pid == 0)
    {
        int fd = open(fifo, O_RDONLY);
        read(fd, read_msg, sizeof(read_msg));
        printf("Reader received: %s\n", read_msg);
        close(fd);
    }
    else
    {
        int fd = open(fifo, O_WRONLY);
        write(fd, write_msg, strlen(write_msg) + 1);
        printf("Writer sent: %s\n", write_msg);
        close(fd);
        wait(NULL);
        unlink(fifo);
    }
}


/* ============ PART D : MEMORY MANAGEMENT ============ */


/* PROGRAM 12 : FIFO Page Replacement Algorithm */
void program12_fifo_page_replacement(void)
{
    int pages[50], frames[20];
    int n, f;
    int i, j, k;
    int pageFaults = 0, pageHits = 0;
    int pointer = 0, found;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for (i = 0; i < f; i++)
    {
        frames[i] = -1;
    }

    printf("\nPage\tFrames\t\tStatus\n");

    for (i = 0; i < n; i++)
    {
        found = 0;

        for (j = 0; j < f; j++)
        {
            if (frames[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if (found)
        {
            pageHits++;
        }
        else
        {
            frames[pointer] = pages[i];
            pointer = (pointer + 1) % f;
            pageFaults++;
        }

        printf("%d\t", pages[i]);
        for (k = 0; k < f; k++)
        {
            if (frames[k] == -1)
                printf("- ");
            else
                printf("%d ", frames[k]);
        }

        if (found)
            printf("\tPage Hit");
        else
            printf("\tPage Fault");

        printf("\n");
    }

    printf("\nTotal Page Hits = %d", pageHits);
    printf("\nTotal Page Faults = %d\n", pageFaults);
}


/* ============ MAIN : PROGRAM SELECTOR ============ */

static void show_menu(void)
{
    printf("\n=========== OPERATING SYSTEMS LAB - PROGRAM MENU ===========\n");
    printf(" PART A : Process Management\n");
    printf("   1.  fork() System Call - Basic\n");
    printf("   2.  fork() - Parent and Child Process IDs\n");
    printf("   3.  wait() System Call\n");
    printf("   4.  Orphan Process\n");
    printf("   5.  Zombie Process\n");
    printf(" PART B : CPU Scheduling\n");
    printf("   6.  FCFS Scheduling\n");
    printf("   7.  SJF Scheduling (Non-Preemptive)\n");
    printf("   8.  Priority Scheduling (Non-Preemptive)\n");
    printf("   9.  Round Robin Scheduling\n");
    printf(" PART C : Inter-Process Communication\n");
    printf("   10. pipe() - Unnamed Pipe\n");
    printf("   11. FIFO - Named Pipe\n");
    printf(" PART D : Memory Management\n");
    printf("   12. FIFO Page Replacement\n");
    printf(" (Programs 13 & 14 are shell scripts - see end of this file)\n");
    printf("=============================================================\n");
    printf("Enter your choice (1-12): ");
}

int main(int argc, char *argv[])
{
    int choice;

    if (argc > 1)
    {
        choice = atoi(argv[1]);
    }
    else
    {
        show_menu();
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input.\n");
            return 1;
        }
    }

    switch (choice)
    {
        case 1:  program1_fork_basic();                break;
        case 2:  program2_fork_parent_child_pid();     break;
        case 3:  program3_wait_system_call();          break;
        case 4:  program4_orphan_process();            break;
        case 5:  program5_zombie_process();            break;
        case 6:  program6_fcfs_scheduling();           break;
        case 7:  program7_sjf_scheduling();            break;
        case 8:  program8_priority_scheduling();       break;
        case 9:  program9_round_robin_scheduling();    break;
        case 10: program10_pipe_system_call();         break;
        case 11: program11_fifo_named_pipe();          break;
        case 12: program12_fifo_page_replacement();    break;
        default:
            printf("Invalid choice. Please select a number between 1 and 12.\n");
            return 1;
    }

    return 0;
}


/* ============ PART E : SHELL SCRIPTS (bash) ============ */

/*
 * PROGRAM 13 : Pattern Matching using grep   (save as pattern_matching.sh)
 *
 * #!/bin/bash
 *
 * echo "=== Pattern Matching using grep ==="
 * echo -n "Enter file name: "
 * read file
 * echo -n "Enter pattern to search: "
 * read pattern
 *
 * if [ ! -f "$file" ]; then
 *     echo "File not found!"
 *     exit 1
 * fi
 *
 * echo -e "\nLines matching '$pattern':"
 * grep -n -i "$pattern" "$file"
 *
 * if [ $? -ne 0 ]; then
 *     echo "No matching pattern found."
 * fi
 *
 *
 * PROGRAM 14 : String Handling in Shell   (save as string_handling.sh)
 *
 * #!/bin/bash
 *
 * echo "=== String Handling in Shell ==="
 * echo -n "Enter a string: "
 * read str
 *
 * echo "Length of string: ${#str}"
 * echo "Substring (first 5 characters): ${str:0:5}"
 *
 * echo -n "Enter another string: "
 * read str2
 *
 * echo "Concatenation: ${str}${str2}"
 *
 * if [ "$str" = "$str2" ]; then
 *     echo "Both strings are equal."
 * else
 *     echo "Both strings are different."
 * fi
 */
