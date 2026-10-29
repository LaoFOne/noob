#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <chrono>
#include <thread>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

using namespace std;

// ANSI 颜色与样式
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string CYAN = "\033[36m";
const string MAGENTA = "\033[35m";
const string BOLD = "\033[1m";
const string BLUE = "\033[34m";
const string WHITE = "\033[37m";

void enableAnsiColorsOnWindows() {
#if defined(_WIN32) || defined(_WIN64)
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}

void clearScreen() {
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}

string separatorLine(char ch = '=', int width = 40) {
    return string(width, ch);
}

string trim(const string& input) {
    size_t first = input.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    size_t last = input.find_last_not_of(" \t\r\n");
    return input.substr(first, last - first + 1);
}

bool parseDoubleString(const string& input, double& value) {
    stringstream ss(input);
    ss >> value;
    if (ss.fail()) return false;
    char extra;
    return !(ss >> extra);
}

bool parseIntString(const string& input, int& value) {
    stringstream ss(input);
    ss >> value;
    if (ss.fail()) return false;
    char extra;
    return !(ss >> extra);
}

void sleepMs(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}

void printCentered(const string& text, int width = 60) {
    int padding = max(0, (width - static_cast<int>(text.length())) / 2);
    cout << string(padding, ' ') << text << endl;
}

void printHeader(const string& title) {
    cout << BOLD << MAGENTA << separatorLine('=', 70) << RESET << endl;
    printCentered(title, 70);
    cout << BOLD << MAGENTA << separatorLine('=', 70) << RESET << endl;
}

void typeText(const string& text, int delay = 25) {
    for (char ch : text) {
        cout << ch;
        cout.flush();
        sleepMs(delay);
    }
    cout << endl;
}

void animateTitle() {
    const string title = "C++ 学习工具盒";
    for (int i = 0; i < 3; ++i) {
        clearScreen();
        cout << BOLD << CYAN;
        printCentered(separatorLine('-', 40), 70);
        printCentered(title, 70);
        printCentered(separatorLine('-', 40), 70);
        cout << RESET << endl;
        sleepMs(180);
        clearScreen();
        cout << BOLD << YELLOW;
        printCentered(separatorLine('-', 40), 70);
        printCentered(title, 70);
        printCentered(separatorLine('-', 40), 70);
        cout << RESET << endl;
        sleepMs(180);
    }
}

void showLoadingAnimation(const string& message) {
    cout << BOLD << CYAN << message << RESET;
    for (int i = 0; i < 4; ++i) {
        cout << ".";
        cout.flush();
        sleepMs(230);
    }
    cout << endl;
}

void showInfoPanel() {
    cout << BOLD << BLUE << "===============================================" << RESET << endl;
    cout << BOLD << WHITE << "  欢迎使用 C++ 学习与工具程序" << RESET << endl;
    cout << BOLD << BLUE << "  学习 • 计算 • 娱乐 • 实用功能" << RESET << endl;
    cout << BOLD << BLUE << "===============================================" << RESET << endl;
}

double readDouble(const string& prompt) {
    while (true) {
        cout << CYAN << prompt << RESET;
        string line;
        if (!getline(cin, line)) {
            cin.clear();
            cout << endl;
            continue;
        }

        string trimmed = trim(line);
        if (trimmed.empty()) {
            cout << YELLOW << "输入为空，请输入数字。" << RESET << endl;
            continue;
        }

        double value = 0.0;
        if (parseDoubleString(trimmed, value)) {
            return value;
        }

        cout << RED << "无效数字，请重试。" << RESET << endl;
    }
}

int readIntChoice(const string& prompt, int minValue, int maxValue) {
    while (true) {
        cout << CYAN << prompt << RESET;
        string line;
        if (!getline(cin, line)) {
            cin.clear();
            cout << endl;
            continue;
        }

        string trimmed = trim(line);
        if (trimmed.empty()) {
            cout << YELLOW << "输入为空，请输入整数选项。" << RESET << endl;
            continue;
        }

        int value = 0;
        if (parseIntString(trimmed, value) && value >= minValue && value <= maxValue) {
            return value;
        }

        cout << RED << "无效输入，请输入 " << minValue << " 到 " << maxValue << " 之间的整数。" << RESET << endl;
    }
}

