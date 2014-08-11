// MyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MyDlg.h"

#include "ListBoxEx.h"


#include<sys\stat.h> 
#include<string.h> 
#include<fcntl.h> 
#include<io.h> 
// CMyDlg 对话框

IMPLEMENT_DYNAMIC(CMyDlg, CDialog)

CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg::IDD, pParent)
	, id(_T(""))
	, command(_T(""))
	, path(_T(""))
	, address(_T(""))
	
{
}

CMyDlg::~CMyDlg()
{
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT3, id);
	DDX_Text(pDX, IDC_EDIT1, command);
	DDX_Text(pDX, IDC_EDIT2, path);
	DDX_Text(pDX, IDC_EDIT4, address);

	DDX_Control(pDX, IDC_EDIT7, p_Edit);
}


BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CMyDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMyDlg 消息处理程序
BOOL CMyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
     //******************************
	BOOL bLoadXml = false;
	CMarkup xml; 
	char HistoryName[260];
	char *tmp;
	CString CurFile;
	
	memset(HistoryName,0,sizeof(HistoryName));
	GetModuleFileName (NULL, HistoryName, sizeof(HistoryName));
	tmp = strrchr (HistoryName, '\\');
	*(tmp + 1) = 0;
	strcpy (++tmp, "History.xml");
	

	//读取当前的配置文件和参数
	bLoadXml = xml.Load(HistoryName);   
	if(bLoadXml)
	{
		 xml.ResetMainPos();   
          xml.FindElem("PP");    
          xml.IntoElem();
		  xml.FindElem("history");    
          xml.IntoElem();

		  xml.FindElem("FILE");
          CurFile=xml.GetData();

	}

	p_Edit.SetWindowText(CurFile);
	bLoadXml = xml.Load(CurFile);   
	if (bLoadXml)    
		{   
          xml.ResetMainPos();   
          xml.FindElem("PP");    
          xml.IntoElem();
		  xml.FindElem("history");    
          xml.IntoElem();

		  xml.FindElem("ID");
          id=xml.GetData();
		  xml.FindElem("COMMAND");
          command=xml.GetData();
		  xml.FindElem("ADDRESS");
		  address=xml.GetData();
		  xml.FindElem("PATH");
          path=xml.GetData();
       

		 

		  SetDlgItemText( IDC_EDIT3,id);
		  SetDlgItemText( IDC_EDIT1,command);
		  SetDlgItemText( IDC_EDIT4,address);
          SetDlgItemText( IDC_EDIT2,path);
         }			 


	return true;
}
void CMyDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL bLoadXml = false;
	CMarkup xml; 

	CString sFileName;
	 p_Edit.GetWindowText(sFileName);

SaveConf(sFileName);
	
	//int j;
	/*char HistoryName[260];
	char *tmp;
	memset(HistoryName,0,sizeof(HistoryName));
	GetModuleFileName (NULL, HistoryName, sizeof(HistoryName));
	tmp = strrchr (HistoryName, '\\');
	*(tmp + 1) = 0;
	strcpy (++tmp, "History.xml");*/
	bLoadXml = xml.Load(sFileName);   
	UpdateData(true);
	/*CString address;
	GetDlgItemText( IDC_IPADDRESS1,address);*/
	if (bLoadXml)    
		{   
          xml.ResetMainPos();   

          xml.FindElem("PP");    
          xml.IntoElem();
		  xml.FindElem("history");    
          xml.IntoElem();
		 

		  xml.FindElem("ID");   
		  xml.RemoveElem();
		  xml.FindElem("COMMAND");
		  xml.RemoveElem();
		  xml.FindElem("ADDRESS");   
		  xml.RemoveElem();
		  xml.FindElem("PATH");  
		  xml.RemoveElem();
              
		 xml.AddElem("ID",id);
		 xml.AddElem("COMMAND",command);
		 xml.AddElem("ADDRESS",address);
		 xml.AddElem("PATH",path);
		  xml.Save(sFileName); 
         }			 
	OnOK();


}
void CMyDlg::SaveConf(CString sFileName)
{
	//保存当前选择的配置文件

		BOOL bLoadXml = false;
	CMarkup xml; 
	int j;
	char HistoryName[260];
	char *tmp;
	memset(HistoryName,0,sizeof(HistoryName));
	GetModuleFileName (NULL, HistoryName, sizeof(HistoryName));
	tmp = strrchr (HistoryName, '\\');
	*(tmp + 1) = 0;
	strcpy (++tmp, "History.xml");
	bLoadXml = xml.Load(HistoryName);   
	UpdateData(true);
	/*CString address;
	GetDlgItemText( IDC_IPADDRESS1,address);*/
	if (bLoadXml)    
		{   
          xml.ResetMainPos();   

          xml.FindElem("PP");    
          xml.IntoElem();
		  xml.FindElem("history");    
          xml.IntoElem();
		 

		  xml.FindElem("FILE");   
		  xml.RemoveElem();
		 
              
		 xml.AddElem("FILE",sFileName);
		  xml.Save(HistoryName); 
         }	
//初始化空的配置文件
	FILE *fp;
	CString init("<?xml version=\"1.0\" encoding=\"UTF-8\"?><PP><history></history></PP>");
	char* buffer=(LPSTR)(LPCTSTR)init;


	fp=fopen(sFileName,"r");
	int size = filelength(fileno(fp));
	fclose(fp);
	
	if(size==0)
	{
		fp=fopen(sFileName,"w");
		fwrite(buffer, 1, strlen(buffer), fp);
		fclose(fp);
	}
	
}
void CMyDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//TCHAR tstrCurrentPath[MAX_PATH];

	BOOL bLoadXml = false;
	CMarkup xml; 
        //initialize
 /*   memset(tstrCurrentPath, 0, MAX_PATH);
    GetCurrentDirectory(MAX_PATH, tstrCurrentPath);*/
	CFileDialog dlg(TRUE , "xml" ,NULL,OFN_OVERWRITEPROMPT|OFN_FILEMUSTEXIST|OFN_HIDEREADONLY ,"隐形宝 加密磁盘文件 (*.xml)|*.xml|all files (*.*)|*.*||");
	if ( dlg.DoModal()!=IDOK )
		 return;
	 //获取文件的绝对路径
    CString sFileName=dlg.GetPathName();
	p_Edit.SetWindowText( LPCTSTR(sFileName) );
    p_Edit.SetFocus();
	bLoadXml = xml.Load(sFileName);   
	if (bLoadXml)    
		{   
          xml.ResetMainPos();   
          xml.FindElem("PP");    
          xml.IntoElem();
		  xml.FindElem("history");    
          xml.IntoElem();

		  xml.FindElem("ID");
          id=xml.GetData();
		  xml.FindElem("COMMAND");
          command=xml.GetData();
		  xml.FindElem("ADDRESS");
		  address=xml.GetData();
		  xml.FindElem("PATH");
          path=xml.GetData();
       

		 

		  SetDlgItemText( IDC_EDIT3,id);
		  SetDlgItemText( IDC_EDIT1,command);
		  SetDlgItemText( IDC_EDIT4,address);
          SetDlgItemText( IDC_EDIT2,path);
         }			
SaveConf(sFileName);
	


}
