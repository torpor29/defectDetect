#pragma once


// NMFC_PASS �Ի���

class NMFC_PASS : public CDialogEx
{
	DECLARE_DYNAMIC(NMFC_PASS)

public:
	NMFC_PASS(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~NMFC_PASS();

// �Ի�������
	enum { IDD = IDD_DIALOG_PASS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_password;
	afx_msg void OnClickedButtonOk();
};