void addTwoNumbers() {
    printHeader("两数相加");
    double a = readDouble("请输入第一个数: ");
    double b = readDouble("请输入第二个数: ");
    double sum = a + b;
    cout << GREEN << "结果: " << a << " + " << b << " = " << sum << RESET << endl;
    cout << MAGENTA << separatorLine('-', 40) << RESET << endl;
}

void calculator() {
    printHeader("简单计算器");
    cout << YELLOW << "支持运算：+  -  *  /  %" << RESET << endl;

    while (true) {
        double a = readDouble("请输入第一个数: ");

        string opInput;
        char op = '?';
        while (true) {
            cout << CYAN << "请选择运算符 (+, -, *, /, %): " << RESET;
            if (!getline(cin, opInput)) {
                cin.clear();
                cout << endl;
                continue;
            }
            opInput = trim(opInput);
            if (opInput.size() == 1 && (opInput[0] == '+' || opInput[0] == '-' || opInput[0] == '*' || opInput[0] == '/' || opInput[0] == '%')) {
                op = opInput[0];
                break;
            }
            cout << RED << "运算符无效，请重新输入。" << RESET << endl;
        }

        double b = readDouble("请输入第二个数: ");
        double result = 0.0;

        if (op == '+') {
            result = a + b;
        } else if (op == '-') {
            result = a - b;
        } else if (op == '*') {
            result = a * b;
        } else if (op == '/') {
            if (fabs(b) < 1e-12) {
                cout << RED << "除数不能为 0。" << RESET << endl;
                continue;
            }
            result = a / b;
        } else if (op == '%') {
            if (fabs(b) < 1e-12) {
                cout << RED << "模运算时除数不能为 0。" << RESET << endl;
                continue;
            }
            result = fmod(a, b);
        }

        cout << GREEN << "结果: " << a << " " << op << " " << b << " = " << result << RESET << endl;

        cout << YELLOW << "是否继续计算？ (Y/N): " << RESET;
        string again;
        getline(cin, again);
        again = trim(again);
        if (again.empty() || again[0] == 'n' || again[0] == 'N') {
            break;
        }
    }
}

void averageCalculator() {
    printHeader("平均值计算器");
    int count = readIntChoice("请输入要统计的数量 (1-100): ", 1, 100);

    double total = 0.0;
    for (int i = 1; i <= count; ++i) {
        double value = readDouble("请输入第 " + to_string(i) + " 个数: ");
        total += value;
    }

    double average = total / count;
    cout << GREEN << "总和: " << total << RESET << endl;
    cout << GREEN << "平均值: " << average << RESET << endl;
}

void bmiCalculator() {
    printHeader("BMI 健康计算器");
    double height = readDouble("请输入身高（米，例如 1.75）: ");
    double weight = readDouble("请输入体重（kg，例如 65）: ");

    if (height <= 0 || weight <= 0) {
        cout << RED << "身高和体重必须大于 0。" << RESET << endl;
        return;
    }

    double bmi = weight / (height * height);
    string category;

    if (bmi < 18.5) {
        category = "偏瘦";
    } else if (bmi < 24) {
        category = "正常";
    } else if (bmi < 28) {
        category = "超重";
    } else {
        category = "肥胖";
    }

    cout << GREEN << "BMI = " << bmi << RESET << endl;
    cout << YELLOW << "体型评估：" << category << RESET << endl;
}

