/*
* Author: tfiwits<http://inori.atifans.net>
* LICENSE: GNU GPLv3
* Created on 2015-06-19
*/

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct work{
	int randInt;
	int randTime;
	int hh;
}sW;

typedef struct node {
	int workSize;
	int freeSize;
	int addr;
	int no;
	int timed;
	struct node *left;
	struct node *right;
	struct node *down;
	struct node *up;
}node;

node* inst(node* top, int item, int time,int no) {
	node* newnode;

	newnode = (node*)malloc(sizeof(node));

	if (newnode == NULL) {
		printf("記憶體配置失敗\n");
		exit(1);
	}
	newnode->freeSize = top->freeSize;
	newnode->workSize = item;
	newnode->timed = time;
	newnode->up = top;
	top->down = newnode;
	newnode->down = 0;
	newnode->addr = 0;
	newnode->no = no;
	return 0;
}

node* add(node* top, int item,int i) {
	node* newnode;

	newnode = (node*)malloc(sizeof(node));

	if (newnode == NULL) {
		printf("記憶體配置失敗\n");
		exit(1);
	}
	newnode->freeSize = item;
	newnode->left = top;
	newnode->right = top->right;
	top->right = newnode;
	newnode->down = 0;
	newnode->addr = 0;
	newnode->no = i;
	return newnode;
}



void PrintList(node *head,int bo)
{
	node *p = head;
	int addrTmp = 0;
	if (bo == 0){
		printf("工作區塊\n");
		p->addr = 0;
		addrTmp += p->freeSize;
		printf("%d.位置=0x%d,大小=%dM\n", p->no, p->addr, p->freeSize);
		for (p = p->left; p->left != 0; p = p->left){
			addrTmp += p->freeSize;
			p->addr = addrTmp;
			printf("%d.位置=0x%d,大小=%dM\n",p->no, p->addr, p->freeSize);
		}
	}
	else if (bo == 2)
	{
		for (p; p != NULL; p = p->right){
			addrTmp += p->freeSize;
			p->addr = addrTmp;
			printf("%d.位置=0x%d,大小=%dM\n", p->no, p->addr, p->freeSize);
		}
	}
}


