#pragma once


// NMFC_PASS 对话框

class NMFC_PASS : public CDialogEx
{
	DECLARE_DYNAMIC(NMFC_PASS)

public:
	NMFC_PASS(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~NMFC_PASS();

// 对话框数据
	enum { IDD = IDD_DIALOG_PASS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_password;
	afx_msg void OnClickedButtonOk();
};
