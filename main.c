#include"stateSim.c"
#include<stdio.h>

void test2() {
	printf("woot \n");
}

int main() {

        addEvent(test2, 1);
        addEvent(test2, 2);
        addEvent(test2, 3);
	nextEvent();
	nextEvent();
	nextEvent();
	nextEvent();

        return 0;

}
