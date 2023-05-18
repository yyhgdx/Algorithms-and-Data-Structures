#include <iostream>
#include <string>
#include <string.h>
#include "../../complex/Complex2.h"
#include "../../stack/stack.h"
#include <cmath>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
Complex evaluter(char *s);

int change(char c) {
	switch (c)
	{
	case '+':return ADD; 
	case '-':return SUB; 
	case '*':return MUI; 
	case '/':return DIV; 
	case '^':return POW;
	case '!':return FAC; 
	case '(':return L_P;
	case ')':return R_P; 
	case '\0':return EOE;
	case 'i':return COM;
	case 's':return SIN;
	case 't':return TAN;
	case 'C':return COS;
	}
}

Complex readNumber(char* &S, Stack<Complex> &opnd) {
	Complex X;
	float x = 0.0;
	bool point=false;//判断是否为小数
	int i = 0;//计小数点后的位数
	while (isdigit(*S)||*S=='.') {
		if (*S != '.') {
			if (point == false) 	x = x * 10 + (*(S++) - 48);//减去48,ASCII转成数字
			if (point == true) { x = x * 10 + (*(S++) - 48); i++; }
		}
		else { S++; point = true; }
	}
	int temp = 1;
	for (int j = 0; j < i; j++) temp *= 10;
	x = x / temp;
	X.read_Real(double(x));
	opnd.push(X);//压入操作数栈
	return X;
}
Complex fac(Complex n, int &flag) {
    float f = 1;	
    if ( n.imag() == 0)
	    if( n.real() >= 1){
		    while (n.real() - 1 >= 1){
	    	    f = f*n.real();
	    	    n.read_Real( n.real() - 1); 
		    }
		    n.read_Real(f);
		    return n;
		}
		else   {  n.read_Real(f);flag = 1; return n;}
    else {flag = 1;return n;}		
}
Complex calcu(char optr, Complex opnd,int &flag) {
	double a;
	if (optr == '!') return fac(opnd,flag);
	else { a=opnd.imag()*-1; opnd.read_Imaginary(opnd.real())  ;opnd.read_Real(a * -1); return opnd;} 
}
Complex calcu(Complex opnd,char optr){
	if (optr = 's'){
	    double a,b;
		a=opnd.imag(); b=opnd.real();
		opnd.read_Real(0.5*sin(b)*(pow(2.718281828459045,a)+pow(2.718281828459045,-a))); 
		opnd.read_Imaginary(0.5*cos(b)*(pow(2.718281828459045,a)-pow(2.718281828459045,-a)));
		return opnd;
	}
	else if (optr = 'c'){
	    double a,b;
	    b=opnd.imag(); a=opnd.real();
	    opnd.read_Real(0.5*cos(a)*(pow(2.718281828459045,b)+pow(2.718281828459045,-b)));
	    opnd.read_Imaginary(0.5*cos(a)*(pow(2.718281828459045,b)-pow(2.718281828459045,-b)));
	    return opnd;
	}
	else return((calcu(opnd,'s')/calcu(opnd,'c')));
}

Complex calcu(Complex opnd1, char op, Complex opnd2,int &flag) {
	Complex result;
	switch (op) //判断运算符
	{
	case '+': {result = opnd1 + opnd2; return result; }
	case '-': {result = opnd1 - opnd2; return result; }
	case '*': {result = opnd1 * opnd2; return result; }
	case '/': {result = opnd1 / opnd2; return result; }
	case '^': { if(opnd1.imag()!=0 or opnd2.imag()!=0 )
	                {cout<<"暂无此项功能";exit(-1);}
	            else return(pow(opnd1.real(),opnd2.real())); 
	}
	}//switch
}
char orderBetween(char c1, char c2) {
	return pri[change(c1)][change(c2)];
}

Complex evaluter(char *s)
{
	int flag = 0;
    Stack<Complex> opnd;//运算数栈
    Stack<char> optr;//运算符栈
    optr.push('\0');//先将尾哨兵推入栈中
    while(!optr.empty()&&flag == 0){
        if(isdigit(*s)){ //若为操作数，存在读入连续数字的情况
            readNumber(s,opnd); //则读入操作数 
            //append(RPN,opnd.top());
        }else
        if (*s == 's'&& *(s+1) == 'i'&& *(s+2) == 'n') { s++;s++; *s = 's';}
        if (*s == 't'&& *(s+1) == 'a'&& *(s+2) == 'n') { s++;s++; *s = 't';}
        if (*s == 'c'&& *(s+1) == 'o'&& *(s+2) == 's') { s++;s++; *s = 'c';}
        switch(orderBetween(optr.top(),*s)){//分别处理 
            case '<'://栈顶运算符优先级低 
                optr.push(*s);s++;break;
            case '='://优先级相等（当前运算符为右括号或者是尾哨兵） 
                optr.pop();s++;break;//脱括号，接收下一个字符
            case '>':{//运算时机到了 
                char op = optr.top(); optr.pop();
			if ('!' == op||'i'== op) {
				Complex pOpnd = opnd.top(); opnd.pop();
				opnd.push(calcu(op, pOpnd,flag));//实施一元运算
			}
			else if ('s'== op || 't' == op || 'c' == op){
				Complex pOpnd = opnd.top(); opnd.pop();
				opnd.push(calcu(pOpnd,op));
			}
			else {
				Complex pOpnd2 = opnd.top(); opnd.pop();
				Complex pOpnd1 = opnd.top(); opnd.pop();
				opnd.push(calcu(pOpnd1, op, pOpnd2,flag));//实施二元运算
			}
			break;
            }
            default: cout<<"请合理使用计算机";exit(-1);
        }
    }

    if (flag == 0)    return opnd.pop();
    else { cout<<"请合理使用计算机";exit(-1);}
}

int main(int argc, char** argv) {
	char S1[] = "tan(4+6i)"; cout << "tan(4+6i)=" ; evaluter(S1).display(); cout<<endl;
	char S6[] = "tan(3.1415926/2)"; cout << "tan(3.1415926/2)=" ; evaluter(S6).display(); cout<<endl;
	char S2[] = "7.3-3.5"; cout << "7.3-3.5=" ;evaluter(S2).display() ;
	char S3[] = "2*6i"; cout << "2*6i=" ;evaluter(S3).display() ;
	char S4[] = "8/2!"; cout << "8/2=" ;evaluter(S4).display() ;
	char S5[] = "(2+3)+3!*6!i"; cout << "(2+3)+3!*6!i=" ;evaluter(S5).display();
	cout<<endl;
	cout<<"如果输入公式正确，才能正常运行。该廉价计算机有一点点小小的bug" ;


}
