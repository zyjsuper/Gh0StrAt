
// Gh0StrATDlg.h: 头文件
//

#pragma once
#include "afxcmn.h"


// CGh0StrATDlg 对话框
class CGh0StrATDlg : public CDialog
{
// 构造
public:
	CGh0StrATDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GH0STRAT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void InitList();
	void AddItemOnline(CString IP,CString NAME,CString OS,CString CPU,CString PING);
	void AddItemLog(bool OK, CString MSG);
	CListCtrl mOnline;
	CListCtrl mLog;
};
