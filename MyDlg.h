#pragma once


// CMyDlg �Ի���
#include"Markup.h"
#include<Resource.h>
#include "afxwin.h"
class CMyDlg : public CDialog
{
	DECLARE_DYNAMIC(CMyDlg)

public:
	CMyDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyDlg();

// �Ի�������
	enum { IDD = IDD_MYDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
		virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();



	CString id;
	CString command;

	CString path;
	CString address;
	afx_msg void OnBnClickedButton1();
	void SaveConf(CString sFileName);
	

	CEdit p_Edit;
};
