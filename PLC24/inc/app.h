#ifndef __APP_H
#define __APP_H

typedef struct{
	struct{
		char display;
		char motorDrive;
	}thread;
}t_app;
t_app _app;

void app(void);
void app_display(void);
void app_display_fault(char fault);
void app_ir(void);
void app_rotarySwitch(void);
void app_trigger(void);
void app_motorDrive(void);

#endif
