/*
 * parse_ref_file.cpp
 * 此cpp文件为解析ref_Sscrofa10.2_top_level.gff3的程序
 * 分离出该文件的前五个字段
 * 该文件以#开头的为注释
 * 第二字段为RefSeq的行为注释信息，不保留
 * 除此之外保留下来的行格式为 编号 不管（保留） 基因类别 起始位置 结束位置
 * author： sunrain
 *   date：2014年 04月 14日 星期一 10:44:27 CST
 */
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <iostream>
#include <map>
#include <string>
using namespace std;
const int maxn = 20000;
char rec[maxn];
map<string,int> m;
char str[6][1000];
int main(int argc,char **argv){
	if(argc < 2){
		printf("Usage Error:%s [input file name] \n",argv[0]);
		return 1;
	}
	freopen(argv[1],"r",stdin);
	int i,j,k;
	while(gets(rec)){
		if(rec[0]=='#')
			continue;
		sscanf(rec,"%s%s%s%s%s%s",str[0],str[1],str[2],str[3],str[4],str[5]);
		if(strcmp(str[1],"RefSeq")==0) continue;
		if(m[string(str[0])]==0){
			freopen(str[0],"w",stdout);
			m[string(str[0])]=1;
		}
		if(strcmp(str[1],"Curated")==0 && strcmp(str[2],"Genomic")==0){
			printf("%s %s_%s %s %s %s \n",str[0],str[1],str[2],str[3],str[4],str[5]);
			continue;
		}
		for(i=0;i<5;i++) printf("%s ",str[i]);
		printf("\n");
	}
	return 0;
}
