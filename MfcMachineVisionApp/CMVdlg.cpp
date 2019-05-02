// CMVdlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MfcMachineVisionApp.h"
#include "CMVdlg.h"
#include "afxdialogex.h"
#include "resource.h"


// CMVdlg 对话框

IMPLEMENT_DYNAMIC(CMVdlg, CDialogEx)

CMVdlg::CMVdlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CCD, pParent)
{
	
}

BOOL CMVdlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	
	return TRUE;
}

void CMVdlg::OnPaint()
{
	m_pic.SetBitmap(m_bitmap);


	CDialogEx::OnPaint();
}

CMVdlg::~CMVdlg()
{
}

void CMVdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PIC, m_pic);
}


BEGIN_MESSAGE_MAP(CMVdlg, CDialogEx)
END_MESSAGE_MAP()


// CMVdlg 消息处理程序
