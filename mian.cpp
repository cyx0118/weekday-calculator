#include <iostream>
#include <cstring>
using namespace std;

// 判断是否为闰年
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 验证日期是否有效
bool isValidDate(int year, int month, int day) {
    if (year < 1) return false;
    if (month < 1 || month > 12) return false;

    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (isLeapYear(year)) {
        daysInMonth[1] = 29;
    }

    if (day < 1 || day > daysInMonth[month - 1]) return false;

    return true;
}

// 使用基姆拉尔森公式计算星期几，返回 0=星期一 ... 6=星期日
int calcWeekday(int year, int month, int day) {
    // 一月和二月当作上一年的13、14月
    if (month <= 2) {
        month += 12;
        year -= 1;
    }

    int w = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7;
    return w;
}

// 手动将字符串转为整数，失败返回 false
bool strToInt(const char* s, int &result) {
    result = 0;
    int i = 0;
    bool negative = false;

    if ([0] == '\0') return false;

    if ([0] == '-') {
        negative = true;
        i = 1;
    } else if ([0] == '+') {
        i = 1;
    }

    if ([i] == '\0') return false;

    while ([i] != '\0') {
        if ([i] < '0' || s[i] > '9') return false;
        result = result * 10 + ([i] - '0');
        i++;
    }

    if (negative) result = -result;
    return true;
}

int main() {
    const char* weekdays[] = {"星期一", "星期二", "星期三", "星期四", "星期五", "星期六", "星期日"};
    char input[100];

    cout << "==============================" << endl;
    cout << "     日期星期计算器" << endl;
    cout << "==============================" << endl;

    while (true) {
        cout << "\n请输入日期（格式：YYYY-MM-DD，输入 q 退出）：";
        cin >> input;

        if (input[0] == 'q' || input[0] == 'Q') {
            cout << "程序已退出。" << endl;
            break;
        }

        // 手动解析日期
        char part1[20] = {0}, part2[20] = {0}, part3[20] = {0};
        int dashCount = 0;
        int idx1 = 0, idx2 = 0, idx3 = 0;

        for (int i = 0; input[i] != '\0'; i++) {
            if (input[i] == '-') {
                dashCount++;
            } else {
                if (dashCount == 0) {
                    if (idx1 < 19) part1[idx1++] = input[i];
                } else if (dashCount == 1) {
                    if (idx2 < 19) part2[idx2++] = input[i];
                } else if (dashCount == 2) {
                    if (idx3 < 19) part3[idx3++] = input[i];
                }
            }
        }

        if (dashCount != 2) {
            cout << "格式错误，请使用 YYYY-MM-DD 格式" << endl;
            continue;
        }

        int year, month, day;
        if (!strToInt(part1, year) || !strToInt(part2, month) || !strToInt(part3, day)) {
            cout << "输入无效，请输入正确的数字日期" << endl;
            continue;
        }

        if (!isValidDate(year, month, day)) {
            cout << "日期无效，请输入正确的日期" << endl;
            continue;
        }

        int w = calcWeekday(year, month, day);
        cout << "\n" << year << "年" << month << "月" << day << "日 是 " << weekdays[w] << endl;
    }

    return 0;
}
