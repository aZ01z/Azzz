#pragma once
class User
{
public:
	CString account;
	CString password;
	User();
	virtual~User();
};
//����Ա˵��
class Controller :public User
{
public:
	CString id;
	Controller(CString a, CString p, CString i);
	~Controller();
};
//ͼ����Ϣ˵��
class Book :public User
{
public:
	CString id;//��¼��
	CString name;//����
	CString author;//����
	CString number;//�����
	CString publisher;//���浥λ
	CString time;//����ʱ��
	CString price;//�۸�
	Book(CString i, CString n, CString a, CString nu, CString p, CString t, CString pr);
	~Book();
};

