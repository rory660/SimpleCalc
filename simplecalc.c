#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *slice(char *inputString, int start, int end){
	char *returnString;
	returnString = malloc(sizeof(char)*100);
	for(int i = start; i <= end; i++){
 		returnString[i - start] = inputString[i];
 	}
 	returnString[end + 1] = '\0';
	return returnString;
}

int evaluate(char *expression){
	int result;
	for(int i = 0; i < strlen(expression); i++){
		if(expression[i] == '+'){
			return evaluate(slice(expression, 0, i - 1)) + evaluate(slice(expression, i + 1, strlen(expression) - 1));
		}
	}
	sscanf(expression, "%d", &result);
	return result;
}

int main(int argc, char *argv[]){
	printf("%d", evaluate(argv[1]));
}

