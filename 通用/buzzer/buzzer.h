
#ifndef _BUZZER_H_
#define _BUZZER_H_

typedef struct
{
	unsigned int setBuzzerOnTime_ms;
	unsigned int setBuzzerOffTime_ms;
	unsigned int C_buzzerOnTime_ms;
	unsigned int C_buzzerOffTime_ms;
	unsigned char buzzerTimes;
}struct_buzzer;
extern struct_buzzer stu_buzzer;

#define setBuzzerOnTime_ms	stu_buzzer.setBuzzerOnTime_ms
#define setBuzzerOffTime_ms	stu_buzzer.setBuzzerOffTime_ms
#define C_buzzerOnTime_ms	stu_buzzer.C_buzzerOnTime_ms
#define C_buzzerOffTime_ms	stu_buzzer.C_buzzerOffTime_ms
#define buzzerTimes		stu_buzzer.buzzerTimes

void buzzerOn(unsigned int bzOnTime_ms,unsigned int bzOffTime_ms,unsigned char bzTimes);

#endif