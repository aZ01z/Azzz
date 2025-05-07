#include "pch.h"
#include "User.h"
#include<CString>
User::User() { }
User::~User() { }

Controller::Controller(CString a, CString p, CString i)
{
	account = a;
	password = p;
	id = i;
}
Controller::~Controller() { }

Book::Book(CString i, CString n, CString a, CString nu, CString p, CString t, CString pr)
{
	id = i;
	name = n;
	author = a;
	number = nu;
	publisher = p;
	time = t;
	price = pr;
}
Book::~Book() { }
