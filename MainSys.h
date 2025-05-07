#pragma once


// MainSys 对话框

class MainSys : public CDialogEx
{
	DECLARE_DYNAMIC(MainSys)

public:
	MainSys(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MainSys();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_id;
	CString m_name;
	CString m_author;
	CString m_publisher;
	CString m_time;
	CString m_number;
	CString m_price;
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedCancel();
};
