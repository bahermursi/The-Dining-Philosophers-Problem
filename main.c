//Baher Moursy
//900131407
//  main.cpp
//  The-Dining-Philosophers-Problem
//
//  Created by Baher Mursi on 12/3/16.
//  Copyright © 2016 bahermursi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


const int philosopher_number = 5;
pthread_t philisophers[philosopher_number];
pthread_mutex_t forks[philosopher_number];

void return_forks(int index){
	//leaving the fork after eating the fork
	printf("\nPhilosopher %d finished.", index);
	printf("\nPhilosopher %d returned left fork.", index);
	pthread_mutex_unlock(&forks[index]);
	printf("\nPhilosopher %d returned right fork.\n", index);
	pthread_mutex_unlock(&forks[(index + 1) % 5]);
}
void pickup_forks(int index){
	//grabbing the forks for eating
	//check for the availabe fork
	if (index > (index + 1) % philosopher_number){
		printf("\nPhilosopher %d wants left fork.", index);
		pthread_mutex_lock(&forks[index]);
		printf("\nPhilosopher %d grabbed left fork.\n", index);
		
		printf("\nPhilosopher %d wants right fork.", index);
		pthread_mutex_lock(&forks[(index + 1) % 5]);
		printf("\nPhilosopher %d grabbed right fork.\n", index);
	}
	else{
		
		printf("\nPhilosopher %d wants right fork.", index);
		pthread_mutex_lock(&forks[(index + 1) % 5]);
		printf("\nPhilosopher %d grabbed right fork.\n", index);
		
		printf("\nPhilosopher %d wants left fork.", index);
		pthread_mutex_lock(&forks[index]);
		printf("\nPhilosopher %d grabbed left fork.\n", index);
		
	}
}

void runner(int index){

	//use random number for sleeping
	//Time for phils to think
	usleep(random() % 2000000 + 1000000);
	
	pickup_forks(index);
	//Time for phils to eat
	usleep(random() % 2000000 + 1000000);
	
	//leave forks
	return_forks(index);
}

int main(int argc, const char * argv[]) {
	//intializing the mutex for the forks
	for(int i = 0; i < philosopher_number; ++i){
		pthread_mutex_init(&forks[i],NULL);
		
	}
	//creating threads with their assigned methods
	for(int i = 0; i < philosopher_number; ++i){
		pthread_create(&philisophers[i], NULL, (void *)runner, (int *)i); /* wait for the thread to exit */
	}
	
	//joining threads to the main thread
	for(int i = 0; i < philosopher_number; ++i){
		pthread_join(philisophers[i], NULL); /* wait for the thread to exit */
	}
	
	return 0;
}
