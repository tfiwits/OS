#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct work{
	int randInt;
	int randTime;
}sW;

typedef struct node {
	int workSize;
	int freeSize;
	int addr;
	int timed;
	struct node *left;
	struct node *right;
	struct node *down;
}node;

node* inst(node* top, int item, int time) {
	node* newnode;

	newnode = (node*)malloc(sizeof(node));

	if (newnode == NULL) {
		printf("記憶體配置失敗\n");
		exit(1);
	}
	newnode->freeSize = 0;
	newnode->workSize = item;
	newnode->timed = time;
	/*printf("fun%d\n",newnode->freeSize);*/
	newnode->left = top;
	top->down = newnode;
	newnode->down = 0;
	return newnode;
}

node* add(node* top, int item) {
	node* newnode;

	newnode = (node*)malloc(sizeof(node));

	if (newnode == NULL) {
		printf("記憶體配置失敗\n");
		exit(1);
	}
	newnode->freeSize = item;
	/*printf("fun%d\n",newnode->freeSize);*/
	newnode->left = top;
	newnode->right = top->right;
	top->right = newnode;
	newnode->down = 0;
	return newnode;
}

/*node* delete(node* top) {*/
	/*node* tmpnode;*/

	/*tmpnode = top;*/
	/*if (tmpnode == NULL) {*/
		/*printf("n堆疊已空！");*/
		/*return NULL;*/
	/*}*/

	/*top = top->next;*/
	/*free(tmpnode);*/

	/*return top;*/
/*}*/

void PrintList(node *head)
{
	node *p=head;
	int addrTmp=0;
	printf("工作區塊\n");
	p->addr=0;
	addrTmp += p->freeSize;
	printf("位置=0x%d,大小=%dM\n",p->addr,p->freeSize);
	for(p=p->left;p->left!=0;p=p->left){
		addrTmp += p->freeSize;
		p->addr = addrTmp;
		printf("位置=0x%d,大小=%dM\n",p->addr,p->freeSize);
	}
}

