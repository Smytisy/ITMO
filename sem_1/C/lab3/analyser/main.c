#include <stdio.h>
#include <malloc.h>
#include "string.h"
#include <time.h>


long long counter_5xx = 0;


struct Node {
    void *value;
    struct Node *next;
};

struct Queue {
    int size;
    int max_size;
    struct Node *head;
    struct Node *tail;
};

struct Queue *newQueue(int capacity) {
    struct Queue *q;
    q = malloc(sizeof(struct Queue));

    if (q == NULL) {
        return q;
    }

    q->size = 0;
    q->max_size = capacity;
    q->head = NULL;
    q->tail = NULL;

    return q;
}

int enqueue(struct Queue *q, void *value) {
    if ((q->size + 1) > q->max_size) {
        return q->size;
    }

    struct Node *node = malloc(sizeof(struct Node));

    if (node == NULL) {
        return q->size;
    }

    node->value = value;
    node->next = NULL;

    if (q->head == NULL) {
        q->head = node;
        q->tail = node;
        q->size = 1;

        return q->size;
    }


    q->tail->next = node;
    q->tail = node;
    q->size += 1;

    return q->size;
}

void *dequeue(struct Queue *q) {
    if (q->size == 0) {
        return NULL;
    }

    void *value = NULL;
    struct Node *tmp = NULL;

    value = q->head->value;
    tmp = q->head;
    q->head = q->head->next;
    q->size -= 1;

    free(tmp);

    return value;
}


void freeQueue(struct Queue *q) {
    if (q == NULL) {
        return;
    }

    while (q->head != NULL) {
        struct Node *tmp = q->head;
        q->head = q->head->next;
        if (tmp->value != NULL) {
            free(tmp->value);
        }

        free(tmp);
    }

    if (q->tail != NULL) {
        free(q->tail);
    }

    free(q);
}


struct max_timeWindow {
    char *max_leftTime;
    char *max_rightTime;
    int max_count;
};


void printLine_5xx(char *line, FILE *fout) {
    int i = 0;
    int canPrintf = 0;
    int digit_status = 0;
    int quotes = 0;

    while (line[i] != '\0') {
        if (quotes == 2 && line[i] != ' ') {
            digit_status++;
            if (line[i] == '5' && digit_status == 1) {
                canPrintf = 1;
            }
        }
        if (line[i] == '"') {
            quotes++;
        }
        i++;
    }
    if (canPrintf == 1) {
        counter_5xx++;
        fprintf(fout, "%s", line);
    }
}

unsigned long long charToDigit(int a, int b) {
    return (a - '0') * 10 + b - '0';
}

unsigned long long yearToDigit(int c, int d) {
    return (c - '0') * 10 + (d - '0');
}

int getNumberMouth(char *month) {
    if (strcmp("Jan", month) == 0) {
        return 1;
    } else if (strcmp("Feb", month) == 0) {
        return 2;
    } else if (strcmp("Mar", month) == 0) {
        return 3;
    } else if (strcmp("Apr", month) == 0) {
        return 4;
    } else if (strcmp("May", month) == 0) {
        return 5;
    } else if (strcmp("Jun", month) == 0) {
        return 6;
    } else if (strcmp("Jul", month) == 0) {
        return 7;
    } else if (strcmp("Aug", month) == 0) {
        return 8;
    } else if (strcmp("Sep", month) == 0) {
        return 9;
    } else if (strcmp("Oct", month) == 0) {
        return 10;
    } else if (strcmp("Nov", month) == 0) {
        return 11;
    } else if (strcmp("Dec", month) == 0) {
        return 12;
    } else {
        return -1;
    }
}

int parseTime(char *time_string) {


    char *month = (char *) malloc(sizeof(char) * 3 + 1);
    month[0] = time_string[3];
    month[1] = time_string[4];
    month[2] = time_string[5];
    month[3] = '\0';


    struct tm *t = (struct tm*)malloc(sizeof(struct tm));
    t->tm_mon = getNumberMouth(month) - 1;
    //printf("%d ", getNumberMouth(month) - 1);

    t->tm_mday = charToDigit(time_string[0], time_string[1]);
    //printf("%llu ", charToDigit(time_string[0], time_string[1]));

    t->tm_hour = charToDigit(time_string[12], time_string[13]);
    //printf("%llu ", charToDigit(time_string[12], time_string[13]));

    t->tm_min = charToDigit(time_string[15], time_string[16]);
    //printf("%llu ", charToDigit(time_string[15], time_string[16]));

    t->tm_sec = charToDigit(time_string[18], time_string[19]);
    //printf("%llu ", charToDigit(time_string[18], time_string[19]));

    t->tm_year = yearToDigit(time_string[9], time_string[10]);
    //printf("%llu \n", yearToDigit(time_string[7], time_string[8], time_string[9], time_string[10]));


    return mktime(t);
}


