#include<stdio.h>
#include<pthread.h>
pthread_mutex_t l1,l2;
pthread_t t1,t2,t3,t4,t5;
int nop=3;plcnt=0,gmcnt=0;

void *stgm()
	{if(gmcnt==0){pthread_mutex_lock(&l1);
	gmcnt++;printf("%d",gmcnt);	
	pthread_mutex_unlock(&l1);
	}else printf("\nCannot start due to pre-exixting game\n");}
void *gme()
	{if(gmcnt>0){
	pthread_mutex_lock(&l1);
	gmcnt--;printf("\nGAME OVER\n");
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
		{pthread_create(&t3,NULL,stgm,NULL);
		pthread_join(t3,NULL);printf("\n Let the GAME begin\n");pthread_create(&t4,NULL,gme,NULL);
		pthread_join(t4,NULL);}}
int main()
	{int i,j,nog=nop/3;;
	for(i=0;i<nop;i++)
		{pthread_create(&t1,NULL,plyron,NULL);
		printf("\nPlayer %d is online\n",i+1);
		pthread_join(t1,NULL);}
	for(j=0;j<nog;j++)
		{
		pthread_create(&t5,NULL,mtst,NULL);pthread_join(t5,NULL);
		}
	for(;i>0;i--)
		{pthread_create(&t2,NULL,plyroff,NULL);printf("\nPlayer %d is offline\n",i);
		pthread_join(t2,NULL);}
	}
