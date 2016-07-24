/**
 * circle源文件，实现函数的定义
 */
#include "circle.h"
/**
 * 计算圆的周长
 */
double Circumference(int radius) {
    return 2 * PI * radius;
}
/**
 * 计算圆的面积
 */
double Area(int radius) {
    return PI * radius * radius;
}