#include "headers.h"
ui* getSize(ui l){
	ui ls=14; /* len of s */
	/* TotalSize,DataSize,RS Size,#Regions,#blocks */
	ui s[][5]={{8,3,5,1,1},
		{10,5,7,1,1},
		{12,8,10,1,1},
		{14,12,12,1,1},
		{16,18,14,1,1},
		{18,22,18,1,1},
		{20,30,20,1,1},
		{22,36,24,1,1},
		{24,44,28,1,1},
		{28,62,36,2,1},
		{32,86,42,2,1},
		{36,114,48,2,1},
		{40,144,56,2,1},
		{44,174,68,2,1}};
	int md=-1;
	ui ms=44;
	f(ls){
		if(s[i][1]>=l){
			if(s[i][0]<md || md==-1){
				md=s[i][0];
				ms=i;
			}
		}
	}
	ui *r=malloc(sizeof(ui)*5);
	f(5) r[i]=s[ms][i];
	return r;
}
