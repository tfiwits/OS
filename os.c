#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct work{
	int randInt;
	int randTime;
}sW;
typedef struct workBlock{
	int workSize;
	int freeSize;
	int cc;
}wB;


int main(int argc, char *argv[])
{
		int cctmp=0,tmp=0,workTime=0,workCount=0,randWorkSize=0,randFull=0,randWork=0,workMem=0,switchOSSize=0,switchMerroy=0,switchArray=0,switchMode=6924;
		srand(time(NULL));
		randWork = (rand() % 3) + 1;
		printf("%d\n",randWork);
		wB workB[randWork*2+1];
		printf("請輸入工作總數：");
		scanf("%d",&switchArray);
		sW workInt[switchArray];
		printf("請輸入OS大小：");
		scanf("%d",&switchOSSize);
		printf("請輸入記憶體大小：");
		scanf("%d",&switchMerroy);
		printf("請選擇模式(1)FIFO(2)最適(3)最不適(其他)離開：");
		scanf("%d",&switchMode);
		printf("記憶體區塊\n");
		for (int i = 0; i < randWork*2 + 1; ++i)
		{
				workB[i].freeSize = 0;
				workB[i].workSize = 0;
				workB[i].cc = 0;
		}
		for (int i = 0; i < randWork * 2; ++i)
		{
			randFull = (switchMerroy - switchOSSize) / randWork;
			if(workB[i].freeSize == 0){
				workB[i].freeSize = randWorkSize = (rand() % randFull) + 1;
				workB[i].cc = i;
				workB[i+1].freeSize = randFull - randWorkSize;
				workB[i+1].cc = i+1;
			}
			workCount += workB[i].freeSize + workB[i*2].freeSize;
		}
		for (int i = 0; i < randWork*2; ++i)
		{
			printf("%d.%d-%d\n",i,workB[i].freeSize,workB[i].cc);
		}
		printf("記憶體大小:%d\n",switchMerroy);
		printf("os佔的:%d\n",switchOSSize);
		/*printf("總%d\n",workCount);*/
		if (switchMerroy - switchOSSize - workCount != 0 && !(switchMerroy - switchOSSize - workCount < 0))
		{
			workB[randWork*2].freeSize = switchMerroy - switchOSSize - workCount;
			printf("最後%d\n",workB[randWork*2].freeSize);
		}
		printf("工作\n");
		for (int i = 0; i < switchArray; ++i)
		{
			workInt[i].randInt=(rand() % (switchMerroy-switchOSSize) + 1) / randWork;
			workInt[i].randTime=(rand() % 15) + 1;
			printf("%d.%d\t%d\n",i,workInt[i].randInt,workInt[i].randTime);
		}
		workMem = switchOSSize;
		switch (switchMode) {
				case 1://FIFO
							for (int i = 0; i < switchArray; ++i){
									for (int j = 0; j < randWork * 2 + 1 ; ++j)
									{
										if (workInt[i].randInt <= workB[j].freeSize)
										{
											printf("工作區塊大小%d\n",workB[j].freeSize );
											workB[j].freeSize = workB[j].freeSize -  workInt[i].randInt;
											workB[j].workSize = workInt[i].randInt;
											printf("工作%d放到%d剩餘%d區塊大小%d工作時間為%d\n\n",i,j,workB[j].freeSize,workB[j].workSize,workInt[i].randTime);
											workInt[i].randInt = 0;
											break;
										}
									}
						}
							for (int i = 0; i < switchArray; ++i){
								if (workInt[i].randInt !=0)
								{
										printf("記憶體不足,工作%d無法執行\n",i);
								}
							}
									/*for (int i = 0;  i < randWork*2 + 1; ++i)*/
									/*{*/
											/*if (workB[i].workSize != 0)*/
											/*{*/
													/*printf("區塊%d內工作執行結束\n",i );*/
													/*workB[i].freeSize+= workB[i].workSize;*/
											/*}*/
									/*}*/
					break;
				case 2://最適
					for (int i = 0; i < randWork * 2; i++)
						for (int j = 0; j < randWork * 2 - i; j++)
						{
								if(workB[j].freeSize>workB[j+1].freeSize){
									tmp = workB[j].freeSize;
									workB[j].freeSize =workB[j+1].freeSize;
									workB[j+1].freeSize = tmp;
									cctmp = workB[j].cc;
									workB[j].cc =workB[j+1].cc;
									workB[j+1].cc= cctmp;
								}
						}
				 	for (int i = 0; i < randWork*2+1; ++i)
				  	{
						  printf("%d.%d-%d\n",i,workB[i].freeSize,workB[i].cc);
					}
							for (int i = 0; i < switchArray; ++i){
									for (int j = 0; j < randWork * 2 + 1 ; ++j)
									{
										if (workInt[i].randInt <= workB[j].freeSize)
										{
											printf("工作區塊大小%d\n",workB[j].freeSize );
											workB[j].freeSize = workB[j].freeSize -  workInt[i].randInt;
											workB[j].workSize = workInt[i].randInt;
											printf("工作%d放到%d剩餘%d工作大小%d工作時間為%d\n\n",i,workB[j].cc,workB[j].freeSize,workB[j].workSize,workInt[i].randTime);
											workInt[i].randInt = 0;
					for (int i = 0; i < randWork * 2; i++)
						for (int j = 0; j < randWork * 2 - i; j++)
						{
								if(workB[j].freeSize>workB[j+1].freeSize){
									tmp = workB[j].freeSize;
									workB[j].freeSize =workB[j+1].freeSize;
									workB[j+1].freeSize = tmp;
									cctmp = workB[j].cc;
									workB[j].cc =workB[j+1].cc;
									workB[j+1].cc= cctmp;
								}
						}
											break;
										}
									}
						}
							for (int i = 0; i < switchArray; ++i){
								if (workInt[i].randInt !=0)
								{
										printf("記憶體不足,工作%d無法執行\n",i);
								}
							}

					break;
				case 3://最不適
					for (int i = 0; i < randWork * 2; i++)
						for (int j = 0; j < randWork * 2 - i; j++)
						{
								if(workB[j].freeSize<workB[j+1].freeSize){
									tmp = workB[j].freeSize;
									workB[j].freeSize =workB[j+1].freeSize;
									workB[j+1].freeSize = tmp;
									cctmp = workB[j].cc;
									workB[j].cc =workB[j+1].cc;
									workB[j+1].cc= cctmp;
								}
						}
				 	for (int i = 0; i < randWork*2+1; ++i)
				  	{
						  printf("%d.%d-%d\n",i,workB[i].freeSize,workB[i].cc);
					}
							for (int i = 0; i < switchArray; ++i){
									for (int j = 0; j <randWork * 2 + 1; ++j)
									{
										if (workInt[i].randInt <= workB[j].freeSize)
										{
											printf("工作區塊大小%d\n",workB[j].freeSize );
											workB[j].freeSize = workB[j].freeSize -  workInt[i].randInt;
											workB[j].workSize = workInt[i].randInt;
											printf("工作%d放到%d剩餘%d工作大小%d工作時間為%d\n\n",i,workB[j].cc,workB[j].freeSize,workB[j].workSize,workInt[i].randTime);
											workInt[i].randInt = 0;
					for (int i = 0; i < randWork * 2; i++)
						for (int j = 0; j < randWork * 2 - i; j++)
						{
								if(workB[j].freeSize<workB[j+1].freeSize){
									tmp = workB[j].freeSize;
									workB[j].freeSize =workB[j+1].freeSize;
									workB[j+1].freeSize = tmp;
									cctmp = workB[j].cc;
									workB[j].cc =workB[j+1].cc;
									workB[j+1].cc= cctmp;
								}
						}
											break;
										}
									}
							}
							for (int i = 0; i < switchArray; ++i){
								if (workInt[i].randInt !=0)
								{
										printf("記憶體不足,工作%d無法執行\n",i);
								}
							}

					break;
				default:
					printf("exit\n");
		}
		return 0;
}
