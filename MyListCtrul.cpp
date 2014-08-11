// MyListCtrul.cpp : implementation file
//

#include "stdafx.h"
#include "DlgTest.h"
#include "MyListCtrul.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrul

CMyListCtrul::CMyListCtrul()
{
}

CMyListCtrul::~CMyListCtrul()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrul, CListCtrl)
	//{{AFX_MSG_MAP(CMyListCtrul)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CMyListCtrul::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int ncount = GetItemCount();

	for (int i = 0;i < ncount;i++)
	{
		if (GetCheck(i))
		{
			CRect rc;
			GetItemRect(i,rc,LVIR_BOUNDS);//获取当前选中的位置
			CDC *pDC = GetDC();//获取dc
			CBitmap bmp;
			bmp.LoadBitmap(IDB_BITMAP1);//加载位图
			CDC dcbmp;
			dcbmp.CreateCompatibleDC(pDC);//创建兼容dc
			dcbmp.SelectObject(&bmp);//选中位图
			pDC->BitBlt(rc.right - 12,rc.top,12,12,&dcbmp,0,0,SRCCOPY);//拷贝dc
			ReleaseDC(pDC);//释放dc
			dcbmp.DeleteDC();//释放dc
			bmp.DeleteObject();//释放位图
		}
		else
		{
			CRect rc;
			GetItemRect(i,rc,LVIR_BOUNDS);
			CDC *pDC = GetDC();
			pDC->FillSolidRect(rc.right - 12,rc.top,12,12,RGB(255,255,255));//刷背景
			ReleaseDC(pDC);
		}
	}

	CListCtrl::OnMouseMove(nFlags, point);
}
