/*
 * 这个文件是求最后结果的
 * 输入两个文件一个是基因周期文件，一个是按结束位置排序的ref文件
 * 输出结果为第一文件名_第二文件名+last_result
 * author:sunrain
 *   date:2014年 04月 14日 星期一 21:07:46 CST
 */
#include <string.h>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string>
#include <set>
#include <map>
using namespace std;
const int maxn = 500000;
struct ref_info{
	char catg[20];
	int begin;
	int end;
}po[maxn];
struct peroid{
	char str[8];
	int num;
	int begin;
	int end;
}tem;
set<string> se;
map<string,int> ma;
map<string,int> cal_by_str;
map<int,int> cal_by_length;
map<string,map<int,int> > cal_by_cat_gene;
char str[100];
int num_of_ref;
int main(int argc,char *argv[]){
	if(4 != argc){
		printf("Error Usage: ./find_last_result <first_file:gene> <second_file:sorted ref file> <output file name :ans>\n");
		return 1;
	}
	int i,j,k=1;
	ma.clear();
	freopen(argv[2],"r+",stdin);
	while(scanf("%s%s%s%d%d",str,str,po[k].catg,&po[k].begin,&po[k].end)!=EOF){
		k++;
	}
	num_of_ref=k;
	freopen(argv[1],"r+",stdin);
	freopen(argv[3],"w+",stdout);
	int now_pos=1,then;
	bool all,part;
	while(scanf("%s%d%d",tem.str,&tem.num,&tem.begin)!=EOF){
		tem.end=tem.num*strlen(tem.str)+tem.begin-1;//注意这里要减去1
		all=part=false;
		/*
		while(now_pos < num_of_ref && po[now_pos].end < tem.begin) now_pos++;
		then=now_pos;
		*/
		printf("%s %d %d",tem.str,tem.num,tem.begin);
		cal_by_str[tem.str]++;
		cal_by_length[strlen(tem.str)]++;
		se.clear();
		/*
		while(then>=0 && tem.end > po[then].begin){
			if(po[then].begin <= tem.begin && po[then].end>=tem.end){
				printf(" %s",po[then].catg);
				all=true;
			}else if(tem.begin < po[then].begin && tem.end >= po[then].begin){
				part=true;
			}else if(tem.end > po[then].end && tem.begin < po[then].end){
				part=true;
			}
			then--;
		}
		*/
		//now_pos=1;
		while(now_pos < num_of_ref){
			if(tem.begin <= po[now_pos].begin && tem.begin >= po[now_pos-1].begin)
				break;
			now_pos++;
		}
		then=now_pos;
		while(then < num_of_ref && po[then].begin <= tem.end){
			if(po[then].begin <= tem.begin && po[then].end>=tem.end){
				//printf(" %s",po[then].catg);
				se.insert(string(po[then].catg));
				all=true;
			}else if(tem.begin < po[then].begin && tem.end >= po[then].begin){
				part=true;
			}else if(tem.end > po[then].end && tem.begin < po[then].end){
				part=true;
			}
			then++;
		}
		//cerr<<now_pos<<' '<<then<<' ';
		then=now_pos-1;
		while(then > 0 && po[then].end >= tem.begin){
			if(po[then].begin <= tem.begin && po[then].end>=tem.end){
				//printf(" %s",po[then].catg);
				se.insert(string(po[then].catg));
				all=true;
			}else if(tem.begin < po[then].begin && tem.end >= po[then].begin){
				part=true;
			}else if(tem.end > po[then].end && tem.begin < po[then].end){
				part=true;
			}
			then--;
		}
		//cerr<<then<<endl;
		if(all) {
			set<string>::iterator it=se.begin();
			for(it;it!=se.end();it++){
				cout<<' '<<*it;
				ma[(*it)]++;
				cal_by_cat_gene[*it][strlen(tem.str)]++;
			}
			putchar('\n');
			continue;
		}
		if(part){
			printf(" part\n");
			ma["P"]++;
			cal_by_cat_gene["P"][strlen(tem.str)]++;
		}
		else{
			printf(" NO\n");
			ma["N"]++;
			cal_by_cat_gene["N"][strlen(tem.str)]++;
		}
	}
	printf("\nCalculation by Cat of gene\n");
	for(map<string,int>::iterator it_m=ma.begin();it_m!=ma.end();it_m++){
		cout<<it_m->first<<' '<<it_m->second<<endl;
	}
	printf("\nCalculation by length 1-6\n");
	for(map<int,int>::iterator it_m=cal_by_length.begin();it_m!=cal_by_length.end();it_m++){
		printf("%d:        %d\n",it_m->first,it_m->second);
	}
	printf("Calculation bu Cat of gene and length\n");
	for(map<string,map<int,int> >::iterator m_it=cal_by_cat_gene.begin();m_it!=cal_by_cat_gene.end();m_it++){
		cout<<m_it->first<<endl;
		for(map<int,int>::iterator int_it=m_it->second.begin();int_it!=m_it->second.end();int_it++){
			printf("%d:      %d\n",int_it->first,int_it->second);
		}
	}
	printf("\nCalculation by string\n");
	for(map<string,int>::iterator it_m=cal_by_str.begin();it_m!=cal_by_str.end();it_m++){
		cout<<it_m->first<<":     "<<it_m->second<<endl;
	}
	return 0;
}
