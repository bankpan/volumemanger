// ListBoxExDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ListBoxExDemo.h"
#include "ListBoxExDemoDlg.h"
#include "Markup.h"
#include   <shlwapi.h> 
#include "htcspapi.h"
#include "InputBox.h"
#include "WinBase.h"
#include "WinUser.h"
#include <tlhelp32.h>
#include <io.h>
#include <windows.h>
#include <winsvc.h>
#include<cstring>

#include<fstream>
 #include<iomanip>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char CListBoxExDemoDlg::buffer[4096]={0};
HANDLE CListBoxExDemoDlg::Write_Buffer=0;
int CListBoxExDemoDlg::BufferMark=0;
/*
 *���з���
 */
BOOL RunUCloakContainerProtectService(char* pName) 
{ 
	//run service with given name
	char pPath[260] = {0};
	char *tmp;
	GetModuleFileNameA (NULL, pPath, sizeof(pPath));
	tmp = strrchr (pPath, '\\');
	*(tmp + 1) = 0;
	strcpy (++tmp, "rsync.exe");
	//strcpy (++tmp, "rsync.exe");
	/*�������Ƿ����*/
	if (_access(pPath,0)==-1)
	{
		/*���ھ��Ҫ����Ϊ��*/
		MessageBox(NULL,"���α����ܴ��̱�����������ļ���ɾ��!���°�װ���޸���","���α�",MB_OK| MB_ICONEXCLAMATION);
		return 0;
	}
	SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
	if (schSCManager!=0) //�ɹ�
	{
		// open the service
		SC_HANDLE schService = OpenService( schSCManager, pName, SERVICE_ALL_ACCESS);
		if (schService!=0) //�ɹ�
		{
			// call StartService to run the service
			if(StartService(schService,0,NULL))
			{
				CloseServiceHandle(schService); 
				CloseServiceHandle(schSCManager); 
				return TRUE;
			}
			CloseServiceHandle(schService); 
		}
		CloseServiceHandle(schSCManager); 
	}
	return FALSE;
}

/*
 *ֹͣ����
 */
BOOL KillUCloakContainerProtectService(char* pName) 
{ 
	// kill service with given name
	SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
	if (schSCManager!=0) //�ɹ�
	{
		// open the service
		SC_HANDLE schService = OpenService( schSCManager, pName, SERVICE_ALL_ACCESS);
		if (schService!=0) //�ɹ�
		{
			// call ControlService to kill the given service
			SERVICE_STATUS status;
			if(ControlService(schService,SERVICE_CONTROL_STOP,&status))
			{
				CloseServiceHandle(schService); 
				CloseServiceHandle(schSCManager); 
				return TRUE;
			}
			CloseServiceHandle(schService); 
		}
		CloseServiceHandle(schSCManager); 
	}
	return FALSE;
}



/////////////////////////////////////////////////////////////////////////////
// CListBoxExDemoDlg dialog

CListBoxExDemoDlg::CListBoxExDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CListBoxExDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CListBoxExDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CListBoxExDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListBoxExDemoDlg)
	DDX_Control(pDX, IDC_LIST, m_ListBoxEx);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_EDIT1, m_ctrlProgress);
	DDX_Control(pDX, IDC_CHECK1, m_Button);
}

