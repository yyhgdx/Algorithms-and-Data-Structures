#include "../../complex/Complex2.h"
#include "../../vector/vector.h"
#include "../../stack/stack.h"
//#include "../../calcu.h"
#include <string.h> 
#include <cmath>
using namespace std;
Operator optr2rank(char op){//由运算符转译出编号
    switch(op){
        case '+': return ADD;//加
        case '-': return SUB;//减
        case '*': return MUL;//乘
        case '/': return DIV;//除
        case '^': return POW;//乘方
        case '!': return FAC;//阶乘
        case '(': return L_P;//左括号
        case ')': return R_P;//右括号
        case '\0':return EOE;//起始符和终止符
        case 's':{
		     
			break;
		}
        default : exit(-1);//未知运算符
    }
}

char orderBetween(char op1,char op2){
    return pri[optr2rank(op1)][optr2rank(op2)];
}
float calcu(char op ,float pOpnd1){
	float out=1;
	if (pOpnd1> 1){
	    while(pOpnd1 - 1 > 0 ){
		    out = out * pOpnd1;
			pOpnd1--;
        }return out;
    }
    else if( pOpnd1 == 0|| pOpnd1==1) return pOpnd1;
    else  return 0;  cout<<"error"<<endl;
}
float calcu(float pOpnd1, char op, float pOpnd2 ){
	switch(op){
		case '+': return  pOpnd1+pOpnd2;break;
		case '-': return  pOpnd1-pOpnd2;break;
		case '*': return  pOpnd1*pOpnd2;break;
		case '/': return  pOpnd1/pOpnd2;break;
		case '^': return  pow(pOpnd1,pOpnd2);break;
	}
}

//void readNumber(char*&s, Stack<float>& opnd) {
//	float sum = 0.0;
//	int i = 0;
//	int pos = 0;
//	while( *s>= 48 && *s<= 57 || *s=='.')
//		for (i = 0; i < strlen(s); i++) {
//			if (*s == '.') { pos = i;  continue; }
//			else sum = sum * 10 + (*s - 48);
//			s++;
//		}
//	if (pos)sum = sum / ((strlen(s) - pos - 1)*10);
//	opnd.push(sum);
//}
void readNumber(char *& p,Stack<float>& stk){//将起始于p的子串解析为数值，并存入操作数栈
    stk.push((float)(*p - '0'));//当前数位对应的数值入栈
    while(isdigit(*(++p)))//只要后续还有紧邻的数字(即多位整数的情况)，则
        stk.push(stk.pop()*10+(*p-'0'));//弹出原操作数并追加新数位后，新数值直接入栈
    if('.'!=(*p)) return ;//此后非小数点意味当前操作数解析完成
    double fraction=1;//否则意味还有小数部分
    while(isdigit(*(++p)))//逐位加入
    stk.push(stk.pop()+(*p-'0')*(fraction/=10));//小数部分
}
void append(char*& RPN, char top){
	*RPN = top;
	RPN++;
}
float evaluate ( char* S, char*& RPN ){
	Stack<float> opnd; Stack<char> optr;
	optr.push ('\0');
	while ( !optr.empty() ){
		if( isdigit( *S)) {
			readNumber ( S, opnd); append ( RPN,opnd.top()); 
		}else
		switch ( orderBetween ( optr.top(),*S ) ){
			case '<':
				optr.push( *S ); S++;
				break;
			case '=':
				optr.pop(); S++;
				break;
			case '>': {
				char op = optr.pop(); append ( RPN, op );
				if( '!' == op ) {
					float pOpnd = opnd.pop();
					opnd.push(calcu( op, pOpnd) );
				}else{
					float pOpnd2= opnd.pop(),pOpnd1 = opnd.pop();
					opnd.push(calcu ( pOpnd1, op, pOpnd2 )); 
				}
				break;
			}
		default : exit (-1);
		}
	}
}
int main(){
	char rpn[100];
	char* RPN =&rpn[0];
	char S1[] = "2.3+3.5"; cout << "2.3+3.5=" << evaluate(S1,RPN) << endl;
	char S2[] = "7.3-3.5"; cout << "7.3-3.5=" << evaluate(S2,RPN) << endl;
	char S3[] = "2*6"; cout << "2*6=" << evaluate(S3,RPN) << endl;
	char S4[] = "8/2"; cout << "8/2=" << evaluate(S4,RPN) << endl;
	char S5[] = "(2+3)+2^3+3!"; cout << "(2+3)+2^3+3!=" << evaluate(S5,RPN) << endl;
	return 0; 
    
}
