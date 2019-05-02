
// MfcMachineVisionAppDlg.h: 头文件
//


#pragma once
#include "CMVdlg.h"

#include <vector>
using std::vector;

class CMfcMachineVisionAppDlgAutoProxy;


// CMfcMachineVisionAppDlg 对话框
class CMfcMachineVisionAppDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMfcMachineVisionAppDlg);
	friend class CMfcMachineVisionAppDlgAutoProxy;

// 构造
public:
	CMfcMachineVisionAppDlg(CWnd* pParent = nullptr);	// 标准构造函数
	virtual ~CMfcMachineVisionAppDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCMACHINEVISIONAPP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	CMfcMachineVisionAppDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()


	vector<CMVdlg*> m_pCCDdlg;
};