BEGIN_MESSAGE_MAP(CListBoxExDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CListBoxExDemoDlg)
	   
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EDITBUTTON, OnEditbutton)
	//}}AFX_MSG_MAP
		

	ON_COMMAND(ID_32773, &CListBoxExDemoDlg::OnConfigure)
	ON_BN_CLICKED(IDOK, &CListBoxExDemoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CListBoxExDemoDlg::OnBnClickedCancel)


	
	

	ON_BN_CLICKED(IDC_CHECK1, &CListBoxExDemoDlg::OnBnClickedCheck1)
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONDOWN()
	
	ON_BN_CLICKED(IDC_BUTTON1, &CListBoxExDemoDlg::OnBnClickedButton1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListBoxExDemoDlg message handlers


BOOL CListBoxExDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	//*******************************************

      // m_ctrlProgress.SetForegroundWind
	
       m_ctrlProgress.SetRange(0,100);
       m_ctrlProgress.SetStep(4);
       m_ctrlProgress.SetPos(0);

     //******************************

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//CInputBox Dlg;
	//Dlg.DoModal();

	/*LONG style=::GetWindowLong(m_hWnd,GWL_STYLE);  */
 //style&=~WS_SIZEBOX; //ȥ���߿�
//::SetWindowLong(m_hWnd,GWL_STYLE,style); 
	//m_hbrush=CreateSolidBrush(RGB(123,95,36));
	//m_ListBoxEx.SetCheckStyle(BS_AUTO3STATE  );
	/*��Ϊֹͣ����ĺ���������Ϊ����ĳ��������û�гɹ�����ʧ��ʱ��ִ��һ��*/
	for(int i=0;i<3;i++)
	{
		if(KillUCloakContainerProtectService("UCloakContainerProtectService")==1)
			break;//�ɹ�����
	}

	BOOL bLoadXml = FALSE;    
	CMarkup xml; 
	char HistoryName[260];
	char *tmp;
	CString File;
	memset(HistoryName,0,sizeof(HistoryName));
	GetModuleFileName (NULL, HistoryName, sizeof(HistoryName));
	tmp = strrchr (HistoryName, '\\');
	*(tmp + 1) = 0;
	/*strcpy (++tmp, "History.xml");
	bLoadXml = xml.Load(HistoryName);  */  

	strcpy (++tmp, "History.xml");

		bLoadXml = xml.Load(HistoryName);   
	if(bLoadXml)
	{
		 xml.ResetMainPos();   
          xml.FindElem("PP");    
          xml.IntoElem();
		  xml.FindElem("history");    
          xml.IntoElem();

		  xml.FindElem("FILE");
          File=xml.GetData();

	}
	//bLoadXml = xml.Load(File); 
	bLoadXml = xml.Load(HistoryName); 

	if (bLoadXml)    
		{    
			  
			  CString strUserID = _T("");    
			  xml.ResetMainPos();    
			  xml.FindElem("PP");    
			  xml.IntoElem();
			  xml.FindElem("history");    
			  xml.IntoElem();
			  int i=0;
			  while (xml.FindElem("volume"))    
			  {    	
					strUserID = xml.GetData();
					m_ListBoxEx.SetItem(i,strUserID,NULL);
					i++;	
			  }    
		}
      Replacelist();

     // Add the listbox buddy
     m_ListBoxExBuddy.SubclassDlgItem( IDC_LISTBUDDY, this );
     m_ListBoxExBuddy.SetListbox( &m_ListBoxEx );



	return TRUE;  // return TRUE  unless you set the focus to a control

}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CListBoxExDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CListBoxExDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CListBoxExDemoDlg::OnEditbutton() 
{
   m_ListBoxEx.EditNew();
}

void CListBoxExDemoDlg::OnConfigure()
{
	CMyDlg dlg;
    dlg.DoModal();

}
int state=0;
 int* buf = new int[10];
 int iSelected;
