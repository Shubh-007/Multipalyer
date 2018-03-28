#include<stdio.h>
#include<pthread.h>
pthread_mutex_t l1,l2;
pthread_t t1,t2,t3,t4,t5;
int nop=3;plcnt=0,gmcnt=0,jj=0;
void *plyroff();
void *gme();
void *stgm();
void *plyron();
void *mtst();



void *stgm()
	{if(gmcnt==0&&plcnt>=3){pthread_mutex_lock(&l1);
	gmcnt++;printf("\nGame no. %d is Starting\n",gmcnt);
	pthread_create(&t2,NULL,plyroff,NULL);printf("\nPlayer %d is offline\n",plcnt);
	pthread_join(t2,NULL);pthread_mutex_unlock(&l1);
	if(plcnt<3){pthread_create(&t4,NULL,gme,NULL);pthread_join(t4,NULL);jj++;}
	
	}else printf("\nCannot start due to pre-existing game\n");}

void *gme()
	{if(gmcnt>0){printf("\nGame no. %d is going to end\n",gmcnt);
	pthread_mutex_lock(&l1);
	gmcnt--;printf("\nGAME ENDS\n");
	pthread_mutex_unlock(&l1);
	}}

void *plyron()
	{
	pthread_mutex_lock(&l2);
	plcnt++;
	pthread_mutex_unlock(&l2);}

void *plyroff()
	{
	pthread_mutex_lock(&l2);
	plcnt--;
	pthread_mutex_unlock(&l2);}

void *mtst()
	{if((plcnt>=3)&&(gmcnt==0))
		{printf("\nLet the Game no. %d begin\n",gmcnt+1);pthread_create(&t3,NULL,stgm,NULL);
		pthread_join(t3,NULL);
		pthread_create(&t4,NULL,gme,NULL);pthread_join(t4,NULL);}
	}

int main()
	{int i,j,nog=nop/3;;
	for(i=0;i<nop;i++)
		{pthread_create(&t1,NULL,plyron,NULL);
		printf("\nPlayer %d is online\n",i+1);
		pthread_join(t1,NULL);if(i==2){pthread_create(&t5,NULL,mtst,NULL);pthread_join(t5,NULL);}
		}
	
	for(j=0;j<nog;j++)
		{pthread_create(&t5,NULL,mtst,NULL);pthread_join(t5,NULL);}
	
	if(jj==0){for(;i>0;i--){
		pthread_create(&t2,NULL,plyroff,NULL);printf("\nPlayer %d is offline\n",i);pthread_join(t2,NULL);}}
	else{for(i-=1;i>0;i--){
		pthread_create(&t2,NULL,plyroff,NULL);printf("\nPlayer %d is offline\n",i);pthread_join(t2,NULL);}}
	}