void showCurrentTime() {
    printHeader("当前时间");
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

void guessNumberGame() {
    printHeader("数字猜谜游戏");
    srand(static_cast<unsigned int>(time(nullptr)));
    int target = rand() % 100 + 1;
    int attempts = 0;

    cout << YELLOW << "我已经想好了一个 1 到 100 之间的数字，开始猜吧！" << RESET << endl;

    while (true) {
        int guess = readIntChoice("请输入你的猜测 (1-100): ", 1, 100);
        attempts++;

        if (guess < target) {
            cout << RED << "偏小，继续努力！" << RESET << endl;
        } else if (guess > target) {
            cout << RED << "偏大，继续调整！" << RESET << endl;
        } else {
            cout << GREEN << "恭喜你，猜对了！答案是 " << target << "，你一共用了 " << attempts << " 次。" << RESET << endl;
            break;
        }
    }
}

void multiplicationTable() {
    printHeader("乘法表");
    int maxNumber = readIntChoice("请输入乘法表最大值 (1-12): ", 1, 12);

    for (int i = 1; i <= maxNumber; ++i) {
        cout << YELLOW;
        for (int j = 1; j <= 9; ++j) {
            cout << i << " * " << j << " = " << i * j << "\t";
        }
        cout << RESET << endl;
    }
}

void showMainMenu() {
    clearScreen();
    showInfoPanel();

    cout << BOLD << BLUE << "┌" << separatorLine('─', 52) << "┐" << RESET << endl;
    cout << BOLD << BLUE << "│" << RESET << BOLD << CYAN << "  1.  简单计算器            " << RESET << BOLD << BLUE << "│" << RESET << endl;
    cout << BOLD << BLUE << "│" << RESET << BOLD << CYAN << "  2.  平均值计算器          " << RESET << BOLD << BLUE << "│" << RESET << endl;
    cout << BOLD << BLUE << "│" << RESET << BOLD << CYAN << "  3.  BMI 健康计算器        " << RESET << BOLD << BLUE << "│" << RESET << endl;
    cout << BOLD << BLUE << "│" << RESET << BOLD << CYAN << "  4.  两数相加              " << RESET << BOLD << BLUE << "│" << RESET << endl;
    cout << BOLD << BLUE << "│" << RESET << BOLD << CYAN << "  5.  显示当前时间          " << RESET << BOLD << BLUE << "│" << RESET << endl;
    cout << BOLD << BLUE << "│" << RESET << BOLD << CYAN << "  6.  数字猜谜游戏          " << RESET << BOLD << BLUE << "│" << RESET << endl;
    cout << BOLD << BLUE << "│" << RESET << BOLD << CYAN << "  7.  乘法表                " << RESET << BOLD << BLUE << "│" << RESET << endl;
    cout << BOLD << BLUE << "│" << RESET << BOLD << MAGENTA << "  8.  退出系统              " << RESET << BOLD << BLUE << "│" << RESET << endl;
    cout << BOLD << BLUE << "└" << separatorLine('─', 52) << "┘" << RESET << endl;
    cout << endl;
}

void waitForContinue() {
    cout << YELLOW << "按回车键继续..." << RESET;
    string temp;
    getline(cin, temp);
}

int main() {
    enableAnsiColorsOnWindows();
    animateTitle();

    while (true) {
        showMainMenu();
        int choice = readIntChoice("请选择 (1-8): ", 1, 8);

        cout << endl;
        switch (choice) {
        case 1:
            showLoadingAnimation("正在启动计算器");
            calculator();
            break;
        case 2:
            showLoadingAnimation("正在启动平均值计算器");
            averageCalculator();
            break;
        case 3:
            showLoadingAnimation("正在启动 BMI 计算器");
            bmiCalculator();
            break;
        case 4:
            showLoadingAnimation("正在启动两数相加功能");
            addTwoNumbers();
            break;
        case 5:
            showLoadingAnimation("正在获取当前时间");
            showCurrentTime();
            break;
        case 6:
            showLoadingAnimation("正在启动数字猜谜游戏");
            guessNumberGame();
            break;
        case 7:
            showLoadingAnimation("正在生成乘法表");
            multiplicationTable();
            break;
        case 8:
            cout << BOLD << GREEN << "再见！感谢使用本程序。" << RESET << endl;
            return 0;
        default:
            cout << RED << "无效选择，请重试。" << RESET << endl;
        }

        cout << endl;
        waitForContinue();
    }

    return 0;
}
