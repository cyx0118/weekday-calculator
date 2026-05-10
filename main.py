def get_weekday(year, month, day):
    """使用纯算法计算指定日期是星期几（蔡勒公式变体）"""
    # 验证日期有效性
    if not is_valid_date(year, month, day):
        return None

    # 一月和二月当作上一年的13、14月
    if month <= 2:
        month += 12
        year -= 1

    # 基姆拉尔森计算公式
    # 0=星期一, 1=星期二, ..., 6=星期日
    w = (day + 2 * month + 3 * (month + 1) // 5 + year + year // 4 - year // 100 + year // 400) % 7

    weekdays = ["星期一", "星期二", "星期三", "星期四", "星期五", "星期六", "星期日"]
    return weekdays[w]


def is_valid_date(year, month, day):
    """纯算法验证日期是否有效（不调用任何库）"""
    if year < 1:
        return False
    if month < 1 or month > 12:
        return False

    # 计算每月天数
    days_in_month = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

    # 闰年判断：能被4整除但不能被100整除，或者能被400整除
    if is_leap_year(year):
        days_in_month[1] = 29

    if day < 1 or day > days_in_month[month - 1]:
        return False

    return True


def is_leap_year(year):
    """纯算法判断是否为闰年"""
    return (year % 4 == 0 and year % 100 != 0) or (year % 400 == 0)


def main():
    print("=" * 30)
    print("   日期星期计算器")
    print("=" * 30)

    while True:
        try:
            date_str = input("\n请输入日期（格式：YYYY-MM-DD，输入 q 退出）：")

            if date_str.lower() == "q":
                print("程序已退出。")
                break

            # 手动解析日期，不用任何库
            parts = date_str.split("-")
            if len(parts) != 3:
                print("格式错误，请使用 YYYY-MM-DD 格式")
                continue

            year = str_to_int(parts[0])
            month = str_to_int(parts[1])
            day = str_to_int(parts[2])

            if year is 无 或 month is 无 or day is None:
                print("输入无效，请输入正确的数字日期")
                continue

            result = get_weekday(year, month, day)

            if result is 无:
                print("日期无效，请输入正确的日期")
            else:
                print(f"\n{year}年{month}月{day}日 是 {result}")

        except KeyboardInterrupt:
            print("\n程序已退出。")
            break


def str_to_int():
    """手动将字符串转换为整数，不调用任何库"""
     = .strip()
    if not :
        return None
    negative = False
    start = 0
    if [0] == "-":
        negative = True
        start = 1
    elif [0] == "+":
        start = 1

    result = 0
    for i in range(start, len()):
        if [i] < "0" or [i] > "9":
            return None
        result = result * 10 + (ord([i]) - ord("0"))

    if negative:
        result = -result
    return result


if __name__ == "__main__":
    main()
