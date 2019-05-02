#pragma once


// CMVdlg 对话框

class CMVdlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMVdlg)

public:
	CMVdlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMVdlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CCD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();


	DECLARE_MESSAGE_MAP()


	CBitmap m_bitmap;
public:
	// 图像控件
	CStatic m_pic;

	CRect rect;
	
};