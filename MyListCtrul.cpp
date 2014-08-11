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
			GetItemRect(i,rc,LVIR_BOUNDS);//��ȡ��ǰѡ�е�λ��
			CDC *pDC = GetDC();//��ȡdc
			CBitmap bmp;
			bmp.LoadBitmap(IDB_BITMAP1);//����λͼ
			CDC dcbmp;
			dcbmp.CreateCompatibleDC(pDC);//��������dc
			dcbmp.SelectObject(&bmp);//ѡ��λͼ
			pDC->BitBlt(rc.right - 12,rc.top,12,12,&dcbmp,0,0,SRCCOPY);//����dc
			ReleaseDC(pDC);//�ͷ�dc
			dcbmp.DeleteDC();//�ͷ�dc
			bmp.DeleteObject();//�ͷ�λͼ
		}
		else
		{
			CRect rc;
			GetItemRect(i,rc,LVIR_BOUNDS);
			CDC *pDC = GetDC();
			pDC->FillSolidRect(rc.right - 12,rc.top,12,12,RGB(255,255,255));//ˢ����
			ReleaseDC(pDC);
		}
	}

	CListCtrl::OnMouseMove(nFlags, point);
}
