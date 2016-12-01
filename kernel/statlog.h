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
#define STAT_RUN 1
#define STAT_BLK 2
#define STAT_TER 3

#endif /* STATLOG_H */