void CListBoxExDemoDlg::OnBnClickedOk()
{		
	    m_ListBoxEx.UpdateData(TRUE);
		BOOL bLoadXml = false;
		CMarkup xml;
		int j;
		char HistoryName[260];
		char *tmp;
		CString str,commandline,File;
		memset(HistoryName,0,sizeof(HistoryName));
		GetModuleFileName (NULL, HistoryName, sizeof(HistoryName));
		tmp = strrchr (HistoryName, '\\');
		*(tmp + 1) = 0;
		strcpy (++tmp, "History.xml");

		bLoadXml = xml.Load(HistoryName);   
	if(bLoadXml)
	{
		 xml.ResetMainPos();   
          xml.FindElem("PP");    
          xml.IntoElem();
		  xml.FindElem("history");    
          xml.IntoElem();

		  xml.FindElem("FILE");
          File=xml.GetData();

	}
/*	bLoadXml = xml.Load(File);  */ 
		bLoadXml = xml.Load(HistoryName);   
		if (bLoadXml)    
			{ //MessageBox(NULL,"CHENG",NULL);  
              CString strUserID = _T("");    
              xml.ResetMainPos();    
              xml.FindElem("PP");    
              xml.IntoElem();
			  xml.FindElem("history");    
              xml.IntoElem();
			 
              while (xml.FindElem("volume"))    
              { 
				xml.RemoveElem();
              }
			  
			  CString strSecondItem;
			   for ( int i=0;i <= m_ListBoxEx.GetCount()-1; i++ )
				{       
						/*�ų���ͬ���б���*/		    
						m_ListBoxEx.GetText( i, strSecondItem );
						for(j=0;j<i;j++)
						{
							CString tmpstr;
							m_ListBoxEx.GetText(j, tmpstr );
							if(strcmp(strSecondItem,tmpstr)==0)
								break;
						}
						if(j==i)
							xml.AddElem("volume",strSecondItem );
				}   
	
			  xml.Save(HistoryName);
             }	 	 
		m_ListBoxEx.UpdateData(FALSE); 

	//m_ListBoxEx.Select
	int count=0;
	for(int i=0;i<m_ListBoxEx.GetCount();i++)
		  if(m_ListBoxEx.GetCheck(i))
			  count++;
   for(int i=0;i<10;i++)
	   buf[i]=-1;
	for(int i=0,j=0;i<m_ListBoxEx.GetCount();i++)
		  if(m_ListBoxEx.GetCheck(i))
			  buf[j++]=i;
	             //��������ļ�
   // m_ListBoxEx.GetSelItems(count,buf); //��ѡ�������������뵽buffer������ 
    for(iSelected = 0; iSelected < count; iSelected++)
	{
        m_ListBoxEx.GetText(buf[iSelected],str); //�õ�ָ��������ֵ�����뵽str��
		
	   //fstream file;  
	   // file.open(str);     //��Ϊ����ļ���
		/*	file.Close();*/

	/*	CFile file2(str,CFile::modeWrite);*/

		try
		{
			CFile file(str,CFile::shareExclusive);
		}
		catch (CFileException* pEx)
		{
		   MessageBox("���ܴ����ļ�"+str+"�Ѿ��������������ʹ�á�","ͬ��ʧ��",MB_ICONSTOP);
		   continue;
		   pEx->Delete();
		}
	
//�����dos���ڣ����Կ������Ϣ�����ÿ���ȥ��
		commandline=getcommand(str);
		WinExec(commandline,SW_SHOWNORMAL);

		ExecDosCmd(str);
	/*	   int count=m_ListBoxEx.GetSelCount();
		int iSelected = m_ListBoxEx.GetCurSel();
		m_ListBoxEx.GetText(iSelected,str);*/

		
	DWORD dwThreadId;
	Write_Buffer = CreateThread(NULL,         /* security attributes */
						   0,            /* use default stack size */
						   (LPTHREAD_START_ROUTINE)ThreadFile, /* thread function */
							(void*)&hRead,   /* argument to thread function */
						   0,            /* thread creation flags */
						   &dwThreadId); /* thread id out */
	
	//WaitForSingleObject(hThread,   INFINITE);   


		//for(int i=0;i<3;i++)
		//{
		//	/*if(RunUCloakContainerProtectService("UCloakContainerProtectService")==1)*/
		//	/*if(RunUCloakContainerProtectService("rsync")==1)*/
		//	commandline=getcommand(str);
		//	/*	WinExec(_T("1.bat"),SW_SHOWMAXIMIZED); */
		//	WinExec(commandline,SW_SHOWNORMAL);
		//	
		//		break;//�ɹ�����
		//}

		
		//************************************
		UpdateData(false);
		HANDLE hThread1;
     
		state=0;
		hThread1 = CreateThread(NULL,         /* security attributes */
							   0,            /* use default stack size */
							   (LPTHREAD_START_ROUTINE)ThreadProcess, /* thread function */
							    (void*)&m_ctrlProgress,   /* argument to thread function */
							   0,            /* thread creation flags */
							   &dwThreadId); /* thread id out */
	
	//*****************************************************************
	/*	m_ctrlProgress.SetWindowTextA(str+" ");*/


	
  
	BOOL bIsok = TRUE;
	while(bIsok)
	{
		DWORD dwTime = MsgWaitForMultipleObjects(1,&hThread1,FALSE, 10, QS_ALLINPUT);
		MSG msg;
		//�ȵ��ź�
		switch(dwTime)
		{
			case WAIT_OBJECT_0:
			{
				bIsok = FALSE;
			}
			break;


			case WAIT_OBJECT_0+1:
			{
			//����Ϣ
				if(PeekMessage(&msg,NULL, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg); 
				}
			}
			break;

			case WAIT_TIMEOUT:
			{
				//��ʱ����
			}
			break;
		}
		if(bIsok == FALSE)
			break;
	}


	
	CRect rc;
	if(buf[iSelected]==-1)
		continue;
	m_ListBoxEx.GetItemRect(buf[iSelected],rc);//��ȡ��ǰѡ�е�λ��

	CDC *pDC = GetDC();//��ȡdc
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP1);//����λͼ
	CDC dcbmp;
	dcbmp.CreateCompatibleDC(pDC);//��������dc
	dcbmp.SelectObject(&bmp);//ѡ��λͼ
	pDC->BitBlt(rc.right-50,rc.top+61,16,16,&dcbmp,0,0,SRCCOPY);//����dc
		//pDC->BitBlt(rc.left+35,rc.top+60,16,16,&dcbmp,0,0,SRCCOPY);//����dc
	ReleaseDC(pDC);//�ͷ�dc
	dcbmp.DeleteDC();//�ͷ�dc
	bmp.DeleteObject();//�ͷ�λͼ

      
	
	}
		//************************************
		//OnOK();
}
//CString CListBoxExDemoDlg::getcommand(CString file)
//{
//	CString str="cmd.exe /c rsync -v -rlt -z  --delete -p -o -g --progress --password-file=\"/cygdrive/C/secret.txt\" \"/cygdrive/";
//	
//	/*CString str="cmd.exe /c rsync -v -rlt -z  --delete -p -o -g --progress --password=\"good1234\" \"/cygdrive/";*/
//	CString id,command,address,path;
//	BOOL bLoadXml = false;
//	CMarkup xml; 
//	char HistoryName[260];
//	char *tmp;
//	memset(HistoryName,0,sizeof(HistoryName));
//	GetModuleFileName (NULL, HistoryName, sizeof(HistoryName));
//	tmp = strrchr (HistoryName, '\\');
//	*(tmp + 1) = 0;
//	strcpy (++tmp, "History.xml");
//	bLoadXml = xml.Load(HistoryName);   
//	if (bLoadXml)    
//		{   
//          xml.ResetMainPos();   
//          xml.FindElem("PP");    
//          xml.IntoElem();
//		  xml.FindElem("history");    
//          xml.IntoElem();
//
//		  xml.FindElem("ID");
//          id=xml.GetData();
//		  xml.FindElem("COMMAND");
//          command=xml.GetData();
//		  xml.FindElem("ADDRESS");
//		  address=xml.GetData();
//		  xml.FindElem("PATH");
//          path=xml.GetData();
//         }	
//
//	FILE *fp;
//	if((fp = fopen("c://secret.txt", "w")) == 0)
//	{
//	   printf("open failed!");
//	   exit(1);
//	}
//	memset(buffer,0,4096);
//	memcpy(buffer,(LPSTR)(LPCTSTR)command,command.GetLength());
//	fwrite(buffer, 1, sizeof(buffer), fp);
//	fclose(fp);
//
//
//	file.Remove(':');
//	file.Replace('\\','/');
//	str=str+file;
//	str=str+CString("\" ");
//	str=str+id;
//	str=str+CString("@");
//	str=str+address;
//	str=str+CString("::");
//	str=str+path;
//	str=str+CString("&&pause");
//	return str;
//}
string m_replace(string str,string pattern,string dstPattern,int count=-1)
{
    string retStr="";
    string::size_type pos;
    int i=0,l_count=0,szStr=str.length();
    if(-1 == count) // replace all
        count = szStr;
    for(i=0; i<szStr; i++)
    {        
        if(string::npos == (pos=str.find(pattern,i)))  break;
        if(pos < szStr)
        {            
            retStr += str.substr(i,pos-i) + dstPattern;
            i=pos+pattern.length()-1;
            if(++l_count >= count)
            {
                i++;
                break;
            }
        }
    }
    retStr += str.substr(i);
    return retStr;
}

