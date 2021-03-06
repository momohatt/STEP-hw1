#include<iostream>
#include<string>
#include<vector>
#include<stack>
using namespace std;

enum Type {NUMBER, PLUS, MINUS, MULTIPLY, DIVIDE, BRACKET_HEAD, BRACKET_TAIL};
//typedef enum Type Type;

struct Token {
    Type type;
    union {
        double number;
    } value;
};

int indx; //used 'indx' instead of 'index'
#define TKBUFSIZE 256
#define NUM(x) ((x).value.number)
char tokenbuf[TKBUFSIZE];

Token readNumber(string line) {
	double number = 0.0;
	while (indx < line.length() && isdigit(line[indx]))
	{
		number = number * 10 + (line[indx] - '0');
		indx++;
	}
	if (indx < line.length() && line[indx] == '.')
	{
		indx++;
		double keta = 0.1;
		while (indx < line.length() && isdigit(line[indx]))
		{
			number += (line[indx] - '0') * keta;
			keta *= 0.1;
			indx++;
		}
	}

	Token token;
	token.type = NUMBER;
	NUM(token) = number;
	return token;
}

Token readPlus(string line) {
	Token token;
	token.type = PLUS;
	indx++;
	return token;
}

Token readMinus(string line) {
	Token token;
	token.type = MINUS;
	indx++;
	return token;
}

Token readMultiply(string line){
    Token token;
    token.type = MULTIPLY;
    indx++;
    return token;
}

Token readDivide(string line){
    Token token;
    token.type = DIVIDE;
    indx++;
    return token;
}

Token readBracketHead(string line){
    Token token;
    token.type = BRACKET_HEAD;
    indx++;
    return token;
}

Token readBracketTail(string line){
    Token token;
    token.type = BRACKET_TAIL;
    indx++;
    return token;
}

vector<Token> tokenize(string line) {
	vector<Token> tokens;
	indx = 0;
	Token token;
	while (indx < line.length()) {
		if (isdigit(line[indx])) {
			token = readNumber(line);
		} else if (line[indx] == '+') {
			token = readPlus(line);
		} else if (line[indx] == '-') {
			token = readMinus(line);
		} else if (line[indx] == '*'){
            token = readMultiply(line);
        } else if (line[indx] == '/'){
            token = readDivide(line);
        } else if (line[indx] == '('){
            token = readBracketHead(line);
        } else if (line[indx] == ')'){
            token = readBracketTail(line);
        } else {
			cout << "Invalid character found: " << line[indx] << endl;
			exit(1);
		}
		tokens.push_back(token);
	}
	return tokens;
}

vector<Token> polishize(vector<Token> tokens)
{
    int length=tokens.size();
    int priority[length];
    vector<Token> polishizedtokens[length];
    stack<Token> stack[length+1];   int sp1=0; //stackpointer
    stack<Token> polish[length+1];  int sp2=0; //stackpointer

    for(int i=0;i<length;++i){
        if(tokens[i].type==NUMBER) priority[i]=3;
        if(tokens[i].type==PLUS||tokens[i].type=='MINUS') priority[i]==1;
        if(tokens[i].type==MULTIPLY||tokens[i].type=='DIVIDE') priority[i]==2;
        if(tokens[i].type==BRACKET_HEAD) priority[i]=0;
        if(tokens[i].type==BRACKET_TAIL) priority[i]=0;
    }

    stack[0].type='NUMBER'; stack.value=0;
    priority[0]=0;

    for(int i=1;i<=length;++i){
        if(tokens[i].type=='BRACKET_HEAD'){ //transact (
            stack[++sp1]=tokens[i];
        } else if(tokens[i].type=='BRACKET_TAIL'){ //transact )
            while(stack[sp1].type=='BRACKET_HEAD')
                polish[++sp2]==stack[sp1--];
            sp1--;
        } else { //transact numbers & operators
            while(priority[i]<=priority[sp1])
                polish[++sp2]=stack[sp1--];
            stack[++sp1]=tokens[i];
        }
    }

    for(i=sp1;i>0;i--){
        polish[++sp2]=stack[i];
    }

    int i=0;
    while(!polish.empty()){
        polishizedtokens[i]=polish[i];
        ++i;
    }

    return polishizedtokens;

}

int main()
{

    return 0;
}
