/*
 * 此文件处理stirng_total处理出来的结果
 * 如果开头相同选择长的
 * 开头结尾都相同选择周期短的
 */
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;
const int maxn = 3094941+5;
struct point{
	char str[7];
	int num;
	int begin;
	int l;
	int end;
};
	bool cmp(const point &b,const point &a){
		if(b.begin == a.begin){
			if(b.num*b.l == a.num*a.l){
				return b.num < a.num;
			}
			return b.num*b.l < a.num*a.l;
		}
		return b.begin < a.begin;
	}
point po[maxn];
int main(int argc,char **argv){
	if(argc < 3) {
		printf("Usage Error: %s [input file name] [output file name] \n",argv[0]);
		return 1;
	}
	freopen(argv[1],"r",stdin);
	freopen(argv[2],"w",stdout);
	int i=0,j,k;
	int num_of_first;//记录第一轮筛选之后得出的结果个数
	int num_of_second;//记录第二轮筛选之后得出的结果个数
	while(scanf("%s %d %d",po[i].str,&po[i].num,&po[i].begin)!=EOF){
		po[i].l=strlen(po[i].str);
		po[i].end=po[i].begin+po[i].l;
		i++;
	}
	sort(po,po+i,cmp);
	//printf("%s %d %d\n",po[0].str,po[0].num,po[0].begin);
	num_of_first=1;
	for(j=1;j<i;j++){
		if(po[j].begin != po[j-1].begin){
			//printf("%s %d %d\n",po[j].str,po[j].num,po[j].begin);
			po[num_of_first++]=po[j];
		}
	}
	int l,r;
	for(i=0;i<num_of_first;i++){
		l=i-20;
		if(l<0) l=0;
		for( ;l<i;l++){
			if(po[i].begin>=po[l].begin && po[i].end<=po[l].end)
				break;
		}
		if(l<i) continue;//只要向前考虑就行了，向后没有必要，因为向后的最多是开始位置一样
		              //不可能出现包含关系了
		printf("%s %d %d\n",po[i].str,po[i].num,po[i].begin);
	}
	return 0;
}