int main(int argc, char *argv[])
{
		int cctmp=0,tmp=0,workTime=0,workCount=0,randWorkSize=0,randFull=0,randWork=0,workMem=0,switchOSSize=0,switchMerroy=0,switchArray=0,switchMode=6924;
		node *workB,*dworkB;
		workB = (node*)malloc(sizeof(node));
		workB->left = 0;
		dworkB = (node*)malloc(sizeof(node));
		dworkB->left = 0;
		dworkB->right = 0;
		workB->right = 0;
		srand(time(NULL));
		randWork = (rand() % 3) + 1;

		printf("%d\n",randWork);
		printf("請輸入工作數量：");
		scanf("%d",&switchArray);
		sW workInt[switchArray];
		printf("請輸入OS大小：");
		scanf("%d",&switchOSSize);
		printf("請輸入記憶體大小：");
		scanf("%d",&switchMerroy);
		printf("請選擇模式(1)FIFO(2)最適(3)最不適(其他)離開：");
		scanf("%d",&switchMode);
		printf("記憶體區塊\n");

		for (int i = 0; i < randWork * 2; i=i+2)
		{
			randFull = (switchMerroy - switchOSSize) / randWork;
			randWorkSize = (rand() % randFull) + 1;
			workB = add(workB,randWorkSize);
			workCount += workB->freeSize;
			workB = add(workB,(randFull - workB->freeSize));
			workCount += workB->freeSize;
		}
		PrintList(workB);
		if (switchMerroy - switchOSSize - workCount != 0 && !(switchMerroy - switchOSSize - workCount < 0))
		{
			workB = add(workB,switchMerroy - switchOSSize - workCount);
			printf("位置=0x%d,大小=%dM\n",workB->right->addr+workB->freeSize,workB->freeSize);
		}
		printf("記憶體大小:%d\n",switchMerroy);
		printf("os佔的:%d\n",switchOSSize);
		printf("總%d\n",workCount);
		printf("工作\n");
		for (int i = 0; i < switchArray; ++i)
		{
			workInt[i].randInt=(rand() % (switchMerroy-switchOSSize) + 2) / randWork;
			workInt[i].randTime=(rand() % 15) + 1;
			printf("%d.%d\t%d\n",i,workInt[i].randInt,workInt[i].randTime);
		}

		workMem = switchOSSize;
		switch (switchMode) {
				case 1:
							for (int i = 0; i < switchArray; ++i){
									for (workB;workB->left!=0;workB=workB->left)
									{
										if (workInt[i].randInt <= workB->freeSize)
										{
											printf("工作區塊大小%d\n",workB->freeSize );
											workB->freeSize = workB->freeSize -  workInt[i].randInt;
											dworkB = inst(workB,workInt[i].randInt,workInt[i].randTime);
											printf("工作%d放到0x%d剩餘%d工作大小%d工作時間為%d\n\n",i,workB->addr,workB->freeSize,workInt[i].randInt,workInt[i].randTime);
											workInt[i].randInt = 0;
											break;
										}
										if (workB->down!=0){
												for (dworkB;dworkB->down!=0;dworkB=dworkB->down)
												{
														if (workInt[i].randInt <= dworkB->freeSize)
														{
															printf("工作區塊大小%d\n",workB->freeSize );
															workB->freeSize = workB->freeSize -  workInt[i].randInt;
															dworkB = inst(workB,workInt[i].randInt,workInt[i].randTime);
															printf("工作%d放到0x%d剩餘%d工作大小%d工作時間為%d\n\n",i,workB->addr,workB->freeSize,workB->workSize,workInt[i].randTime);
															workInt[i].randInt = 0;
															break;
														}
													
												}
											}
									}
						}
						/*for (workB;workB->left!=0;workB=workB->left){*/
							/*if(workB->timed > workB->left->timed){*/
								/*workB->left->freeSize+=workB->left->workSize;*/
								/*workB->left->timed = 0;*/
								/*workB->left->right = workB->right;*/
								/*workB->left = workB->left->left;*/
								/*workB->right = workB->left;*/
								/*workB->left->left = workB;*/
							/*}*/
						/*}*/
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
				case 2:
					/*for (int i = 0; i < randWork * 2; i++)*/
						/*for (int j = 0; j < randWork * 2 - i; j++)*/
						/*{*/
								/*if(workB[j].freeSize>workB[j+1].freeSize){*/
									/*tmp = workB[j].freeSize;*/
									/*workB[j].freeSize =workB[j+1].freeSize;*/
									/*workB[j+1].freeSize = tmp;*/
									/*cctmp = workB[j].cc;*/
									/*workB[j].cc =workB[j+1].cc;*/
									/*workB[j+1].cc= cctmp;*/
								/*}*/
						/*}*/
					 /*for (int i = 0; i < randWork*2+1; ++i)*/
					  /*{*/
						  /*printf("%d.%d-%d\n",i,workB[i].freeSize,workB[i].cc);*/
					/*}*/
							/*for (int i = 0; i < switchArray; ++i){*/
									/*for (int j = 0; j < randWork * 2 + 1 ; ++j)*/
									/*{*/
										/*if (workInt[i].randInt <= workB[j].freeSize)*/
										/*{*/
											/*printf("工作區塊大小%d\n",workB[j].freeSize );*/
											/*workB[j].freeSize = workB[j].freeSize -  workInt[i].randInt;*/
											/*workB[j].workSize = workInt[i].randInt;*/
											/*printf("工作%d放到%d剩餘%d工作大小%d工作時間為%d\n\n",i,workB[j].cc,workB[j].freeSize,workB[j].workSize,workInt[i].randTime);*/
											/*workInt[i].randInt = 0;*/
					/*for (int i = 0; i < randWork * 2; i++)*/
						/*for (int j = 0; j < randWork * 2 - i; j++)*/
						/*{*/
								/*if(workB[j].freeSize>workB[j+1].freeSize){*/
									/*tmp = workB[j].freeSize;*/
									/*workB[j].freeSize =workB[j+1].freeSize;*/
									/*workB[j+1].freeSize = tmp;*/
									/*cctmp = workB[j].cc;*/
									/*workB[j].cc =workB[j+1].cc;*/
									/*workB[j+1].cc= cctmp;*/
								/*}*/
						/*}*/
											/*break;*/
										/*}*/
									/*}*/
						/*}*/
							/*for (int i = 0; i < switchArray; ++i){*/
								/*if (workInt[i].randInt !=0)*/
								/*{*/
										/*printf("記憶體不足,工作%d無法執行\n",i);*/
								/*}*/
							/*}*/

					break;
				case 3:
					/*for (int i = 0; i < randWork * 2; i++)*/
						/*for (int j = 0; j < randWork * 2 - i; j++)*/
						/*{*/
								/*if(workB[j].freeSize<workB[j+1].freeSize){*/
									/*tmp = workB[j].freeSize;*/
									/*workB[j].freeSize =workB[j+1].freeSize;*/
									/*workB[j+1].freeSize = tmp;*/
									/*cctmp = workB[j].cc;*/
									/*workB[j].cc =workB[j+1].cc;*/
									/*workB[j+1].cc= cctmp;*/
								/*}*/
						/*}*/
					 /*for (int i = 0; i < randWork*2+1; ++i)*/
					  /*{*/
						  /*printf("%d.%d-%d\n",i,workB[i].freeSize,workB[i].cc);*/
					/*}*/
							/*for (int i = 0; i < switchArray; ++i){*/
									/*for (int j = 0; j <randWork * 2 + 1; ++j)*/
									/*{*/
										/*if (workInt[i].randInt <= workB[j].freeSize)*/
										/*{*/
											/*printf("工作區塊大小%d\n",workB[j].freeSize );*/
											/*workB[j].freeSize = workB[j].freeSize -  workInt[i].randInt;*/
											/*workB[j].workSize = workInt[i].randInt;*/
											/*printf("工作%d放到%d剩餘%d工作大小%d工作時間為%d\n\n",i,workB[j].cc,workB[j].freeSize,workB[j].workSize,workInt[i].randTime);*/
											/*workInt[i].randInt = 0;*/
					/*for (int i = 0; i < randWork * 2; i++)*/
						/*for (int j = 0; j < randWork * 2 - i; j++)*/
						/*{*/
								/*if(workB[j].freeSize<workB[j+1].freeSize){*/
									/*tmp = workB[j].freeSize;*/
									/*workB[j].freeSize =workB[j+1].freeSize;*/
									/*workB[j+1].freeSize = tmp;*/
									/*cctmp = workB[j].cc;*/
									/*workB[j].cc =workB[j+1].cc;*/
									/*workB[j+1].cc= cctmp;*/
								/*}*/
						/*}*/
											/*break;*/
										/*}*/
									/*}*/
							/*}*/
							/*for (int i = 0; i < switchArray; ++i){*/
								/*if (workInt[i].randInt !=0)*/
								/*{*/
										/*printf("記憶體不足,工作%d無法執行\n",i);*/
								/*}*/
							/*}*/

					break;
				default:
					printf("exit\n");
		}
		return 0;
}