CString CListBoxExDemoDlg::getcommand(CString file)
{
	//CString str="cmd.exe /c rsync -v -rlt -z  --delete -p -o -g --progress --password-file=\"/cygdrive/";

	/*CString str="cmd.exe /c rsync -v -rlt -z  --delete -p -o -g --progress --password=\"good1234\" \"/cygdrive/";*/
	CString id,command,address,path;
	BOOL bLoadXml = false;
	CMarkup xml; 
	char HistoryName[260];
	char *tmp;

	CString File;
	memset(HistoryName,0,sizeof(HistoryName));
	GetModuleFileName (NULL, HistoryName, sizeof(HistoryName));

	tmp = strrchr (HistoryName, '\\');
	*(tmp + 1) = 0;
	/*strcpy (++tmp, "History.xml");*/
/*	bLoadXml = xml.Load(HistoryName);  */ 
	strcpy (++tmp, "History.xml");
		bLoadXml = xml.Load(HistoryName);   
	if(bLoadXml)
	{
		 xml.ResetMainPos();   
          xml.FindElem("PP");    
          xml.IntoElem();
		  xml.FindElem("history");    
          xml.IntoElem();

		  xml.FindElem("FILE");
          File=xml.GetData();

	}
	bLoadXml = xml.Load(File);   
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
         }	

	CString str="cmd.exe /k ";
	tmp = strrchr (HistoryName, '\\');
	*(tmp + 1) = 0;
	//m_replace(HistoryName,"\\","\\\"");
	strcpy (++tmp, "rsync.exe\"");

	CString temp_str(HistoryName);
	temp_str.Replace("\\","\"\\\"");
	temp_str.Delete(2,1);
	str=str+temp_str;

	
	CString str2=" -v -rlt -z --delete -p -o -g --progress -stats --password-file=\"/cygdrive/";
	str=str+str2;

	FILE *fp;
	tmp = strrchr (HistoryName, '\\');
	*(tmp+ 1) = 0;
	strcpy (++tmp, "secret.txt");
	if((fp = fopen(HistoryName, "w")) == 0)
	{
	   printf("open failed!");
	   exit(1);
	}
	CString str_tmp="";
	str_tmp=str_tmp+HistoryName;
	str_tmp.Remove(':');
	str_tmp.Replace('\\','/');
	str=str+str_tmp;
	CString str3="\" \"/cygdrive/";
	str=str+str3;

	
	memset(buffer,0,4096);
	memcpy(buffer,(LPSTR)(LPCTSTR)command,command.GetLength());
	fwrite(buffer, 1, sizeof(buffer), fp);
	fclose(fp);


	file.Remove(':');
	file.Replace('\\','/');


	str=str+file;
	str=str+CString("\" ");
	str=str+id;
	str=str+CString("@");
	str=str+address;
	str=str+CString("::");
	str=str+path;
	str=str+CString("&&pause");
	
	//str="cmd.exe /c c:\\Users\\god\\Desktop\\�½��ļ���\\Դ��\\��������\\\"volumemanger\"\\Debug\\rsync.exe -v -rlt -z --delete -p -o -g --progress --password-file=\"/cygdrive/c/Users/god/Desktop/�½��ļ���/Դ��/��������/volumemanger/Debug/secret.txt\" \"/cygdrive/C/360safe.exe\" hhf@192.168.2.229::hhf&&pause";
	return str;	
}
BOOL CListBoxExDemoDlg::ExecDosCmd(CString file_to_command) 
{    
	file_to_command=getcommand(file_to_command);


	//#define EXECDOSCMD "1.bat" //���Ի����������
	SECURITY_ATTRIBUTES sa; 
	sa.nLength = sizeof(SECURITY_ATTRIBUTES); 
	sa.lpSecurityDescriptor = NULL; 
	sa.bInheritHandle = TRUE; 
	if (!CreatePipe(&hRead,&hWrite,&sa,0)) 
	{ 
		return FALSE; 
	} 
	//char command[1024];    //����1K�������У������˰� 
	//strcpy(command,"Cmd.exe /C "); 
	//strcat(command,EXECDOSCMD); 
	STARTUPINFO si; 
	PROCESS_INFORMATION pi; 
	si.cb = sizeof(STARTUPINFO); 
	GetStartupInfo(&si); 
	si.hStdError = hWrite;            //�Ѵ������̵ı�׼��������ض��򵽹ܵ����� 
	si.hStdOutput = hWrite;           //�Ѵ������̵ı�׼����ض��򵽹ܵ����� 
	si.wShowWindow = SW_HIDE; 
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES; 
	//�ؼ����裬CreateProcess�����������������MSDN 

	HANDLE handle;
	if (!CreateProcess(NULL,(LPSTR)(LPCSTR)file_to_command,NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi)) 
	{ 
		CloseHandle(hWrite); 
		CloseHandle(hRead); 
		return FALSE; 
	} 
	ProcessId=pi.dwProcessId;
	CloseHandle(hWrite);
	return TRUE; 
}
DWORD CListBoxExDemoDlg::ThreadFile(LPVOID lpArg )
{
	 HANDLE *hRead1=(HANDLE*)lpArg;
	 HANDLE hRead=*hRead1;

	DWORD bytesRead=0;  

	FILE *fp;
	char *string="***";
	//if((fp = fopen("c://example.txt", "w")) == 0)
	//{
	//   printf("open failed!");
	//   exit(1);
	//}
	while (true) 
	{ 
	
		 memset(buffer,0,4095);
		if (ReadFile(hRead,buffer,4095,&bytesRead,NULL) == NULL) 
		   break;
		Sleep(50);
		//BufferMark=1;
		//while(BufferMark);

		//buffer�о���ִ�еĽ�������Ա��浽�ı���Ҳ����ֱ����� 
	/*	fwrite(string, 1, 3, fp);
		fwrite(buffer, 1, strlen(buffer), fp);
		fflush(fp);*/

	  
	   //Sleep(2000);
	  // AfxMessageBox(buffer);   //�����ǵ����Ի�����ʾ 
	}  
	//fclose(fp);
	CloseHandle(hRead); 
    return((DWORD)NULL);
}