char *getTimeInquire(char *str_inquire) {
    int i = 0;
    int is_Open = 0;
    int j = 0;
    while (str_inquire[i] != ']') {
        if (is_Open == 1) {
            str_inquire[j] = str_inquire[i];
            j++;
        }
        if (str_inquire[i] == '[') {
            is_Open = 1;
        }
        i++;
    }
    char *time;
    time = (char *) malloc(sizeof(char) * j + 1);
    strncpy(time, str_inquire, j);
    time[j] = '\0';
    return time;
}

void put_in_queue(char *time, struct Queue *q, unsigned long long time_window, struct max_timeWindow *maxT) {
    unsigned long long time_second = parseTime(time);
    if (q->size == 0 || time_second <= parseTime(q->head->value) + time_window) {
        enqueue(q, time);

        if (q->size > maxT->max_count) {
            maxT->max_count = q->size;
            maxT->max_leftTime = q->head->value;
            maxT->max_rightTime = q->tail->value;
        }
    } else {
        while (q->size != 0 && time_second > parseTime(q->head->value) + time_window) {
            dequeue(q);
        }
        enqueue(q, time);
    }
}

void find_time_window(unsigned long long time_window) {
    char *str_inquire;
    FILE *fin = fopen("C:\\Users\\mailo\\CLionProjects\\analysisAccessLog\\access_log_Jul95", "r");
    str_inquire = (char *) malloc(500 * sizeof(char));
    char *time_tmp;
    struct max_timeWindow *maxT;
    maxT = malloc(sizeof(struct max_timeWindow));
    maxT->max_count = -1;
    struct Queue *q = newQueue(2000000);

    while (fgets(str_inquire, 500, fin) != NULL) {
        time_tmp = getTimeInquire(str_inquire);
        put_in_queue(time_tmp, q, time_window, maxT);
    }
    printf("\nMax requests in your interval: %d\nSTART: %s\nEND:   %s\n", maxT->max_count, maxT->max_leftTime,
           maxT->max_rightTime);
    freeQueue(q);
    free(maxT);
    fclose(fin);
}


unsigned long long time_interval_to_ull(char *time_interval) {
    return charToDigit(time_interval[0], time_interval[1]) * 86400
           + charToDigit(time_interval[3], time_interval[4]) * 3600
           + charToDigit(time_interval[6], time_interval[7]) * 60
           + charToDigit(time_interval[9], time_interval[10]);
}

void do_lab_3(FILE *fin, FILE *fout) {
    char *str_inquire;
    str_inquire = (char *) malloc(500 * sizeof(char));

    while (fgets(str_inquire, 500, fin) != NULL) {
        printLine_5xx(str_inquire, fout);
    }
    free(str_inquire);

    printf("\nNumber of lines with error 5xx: %lld \n", counter_5xx);

    printf("\nEnter time interval (format: <day>:<hour>:<minute>:<second>)\n ");
    char *time_interval;
    time_interval = (char *) malloc(15 * sizeof(char));
    scanf("%s", time_interval);

    clock_t start, end;
    start = clock();
    find_time_window(time_interval_to_ull(time_interval));
    end = clock();
    printf("\nThe program was completed in %.2f seconds",
           (double) (end - start) / CLOCKS_PER_SEC);
}


int main() {
    FILE *fin = fopen("C:\\Users\\mailo\\CLionProjects\\analysisAccessLog\\access_log_Jul95", "r");
    FILE *fout = fopen("C:\\Users\\mailo\\CLionProjects\\analysisAccessLog\\access_log_5xx", "w");
    if (fin == NULL) {
        printf("File not found!");
        return 0;
    }
    do_lab_3(fin, fout);

    fclose(fin);
    fclose(fout);
    return 0;
}


