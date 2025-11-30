#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

int direction = 0;

typedef struct {
	volatile uint32_t ODR;
} Traffic_TypeDef;

uint32_t VIRTUAL_MEMORY[1];
#define TRAFFIC_PORT ((Traffic_TypeDef *) VIRTUAL_MEMORY)
void State_Stop(void);
void State_Ready(void);
void State_Go(void);
void (*Next_State)(void) = State_Stop; 


void State_Stop(void)
{
	TRAFFIC_PORT->ODR |= (1 << 0);
	printf("light is red, stop.");
	sleep(2);
	TRAFFIC_PORT->ODR &= ~(1 << 0);
	direction = 0;
	Next_State = State_Ready;
}
void State_Ready(void)
{
	TRAFFIC_PORT->ODR |= (1 << 1);
	printf("light is yellow, get ready.");
	sleep(1);
	TRAFFIC_PORT->ODR &= ~(1 << 1);
	if(direction == 0)
	{
		Next_State = State_Go;
	}
	else
	{
		Next_State = State_Stop;
	}
}

void State_Go(void)
{
	TRAFFIC_PORT->ODR |= (1 << 2);
	printf("light is green, go.");
	sleep(2);
	TRAFFIC_PORT->ODR &= ~(1 << 2);
	direction = 1;
	Next_State = State_Ready;
}

int main()
{
	printf("Traffic Lights starting.");
	while(1)
	{
		Next_State();
		printf("register değeri: 0x%X\n\n", TRAFFIC_PORT->ODR);
	}
	return 0;
}










	
	
