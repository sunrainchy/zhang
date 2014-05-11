/*
 * 这个文件是排序解析过后的ref文件，对每个文件按照基因起始位置进行排序
 * 结束位置小的放在前面，结束位置一样起始小的放在前面
 * sort_parsed_rec.cpp
 * author: sunrain
 *   date: 2014年 04月 14日 星期一 19:50:37 CST
 */
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <iostream>
using namespace std;
const int maxn = 500000;
struct ref_info{
	char seq[20];
	char no_use[20];
	char catg[20];
	int begin;
	int end;
}po[maxn];
bool cmp(const ref_info &a,const ref_info &b){
	if(a.begin == b.begin)
		return a.end < b.end;
	return a.begin < b.begin;
}
int main(int argc,char *argv[]){
	int i,j,k;
	char file_name[50];
	if(2 != argc){
		printf("Error Usage: ./sort_parsed_ref [the file name that you want to sort]\n");
		return 1;
	}
	strcpy(file_name,argv[1]);
	strcat(file_name,"_sorted");
	freopen(argv[1],"r+",stdin);
	freopen(file_name,"w+",stdout);
	k=0;
	while(scanf("%s%s%s%d%d",po[k].seq,po[k].no_use,po[k].catg,&po[k].begin,&po[k].end)!=EOF){
		k++;
	}
	sort(po,po+k,cmp);
	for(i=0;i<k;i++){
		printf("%s %s %s %d %d\n",po[i].seq,po[i].no_use,po[i].catg,po[i].begin,po[i].end);
	}
	return 0;
}
