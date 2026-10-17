#include <iostream>
using namespace std;

void func1()
{
    cout << "执行功能1：数据计算" << endl;
}

void func2()
{
    cout << "执行功能2：数据统计" << endl;
}

void func3()
{
    cout << "执行功能3：参数对比" << endl;
}

void showMenu()
{
    cout << "\n=====功能菜单=====" << endl;
    cout << "1. 数据计算" << endl;
    cout << "2. 数据统计" << endl;
    cout << "3. 参数对比" << endl;
    cout << "0. 退出程序" << endl;
    cout << "请输入选择：";
}

int main()
{
    int op;
    while (true)
    {
        showMenu();
        cin >> op;
        if (op == 0)
        {
            cout << "程序结束" << endl;
            break;
        }
        switch (op)
        {
        case 1: func1(); break;
        case 2: func2(); break;
        case 3: func3(); break;
        default: cout << "输入错误" << endl;
        }
    }
    return 0;
}
