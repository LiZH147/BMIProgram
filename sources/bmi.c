#include "../include/bmi.h"
#include "../include/operation.h"
#include <stdio.h>

double calculateBMI(double height, double weight)
{
	if (height <= 0 || weight <= 0)
	{
		return -1;
	}
	double BMI = weight / (height * height);
	return BMI;
}
void judgeBMI(double bmi, double a, double b, double c)
{
	if (bmi < a)
	{
		printf("BMI: %.3f，过轻。", bmi);
	}
	else if (bmi < b)
	{
		printf("BMI: %.3f，正常。", bmi);
	}
	else if (bmi < c)
	{
		printf("BMI: %.3f，过重。", bmi);
	}
	else
	{
		printf("BMI: %.3f，肥胖。", bmi);
	}
}
void printMessage(double bmi, int age, double height, double weight, int gender)
{
	formatNum(&bmi);

	if (age <= 18)
	{
		switch (gender)
		{
		case 1:
			// 男性年龄<=18
			judgeBMI(bmi, 17.5, 23.8, 26.8);
			break;
		case 2:
			// 女性年龄<=18
			judgeBMI(bmi, 16.9, 23.4, 26.3);
			break;
		default:
			break;
		}
	}
	else if (age >= 19 && age <= 34)
	{
		switch (gender)
		{
		case 1:
			// 男性年龄18~34
			judgeBMI(bmi, 18.5, 25, 30);
			break;
		case 2:
			// 女性年龄18~34
			judgeBMI(bmi, 18.5, 24, 29);
			break;
		default:
			break;
		}
	}
	else if (age >= 35 && age <= 44)
	{
		switch (gender)
		{
		case 1:
			// 男性年龄34~44
			judgeBMI(bmi, 22, 27, 31);
			break;
		case 2:
			// 女性年龄34~44
			judgeBMI(bmi, 19, 24, 29);
			break;
		default:
			break;
		}
	}
	else if (age >= 45 && age <= 54)
	{
		switch (gender)
		{
		case 1:
			// 男性年龄44~54
			judgeBMI(bmi, 23, 28, 33);
			break;
		case 2:
			// 女性年龄44~54
			judgeBMI(bmi, 20, 25, 30);
			break;
		default:
			break;
		}
	}
	else if (age >= 55 && age <= 64)
	{
		switch (gender)
		{
		case 1:
			// 男性年龄54~64
			judgeBMI(bmi, 24, 28, 34);
			break;
		case 2:
			// 女性年龄54~64
			judgeBMI(bmi, 21, 26, 31);
			break;
		default:
			break;
		}
	}
	else
	{
		switch (gender)
		{
		case 1:
			// 男性年龄>64
			judgeBMI(bmi, 25, 30, 32);
			break;
		case 2:
			// 女性年龄>64
			judgeBMI(bmi, 23, 28, 33);
			break;
		default:
			break;
		}
	}
}
