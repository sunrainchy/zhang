#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <iostream>
#include <cmath>
using namespace std;
const int maxn =400000000;
int len,down;//down=length
char str[maxn];
long long total_len;
unsigned short rec[maxn],my_map[10];
char my_ch[5]={'N','A','G','C','T'};
int init(){
	int i,j,k;
	scanf("%s",str);
	for(i=0;str[i];i++){
		if(str[i]=='A') str[i]=1;
		else if(str[i]=='G') str[i]=2;
		else if(str[i]=='C') str[i]=3;
		else if(str[i]=='T') str[i]=4;
		else str[i]=0;
	}
	len=i;
	str[len]=5;//最后补一个，保证最后一个一定不一样
	len++;
	str[len]=0;
	for(i=0;i<6;i++)
	my_map[i]=pow(5,i);
	return 0;
}
int find_one(int low){//处理长度为1的情况	
	int num=1;
	for(int i=1;i<len;i++){
		if(str[i]==str[i-1]) num++;
		else{
			if(str[i-1]==0){
				num=1;
				continue;
			}
			if(num>=low){
				printf("%c %d %lld\n",my_ch[str[i-1]],num,total_len+i-num+1);//string num pos
			}
			num=1;
		}
	}
	return 0;
}
int find_ans(int length,int low){
	int i,j,k,num,now_len=len-length+1;
	rec[0]=0;
	for(int i=0;i<=now_len;i+=length){
		rec[i]=0;
		for(j=0;j<length;j++)
			rec[i]=rec[i]*5+str[i+j];
		for(j=1;j<length;j++){
			k=i+j;
			rec[k]=rec[k-1];
			rec[k]-=str[k-1]*my_map[length-1];
			rec[k]=rec[k]*5+str[k+length-1];
		}
	}
	//for(i=0;i<now_len-length;i++)
	//	cout<<rec[i]<<' ';
	//cout<<endl;
	for(i=0;i<length;i++){
		num=1;
		for(j=i+length;j<=now_len;j+=length){
			if(rec[j]==rec[j-length]) num++;
			else {
				//printf("i:%d num:%d ,rec[j]:%d rec[j-length]:%d,j:%d j-length:%d\n",i,num,rec[j],rec[j-length],j,j-length);
				if(num*length > low){
					for(k=0;k<length;k++)
						if(str[j-length+k]==0) break;
					if(k<length){
						num=1;
						continue;
					}
					for(k=0;k<length;k++)
					putchar(my_ch[str[j-length+k]]);
					printf(" %d %lld\n",num,total_len+j-num*length+1);
				}
				num=1;
			}
		}
	}
	return 0;
}
char name[10][5]={"xaa","xab","xac","xad","xaf","xag","xah","xai"};
int main(){
	int i,j,k;
	//scanf("%d",&down);
	down=10;
//	freopen("ans","rw",stdout);
	for(k=0;k<8;k++){
		freopen(name[k],"rw",stdin);
		init();
		down=10;
		find_one(down);
		for(i=2;i<=6;i++){
			find_ans(i,down);
		}
		total_len+=len-1;
	}
	cerr<<total_len<<endl;
	return 0;
}
