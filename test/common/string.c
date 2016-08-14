/**
 * 字符串的功能的测试
 */
#include <stdio.h>
#include <string.h>
int main() {
    /** 字符串按照地址获取内容 */
    // char *sin;
    // char str[] = "http://www.baidu.com";
    // sin = str;
    // sin++;
    // printf("%c\n", *sin);
    /** 字符串按照下标赋值 */
    // char str[10] = {};
    // str[0] = 'a';
    // str[1] = 'b';
    // printf("%s\n", str);
    /** 初始化赋值, 这种赋值输出为空，为啥呢，因为第一个下标就赋值为结束符0了，后面的再赋值也没用了 */
    char str1[20];
    str1[0] = 0;
    str1[1] = 'a';
    str1[2] = 0;
    str1[19] = '\0';
    printf("%ld\n", sizeof(str1));
    printf("%s\n", str1);
    return 0;
}