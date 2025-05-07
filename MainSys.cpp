// MainSys.cpp: 实现文件
//
#include "pch.h"
#include "BookMangeagement.h"
#include "MainSys.h"
#include "afxdialogex.h"
#include"User.h"

// MainSys 对话框

IMPLEMENT_DYNAMIC(MainSys, CDialogEx)

MainSys::MainSys(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_id(_T(""))
	, m_name(_T(""))
	, m_author(_T(""))
	, m_publisher(_T(""))
	, m_time(_T(""))
	, m_number(_T(""))
	, m_price(_T(""))
{

}

MainSys::~MainSys()
{
}

void MainSys::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT4, m_id);
	DDX_Text(pDX, IDC_EDIT3, m_name);
	DDX_Text(pDX, IDC_EDIT5, m_author);
	DDX_Text(pDX, IDC_EDIT7, m_publisher);
	DDX_Text(pDX, IDC_EDIT6, m_time);
	DDX_Text(pDX, IDC_EDIT9, m_number);
	DDX_Text(pDX, IDC_EDIT8, m_price);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(MainSys, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &MainSys::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON2, &MainSys::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &MainSys::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &MainSys::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &MainSys::OnBnClickedButton4)
	ON_BN_CLICKED(IDCANCEL, &MainSys::OnBnClickedCancel)
END_MESSAGE_MAP()


// MainSys 消息处理程序


