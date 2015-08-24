#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
	char s[]="werfwe";
	char *s1=(char*)malloc(sizeof(char));
	scanf("%s",s1);
	printf("%d\n",strcmp(s1,"sdfsdf"));
	return 0;
}
