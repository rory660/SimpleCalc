#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *slice(char *inputString, int start, int end){
	char *returnString;
	returnString = malloc(sizeof(char)*100);
	for(int i = start; i <= end; i++){
 		returnString[i - start] = inputString[i];
 	}
 	returnString[end - start + 1] = '\0';
	return returnString;
}

float evaluate(char *expression){
	float result;
	int depth = 0;
	int openBracketIndex = NULL;
	for(int i = 0; i < strlen(expression); i++){
		if(expression[i] == '('){
			if(depth == 0){
				openBracketIndex = i;
			}
			depth++;
		}
		else if(expression[i] == ')'){
			depth--;
			if(depth == 0){
				char bracketsEval[100];
				sprintf(bracketsEval, "%f", evaluate(slice(expression, openBracketIndex + 1, i - 1)));
				char afterBrackets[100];
				strcpy(afterBrackets, slice(expression, i + 1, strlen(expression) - 1));
				strcpy(expression, slice(expression, 0, openBracketIndex - 1));
				strcat(expression, bracketsEval);
				strcat(expression, afterBrackets);
			}
		}
	}

	for(int i = 0; i < strlen(expression); i++){
		if(expression[i] == '+'){
			return evaluate(slice(expression, 0, i - 1)) + evaluate(slice(expression, i + 1, strlen(expression) - 1));
		}
		else if(expression[i] == '-'){
			return evaluate(slice(expression, 0, i - 1)) - evaluate(slice(expression, i + 1, strlen(expression) - 1));
		}
	}

	for(int i = 0; i < strlen(expression); i++){
		if(expression[i] == '*'){
			return evaluate(slice(expression, 0, i - 1)) * evaluate(slice(expression, i + 1, strlen(expression) - 1));
		}
	}

	for(int i = 0; i < strlen(expression); i++){
		if(expression[i] == '/'){
			return evaluate(slice(expression, 0, i - 1)) / evaluate(slice(expression, i + 1, strlen(expression) - 1));
		}
	}
	sscanf(expression, "%f", &result);
	return result;
}

int main(int argc, char *argv[]){
	printf("%g", evaluate(argv[1]));
	return 0;
}