/** Start a second thread in Windows because TUNTAP interfaces do not expose
 *  file descriptors. */

void CListBoxExDemoDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		BOOL bLoadXml = false;
		CMarkup xml; 
		int j;
		CString File;
		char HistoryName[260];
		char *tmp;
		memset(HistoryName,0,sizeof(HistoryName));
		GetModuleFileName (NULL, HistoryName, sizeof(HistoryName));
		tmp = strrchr (HistoryName, '\\');
		*(tmp + 1) = 0;
		/*strcpy (++tmp, "History.xml");
		bLoadXml = xml.Load(HistoryName);  */ 



		strcpy (++tmp, "History.xml");

		bLoadXml = xml.Load(HistoryName);   
	if(bLoadXml)
	{
		 xml.ResetMainPos();   
          xml.FindElem("PP");    
          xml.IntoElem();
		  xml.FindElem("history");    
          xml.IntoElem();

		  xml.FindElem("FILE");
          File=xml.GetData();

	}
	//bLoadXml = xml.Load(File);  
	bLoadXml = xml.Load(HistoryName);   

		if (bLoadXml)    
			{   
              CString strUserID = _T("");    
              xml.ResetMainPos();    
              xml.FindElem("PP");    
              xml.IntoElem();
			  xml.FindElem("history");    
              xml.IntoElem();
			 
              while (xml.FindElem("volume"))    
              { 
				xml.RemoveElem();
              }
			  
			  CString strSecondItem;
			   for ( int i=0;i <= m_ListBoxEx.GetCount()-1; i++ )
				{       
								    
						m_ListBoxEx.GetText( i, strSecondItem );
						/*�ų���ͬ���б���*/
						for(j=0;j<i;j++)
						{
							CString tmpstr;
							m_ListBoxEx.GetText(j, tmpstr );
							if(strcmp(strSecondItem,tmpstr)==0)
								break;
						}
						if(j==i)
							xml.AddElem("volume",strSecondItem );
						
									
				}   
			  xml.Save(HistoryName); 
             }			 
		m_ListBoxEx.UpdateData(FALSE);


		//for(int i=0;i<3;i++)
		//{
		//	if(RunUCloakContainerProtectService("UCloakContainerProtectService")==1)
		//		break;//�ɹ�����
		//}
		OnOK();
}
void CListBoxExDemoDlg:: Replacelist()
{				
		CString fileName;
		int i=0;
		while ( i <= m_ListBoxEx.GetCount()-1 )
		{ 
				m_ListBoxEx.GetText( i, fileName );
				if(_access(fileName,0)!=0)
				{
					m_ListBoxEx.DeleteString( i);
				}
				else
				{
					i++;
				}						
		}    


}






