// ListBoxExDemoDlg.h : header file
//

#if !defined(AFX_LISTBOXEXDEMODLG_H__BF92D786_D35C_11D3_B5AC_A965B72AE035__INCLUDED_)
#define AFX_LISTBOXEXDEMODLG_H__BF92D786_D35C_11D3_B5AC_A965B72AE035__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CListBoxExDemoDlg dialog
#include "TextProgressCtrl.h"
#include"InPlaceCtrls.h"
#include "ListBoxEx.h"
#include "SHBrowseDlg.h"
#include<string>
#include "afxcmn.h"
#include"MyDlg.h"
#include "afxwin.h"
using namespace std;

//void string_replace(string & strBig, const string & strsrc, const string &strdst) {
//        string::size_type pos=0;
//        string::size_type srclen=strsrc.size();
//        string::size_type dstlen=strdst.size();
//        while( (pos=strBig.find(strsrc, pos)) != string::npos){
//                strBig.replace(pos, srclen, strdst);
//                pos += dstlen;
//        }
//}
class CMyListBoxEx: public CListBoxEx
{
public:

   CMyListBoxEx()
   {
      SetEditStyle( LBEX_EDITBUTTON );
   };

   virtual void OnBrowseButton( int iItem )
   {
		TCHAR tstrCurrentPath[MAX_PATH];
		
		
	
        //initialize
        memset(tstrCurrentPath, 0, MAX_PATH);
        GetCurrentDirectory(MAX_PATH, tstrCurrentPath);
		CFileDialog dlg(TRUE , "yxb" ,NULL,OFN_OVERWRITEPROMPT|OFN_FILEMUSTEXIST|OFN_HIDEREADONLY ,"隐形宝 加密磁盘文件 (*.yxb)|*.yxb|all files (*.*)|*.*||");
		if ( dlg.DoModal()!=IDOK )
			 return;
		 //获取文件的绝对路径
	    CString sFileName=dlg.GetPathName();
		


		SetEditText( sFileName );
		SetCurrentDirectory(tstrCurrentPath);
   };
};

class CListBoxExDemoDlg : public CDialog
{
// Construction
public:
	DWORD ProcessId;
	BOOL ExecDosCmd(CString str);
	CListBoxExDemoDlg(CWnd* pParent = NULL);	// standard constructor
	static DWORD ThreadProcess(LPVOID);
	static DWORD CListBoxExDemoDlg::ThreadFile(LPVOID);
// Dialog Data
	//{{AFX_DATA(CListBoxExDemoDlg)
	enum { IDD = IDD_LISTBOXEXDEMO_DIALOG };
	CMyListBoxEx	m_ListBoxEx;
	//}}AFX_DATA

        CListBoxExBuddy m_ListBoxExBuddy;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListBoxExDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	HBRUSH m_hbrush; 
	int m_cursel ;
	HICON m_hIcon;
	HANDLE hRead,hWrite;
	static HANDLE Write_Buffer;
	static char buffer[4096];
	static int BufferMark;
	

	// Generated message map functions
	//{{AFX_MSG(CListBoxExDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnEditbutton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	
  
	CString getcommand(CString file);
	afx_msg void OnConfigure();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	void Replacelist();
	
public:
	CTextProgressCtrl m_ctrlProgress;
	afx_msg void OnBnClickedCheck1();
	CButton m_Button;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	
	afx_msg void OnBnClickedButton1();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTBOXEXDEMODLG_H__BF92D786_D35C_11D3_B5AC_A965B72AE035__INCLUDED_)
