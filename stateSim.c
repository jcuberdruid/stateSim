#include<stdio.h>
#include<stdlib.h>

typedef struct event { // Doubley linked list structure, with a function call as the action.
	struct event* next;
	struct event* prev;
	void (*action)();
	int time; 
} event;

struct event* origin; // Pointer to origin of event queue.

// Prototypes for functions to be used in conjunction with the addEvent function pointer.
void protoAddEvent(void(*action)(), int time);
void subsequentAddEvent(void (*action)(), int time); 

void (*addEvent)(void(*action)(), int time) = protoAddEvent; // user-facing function pointer for adding events.

void protoAddEvent(void(*action)(), int time) {; // called when the queue is empty to set up the added task as the origin.
	origin = (event*)(malloc(sizeof(event)));
	origin->next = origin;
	origin->prev = origin;
	origin->time = time;
	origin->action = action;
	addEvent = subsequentAddEvent;
}

void subsequentAddEvent(void (*action)(), int time) { // called when the queue is not empty, ensures the event is placed in cronological order.
	struct event* adding = (event*)(malloc(sizeof(event)));
	adding->action = action;
	adding->time = time;
	struct event* current = origin;
	for(;;) {
		if(current->time > adding->time){
			adding->next = current;
			adding->prev = current->prev;
			current->prev->next = adding;
			current->prev = adding;
			break;
		}		
		if(current->next == origin){
			adding->next = current->next;
			adding->prev = current;
			current->next->prev = adding;
			current->next = adding;
			break;
		}
		current = current->next;
	}
}

void nextEvent() { // calls the "action" function of the origin, and then pops the event queue if there are successive actions.
	if(origin != NULL) {
		origin->action();
		if(origin->next != origin) {	
			origin->next->prev = origin->prev;
			origin->prev->next = origin->next;
			struct event* garbageTemp = origin;
			origin = origin->next;
			free(garbageTemp);
		} else if(origin!= NULL) {
			addEvent = protoAddEvent;
			struct event* garbageTemp = origin;
			origin = NULL; 	
			free(garbageTemp);
		} 
	} else {
		printf("Event queue is empty, no actions to perform \n");
	}
}