DWORD CListBoxExDemoDlg::ThreadProcess(LPVOID lpArg )
	{
		
	   CTextProgressCtrl *m_ctrlProgress1=(CTextProgressCtrl*)lpArg;
	   int nLower=0;
       int nUpper=100;
	   char str[5]={'0','0','0','0','0'};
	   int i;
	   CString BufStr;
	   int success=0;
	   m_ctrlProgress1->SetPos(0);
       m_ctrlProgress1->GetRange(nLower,nUpper);
      /* if(m_ctrlProgress1->GetPos()==nUpper){
              m_ctrlProgress1->SetPos(nLower);
       }*/

	 
	   while(m_ctrlProgress1->GetPos()<nUpper)
	   {
		 
		   BufStr=buffer;
		   if(BufStr.Find("received")!=-1)
			   success=1;
			for(i=0;i<sizeof(buffer);i++)
			{
				if (buffer[i]=='%')
				{
					if(buffer[i-2]!=' ')
						str[1]=buffer[i-2];
					if(buffer[i-3]!=' ')
						str[0]=buffer[i-3];
					str[2]=buffer[i-1];
					str[3]=buffer[i];
					break;
				}
				
			}
		
			if(str[0]=='1')
			{
				m_ctrlProgress1->SetPos(100);
				
				break;
			}
			m_ctrlProgress1->SetPos((str[1]-'0')*10+str[2]-'0');

		
			
			DWORD exitCode=0;
			GetExitCodeThread(Write_Buffer,&exitCode);
			if (exitCode!=STILL_ACTIVE)
			{
				if(success==0)
				{
					buf[iSelected]=-1;
					AfxMessageBox("�ƶ˱���ʧ�ܣ������������");
				}
				else
				{
					m_ctrlProgress1->SetPos(100);
					Sleep(300);
					m_ctrlProgress1->SetPos(0);
				}
				break;
			}
		/*	BufferMark=0;*/
	   }
	   	Sleep(300);
		m_ctrlProgress1->SetPos(0);
	
	   state=m_ctrlProgress1->GetPos();
		return((DWORD)NULL);
	}