int _tmain(int argc, _TCHAR* argv[]){
		int hhnb = 184,hhtmph = 0,hhtmp = 0,cctmp = 0, tmp = 0, workTime = 0, workCount = 0, randWorkSize = 0, randFull = 0, randWork = 0, workMem = 0, switchOSSize = 0, switchMerroy = 0, switchArray = 0, switchMode = 6924;
		node *workB, *dworkB, *oworkB, *cworkB,*crworkB;
		crworkB = (node*)malloc(sizeof(node));
		crworkB->left = 0;
		crworkB->right = 0;
		workB = (node*)malloc(sizeof(node));
		workB->left = 0;
		workB->down = 0;
		cworkB = (node*)malloc(sizeof(node));
		cworkB->left = 0;
		cworkB->right = 0;
		oworkB = (node*)malloc(sizeof(node));
		oworkB->left = 0;
		oworkB->right = 0;
		oworkB->down = 0;
		dworkB = (node*)malloc(sizeof(node));
		dworkB->left = 0;
		dworkB->right = 0;
		dworkB->down = 0;
		workB->right = 0;
		srand(time(NULL));
		randWork = (rand() % 2) + 1;

		printf("%d\n", randWork);
		printf("請輸入工作數量：");
		scanf_s("%d", &switchArray);
		sW workInt[100];
		printf("請輸入OS大小：");
		scanf_s("%d", &switchOSSize);
		printf("請輸入記憶體大小：");
		scanf_s("%d", &switchMerroy);
		if (switchOSSize > switchMerroy){
			exit(1);
		}
		printf("請選擇模式(1)先適(2)最適(3)最不適(其他)離開：");
		scanf_s("%d", &switchMode);
		printf("記憶體區塊\n");

		for (int i = 0; i < randWork * 2; i = i + 2)
		{
			randFull = (switchMerroy - switchOSSize) / randWork;
			do
			{
				randWorkSize = (rand() % randFull) + 1;
			} while (randWorkSize < 0);
			workB = add(workB, randWorkSize, i + 1);
			workCount += workB->freeSize;
			workB = add(workB, (randFull - workB->freeSize),  i + 2);
			workCount += workB->freeSize;
			cctmp += 2;
		}
		if (switchMerroy - switchOSSize - workCount != 0 && !(switchMerroy - switchOSSize - workCount < 0))
		{
			workB = add(workB, switchMerroy - switchOSSize - workCount,0);
			cctmp++;
		}
		PrintList(workB,0);

		printf("記憶體大小:%d\n", switchMerroy);
		printf("os佔的記憶體大小:%d\n", switchOSSize);
		printf("可用記憶體大小:%d\n", workCount);
		printf("工作\n");
		for (int i = 0; i < switchArray; ++i)
		{
			
			workInt[i].randInt = (rand() % (switchMerroy - switchOSSize) + 2) / randWork;
			workInt[i].randTime = (rand() % 15) + 1;
			workInt[i].hh = 1;
			printf("%d.%dM\n", i, workInt[i].randInt);
		}

		workMem = switchOSSize;
		oworkB = workB;
		workCount = 0;
		switch (switchMode) {
		case 1:
			for (int i = 0; i < switchArray; ++i){
				for (int i = 0; i < switchArray; ++i){
					workB = oworkB;
					if (workInt[i].randInt != 0){
						for (workB; workB->left != 0; workB = workB->left)
						{
							if (workInt[i].randInt <= workB->freeSize)
							{
								printf("工作區塊大小%dM\n", workB->freeSize);
								workB->freeSize = workB->freeSize - workInt[i].randInt;
								printf("工作%d放到區塊%d剩餘%dM工作大小%dM\n\n", i, workB->no, workB->freeSize, workInt[i].randInt);
								if (workB->down != 0){
									for (workB; workB->down != 0; workB = workB->down);
									inst(workB, workInt[i].randInt, workInt[i].randTime,workB->no);
								}
								else
								{
									inst(workB, workInt[i].randInt, workInt[i].randTime, workB->no);
								}
								workInt[i].randInt = 0;
								break;
							}
						}
					}
				}
				workB = oworkB;
				for (workB; workB->left != 0; workB = workB->left){
					if (workB->down != 0){
						dworkB = workB->down;
						for (dworkB; dworkB != 0; dworkB = dworkB->down)
						{
							workB->freeSize += dworkB->workSize;
							dworkB->workSize = 0;
							if (dworkB->down == 0)
							{
								workB->down = 0;
								break;
							}
						}
					}
				}
				
				printf_s("本次結果\n");
				for (int f = 0; f < switchArray; ++f)
				{
					if (workInt[f].randInt != 0)
					{
						printf_s("記憶體不足,工作%d無法執行\n\n", f);
						workCount += workInt[f].randInt;
						hhtmp++;
						workB = oworkB;
						for (workB; workB->left != 0; workB = workB->left){
							if (workInt[f].randInt <= workB->freeSize)
							{
								workInt[f].hh = 0;
								break;
							}
						}
						if (workInt[f].hh == 1){
							hhtmph++;
						}
						continue;
					}
				}

				printf_s("目前工作完成,完成工作之資源皆已釋放,等待下一輪\n\n");
				if (workCount == 0)
				{
					printf_s("最終結果\n");
					printf_s("所有工作順利結束\n");
					workCount = 1842;
					break;
				}
				workCount = 0;
					if (hhtmph == hhtmp)
					{
						break;
					}
					else
					{
						hhtmph = 0;
						hhtmp = 0;
					}

			}
			if (workCount != 1842)
			{
				printf_s("最終結果\n");
			}

			for (int i = 0; i < switchArray; ++i)
			{
				if (workInt[i].randInt != 0)
				{
					printf_s("記憶體不足,工作%d無法執行\n", i);
					continue;
				}
				
			}

				break;
		case 2:
		for (int i = 0; i <= cctmp; i++){
			 workB = oworkB;
			for (workB; workB->left != NULL; workB){
				if (workB->freeSize < workB->left->freeSize){
					*cworkB = *workB->left;
					workB->left->left = workB;
					if (workB->right != NULL){
						workB->right->left = workB->left;
					}
					workB->left->right = workB->right;
					workB->right = workB->left;
					workB->left = cworkB->left;
					workB->left->right = workB;
				}
				else
				{
					workB = workB->left;
				}
			}
		}
		oworkB = workB;
			for (int i = 0; i < switchArray; ++i){
				for (int j = 0; j < switchArray; ++j){
					for (int k = 0; k <= cctmp; k++){
						workB = oworkB;
						for (workB; workB->left != NULL; workB){
							if (workB->freeSize < workB->left->freeSize){
								*cworkB = *workB->left;
								workB->left->left = workB;
								if (workB->right != NULL){
									workB->right->left = workB->left;
								}
								workB->left->right = workB->right;
								workB->right = workB->left;
								workB->left = cworkB->left;
								workB->left->right = workB;
							}
							else
							{
								workB = workB->left;
							}
						}
					}
					if (workInt[j].randInt != 0){
						for (workB; workB != NULL; workB = workB->right)
						{
							if (workInt[j].randInt <= workB->freeSize)
							{
								printf("工作區塊大小%dM\n", workB->freeSize);
								workB->freeSize = workB->freeSize - workInt[j].randInt;
								printf("工作%d放到區塊%d剩餘%dM工作大小%dM\n\n", j, workB->no, workB->freeSize, workInt[j].randInt);
								if (workB->down != 0){
									for (workB; workB->down != 0; workB = workB->down);
									inst(workB, workInt[j].randInt, workInt[j].randTime, workB->no);
								}
								else
								{
									inst(workB, workInt[j].randInt, workInt[j].randTime, workB->no);
								}
								workInt[j].randInt = 0;
								break;
							}
						}
					}
				}
				workB = oworkB;
				for (workB; workB != NULL; workB = workB->right){
					if (workB->down != 0){
						dworkB = workB->down;
						for (dworkB; dworkB != 0; dworkB = dworkB->down)
						{
							workB->freeSize += dworkB->workSize;
							dworkB->workSize = 0;
							if (dworkB->down == 0)
							{
								workB->down = 0;
								break;
							}
						}
					}
				}
				

				printf_s("本次結果\n");
				for (int f= 0; f < switchArray; ++f)
				{
					
					if (workInt[f].randInt != 0)
					{
						printf_s("記憶體不足,工作%d無法執行\n\n", f);
						workCount += workInt[f].randInt;
						hhtmp++;
						workB = oworkB;
						for (workB; workB != NULL; workB = workB->right){
							if (workInt[f].randInt <= workB->freeSize)
							{

								workInt[f].hh = 0;
								break;
							}
						}
						if (workInt[f].hh == 1){
							hhtmph++;
						}
						continue;
					}
				}
				printf_s("目前工作完成,完成工作之資源皆已釋放,等待下一輪\n\n");
				if (workCount == 0)
				{
					printf_s("最終結果\n");
					printf_s("所有工作順利結束\n");
					workCount = 1842;
					break;
				}
				workCount = 0;
				if (hhtmph == hhtmp)
				{
					break;
				}
				else
				{
					hhtmph = 0;
					hhtmp = 0;
				}
			}

			if (workCount != 1842)
			{
				printf_s("最終結果\n");
			}
			for (int i = 0; i < switchArray; ++i)
			{
				if (workInt[i].randInt != 0)
				{
					
					printf_s("記憶體不足,工作%d無法執行\n", i);
					continue;
				}

			}

			break;
		case 3:
			for (int i = 0; i <= cctmp; i++){
				workB = oworkB;
				for (workB; workB->left != NULL; workB){
					if (workB->freeSize < workB->left->freeSize){
						*cworkB = *workB->left;
						workB->left->left = workB;
						if (workB->right != NULL){
							workB->right->left = workB->left;
						}
						workB->left->right = workB->right;
						workB->right = workB->left;
						workB->left = cworkB->left;
						workB->left->right = workB;
					}
					else
					{
						workB = workB->left;
					}
				}
			}
			for (workB; workB != NULL; workB = workB->right){
				oworkB = workB;
			}
			for (int i = 0; i < switchArray; ++i){
				for (int j = 0; j < switchArray; ++j){
					for (int k = 0; k <= cctmp; k++){
						workB = oworkB;
						for (workB; workB->left != NULL; workB){
							if (workB->freeSize < workB->left->freeSize){
								*cworkB = *workB->left;
								workB->left->left = workB;
								if (workB->right != NULL){
									workB->right->left = workB->left;
								}
								workB->left->right = workB->right;
								workB->right = workB->left;
								workB->left = cworkB->left;
								workB->left->right = workB;
							}
							else
							{
								workB = workB->left;
							}
						}
					}
					for (workB; workB != NULL; workB = workB->right){
						oworkB = workB;
					}
					workB = oworkB;
					if (workInt[j].randInt != 0){
						for (workB; workB != NULL; workB = workB->left)
						{
							if (workInt[j].randInt <= workB->freeSize)
							{
								printf("工作區塊大小%dM\n", workB->freeSize);
								workB->freeSize = workB->freeSize - workInt[j].randInt;
								printf("工作%d放到區塊%d剩餘%dM工作大小%dM\n\n", j, workB->no, workB->freeSize, workInt[j].randInt);
								if (workB->down != 0){
									for (workB; workB->down != 0; workB = workB->down);
									inst(workB, workInt[j].randInt, workInt[j].randTime, workB->no);
								}
								else
								{
									inst(workB, workInt[j].randInt, workInt[j].randTime, workB->no);
								}
								workInt[j].randInt = 0;
								break;
							}
						}
					}
				}
				workB = oworkB;
				for (workB; workB != NULL; workB = workB->left){
					if (workB->down != 0){
						dworkB = workB->down;
						for (dworkB; dworkB != 0; dworkB = dworkB->down)
						{
							workB->freeSize += dworkB->workSize;
							dworkB->workSize = 0;
							if (dworkB->down == 0)
							{
								workB->down = 0;
								break;
							}
						}
					}
				}
				

				printf_s("本次結果\n");
				for (int f = 0; f < switchArray; ++f)
				{
					
					if (workInt[f].randInt != 0)
					{
						printf_s("記憶體不足,工作%d無法執行\n", f);
						workCount += workInt[f].randInt;
						hhtmp++;
						workB = oworkB;
						for (workB; workB != NULL; workB = workB->left){
							if (workInt[f].randInt <= workB->freeSize)
							{

								workInt[f].hh = 0;
								break;
							}
						}
						if (workInt[f].hh == 1){
							hhtmph++;
						}
						continue;
					}


				}
				printf_s("目前工作完成,完成工作之資源皆已釋放,等待下一輪\n\n");
				if (workCount == 0)
				{
					printf_s("最終結果\n\n");
					printf_s("所有工作順利結束\n");
					workCount = 1842;
					break;
				}
				workCount = 0;
				if (hhtmph == hhtmp)
				{
					break;
				}
				else
				{
					hhtmph = 0;
					hhtmp = 0;
				}
			}

			if (workCount != 1842)
			{
				printf_s("最終結果\n");
			}
			for (int i = 0; i < switchArray; ++i)
			{
				if (workInt[i].randInt != 0)
				{

					printf_s("記憶體不足,工作%d無法執行\n", i);
					continue;
				}

			}
			break;
		default:
			printf("exit\n");
		}
		system("pause");
		return 0;
	}

