#ifndef STATLOG_H
#define STATLOG_H


struct statBuf {
	int p_id;
	int prevState;
	int state;
	int stateTime;
};

/* for statlog */
#define BUFFER_LENGTH 512
#define STAT_RDY	0
#define STAT_RUN	1
#define STAT_BLK	2
#define STAT_TER	3
#define STAT_ADD	4

/* List of functions for kernel call */
#define POLL_LOG			0
#define START_TRACKING		1
#define ADD_PID				2
#define STOP_TRACKING		3
#define RM_PID				4
#define STAT_FORK			5
#define STAT_EXIT				6

#define PROCESS_TABLE_LIMIT 261

#endif /* STATLOG_H */