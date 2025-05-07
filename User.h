#pragma once
class User
{
public:
	CString account;
	CString password;
	User();
	virtual~User();
};
//管理员说明
class Controller :public User
{
public:
	CString id;
	Controller(CString a, CString p, CString i);
	~Controller();
};
//图书信息说明
class Book :public User
{
public:
	CString id;//登录号
	CString name;//书名
	CString author;//作者
	CString number;//分类号
	CString publisher;//出版单位
	CString time;//出版时间
	CString price;//价格
	Book(CString i, CString n, CString a, CString nu, CString p, CString t, CString pr);
	~Book();
};

