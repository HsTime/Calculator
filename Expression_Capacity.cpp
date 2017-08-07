#include "stdafx.h"
#include"Expression_Capacity.h"

//���캯��
Expression_Capacity::Expression_Capacity(string s)
:str(s)
, index(0)
, err(0)
, syn(0)
, Right(true)
{}
// �ⲿ�ӿڣ��жϱ��ʽ�Ƿ�Ϸ�  
bool Expression_Capacity::test()
{
	if (!word.empty())
	{
		return Right;
	}
	int err_num = word_analysis(word, str);
	if (err_num == -1)
	{
		Right = false;
	}
	else
	{
		// �ʷ���ȷ�������﷨����
		Next();
		E();
		if (syn == 0 && err == 0)  // ע��Ҫ�ж���������
			Right = true;
		else
			Right = false;
	}
	return Right;
}

double Expression_Capacity::calculate()// �ⲿ�ӿڣ�������ʽ��ֵ  
{
	if (test())
	{
		return expCalculate(getPostfix(word));
	}
	else
	{
		exit(0);
	}
}

//****************�ڲ�����**********//
int  Expression_Capacity::word_analysis(vector<pair<string, int>>& vec, const string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		//��+ - * / �� ��
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' ||
			str[i] == '/' || str[i] == '(' || str[i] == ')')
		{
			string tmp;
			tmp.push_back(str[i]);
			switch (str[i])
			{
			case '+':
				vec.push_back(make_pair(tmp, 1));
				break;
			case '-':
				vec.push_back(make_pair(tmp, 2));
				break;
			case '*':
				vec.push_back(make_pair(tmp, 3));
				break;
			case '/':
				vec.push_back(make_pair(tmp, 4));
				break;
			case '(':
				vec.push_back(make_pair(tmp, 6));
				break;
			case ')':
				vec.push_back(make_pair(tmp, 7));
				break;
			}
		}
		else if (str[i] >= '0' && str[i] <= '9')
		{
			string tmp;
			while (str[i] >= '0' && str[i] <= '9')
			{
				tmp.push_back(str[i]);
				i++;
			}
			if (str[i] == '.')
			{
				++i;
				if (str[i] >= '0' && str[i] <= '9')
				{
					tmp.push_back('.');
					while (str[i] >= '0' && str[i] <= '9')
					{
						tmp.push_back(str[i]);
						i++;
					}
				}
				else
				{
					return -1;
				}
			}
			vec.push_back(make_pair(tmp, 5));
			--i;
		}
		else
			return -1;
	}
	return 0;
}

void Expression_Capacity::T()  //T ->{ *F | /F}
{
	F();
	while (syn == 3 || syn == 4)
	{
		Next();
		F();
	}
}
void Expression_Capacity::F() // F -> { (E)|d }
{
	if (syn == 5)
	{
		Next();
	}
	else if (syn == 6)
	{
		Next();
		E();
		if (syn == 7)
		{
			Next();
		}
		else
		{
			err = -1;
		}
	}
	else
	{
		err = -1;
	}
}
void Expression_Capacity::E() //E ->{ +F | - F}
{
	T();
	while (syn == 1 || syn == 2)
	{
		Next();
		T();
	}
}

void Expression_Capacity::Next()
{
	if (index < word.size())
		syn = word[index++].second;
	else
		syn = 0;
}

int Expression_Capacity::prior(int syn)//�ж���������ȼ�
{
	switch (syn)
	{
	case 1:
	case 2:
		return 1;
	case 3:
	case 4:
		return 2;
	default:
		return 0;
	}
}

bool Expression_Capacity::isOperator(int syn)// �ж��Ƿ�������� 
{
	switch (syn)
	{
	case 1:
	case 2:
	case 3:
	case 4:
		return true;
	default:
		return false;
	}
}

double Expression_Capacity::stringToDouble(const string& str)//�ַ���ת��������
{
	double d;
	stringstream ss;
	ss << str;    // ���ַ���д���ַ���  
	ss >> d;      // �����double  
	return d;
}
void Expression_Capacity::popTwoNumbers(stack<double>& s, double& first, double& second) //��ջ������ȡ��������
{
	first = s.top();
	s.pop();
	second = s.top();
	s.pop();
}
vector<pair<string, int>> Expression_Capacity::getPostfix(const vector<pair<string, int>>& vec)//����׺���ʽת��׺���ʽ
{
	vector<pair<string, int>> output;
	stack<pair<string, int>> s;
	for (int i = 0; i < vec.size(); i++)
	{
		pair<string, int> p = vec[i];
		if (isOperator(p.second))
		{
			while (!s.empty() && isOperator(s.top().second) && prior(s.top().second) >= prior(p.second))
			{
				output.push_back(s.top());
				s.pop();
			}
			s.push(p);
		}
		else if (p.second == 6)
		{
			s.push(p);
		}
		else if (p.second == 7)
		{
			while (s.top().second != 6)
			{
				output.push_back(s.top());
				s.pop();
			}
			s.pop();
		}
		else
		{
			output.push_back(p);
		}
	}
	while (!s.empty())
	{
		output.push_back(s.top());
		s.pop();
	}
	return output;
}
double Expression_Capacity::expCalculate(const vector<pair<string, int>>& vec) //�����׺���ʽ���
{
	double first, second;
	stack<double> s;
	for (int i = 0; i < vec.size(); ++i)
	{
		pair<string, int> p = vec[i];
		switch (p.second)
		{
		case 1:
			popTwoNumbers(s, first, second);
			s.push(second + first);
			break;
		case 2:
			popTwoNumbers(s, first, second);
			s.push(second - first);
			break;
		case 3:
			popTwoNumbers(s, first, second);
			s.push(second * first);
			break;
		case 4:
			popTwoNumbers(s, first, second);
			s.push(second / first);
			break;
		default:
			s.push(stringToDouble(p.first));
			break;
		}
	}
	double result = s.top();
	s.pop();
	return result;
}