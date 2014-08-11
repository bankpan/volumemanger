#if !defined(AFX_INPUTBOX_H__7A0E7CEB_E557_4424_8C09_B2BF0303325B__INCLUDED_)
#define AFX_INPUTBOX_H__7A0E7CEB_E557_4424_8C09_B2BF0303325B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInputBox dialog

class CInputBox : public CDialog
{
// Construction
public:
	CInputBox(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInputBox)
public:
	enum { IDD = IDD_INPUTBOX };
	CString	m_input;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInputBox)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInputBox)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeInput();
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTBOX_H__7A0E7CEB_E557_4424_8C09_B2BF0303325B__INCLUDED_)
