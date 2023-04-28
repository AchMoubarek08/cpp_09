#include <iostream>
#include <stack>
#include <string>
#include <cstdlib>

int is_operator(char ex)
{
    if (ex == '+' || ex == '-'|| ex == '*' || ex == '/')
        return (1);
    return (0);
    
}
int is_valid_rpn(std::string exp)
{
    int count = 0;
    for(size_t i = 0; i < exp.length(); i++)
    {
        if (isblank(exp[i]))
            continue ;
        if (isdigit(exp[i]))
        {
            count++;
            continue ;
        }
        if (is_operator(exp[i]))
        {
            if (count < 2)
                return (0);
            count--;
        }
        else
            return (0);
    }
    if (count == 1)
        return (1);
    return (0);
}

void    check_args(std::string expr)
{
    if (!is_valid_rpn(expr))
    {
        std::cerr << "Error : invalid rpn" << std::endl;
        exit(1);
    }
    for(size_t i = 0; i < expr.length(); i++)
    {
        if (!isdigit(expr[i]) && !is_operator(expr[i]) && !isblank(expr[i]))
        {
            std::cerr << "Error : Bad args" << std::endl;
            exit(1);
        }
    }
}
int calcul_rpn(std::string exp)
{
    std::stack<int> stack;
    int num1, num2;
    for (size_t i = 0; i < exp.length(); i++) {
        if (isdigit(exp[i]))
        {
            stack.push(exp[i] - '0');
        }
        else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/') 
        {
            num2 = stack.top();
            stack.pop();
            num1 = stack.top();
            stack.pop();

            switch (exp[i])
            {
                case '+':
                {
                    stack.push(num1 + num2);
                    break;
                }
                case '-':
                {
                    stack.push(num1 - num2);
                    break;
                }
                case '*':
                {
                    stack.push(num1 * num2);
                    break;
                }
                case '/':
                {
                    stack.push(num1 / num2);
                    break; 
                }
            }
        }
    }
    return stack.top();
}
int main(int ac, char **av) 
{
    if (ac != 2)
    {
        std::cerr << "Usage: " << av[0] << " <inverted Polish mathematical exp>" << std::endl;
        return (1);
    }
    std::string rpn = av[1];
    check_args(rpn);
    int result = calcul_rpn(rpn);
    std::cout << result << std::endl;
    return 0;
}