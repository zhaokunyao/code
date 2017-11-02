#include<stdio.h>
#include<stdlib.h>
// 树节点中保存的最大字符长度
#define NODE_DATA_LENGTH  20

// 定义树的node
typedef struct tree
{
    // 字符（如 34， +等等）
    char data[NODE_DATA_LENGTH];
    // 左子树
    struct tree *left;
    // 右子树
    struct tree *right;
    // 算术表达式的结果
    double result;
} * node;

// 创建一个新的node 并返回指针
node newnode(char *b)
{
    node temp;
    temp=(struct tree*)malloc(sizeof(struct tree));
    sprintf(temp->data, "%s", b);
    temp->left=NULL;
    temp->right=NULL;
    temp->result = atof(b);
    return temp;
}

// 中序遍历
void inorder(node t)
{
    if(t!=NULL)
    {
        inorder(t->left);
        printf("%s, ",t->data);
        inorder(t->right);
    }
}

// 前序遍历
void preorder(node t)
{
    if(t ==NULL){ 
        return;
    }

    printf("%s, ", t->data);
    preorder(t->left);
    preorder(t->right);
}

// 后序遍历
void postorder(node t)
{
    if(t!=NULL)
    {
        postorder(t->left);
        postorder(t->right);
        printf("%s, ",t->data);
    }
}

// 打印树的结构
// 逆时针翻转了90度
void print_tree(node t, int level)
{
    if(t!=NULL)
    {
        print_tree(t->right, level+1);
        int i;
        for (i =0 ; i < level*10 ; i++) {
            printf(" ");
        }
        printf("%s\n", t->data);
        print_tree(t->left, level+1);
    }
}

// 创建树并返回根节点
node make_tree(char * str) {
    // 栈1：用来保存node
    node stack[300];
    // 栈2：用来保存 + - * /
    node stack_operator[300];
    // 栈1的头部
    int top=-1;
    // 栈2的头部
    int top_operator= -1;

    int i;
    int j = 0;
    node tmp;
    node a;
    node b;
    // 遍历字符串
    for(i=0; str[i]!= '\n'; i++)
    {
        switch (str[i])
        {
        case ' ': 
            // 空格不处理
            break;
        case '+':
        case '-':
        case '*':
        case '/':
            // 创建新的node并保存到栈2中
            j = 0;
            char data[NODE_DATA_LENGTH];
            data[0] = str[i];
            data[1] = '\0';
            // 如果栈2是空的， 入栈2 
            if (top_operator == -1){
                tmp = newnode(data);
                stack_operator[++top_operator]=tmp;
                continue;
            }

            // 读取栈2的头部
            tmp =  stack_operator[top_operator];
            // 如果是  -  且当前操作符是 +
            if (tmp->data[0] == '-'  && data[0] == '+') {
                tmp = stack_operator[top_operator--];
                a = stack[top--];
                b = stack[top--];
                tmp->left   = b;
                tmp->right  = a;
                tmp->result = b->result - a->result;
                // 然后把新的node保存到栈1中。
                stack[++top]=tmp;
            }
            // 操作符入栈2
            tmp = newnode(data);
            stack_operator[++top_operator]=tmp;
            break;

        case '(':
            // 如果是 (， 则一直往后面读到匹配的 ）
            // 可能会有 ( ( )) 嵌套的情况， 要读到最后一个匹配的 )
            // 并把这个字符串保存到 new_buff 中。
            j = 0;
            int kehao_count  = 1;
            char new_buff[1024];
            while (str[++i] != '\n' && kehao_count >0) {
                new_buff[j++] = str[i];
                if (str[i] == '(') {
                    kehao_count ++;
                    continue;
                }
                if (str[i] == ')') {
                    kehao_count --;
                    continue;
                }
            }
            new_buff[j-1] = '\n';
            new_buff[j] = '\0';
            // i多读了一位，还原
            i--;
            // 递归调用建树的方法
            node p_kehao = make_tree(new_buff);
            // 把新树的root节点保存到栈1
            stack[++top]=p_kehao;


            // 如果栈2是空的， 什么也不做
            if (top_operator == -1){
                continue;
            }

            // 读取栈2的头部
            tmp =  stack_operator[top_operator];
            // 如果是 + - 则什么也不做
            if (tmp->data[0] == '+' || tmp->data[0] == '-') {
                continue;
            }
            // 如果是* / 就取栈1头部的2个数字计算
            // 并把结果保存到新的node
            tmp = stack_operator[top_operator--];
            a = stack[top--];
            b = stack[top--];
            tmp->left   = b;
            tmp->right  = a;
            if (tmp->data[0] == '*') {
                tmp->result = b->result * a->result;
            } else {
                tmp->result = b->result / a->result;
            }
            // 然后把新的node保存到栈1中。
            stack[++top]=tmp;

            break;

        default:
            // 非 + - * / () 的字符
            j = 0;
            char d[100];
            // 一直往后面读数字, 比如34
            do
            {
                d[j++] = str[i];
                i++;
            } while (str[i] >= '0' && str[i] <= '9'); 
            d[j] = '\0'; 
            // i多读了一位，还原一下
            i--;
            // 创建新的node并保存到stack1中
            tmp = newnode(d);
            stack[++top]=tmp;

            // 如果栈2是空的， 什么也不做
            if (top_operator == -1){
                continue;
            }

            // 读取栈2的头部
            tmp =  stack_operator[top_operator];
            // 如果是 + - 则什么也不做
            if (tmp->data[0] == '+' || tmp->data[0] == '-') {
                continue;
            }
            // 如果是* / 就取栈1头部的2个数字计算
            // 并把结果保存到新的node
            tmp = stack_operator[top_operator--];
            a = stack[top--];
            b = stack[top--];
            tmp->left   = b;
            tmp->right  = a;
            if (tmp->data[0] == '*') {
                tmp->result = b->result * a->result;
            } else {
                tmp->result = b->result / a->result;
            }
            // 然后把新的node保存到栈1中。
            stack[++top]=tmp;
            break;
        }

    }

    while (top_operator != -1) {
        // 从栈2头部取出二个数字并计算结果
        // 之后保存到新的node并保存到栈1
        node tmp = stack_operator[top_operator--];
        node a = stack[top--];
        node b = stack[top--];
        tmp->left = b;
        tmp->right = a;
        if (tmp->data[0] == '+') {
            tmp->result = b->result + a->result;
        } else if (tmp->data[0] == '-') {
            tmp->result = b->result - a->result;
        } else if (tmp->data[0] == '*') {
            tmp->result = b->result * a->result;
        } else {
            tmp->result = b->result / a->result;
        }
        stack[++top]=tmp;
    }

    // 此时stack应该只有一个元素了，它就是树的root
    return stack[top--];
}

// main
int main()
{
    int size = 1024;
    char str[size];
    while (1) {
        printf("\nEnter the postfix expression: ");

        // 输入表达式
        fgets(str, size, stdin);

        double result = 0;

        // 建树并返回树的根节点
        node root = make_tree(str);

        // 表达式的结果就保存在根节点里面
        result = root->result;
        printf("result is %f\n", result);

        printf("preorder: \n");
        preorder(root);
        printf("\n");

        printf("postorder: \n");
        postorder(root);
        printf("\n");

        printf("inorder: \n");
        inorder(root);
        printf("\n");

        print_tree(root, 1);
    }
    return 0;
}
