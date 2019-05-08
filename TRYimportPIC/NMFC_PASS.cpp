// NMFC_PASS.cpp : 实现文件
//

#include "stdafx.h"
#include "TRYimportPIC.h"
#include "NMFC_PASS.h"
#include "afxdialogex.h"
#include "NMFC_SETTING.h"
#include "TRYimportPICDlg.h"


// NMFC_PASS 对话框

IMPLEMENT_DYNAMIC(NMFC_PASS, CDialogEx)

NMFC_PASS::NMFC_PASS(CWnd* pParent /*=NULL*/)
	: CDialogEx(NMFC_PASS::IDD, pParent)
	, m_password(_T(""))
{

}

NMFC_PASS::~NMFC_PASS()
{
}

void NMFC_PASS::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_password);
}


BEGIN_MESSAGE_MAP(NMFC_PASS, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OK, &NMFC_PASS::OnClickedButtonOk)
END_MESSAGE_MAP()


// NMFC_PASS 消息处理程序


void NMFC_PASS::OnClickedButtonOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	if (m_password == "123456"){
		NMFC_SETTING *m_SetDlg = new NMFC_SETTING(this);
		m_SetDlg->Create(IDD_DIALOG_SETTING);
		m_SetDlg->ShowWindow(SW_SHOW);
		if (p_checkbacklight)
		((CButton *)m_SetDlg->GetDlgItem(IDC_CHECK_BACKLIGHT))->SetCheck(BST_CHECKED);
		if (p_checkballerramin)
		((CButton *)m_SetDlg->GetDlgItem(IDC_CHECK_BALLERRAMIN))->SetCheck(BST_CHECKED);
		if (p_checkcirlight)

		((CButton *)m_SetDlg->GetDlgItem(IDC_CHECK_CIRLIGHT))->SetCheck(BST_CHECKED);
		if (p_checkcirratio)

		((CButton *)m_SetDlg->GetDlgItem(IDC_CHECK_CIRRATIO))->SetCheck(BST_CHECKED);
		if (p_checkneeamin)

		((CButton *)m_SetDlg->GetDlgItem(IDC_CHECK_NEEAMIN))->SetCheck(BST_CHECKED);
		if (p_checkneegreymin)

		((CButton *)m_SetDlg->GetDlgItem(IDC_CHECK_NEEGREYMIN))->SetCheck(BST_CHECKED);
		if (p_checkouterramin)

		((CButton *)m_SetDlg->GetDlgItem(IDC_CHECK_OUTERRAMIN))->SetCheck(BST_CHECKED);
		if (p_checkoutserramin)

		((CButton *)m_SetDlg->GetDlgItem(IDC_CHECK_OUTSERRAMIN))->SetCheck(BST_CHECKED);
		if (p_checkNGimg)
			((CButton *)m_SetDlg->GetDlgItem(IDC_CHECK_SAVENGIMG))->SetCheck(BST_CHECKED);

		if (p_checksave)
			((CButton *)m_SetDlg->GetDlgItem(IDC_CHECK_SaveIMG))->SetCheck(BST_CHECKED);
		NMFC_PASS::OnOK();
	}
}
