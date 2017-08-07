#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<stack>
#include <sstream> 
#include <utility> 
using namespace std;

class Expression_Capacity
{
public:
	Expression_Capacity(string str);
	bool test();         // �ⲿ�ӿڣ��жϱ��ʽ�Ƿ�Ϸ�  
	double calculate();  // �ⲿ�ӿڣ�������ʽ��ֵ   
private:
	vector<pair<string, int>> word;
	int word_analysis(vector<pair<string, int>>& vec, const string str);
	string str;//�������ʽ
	int index;//λ��
	int err;  //�жϴ���
	int syn;  //�����ձ����
	void T();
	void F();
	void E();
	void Next();
	bool Right;//����text���
private:
	int prior(int syn);//�ж���������ȼ�
	bool isOperator(int syn);// �ж��Ƿ�������� 
	double stringToDouble(const string& str);//�ַ���ת��������
	void popTwoNumbers(stack<double>& s, double& first, double& second); //��ջ������ȡ��������
	vector<pair<string, int>> getPostfix(const vector<pair<string, int>>& vec); //����׺���ʽת��׺���ʽ
	double expCalculate(const vector<pair<string, int>>& vec); //�����׺���ʽ���
};
