#pragma once
#include<iostream>
using namespace std;
void memory()
{
	/*
		sizeof ����������������ڴ�Ĵ�С�����������Ԫ���޹�
		ch1���ڴ��С�� 6�ֽ�,5���ַ���һ����������\0����֧���Ŵ��ĳ�����5
		ch2�������ָ��Ĵ�С��ָ���СΪ 4�ֽڣ�ָ����ַ�������Ϊ5
		ch3���ڴ��С�� 10�ֽڣ��ַ�������Ϊ5
	*/
	char ch1[] = "abcde";
	const char *ch2 = "abcde";
	char ch3[10] = "abcde";
	cout << sizeof(ch1) << " " << strlen(ch1) << endl;
	cout << sizeof(ch2) << " " << strlen(ch2) << endl;
	cout << sizeof(ch3) << " " << strlen(ch3) << endl;
	/*
		�����
		6 5
		4 5
		10 5
	*/
}

