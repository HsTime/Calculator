
// CalculatorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCalculatorDlg �Ի���



CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCalculatorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mEdit); //1.������m_Edit�Ϳؼ�IDC_EDIT���а�2.ͨ���޸ı�������ֵ���ƿؼ�������
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &CCalculatorDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &CCalculatorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON12, &CCalculatorDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON14, &CCalculatorDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &CCalculatorDlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON17, &CCalculatorDlg::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON10, &CCalculatorDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CCalculatorDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON6, &CCalculatorDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CCalculatorDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CCalculatorDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON2, &CCalculatorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CCalculatorDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CCalculatorDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON9, &CCalculatorDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON13, &CCalculatorDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON18, &CCalculatorDlg::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON21, &CCalculatorDlg::OnBnClickedButton21)
	ON_BN_CLICKED(IDC_BUTTON22, &CCalculatorDlg::OnBnClickedButton22)
END_MESSAGE_MAP()


// CCalculatorDlg ��Ϣ�������

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	CFont* m_font = new CFont;
	//����һ���������Ե��߼�����
	m_font->CreateFont(36, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_SWISS, _T("Arial"));
	mEdit.SetFont(m_font, FALSE);
	lastPress = false;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCalculatorDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CCalculatorDlg::OnBnClickedButton1()
{
	// ����������ť
	mEdit.SetWindowText(_T(""));
}

void CCalculatorDlg::Clear()
{
	if (lastPress == true)
	{
		mEdit.SetWindowText(_T(""));
		lastPress = false;
	}
}

void CCalculatorDlg::OnBnClickedButton12()  //6
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Clear();
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("6");
	mEdit.SetWindowText(str);
}



void CCalculatorDlg::OnBnClickedButton14()//1
{
	Clear();
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("1");
	mEdit.SetWindowText(str);
}


void CCalculatorDlg::OnBnClickedButton15() //2
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Clear();
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("2");
	mEdit.SetWindowText(str);
}


void CCalculatorDlg::OnBnClickedButton17()//3
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Clear();
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("3");
	mEdit.SetWindowText(str);
}


void CCalculatorDlg::OnBnClickedButton10()  //4
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Clear();
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("4");
	mEdit.SetWindowText(str);
}


void CCalculatorDlg::OnBnClickedButton11() //6
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Clear();
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("5");
	mEdit.SetWindowText(str);
}



void CCalculatorDlg::OnBnClickedButton6()//7
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Clear();
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("7");
	mEdit.SetWindowText(str);
}


void CCalculatorDlg::OnBnClickedButton7()//8
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Clear();
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("8");
	mEdit.SetWindowText(str);
}



void CCalculatorDlg::OnBnClickedButton8()//9
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Clear();
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("9");
	mEdit.SetWindowText(str);
}



void CCalculatorDlg::OnBnClickedButton2()
{
	// �����ˡ���ť
	Clear();
	CString str;
	mEdit.GetWindowText(str);
	str = str.Left(str.GetLength() - 1);
	mEdit.SetWindowText(str);
}



void CCalculatorDlg::OnBnClickedButton4()
{
	// �������š���ť
	Clear();
	CString str;
	mEdit.GetWindowText(str);
	if (str == "")
	{
		str = str + _T("(");
		mEdit.SetWindowText(str);
	}
	else
	{
		if (str.GetAt(str.GetLength() - 1)<'0' || str.GetAt(str.GetLength() - 1)>'9')
		{
			str = str + _T("(");
			mEdit.SetWindowText(str);
		}
	}
}



void CCalculatorDlg::OnBnClickedButton5()
{
	// �������š���ť
	Clear();
	CString str;
	mEdit.GetWindowText(str);
	if (str != "")
	{
		if (str.GetAt(str.GetLength() - 1) >= '0' && str.GetAt(str.GetLength() - 1) <= '9')
		{
			str = str + _T(")");
			mEdit.SetWindowText(str);
		}
	}
}


void CCalculatorDlg::OnBnClickedButton9()
{
	// �Ӻ�
	lastPress = false;
	CString str;
	mEdit.GetWindowText(str);
	if (str != "")
	{
		if (str.GetAt(str.GetLength() - 1) != '+' && str.GetAt(str.GetLength() - 1) != '-'
			&& str.GetAt(str.GetLength() - 1) != '*' && str.GetAt(str.GetLength() - 1) != '/')
		{
			str = str + _T("+");
			mEdit.SetWindowText(str);
		}
	}
}



void CCalculatorDlg::OnBnClickedButton13()
{
	// ����
	lastPress = false;
	CString str;
	mEdit.GetWindowText(str);
	if (str != "")
	{
		if (str.GetAt(str.GetLength() - 1) != '+' && str.GetAt(str.GetLength() - 1) != '-'
			&& str.GetAt(str.GetLength() - 1) != '*' && str.GetAt(str.GetLength() - 1) != '/')
		{
			str = str + _T("-");
			mEdit.SetWindowText(str);
		}
	}
}


void CCalculatorDlg::OnBnClickedButton18()
{
	// �˺�
	lastPress = false;
	CString str;
	mEdit.GetWindowText(str);
	if (str != "")
	{
		if (str.GetAt(str.GetLength() - 1) != '+' && str.GetAt(str.GetLength() - 1) != '-'
			&& str.GetAt(str.GetLength() - 1) != '*' && str.GetAt(str.GetLength() - 1) != '/')
		{
			str = str + _T("*");
			mEdit.SetWindowText(str);
		}
	}
}


void CCalculatorDlg::OnBnClickedButton21()
{
	// ����
	lastPress = false;
	CString str;
	mEdit.GetWindowText(str);
	if (str != "")
	{
		if (str.GetAt(str.GetLength() - 1) != '+' && str.GetAt(str.GetLength() - 1) != '-'
			&& str.GetAt(str.GetLength() - 1) != '*' && str.GetAt(str.GetLength() - 1) != '/')
		{
			str = str + _T("/");
			mEdit.SetWindowText(str);
		}
	}
}



void CCalculatorDlg::OnBnClickedButton22()
{
	// �Ⱥţ�������
	CString str;
	mEdit.GetWindowText(str);
	if (str.Find('+') == -1 && str.Find('-') == -1 && str.Find('*') == -1 && str.Find('/') == -1)
		return;
	else
		lastPress = true;

	CT2CA pszConvertedAnsiString(str);  // �� TCHAR ת��Ϊ LPCSTR
	string exp_str(pszConvertedAnsiString); // �� LPCSTR ���� string

	if (exp_str != "")
	{
		Expression_Capacity e(exp_str);
		if (e.test())
		{
			string tmp;
			stringstream ss;
			ss << e.calculate();
			ss >> tmp;
			str = tmp.c_str();
		}
		else
		{
			str = "�������";
		}
		mEdit.SetWindowText(str);
	}
}
