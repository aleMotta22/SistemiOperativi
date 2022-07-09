#include <stdio.h>

#include <stdlib.h>

#include <sys/ipc.h>

#include <sys/shm.h>

#include <sys/wait.h>

#include <unistd.h>







#define DIM_BUFFER 3

#define HOW_MANY 200

#define S_MUTEX 0

#define S_EMPTY 1

#define S_FULL 2



int WAIT(int sem_des, int num_semaforo) {

    struct sembuf operazioni[1] = {{num_semaforo, -1, 0}};

    return semop(sem_des, operazioni, 1);

}



int SIGNAL(int sem_des, int num_semaforo) {

    struct sembuf operazioni[1] = {{num_semaforo, +1, 0}};

    return semop(sem_des, operazioni, 1);

}



void manager(int shm, int sems) {

	int *p, *in, *out;



	if ((p = (int *)shmat(shm, NULL, 0)) == (int *)-1) { // attacca la memoria condivisia

		perror("shmat");

		exit(1);

	}

    FILE *in;



	in = fopen("file.txt", "r");



	if(file == NULL){

		perror("file");

		exit(1);

	}



		p[0] = 0;



 while ((c = fgetc(in)) != EOF){

      	  	WAIT(sems, S_EMPTY); // diminuisce le posizioni vuote

        WAIT(sems, S_MUTEX); // entra nella sezione critica

        p[1] = p[0];



     }







}





int main(int argc,char * argv[]){

	int id_shm, id_sems;





	if((id_shm =shmget(IPC_PRIVATE, (DIM_BUFFER +2 ) * sizeof(int),IPC_CREATE | 0600)) == -1){

		perror("shmget");

		exit(1);

	}



	if((id_sems = semget(IPC_PRIVATE,3,IPC_CREATE | 0600)) == -1){

		perror("semget");

		exit(1);



	}



	semctl(id_sems, S_MUTEX, SETVAL, 1);

	semctl(id_sems, S_EMPTY, SETVAL, DIM_BUFFER);

	semctl(id_sems, S_FULL, SETVAL, 0);





	shmctl(id_shm, IPC_RMID, NULL);

	semctl(id_sems, 0, IPC_RMID, 0);

	exit(0);

}