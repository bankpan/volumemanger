#if !defined(AFX_MYLISTCTRUL_H__8938581C_6A88_43E5_8517_DE8476056770__INCLUDED_)
#define AFX_MYLISTCTRUL_H__8938581C_6A88_43E5_8517_DE8476056770__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyListCtrul.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrul window

class CMyListCtrul : public CListCtrl
{
// Construction
public:
	CMyListCtrul();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListCtrul)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyListCtrul();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyListCtrul)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTCTRUL_H__8938581C_6A88_43E5_8517_DE8476056770__INCLUDED_)