BOOL MainSys::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//插入表头
	//样式设置为整行选择、网格线
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list.InsertColumn(0, _T("登录号"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(1, _T("书名"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(2, _T("作者"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(3, _T("出版单位"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(4, _T("出版时间"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(5, _T("分类号"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(6, _T("价格"), LVCFMT_LEFT, 100);
	//初始化图书信息并填入
	Book bok = Book(_T("123"), _T("中国文脉"), _T("余秋雨"), _T("人民出版社"), _T("2005"), _T("001"), _T("30.5"));
	m_list.InsertItem(0, (LPCTSTR)bok.id);
	m_list.SetItemText(0, 0, (LPCTSTR)bok.id);
	m_list.SetItemText(0, 1, (LPCTSTR)bok.name);
	m_list.SetItemText(0, 2, (LPCTSTR)bok.author);
	m_list.SetItemText(0, 3, (LPCTSTR)bok.publisher);
	m_list.SetItemText(0, 4, (LPCTSTR)bok.time);
	m_list.SetItemText(0, 5, (LPCTSTR)bok.number);
	m_list.SetItemText(0, 6, (LPCTSTR)bok.price);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void MainSys::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	DWORD dwPos = GetMessagePos();
	CPoint point(LOWORD(dwPos), HIWORD(dwPos));
	//查看单击位置
	m_list.ScreenToClient(&point);
	LVHITTESTINFO lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = LVHT_ABOVE;
	int nItem = m_list.SubItemHitTest(&lvinfo);
	if (nItem != LB_ERR)
	{
		for (int i = 0; i < m_list.GetItemCount(); i++)
		{
			if (m_list.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
			{
				//获取选中行，将对应值赋给对应编辑框的绑定变量
				m_id = m_list.GetItemText(i, 0);
				m_name = m_list.GetItemText(i, 1);
				m_author = m_list.GetItemText(i, 2);
				m_publisher = m_list.GetItemText(i, 3);
				m_time = m_list.GetItemText(i, 4);
				m_number = m_list.GetItemText(i, 5);
				m_price = m_list.GetItemText(i, 6);
				//将变量值更新至编辑框内
				UpdateData(FALSE);
			}
		}
		//单击列表中数据行时，［添加］按钮（ IDC BUTTON1)、学号编辑框不可操作
		//［修改］和［删除］按钮（ IDC _BUTTON2、3）可单击
		GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
	}
	else
	{
		//单击列表中空白行时，［添加］按钮（ IDC BUTTON1)、学号编辑框可操作
		//［修改］和［删除］按钮（ IDC _BUTTON2、3）不可单击 
		GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
		//清空对应编辑框
		m_id = "";
		m_name = "";
		m_author = "";
		m_publisher = "";
		m_time = "";
		m_number = "";
		m_price = "";
		UpdateData(FALSE);
	}
	*pResult = 0;
}


void MainSys::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	//添加前异常检查
	CString old_id;
	int i = 0;
	int nCount = m_list.GetItemCount();
	while (i < nCount)
	{
		old_id = m_list.GetItemText(i, 0);
		if (old_id == m_id)
		{
			MessageBox(_T("登录号重复！"));
			return;
		}
		i++;
	}
	if (m_name.IsEmpty())
	{
		MessageBox(_T("书名不能为空！"));
		return;
	}
	if (m_author.IsEmpty())
	{
		MessageBox(_T("作者不能为空！"));
		return;
	}
	if (m_publisher.IsEmpty())
	{
		MessageBox(_T("出版单位不能为空！"));
		return;
	}
	if (m_time.IsEmpty())
	{
		MessageBox(_T("出版时间不能为空！"));
		return;
	}
	if (m_number.IsEmpty())
	{
		MessageBox(_T("分类号不能为空！"));
		return;
	}
	if (m_price.IsEmpty())
	{
		MessageBox(_T("价格不能为空！"));
		return;
	}
	m_list.InsertItem(0, m_id);
	m_list.SetItemText(0, 1, m_name);
	m_list.SetItemText(0, 2, m_author);
	m_list.SetItemText(0, 3, m_publisher);
	m_list.SetItemText(0, 4, m_time);
	m_list.SetItemText(0, 5, m_number);
	m_list.SetItemText(0, 6, m_price);
	//清空编辑框内容
	m_id = "";
	m_name = "";
	m_author = "";
	m_publisher = "";
	m_time = "";
	m_number = "";
	m_price = "";
	UpdateData(FALSE);
}


void MainSys::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	int nItem = m_list.GetSelectionMark();
	UpdateData(TRUE);//读取控件值到变量
	//修改前异常检查
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	if (m_name.IsEmpty())
	{
		MessageBox(_T("书名不能为空！"));
		return;
	}
	if (m_author.IsEmpty())
	{
		MessageBox(_T("作者不能为空！"));
		return;
	}
	if (m_publisher.IsEmpty())
	{
		MessageBox(_T("出版单位不能为空！"));
		return;
	}
	if (m_time.IsEmpty())
	{
		MessageBox(_T("出版时间不能为空！"));
		return;
	}
	if (m_number.IsEmpty())
	{
		MessageBox(_T("分类号不能为空！"));
		return;
	}
	if (m_price.IsEmpty())
	{
		MessageBox(_T("价格不能为空！"));
		return;
	}
	//在表格修改行的上一行新增修改后标准行
	m_list.InsertItem(nItem, m_id);
	m_list.SetItemText(nItem, 1, m_name);
	m_list.SetItemText(nItem, 2, m_author);
	m_list.SetItemText(nItem, 3, m_publisher);
	m_list.SetItemText(nItem, 4, m_time);
	m_list.SetItemText(nItem, 5, m_number);
	m_list.SetItemText(nItem, 6, m_price);
	//删除原行
	m_list.DeleteItem(nItem + 1);
	//编辑框内容置空
	m_id = "";
	m_name = "";
	m_author = "";
	m_publisher = "";
	m_time = "";
	m_number = "";
	m_price = "";
	UpdateData(FALSE);
}


void MainSys::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	// 获取选中行，删除
	int nItem = m_list.GetSelectionMark();
	m_list.DeleteItem(nItem);
	//编辑框内容置空
	m_id = "";
	m_name = "";
	m_author = "";
	m_publisher = "";
	m_time = "";
	m_number = "";
	m_price = "";
	UpdateData(FALSE);
}


void MainSys::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//文件存储位置选择对话框
	CFileDialog fDlg (FALSE , NULL, _T("图书信息.txt"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("文本文档（ * .txt) | *.txt | 数据（ * .dat) | *.dat"), NULL);
	//确认存储位置后进行写入
	if (fDlg.DoModal() == IDOK)
	{
		CString sPath = fDlg.GetPathName();
		CStdioFile file(sPath, CFile::modeWrite | CFile::modeCreate);
		CString content = _T("登录号#书名#作者#出版单位#出版时间#分类号#价格\n");
		int i = 0;
		int nCount = m_list.GetItemCount();
		while (i < nCount)
		{
			content = content + m_list.GetItemText(i, 0) + _T("#");
			content = content + m_list.GetItemText(i, 1) + _T("#");
			content = content + m_list.GetItemText(i, 2) + _T("#");
			content = content + m_list.GetItemText(i, 3) + _T("#");
			content = content + m_list.GetItemText(i, 4) + _T("#");
			content = content + m_list.GetItemText(i, 5) + _T("#");
			content = content + m_list.GetItemText(i, 6) + _T("\n");

			i++;
		}
		file.Write(content, content.GetLength() * sizeof(TCHAR));
		file.Close();
		MessageBox(_T("文件保存成功！"),_T("保存成功！"));
	}
}


void MainSys::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