void CListBoxExDemoDlg::OnBnClickedCheck1()
{	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int num=m_ListBoxEx.GetCount();
	for(int i=0;i<num;i++)
		if(m_Button.GetCheck())
			m_ListBoxEx.SetCheck(i,1);
		//else
		//	m_ListBoxEx.SetCheck(i,0);
}

HBRUSH CListBoxExDemoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//int ncount = m_ListBoxEx.GetCount();

	//for (int i = 0;i < ncount;i++)
	//{
	//	if (m_ListBoxEx.GetCheck(i))
	//	{
	//		CRect rc;
	//		m_ListBoxEx.GetItemRect(i,rc);//��ȡ��ǰѡ�е�λ��
	//		CDC *pDC = GetDC();//��ȡdc
	//		CBitmap bmp;
	//		bmp.LoadBitmap(IDB_BITMAP1);//����λͼ
	//		CDC dcbmp;
	//		dcbmp.CreateCompatibleDC(pDC);//��������dc
	//		dcbmp.SelectObject(&bmp);//ѡ��λͼ
	//		pDC->BitBlt(rc.right-50,rc.top+62,12,12,&dcbmp,0,0,SRCCOPY);//����dc
	//		ReleaseDC(pDC);//�ͷ�dc
	//		dcbmp.DeleteDC();//�ͷ�dc
	//		bmp.DeleteObject();//�ͷ�λͼ
	//	}
	//	else
	//	{
	//		CRect rc;
	//		m_ListBoxEx.GetItemRect(i,rc);
	//		CDC *pDC = GetDC();
	//		pDC->FillSolidRect(rc.right-50,rc.top+62,12,12,RGB(255,255,255));//ˢ����
	//		ReleaseDC(pDC);
	//	}
	//}

	//CListBox::OnMouseMove(nFlags, point);


	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO:  �ڴ˸��� DC ���κ�����
		/*if(nCtlColor== CTLCOLOR_BTN  )*/


	
	if(pWnd->GetDlgCtrlID()==IDC_LIST)
	{
	
	
	
		//pDC->SetBkMode(TRANSPARENT);
		////�˴������������ɫ
		//pDC->SetTextColor(RGB(25,36,235));
		/*m_hbrush= CreateSolidBrush(RGB(15,0,255)); */
		return m_hbrush;
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

void CListBoxExDemoDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//MessageBox("hello");
	CDialog::OnLButtonDown(nFlags, point);

	
}


void CListBoxExDemoDlg::OnBnClickedButton1()
{
	MessageBox("��ֹͬ��");

	// TODO: �ڴ���ӿؼ�֪ͨ����������

	/*HANDLE hProcess=OpenProcess(PROCESS_TERMINATE,FALSE,ProcessId);
    if(hProcess==NULL)
        return ;
    TerminateProcess(hProcess,0);*/


::PostThreadMessage(ProcessId, WM_CLOSE, 0, 0);
	DWORD dwDesiredAccess = PROCESS_TERMINATE;
    BOOL  bInheritHandle  = FALSE;
    HANDLE hProcess = OpenProcess(dwDesiredAccess, bInheritHandle, ProcessId);
    if (hProcess == NULL)
        return ;
    BOOL result = TerminateProcess(hProcess, 0);
    CloseHandle(hProcess);
    return ;

}
//BOOL KillProcess(DWORD ProcessId)
//{
//    HANDLE hProcess=OpenProcess(PROCESS_TERMINATE,FALSE,ProcessId);
//    if(hProcess==NULL)
//        return FALSE;
//    if(!TerminateProcess(hProcess,0))
//        return FALSE;
//    return TRUE;
//}