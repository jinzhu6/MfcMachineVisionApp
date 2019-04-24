
// DlgProxy.cpp: 实现文件
//

#include "stdafx.h"
#include "MfcMachineVisionApp.h"
#include "DlgProxy.h"
#include "MfcMachineVisionAppDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMfcMachineVisionAppDlgAutoProxy

IMPLEMENT_DYNCREATE(CMfcMachineVisionAppDlgAutoProxy, CCmdTarget)

CMfcMachineVisionAppDlgAutoProxy::CMfcMachineVisionAppDlgAutoProxy()
{
	EnableAutomation();

	// 为使应用程序在自动化对象处于活动状态时一直保持
	//	运行，构造函数调用 AfxOleLockApp。
	AfxOleLockApp();

	// 通过应用程序的主窗口指针
	//  来访问对话框。  设置代理的内部指针
	//  指向对话框，并设置对话框的后向指针指向
	//  该代理。
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CMfcMachineVisionAppDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CMfcMachineVisionAppDlg)))
		{
			m_pDialog = reinterpret_cast<CMfcMachineVisionAppDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CMfcMachineVisionAppDlgAutoProxy::~CMfcMachineVisionAppDlgAutoProxy()
{
	// 为了在用 OLE 自动化创建所有对象后终止应用程序，
	//	析构函数调用 AfxOleUnlockApp。
	//  除了做其他事情外，这还将销毁主对话框
	if (m_pDialog != nullptr)
		m_pDialog->m_pAutoProxy = nullptr;
	AfxOleUnlockApp();
}

void CMfcMachineVisionAppDlgAutoProxy::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CMfcMachineVisionAppDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMfcMachineVisionAppDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// 注意: 我们添加了对 IID_IMfcMachineVisionApp 的支持来支持类型安全绑定
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {bea6719b-f874-41e4-bc3b-2b4a1e4b61ff}
static const IID IID_IMfcMachineVisionApp =
{0xbea6719b,0xf874,0x41e4,{0xbc,0x3b,0x2b,0x4a,0x1e,0x4b,0x61,0xff}};

BEGIN_INTERFACE_MAP(CMfcMachineVisionAppDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CMfcMachineVisionAppDlgAutoProxy, IID_IMfcMachineVisionApp, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 宏在此项目的 StdAfx.h 中定义
// {f80aa0dc-c5b2-47c9-983d-187a5f132977}
IMPLEMENT_OLECREATE2(CMfcMachineVisionAppDlgAutoProxy, "MfcMachineVisionApp.Application", 0xf80aa0dc,0xc5b2,0x47c9,0x98,0x3d,0x18,0x7a,0x5f,0x13,0x29,0x77)


// CMfcMachineVisionAppDlgAutoProxy 消息处理程序
