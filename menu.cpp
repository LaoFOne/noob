#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <ctime>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

using namespace std;

// 颜色与样式（ANSI）
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string CYAN = "\033[36m";
const string MAGENTA = "\033[35m";
const string BOLD = "\033[1m";

void enableAnsiColorsOnWindows() {
#if defined(_WIN32) || defined(_WIN64)
    // 尝试启用 Windows 控制台的虚拟终端序列支持
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}

string separatorLine(char ch = '=', int width = 40) {
    return string(width, ch);
}

// 从一行读取并解析为 double，直到用户输入合法的数字为止
double readDouble(const string& prompt) {
    while (true) {
        cout << CYAN << prompt << RESET;
        string line;
        if (!std::getline(cin, line)) {
            // 遇到 EOF：重置流并继续或退出
            cin.clear();
            cout << endl;
            continue;
        }

        // 去除首尾空白
        size_t first = line.find_first_not_of(" \t\r\n");
        if (first == string::npos) {
            cout << YELLOW << "输入为空，请输入数字。" << RESET << endl;
            continue;
        }
        size_t last = line.find_last_not_of(" \t\r\n");
        string trimmed = line.substr(first, last - first + 1);

        // 使用 stringstream 尝试解析 double，确保整行都是数字（可带小数和负号）
        stringstream ss(trimmed);
        double value;
        if (ss >> value) {
            // 确保没有多余的非空字符
            char extra;
            if (ss >> extra) {
                cout << YELLOW << "包含多余字符，请只输入数字（例如 12.34 或 -5）。" << RESET << endl;
                continue;
            }
            return value;
        }
        else {
            cout << RED << "无效数字，请重试。" << RESET << endl;
            continue;
        }
    }
}

// 从一行读取并解析为 int 菜单选择
int readIntChoice(const string& prompt) {
    while (true) {
        cout << CYAN << prompt << RESET;
        string line;
        if (!std::getline(cin, line)) {
            cin.clear();
            cout << endl;
            continue;
        }
        // trim
        size_t first = line.find_first_not_of(" \t\r\n");
        if (first == string::npos) {
            cout << YELLOW << "输入为空，请输入数字选项。" << RESET << endl;
            continue;
        }
        size_t last = line.find_last_not_of(" \t\r\n");
        string trimmed = line.substr(first, last - first + 1);

        stringstream ss(trimmed);
        int value;
        if (ss >> value) {
            char extra;
            if (ss >> extra) {
                cout << YELLOW << "包含多余字符，请只输入整数选项。" << RESET << endl;
                continue;
            }
            return value;
        }
        else {
            cout << RED << "无效输入，请输入数字选项。" << RESET << endl;
        }
    }
}

void option1() {
    cout << GREEN << "执行 功能 1 的操作（占位）..." << RESET << endl;
    // TODO: 在此实现功能 1
}

void option2() {
    cout << GREEN << "执行 功能 2 的操作（占位）..." << RESET << endl;
    // TODO: 在此实现功能 2
}

void option3() {
    cout << GREEN << "执行 功能 3 的操作（占位）..." << RESET << endl;
    // TODO: 在此实现功能 3
}

// 新增：计算两数相加
void addTwoNumbers() {
    cout << MAGENTA << separatorLine('-', 40) << RESET << endl;
    cout << BOLD << "两数相加" << RESET << endl;
    double a = readDouble("请输入第一个数: ");
    double b = readDouble("请输入第二个数: ");
    double sum = a + b;
    cout << GREEN << "结果: " << a << " + " << b << " = " << sum << RESET << endl;
    cout << MAGENTA << separatorLine('-', 40) << RESET << endl;
}

// 演示用：显示当前时间（保留）
void showCurrentTime() {
    time_t t = time(nullptr);
    tm local_tm;
#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&local_tm, &t);
#else
    localtime_r(&t, &local_tm);
#endif
    char buf[64];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &local_tm);
    cout << GREEN << "当前时间: " << buf << RESET << endl;
}

int main() {
    enableAnsiColorsOnWindows();

    while (true) {
        cout << BOLD << separatorLine('=', 50) << RESET << endl;
        cout << BOLD << CYAN << "          欢迎使用 C++ 菜单程序" << RESET << endl;
        cout << BOLD << separatorLine('=', 50) << RESET << endl;

        cout << YELLOW << "1." << RESET << " 功能 1" << endl;
        cout << YELLOW << "2." << RESET << " 功能 2" << endl;
        cout << YELLOW << "3." << RESET << " 功能 3" << endl;
        cout << YELLOW << "4." << RESET << " 两数相加（新功能）" << endl;
        cout << YELLOW << "5." << RESET << " 显示当前时间" << endl;
        cout << YELLOW << "0." << RESET << " 退出" << endl;

        cout << endl;
        int choice = readIntChoice("请选择 (0-5): ");

        cout << endl;
        switch (choice) {
        case 1: option1(); break;
        case 2: option2(); break;
        case 3: option3(); break;
        case 4: addTwoNumbers(); break; // 新增处理
        case 5: showCurrentTime(); break;
        case 0:
            cout << GREEN << "再见！" << RESET << endl;
            return 0;
        default:
            cout << RED << "无效选择，请重试。" << RESET << endl;
        }

        cout << endl;
    }
    return 0;
}