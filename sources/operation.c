#include "../include/operation.h"
#include <stdio.h>

void formatNum(double *num){
	//取小数点后三位，实现四舍五入
	*num = (*num * 1000 + 0.5) / 1000.0; 
}
