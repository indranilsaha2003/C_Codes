#include<stdio.h>
#include<unistd.h>

int main(){
	pid_t pid ;
	pid = fork();
	if(pid>0){
		printf("[PARENT PROCESS]\n");
		printf("Parent of parent ID : %d\n",getppid());
		printf("Parent ID : %d\n",getpid());
		printf("Child Id : %d\n",pid);
	}
	else if(pid==0){
		printf("[CHILD PROCESS]\n");
		printf("Parent ID : %d\n",getppid());
		printf("Child Id : %d\n",getpid());
	}	
	else{
		printf("PROCESS FAILED !");
	}
	
	return 0;
}

