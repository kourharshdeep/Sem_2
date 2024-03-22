//Wap for infix operator.
#include<stdio.h>
int top1=-1, top2=-1; //top1 for opearnd stack and top2 for operator stack.
char operator[100]; // for operators.
int operand[100]; // for operands
void Process() {
    int x= operand[top1--];
    int y=operand[top1--];
    char op= operator[top2--];
    int z;
    switch(op){
        case '+':
        z=x+y;
        break;
        case '-':
        z=y-x;
        break;
        case '*':
        z=x*y;
        break;
        case '/':
        z=y/x;
        break;
    }
    operand[++top1]=z;
}
int Precedence(char op) { //for precedence choice. the operator with higher precedence had given higher number.
    switch(op) {
        case '+':
        case '-':
        return 1;
        case '*':
        case '/' :
        return 2;
        default:
        return 0;
    }
}
int evalInfixExpression(char *str) {
    int i;
    for(i=0;str[i]!='\0';i++) {
        char ch= str[i];
        if(ch>=48&&ch<=57) // ascii values for digits 0 to 9. 0-->48 and 9-->57.
        operand[++top1]= ch-48; //conversion of ascii values to digits,
        else if(ch=='+'|| ch=='-' || ch=='*' || ch=='/') {    // for operator stack
        if(top2==-1)
           operator[++top2]=ch;
        else {
            while(top2!=-1 && Precedence(ch)<=Precedence(operator[top2])) {
                Process();
            }
            operator[++top2]=ch;
        }
        }
        else if(ch=='(') {
            operator[++top2]= ch;
        }
        else if(ch==')') {
            while(operator[top2]!='(') {
                Process();
            }
            top2--;
        }
    }
    while(top2!=-1) {
        Process();
    }
    return operand[top1--];
}

int main() {
    int result= evalInfixExpression("3+(2*5)/(4-2)");
    printf("%d",result);
    return 0;
}
