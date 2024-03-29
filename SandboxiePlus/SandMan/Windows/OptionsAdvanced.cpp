#include "stdafx.h"
#include "OptionsWindow.h"
#include "SandMan.h"
#include "SettingsWindow.h"
#include "../MiscHelpers/Common/Settings.h"
#include "../MiscHelpers/Common/Common.h"
#include "../MiscHelpers/Common/ComboInputDialog.h"
#include "../MiscHelpers/Common/SettingsWidgets.h"
#include "../AddonManager.h"
#include "Helpers/WinAdmin.h"

void COptionsWindow::CreateAdvanced()
{
	connect(ui.chkNoPanic, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));

	connect(ui.chkPreferExternalManifest, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));
	connect(ui.chkElevateCreateProcessFix, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));
	connect(ui.chkNoWindowRename, SIGNAL(clicked(bool)), this, SLOT(OnNoWindowRename()));
	connect(ui.chkNestedJobs, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));
	connect(ui.chkUseSbieDeskHack, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));
	connect(ui.chkUseSbieWndStation, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));

	connect(ui.chkAddToJob, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));
	connect(ui.chkProtectSCM, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));
	connect(ui.chkRestrictServices, SIGNAL(clicked(bool)), this, SLOT(OnSysSvcChanged()));
	connect(ui.chkElevateRpcss, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));
	connect(ui.chkProtectSystem, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));
	connect(ui.chkDropPrivileges, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));

	connect(ui.chkOpenCOM, SIGNAL(clicked(bool)), this, SLOT(OnOpenCOM()));
	connect(ui.chkComTimeout, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));

	connect(ui.chkNoSecurityIsolation, SIGNAL(clicked(bool)), this, SLOT(OnIsolationChanged()));
	connect(ui.chkNoSecurityFiltering, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));

	connect(ui.chkOpenDevCMApi, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));
	//connect(ui.chkOpenLsaSSPI, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));
	connect(ui.chkOpenSamEndpoint, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));
	connect(ui.chkOpenLsaEndpoint, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));

	connect(ui.chkSbieLogon, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));


	m_AdvOptions.insert("UseWin32kHooks",				SAdvOption{eSpec, QStringList() << "y" << "n", tr("Enable the use of win32 hooks for selected processes. Note: You need to enable win32k syscall hook support globally first.")});
	m_AdvOptions.insert("EnableMiniDump",				SAdvOption{eSpec, QStringList() << "y" << "n", tr("Enable crash dump creation in the sandbox folder")});
	m_AdvOptions.insert("ApplyElevateCreateProcessFix", SAdvOption{eOnlySpec, QStringList() << "y" << "n", tr("Always use ElevateCreateProcess fix, as sometimes applied by the Program Compatibility Assistant.")});
	m_AdvOptions.insert("PreferExternalManifest",		SAdvOption{eOnlySpec, QStringList() << "y" << "n", tr("")});
	m_AdvOptions.insert("ExternalManifestHack",			SAdvOption{eSpec, QStringList() << "y" << "n", tr("Enable special inconsistent PreferExternalManifest behaviour, as needed for some Edge fixes")});
	m_AdvOptions.insert("RpcMgmtSetComTimeout",			SAdvOption{eSpec, QStringList() << "n" << "y", tr("Set RpcMgmtSetComTimeout usage for specific processes")});
	m_AdvOptions.insert("CopyBlockDenyWrite",			SAdvOption{eSpec, QStringList() << "y" << "n", tr("Makes a write open call to a file that won't be copied fail instead of turning it read-only.")});
	m_AdvOptions.insert("UseSbieDeskHack",				SAdvOption{eOnlySpec, QStringList() << "n" << "y", tr("")});
	m_AdvOptions.insert("UseSbieWndStation",			SAdvOption{eOnlySpec, QStringList() << "n" << "y", tr("")});
	m_AdvOptions.insert("FakeAdminRights",				SAdvOption{eOnlySpec, QStringList() << "y" << "n", tr("Make specified processes think they have admin permissions.")});
	m_AdvOptions.insert("WaitForDebugger",				SAdvOption{eOnlySpec, QStringList() << "y" << "n", tr("Force specified processes to wait for a debugger to attach.")});
	m_AdvOptions.insert("BoxNameTitle",					SAdvOption{eOnlySpec, QStringList() << "y" << "n" << "-", tr("")});
	m_AdvOptions.insert("FileRootPath",					SAdvOption{eNoSpec, QStringList(), tr("Sandbox file system root")});
	m_AdvOptions.insert("KeyRootPath",					SAdvOption{eNoSpec, QStringList(), tr("Sandbox registry root")});
	m_AdvOptions.insert("IpcRootPath",					SAdvOption{eNoSpec, QStringList(), tr("Sandbox ipc root")});

		

	connect(ui.btnAddOption, SIGNAL(clicked(bool)), this, SLOT(OnAddOption()));
	connect(ui.chkShowOptionsTmpl, SIGNAL(clicked(bool)), this, SLOT(OnShowOptionTmpl()));
	connect(ui.btnDelOption, SIGNAL(clicked(bool)), this, SLOT(OnDelOption()));

	//connect(ui.treeOptions, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(OnOptionItemClicked(QTreeWidgetItem*, int)));
	connect(ui.treeOptions, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(OnOptionItemDoubleClicked(QTreeWidgetItem*, int)));
	connect(ui.treeOptions, SIGNAL(itemSelectionChanged()), this, SLOT(OnOptionSelectionChanged()));
	connect(ui.treeOptions, SIGNAL(itemChanged(QTreeWidgetItem *, int)), this, SLOT(OnOptionChanged(QTreeWidgetItem *, int)));


	connect(ui.chkDisableMonitor, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));

	connect(ui.chkCallTrace, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));
	connect(ui.chkFileTrace, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));
	connect(ui.chkPipeTrace, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));
	connect(ui.chkKeyTrace, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));
	connect(ui.chkIpcTrace, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));
	connect(ui.chkGuiTrace, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));
	connect(ui.chkComTrace, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));
	connect(ui.chkNetFwTrace, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));
	connect(ui.chkHookTrace, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));
	connect(ui.chkDbgTrace, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));
	connect(ui.chkErrTrace, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));

	connect(ui.treeTriggers, SIGNAL(itemChanged(QTreeWidgetItem *, int)), this, SLOT(OnTriggerChanged(QTreeWidgetItem *, int)));
	connect(ui.btnAddAutoRun, SIGNAL(clicked(bool)), this, SLOT(OnAddAutoRun()));
	connect(ui.btnAddAutoSvc, SIGNAL(clicked(bool)), this, SLOT(OnAddAutoSvc()));
	connect(ui.btnAddAutoExec, SIGNAL(clicked(bool)), this, SLOT(OnAddAutoExec()));
	connect(ui.btnAddRecoveryCmd, SIGNAL(clicked(bool)), this, SLOT(OnAddRecoveryCheck()));
	connect(ui.btnAddDeleteCmd, SIGNAL(clicked(bool)), this, SLOT(OnAddDeleteCmd()));
	connect(ui.btnAddTerminateCmd, SIGNAL(clicked(bool)), this, SLOT(OnAddTerminateCmd()));
	connect(ui.btnDelAuto, SIGNAL(clicked(bool)), this, SLOT(OnDelAuto()));
	connect(ui.chkShowTriggersTmpl, SIGNAL(clicked(bool)), this, SLOT(OnShowTriggersTmpl()));

	connect(ui.chkHideOtherBoxes, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));
	connect(ui.btnAddProcess, SIGNAL(clicked(bool)), this, SLOT(OnAddProcess()));
	connect(ui.btnDelProcess, SIGNAL(clicked(bool)), this, SLOT(OnDelProcess()));
	connect(ui.chkShowHiddenProcTmpl, SIGNAL(clicked(bool)), this, SLOT(OnShowHiddenProcTmpl()));

	connect(ui.btnHostProcessAllow, SIGNAL(clicked(bool)), this, SLOT(OnHostProcessAllow()));
	connect(ui.btnHostProcessDeny, SIGNAL(clicked(bool)), this, SLOT(OnHostProcessDeny()));
	connect(ui.btnDelHostProcess, SIGNAL(clicked(bool)), this, SLOT(OnDelHostProcess()));
	connect(ui.chkShowHostProcTmpl, SIGNAL(clicked(bool)), this, SLOT(OnShowHostProcTmpl()));
	connect(ui.chkConfidential, SIGNAL(clicked(bool)), this, SLOT(OnConfidentialChanged()));
	connect(ui.chkLessConfidential, SIGNAL(clicked(bool)), this, SLOT(OnLessConfidentialChanged()));
	connect(ui.chkProtectWindow, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));
	connect(ui.chkBlockCapture, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));
	connect(ui.chkNotifyProtect, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));

	connect(ui.treeInjectDll, SIGNAL(itemChanged(QTreeWidgetItem *, int)), this, SLOT(OnToggleInjectDll(QTreeWidgetItem *, int)));
	connect(ui.treeInjectDll, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(OnDblClickInjedtDll(QTreeWidgetItem*, int)));

	connect(ui.chkHostProtect, SIGNAL(clicked(bool)), this, SLOT(OnHostProtectChanged()));
	connect(ui.chkHostProtectMsg, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));

	connect(ui.btnAddUser, SIGNAL(clicked(bool)), this, SLOT(OnAddUser()));
	connect(ui.btnDelUser, SIGNAL(clicked(bool)), this, SLOT(OnDelUser()));
	connect(ui.chkMonitorAdminOnly, SIGNAL(clicked(bool)), this, SLOT(OnAdvancedChanged()));
}


void COptionsWindow::LoadAdvanced()
{
	ui.chkNoPanic->setChecked(m_pBox->GetBool("ExcludeFromTerminateAll", false));

	ui.chkPreferExternalManifest->setChecked(m_pBox->GetBool("PreferExternalManifest", false));
	ui.chkElevateCreateProcessFix->setChecked(m_pBox->GetBool("ApplyElevateCreateProcessFix", false));

	ui.chkNestedJobs->setChecked(m_pBox->GetBool("AllowBoxedJobs", false));
	ui.chkUseSbieDeskHack->setChecked(m_pBox->GetBool("UseSbieDeskHack", true));
	ui.chkUseSbieWndStation->setChecked(m_pBox->GetBool("UseSbieWndStation", true));

	ui.chkAddToJob->setChecked(!m_pBox->GetBool("NoAddProcessToJob", false));
	ui.chkProtectSCM->setChecked(!m_pBox->GetBool("UnrestrictedSCM", false));
	ui.chkRestrictServices->setChecked(!m_pBox->GetBool("RunServicesAsSystem", false));
	ui.chkElevateRpcss->setChecked(m_pBox->GetBool("RunRpcssAsSystem", false));
	ui.chkProtectSystem->setChecked(!m_pBox->GetBool("ExposeBoxedSystem", false));
	ui.chkDropPrivileges->setChecked(m_pBox->GetBool("StripSystemPrivileges", true));

	CheckOpenCOM();
	ui.chkComTimeout->setChecked(!m_pBox->GetBool("RpcMgmtSetComTimeout", true));

	ui.chkNoSecurityIsolation->setChecked(m_pBox->GetBool("NoSecurityIsolation", false));
	ui.chkNoSecurityFiltering->setChecked(m_pBox->GetBool("NoSecurityFiltering", false));

	ui.chkOpenDevCMApi->setChecked(m_pBox->GetBool("OpenDevCMApi", false));
	//ui.chkOpenLsaSSPI->setChecked(!m_pBox->GetBool("BlockPassword", true)); // OpenLsaSSPI
	ui.chkOpenSamEndpoint->setChecked(m_pBox->GetBool("OpenSamEndpoint", false));
	ui.chkOpenLsaEndpoint->setChecked(m_pBox->GetBool("OpenLsaEndpoint", false));

	ui.treeInjectDll->clear();
	QStringList InjectDll = m_pBox->GetTextList("InjectDll", false);
	QStringList InjectDll64 = m_pBox->GetTextList("InjectDll64", false);
#ifdef _M_ARM64
	QStringList InjectDllARM64 = m_pBox->GetTextList("InjectDllARM64", false);
#endif
	foreach(const CAddonInfoPtr pAddon, theGUI->GetAddonManager()->GetAddons()) {
		if (!pAddon->Installed)
			continue;
		QVariantMap InjectDlls = pAddon->Data["injectDlls"].toMap();
		if (!InjectDlls.isEmpty()) 
		{
			int Found = 0;
			int Count = 0;
			foreach(const QString & Key, InjectDlls.keys()) {
				QStringList List;
				if (Key == "x64")		List = InjectDll64;
				else if (Key == "x86")	List = InjectDll;
#ifdef _M_ARM64
				else if (Key == "a64")	List = InjectDllARM64;
#endif
				else
					continue;
				Count++;
				foreach(const QString & DllPath, List) {
					if (DllPath.endsWith(InjectDlls[Key].toString(), Qt::CaseInsensitive)) {
						Found++;
						break;
					}
				}
			}

			QTreeWidgetItem* pItem = new QTreeWidgetItem();
			pItem->setData(0, Qt::UserRole, pAddon->Id);
			pItem->setText(0, pAddon->GetLocalizedEntry("name"));
			if (Found == Count) {
				pItem->setCheckState(0, Qt::Checked);
				pItem->setData(0, Qt::UserRole + 1, Qt::Checked);
			} else if (Found > 0) {
				pItem->setCheckState(0, Qt::PartiallyChecked);
				pItem->setData(0, Qt::UserRole + 1, Qt::PartiallyChecked);
			}
			else {
				pItem->setCheckState(0, Qt::Unchecked);
				pItem->setData(0, Qt::UserRole + 1, Qt::Unchecked);
			}
			pItem->setText(1, pAddon->GetLocalizedEntry("description"));
			ui.treeInjectDll->addTopLevelItem(pItem);
		}
	}

	
	ui.chkHostProtect->setChecked(m_pBox->GetBool("ProtectHostImages", false));
	ui.chkHostProtectMsg->setEnabled(ui.chkHostProtect->isChecked());
	ui.chkHostProtectMsg->setChecked(m_pBox->GetBool("NotifyImageLoadDenied", true));

	ReadGlobalCheck(ui.chkSbieLogon, "SandboxieLogon", false);

	LoadOptionList();

	bool bGlobalNoMon = m_pBox->GetAPI()->GetGlobalSettings()->GetBool("DisableResourceMonitor", false);
	ui.chkDisableMonitor->setChecked(m_pBox->GetBool("DisableResourceMonitor", bGlobalNoMon));
	ReadAdvancedCheck("CallTrace", ui.chkCallTrace, "*");
	ReadAdvancedCheck("FileTrace", ui.chkFileTrace, "*");
	ReadAdvancedCheck("PipeTrace", ui.chkPipeTrace, "*");
	ReadAdvancedCheck("KeyTrace", ui.chkKeyTrace, "*");
	ReadAdvancedCheck("IpcTrace", ui.chkIpcTrace, "*");
	ReadAdvancedCheck("GuiTrace", ui.chkGuiTrace, "*");
	ReadAdvancedCheck("ClsidTrace", ui.chkComTrace, "*");
	ReadAdvancedCheck("NetFwTrace", ui.chkNetFwTrace, "*");
	ui.chkHookTrace->setChecked(m_pBox->GetBool("ApiTrace", false));
	ui.chkDbgTrace->setChecked(m_pBox->GetBool("DebugTrace", false));
	ui.chkErrTrace->setChecked(m_pBox->GetBool("ErrorTrace", false));

	// triggers
	ui.treeTriggers->clear();
	foreach(const QString & Value, m_pBox->GetTextList("StartProgram", m_Template))
		AddTriggerItem(Value, eOnStartCmd);
	foreach(const QString & Value, m_pBox->GetTextList("StartService", m_Template))
		AddTriggerItem(Value, eOnStartSvc);
	foreach(const QString & Value, m_pBox->GetTextList("AutoExec", m_Template))
		AddTriggerItem(Value, eAutoExec);
	foreach(const QString & Value, m_pBox->GetTextList("OnFileRecovery", m_Template))
		AddTriggerItem(Value, eRecoveryCheck);
	foreach(const QString & Value, m_pBox->GetTextList("OnBoxDelete", m_Template))
		AddTriggerItem(Value, eDeleteCmd);
	foreach(const QString & Value, m_pBox->GetTextList("OnBoxTerminate", m_Template))
		AddTriggerItem(Value, eTerminateCmd);

	ShowTriggersTmpl();
	//

	ui.chkHideOtherBoxes->setChecked(m_pBox->GetBool("HideOtherBoxes", true));
	
	ui.treeHideProc->clear();
	foreach(const QString& Value, m_pBox->GetTextList("HideHostProcess", m_Template))
		AddHiddenProcEntry(Value);
	ShowHiddenProcTmpl();

	ui.treeHostProc->clear();
	foreach(const QString & Value, m_pBox->GetTextList("DenyHostAccess", m_Template)) {
		StrPair NameVal = Split2(Value, ",");
		if (NameVal.second.isEmpty()) {
			NameVal.second = NameVal.first;
			NameVal.first = "*";
		}
		AddHostProcEntry(NameVal.first, NameVal.second.left(1).toLower() == "y");
	}
	ShowHostProcTmpl();

	ui.chkConfidential->setChecked(m_pBox->GetBool("ConfidentialBox", false));
	ui.chkLessConfidential->setEnabled(ui.chkConfidential->isChecked());
	ui.chkLessConfidential->setChecked(m_BoxTemplates.contains("LessConfidentialBox"));
	ui.chkNotifyProtect->setChecked(m_pBox->GetBool("NotifyBoxProtected", false));

	ui.chkProtectWindow->setChecked(m_pBox->GetBool("IsProtectScreen"));
	QString str = m_pBox->GetText("OpenWinClass", "");
	ui.chkBlockCapture->setChecked(m_pBox->GetBool("IsBlockCapture") && QString::compare(str, "*") != 0);
	ui.chkBlockCapture->setCheckable(QString::compare(str, "*") != 0);

	/*ui.chkLockWhenClose->setChecked(m_pBox->GetBool("LockWhenClose", false));
	ui.chkLockWhenClose->setCheckable(m_pBox->GetBool("UseFileImage", false));
	ui.chkLockWhenClose->setEnabled(m_pBox->GetBool("UseFileImage", false));
	*/
	
	QStringList Users = m_pBox->GetText("Enabled").split(",");
	ui.lstUsers->clear();
	if (Users.count() > 1)
		ui.lstUsers->addItems(Users.mid(1));
	ui.chkMonitorAdminOnly->setChecked(m_pBox->GetBool("MonitorAdminOnly", false));

	UpdateBoxIsolation();
	OnSysSvcChanged();

	ui.chkOpenCredentials->setEnabled(!ui.chkOpenProtectedStorage->isChecked());
	if (!ui.chkOpenCredentials->isEnabled()) ui.chkOpenCredentials->setChecked(true);

	m_AdvancedChanged = false;
}

void COptionsWindow::OnPSTChanged()
{
	if(!ui.chkOpenProtectedStorage->isChecked())
		ui.chkOpenCredentials->setChecked(m_pBox->GetBool("OpenCredentials", false));

	OnGeneralChanged();
}

void COptionsWindow::ShowTriggersTmpl(bool bUpdate)
{
	if (ui.chkShowTriggersTmpl->isChecked())
	{
		foreach(const QString& Template, m_pBox->GetTemplates())
		{
			foreach(const QString & Value, m_pBox->GetTextListTmpl("StartProgram", Template))
				AddTriggerItem(Value, eOnStartCmd, Template);
			foreach(const QString & Value, m_pBox->GetTextListTmpl("StartService", Template))
				AddTriggerItem(Value, eOnStartSvc, Template);
			foreach(const QString & Value, m_pBox->GetTextListTmpl("AutoExec", Template))
				AddTriggerItem(Value, eAutoExec, Template);
			foreach(const QString & Value, m_pBox->GetTextListTmpl("OnFileRecovery", Template))
				AddTriggerItem(Value, eRecoveryCheck, Template);
			foreach(const QString & Value, m_pBox->GetTextListTmpl("OnBoxDelete", Template))
				AddTriggerItem(Value, eDeleteCmd, Template);
			foreach(const QString & Value, m_pBox->GetTextListTmpl("OnBoxTerminate", Template))
				AddTriggerItem(Value, eTerminateCmd, Template);
		}
	}
	else if (bUpdate)
	{
		for (int i = 0; i < ui.treeTriggers->topLevelItemCount(); )
		{
			QTreeWidgetItem* pItem = ui.treeTriggers->topLevelItem(i);
			int Type = pItem->data(0, Qt::UserRole).toInt();
			if (Type == -1) {
				delete pItem;
				continue; // entry from template
			}
			i++;
		}
	}
}

void COptionsWindow::SaveAdvanced()
{
	WriteAdvancedCheck(ui.chkNoPanic, "ExcludeFromTerminateAll", "y", "");

	WriteAdvancedCheck(ui.chkPreferExternalManifest, "PreferExternalManifest", "y", "");
	WriteAdvancedCheck(ui.chkElevateCreateProcessFix, "ApplyElevateCreateProcessFix", "y", "");

	WriteAdvancedCheck(ui.chkUseSbieDeskHack, "UseSbieDeskHack", "", "n");
	WriteAdvancedCheck(ui.chkUseSbieWndStation, "UseSbieWndStation", "", "n");

	WriteAdvancedCheck(ui.chkAddToJob, "NoAddProcessToJob", "", "y");
	WriteAdvancedCheck(ui.chkProtectSCM, "UnrestrictedSCM", "", "y");
	WriteAdvancedCheck(ui.chkNestedJobs, "AllowBoxedJobs", "y", "");
	WriteAdvancedCheck(ui.chkRestrictServices, "RunServicesAsSystem", "", "y");
	WriteAdvancedCheck(ui.chkElevateRpcss, "RunRpcssAsSystem", "y", "");
	WriteAdvancedCheck(ui.chkProtectSystem, "ExposeBoxedSystem", "", "y");
	WriteAdvancedCheck(ui.chkDropPrivileges, "StripSystemPrivileges", "", "n");

	WriteAdvancedCheck(ui.chkComTimeout, "RpcMgmtSetComTimeout", "n", "");

	WriteAdvancedCheck(ui.chkNoSecurityIsolation, "NoSecurityIsolation", "y", "");
	WriteAdvancedCheck(ui.chkNoSecurityFiltering, "NoSecurityFiltering", "y", "");

	WriteAdvancedCheck(ui.chkOpenDevCMApi, "OpenDevCMApi", "y", "");
	//WriteAdvancedCheck(ui.chkOpenLsaSSPI, "BlockPassword", "n", ""); // OpenLsaSSPI
	WriteAdvancedCheck(ui.chkOpenSamEndpoint, "OpenSamEndpoint", "y", "");
	WriteAdvancedCheck(ui.chkOpenLsaEndpoint, "OpenLsaEndpoint", "y", "");

	QStringList InjectDll = m_pBox->GetTextList("InjectDll", false);
	QStringList InjectDll64 = m_pBox->GetTextList("InjectDll64", false);
#ifdef _M_ARM64
	QStringList InjectDllARM64 = m_pBox->GetTextList("InjectDllARM64", false);
#endif
	for (int i = 0; i < ui.treeInjectDll->topLevelItemCount(); i++) {
		QTreeWidgetItem* pItem = ui.treeInjectDll->topLevelItem(i);
		CAddonPtr pAddon = theGUI->GetAddonManager()->GetAddon(pItem->data(0, Qt::UserRole).toString());
		if (pAddon && pItem->checkState(0) != Qt::PartiallyChecked && pItem->checkState(0) != pItem->data(0, Qt::UserRole + 1))
		{
			QVariantMap InjectDlls = pAddon->Data["injectDlls"].toMap();
			foreach(const QString & Key, InjectDlls.keys()) {
				QStringList* pList;
				if (Key == "x64")		pList = &InjectDll64;
				else if (Key == "x86")	pList = &InjectDll;
#ifdef _M_ARM64
				else if (Key == "a64")	pList = &InjectDllARM64;
#endif
				else
					continue;

				// remove old entries
				for (int i = 0; i < pList->size(); i++) {
					if (pList->at(i).endsWith(InjectDlls[Key].toString(), Qt::CaseInsensitive))
						pList->removeAt(i--);
				}

				// add new entries
				if (pItem->checkState(0) == Qt::Checked)
					pList->append(pAddon->Data["installPath"].toString() + InjectDlls[Key].toString());
			}
		}
	}
	m_pBox->UpdateTextList("InjectDll", InjectDll, false);
	m_pBox->UpdateTextList("InjectDll64", InjectDll64, false);
#ifdef _M_ARM64
	m_pBox->UpdateTextList("InjectDllARM64", InjectDllARM64, false);
#endif

	WriteAdvancedCheck(ui.chkHostProtect, "ProtectHostImages", "y", "");
	WriteAdvancedCheck(ui.chkHostProtectMsg, "NotifyImageLoadDenied", "", "n");


	WriteGlobalCheck(ui.chkSbieLogon, "SandboxieLogon", false);

	SaveOptionList();

	bool bGlobalNoMon = m_pBox->GetAPI()->GetGlobalSettings()->GetBool("DisableResourceMonitor", false);
	WriteAdvancedCheck(ui.chkDisableMonitor, "DisableResourceMonitor", bGlobalNoMon ? "" : "y", bGlobalNoMon ? "n" : "");
	WriteAdvancedCheck(ui.chkCallTrace, "CallTrace", "*");
	WriteAdvancedCheck(ui.chkFileTrace, "FileTrace", "*");
	WriteAdvancedCheck(ui.chkPipeTrace, "PipeTrace", "*");
	WriteAdvancedCheck(ui.chkKeyTrace, "KeyTrace", "*");
	WriteAdvancedCheck(ui.chkIpcTrace, "IpcTrace", "*");
	WriteAdvancedCheck(ui.chkGuiTrace, "GuiTrace", "*");
	WriteAdvancedCheck(ui.chkComTrace, "ClsidTrace", "*");
	WriteAdvancedCheck(ui.chkNetFwTrace, "NetFwTrace", "*");
	WriteAdvancedCheck(ui.chkHookTrace, "ApiTrace", "y");
	WriteAdvancedCheck(ui.chkDbgTrace, "DebugTrace", "y");
	WriteAdvancedCheck(ui.chkErrTrace, "ErrorTrace", "y");

	// triggers
	QStringList StartProgram;
	QStringList StartService;
	QStringList RecoveryCheck;
	QStringList DeleteCommand;
	QStringList AutoExec;
	QStringList TerminateCommand;
	for (int i = 0; i < ui.treeTriggers->topLevelItemCount(); i++) {
		QTreeWidgetItem* pItem = ui.treeTriggers->topLevelItem(i);
		switch (pItem->data(0, Qt::UserRole).toInt())
		{
		case eOnStartCmd:	StartProgram.append(pItem->text(2)); break;
		case eOnStartSvc:	StartService.append(pItem->text(2)); break;
		case eAutoExec:		AutoExec.append(pItem->text(2)); break;
		case eRecoveryCheck:		RecoveryCheck.append(pItem->text(2)); break;
		case eDeleteCmd:	DeleteCommand.append(pItem->text(2)); break;
		case eTerminateCmd:		TerminateCommand.append(pItem->text(2)); break;
		}
	}
	WriteTextList("StartProgram", StartProgram);
	WriteTextList("StartService", StartService);
	WriteTextList("AutoExec", AutoExec);
	WriteTextList("OnFileRecovery", RecoveryCheck);
	WriteTextList("OnBoxDelete", DeleteCommand);
	WriteTextList("OnBoxTerminate", TerminateCommand);
	//


	WriteAdvancedCheck(ui.chkHideOtherBoxes, "HideOtherBoxes", "", "n");

	QStringList HideProcesses;
	for (int i = 0; i < ui.treeHideProc->topLevelItemCount(); i++)
	{
		QTreeWidgetItem* pItem = ui.treeHideProc->topLevelItem(i);
		int Type = pItem->data(0, Qt::UserRole).toInt();
		if (Type == -1)
			continue; // entry from template
		HideProcesses.append(pItem->text(0)); 
	}
	WriteTextList("HideHostProcess", HideProcesses);

	QStringList DenyHostProcesses;
	for (int i = 0; i < ui.treeHostProc->topLevelItemCount(); i++)
	{
		QTreeWidgetItem* pItem = ui.treeHostProc->topLevelItem(i);
		int Type = pItem->data(0, Qt::UserRole).toInt();
		if (Type == -1)
			continue; // entry from template
		DenyHostProcesses.append(pItem->text(0) + "," + (pItem->data(1, Qt::UserRole).toBool() ? "y" : "n")); 
	}
	WriteTextList("DenyHostAccess", DenyHostProcesses);

	WriteAdvancedCheck(ui.chkConfidential, "ConfidentialBox", "y", "");
	WriteAdvancedCheck(ui.chkNotifyProtect, "NotifyBoxProtected", "y", "");

	WriteAdvancedCheck(ui.chkProtectWindow, "IsProtectScreen", "y", "n");
	WriteAdvancedCheck(ui.chkBlockCapture, "IsBlockCapture", "y", "n");
	//WriteAdvancedCheck(ui.chkLockWhenClose, "LockWhenClose", "y", "n");

	QStringList Users;
	for (int i = 0; i < ui.lstUsers->count(); i++)
		Users.append(ui.lstUsers->item(i)->text());
	WriteText("Enabled", Users.count() > 0 ? "y," + Users.join(",") : "y");
	WriteAdvancedCheck(ui.chkMonitorAdminOnly, "MonitorAdminOnly");

	m_AdvancedChanged = false;
}

void COptionsWindow::OnIsolationChanged()
{
	if (sender() == ui.chkNoSecurityIsolation) {
		// we can ignore chkNoSecurityFiltering as it requires chkNoSecurityIsolation
		if (ui.chkNoSecurityIsolation->isChecked())
			theGUI->CheckCertificate(this);
	}

	UpdateBoxIsolation();

	if (sender() == ui.chkNoSecurityIsolation && !ui.chkNoSecurityIsolation->isChecked()) {
		ui.chkCloseForBox->setChecked(m_pBox->GetBool("AlwaysCloseForBoxed", true));
		ui.chkNoOpenForBox->setChecked(m_pBox->GetBool("DontOpenForBoxed", true));
	}

	m_AdvancedChanged = true;
	OnOptChanged();
}

void COptionsWindow::UpdateBoxIsolation()
{
	ui.chkNoSecurityFiltering->setEnabled(ui.chkNoSecurityIsolation->isChecked());

	ui.chkAddToJob->setEnabled(!ui.chkNoSecurityIsolation->isChecked());
	ui.chkNestedJobs->setEnabled(!ui.chkNoSecurityIsolation->isChecked());

	ui.chkOpenDevCMApi->setEnabled(!ui.chkNoSecurityIsolation->isChecked());
	ui.chkOpenSamEndpoint->setEnabled(!ui.chkNoSecurityIsolation->isChecked());
	ui.chkOpenLsaEndpoint->setEnabled(!ui.chkNoSecurityIsolation->isChecked());


	ui.chkRawDiskRead->setEnabled(!ui.chkNoSecurityIsolation->isChecked()); //  without isolation only user mode
	ui.chkRawDiskNotify->setEnabled(!ui.chkNoSecurityIsolation->isChecked());

	ui.chkBlockNetShare->setEnabled(!ui.chkNoSecurityFiltering->isChecked());

	ui.chkBlockSpooler->setEnabled(!ui.chkNoSecurityIsolation->isChecked());
	ui.chkOpenSpooler->setEnabled(!ui.chkBlockSpooler->isChecked() && !ui.chkNoSecurityIsolation->isChecked());
	ui.chkPrintToFile->setEnabled(!ui.chkBlockSpooler->isChecked() && !ui.chkNoSecurityFiltering->isChecked());

	ui.chkCloseClipBoard->setEnabled(!ui.chkNoSecurityIsolation->isChecked());
	ui.chkVmRead->setEnabled(!ui.chkNoSecurityIsolation->isChecked());

	//ui.chkBlockCapture->setEnabled(!ui.chkNoSecurityIsolation->isChecked());
	ui.chkProtectPower->setEnabled(!ui.chkNoSecurityIsolation->isChecked());

	ui.chkCloseForBox->setEnabled(!ui.chkNoSecurityIsolation->isChecked());
	ui.chkNoOpenForBox->setEnabled(!ui.chkNoSecurityIsolation->isChecked());

	if (ui.chkNoSecurityIsolation->isChecked()) {
		ui.chkCloseForBox->setChecked(false);
		ui.chkNoOpenForBox->setChecked(false);
	}
}

void COptionsWindow::OnSysSvcChanged()
{
	ui.chkElevateRpcss->setDisabled(ui.chkNoSecurityIsolation->isChecked() && (!ui.chkRestrictServices->isChecked() || ui.chkMsiExemptions->isChecked()));
	m_AdvancedChanged = true;
	OnOptChanged();
}

void COptionsWindow::OnConfidentialChanged()
{
	ui.chkLessConfidential->setEnabled(ui.chkConfidential->isChecked());
	OnAdvancedChanged();
}

void COptionsWindow::OnLessConfidentialChanged()
{
	SetTemplate("LessConfidentialBox", ui.chkLessConfidential->isChecked());
}

void COptionsWindow::OnAdvancedChanged()
{
	m_AdvancedChanged = true;
	OnOptChanged();
}

void COptionsWindow::CheckOpenCOM()
{
	bool bComIpcOpen = IsAccessEntrySet(eIPC, "", eOpen, "\\RPC Control\\epmapper") || IsAccessEntrySet(eIPC, "", eOpen, "*");
	if(bComIpcOpen)
		ui.chkOpenCOM->setChecked(!m_BoxTemplates.contains("BoxedCOM"));
	else
		ui.chkOpenCOM->setChecked(m_BoxTemplates.contains("OpenCOM"));
}

void COptionsWindow::OnOpenCOM()
{
	bool bComIpcOpen = IsAccessEntrySet(eIPC, "", eOpen, "\\RPC Control\\epmapper") || IsAccessEntrySet(eIPC, "", eOpen, "*");
	SetTemplate("OpenCOM", !bComIpcOpen && ui.chkOpenCOM->isChecked());
	SetTemplate("BoxedCOM", bComIpcOpen && !ui.chkOpenCOM->isChecked());
}

void COptionsWindow::OnNoWindowRename()
{
	if (ui.chkNoWindowRename->isChecked())
		SetAccessEntry(eWnd, "", eOpen, "#");
	else
		DelAccessEntry(eWnd, "", eOpen, "#");
}

void COptionsWindow::OnToggleInjectDll(QTreeWidgetItem* pItem, int Column)
{
	OnAdvancedChanged();
}

void COptionsWindow::OnDblClickInjedtDll(QTreeWidgetItem* pItem, int Column)
{
	CAddonPtr pAddon = theGUI->GetAddonManager()->GetAddon(pItem->data(0, Qt::UserRole).toString());
	if (!pAddon || pAddon->Data["configFile"].toString().isEmpty())
		return;

	theGUI->EditIni(theAPI->GetSbiePath() + pAddon->Data["installPath"].toString() + pAddon->Data["configFile"].toString());
}

void COptionsWindow::OnHostProtectChanged()
{
	ui.chkHostProtectMsg->setEnabled(ui.chkHostProtect->isChecked());
	OnAdvancedChanged();
}

// options
void COptionsWindow::LoadOptionList()
{
	if (!ui.treeOptions) return;

	ui.treeOptions->clear();
	foreach(const QString& Name, m_AdvOptions.keys()) {
		foreach(const QString & Value, m_pBox->GetTextList(Name, m_Template)) {
			QStringList Values = Value.split(",");
			if (Values.count() >= 2) 
				AddOptionEntry(Name, Values[0], Values[1]);
			else if(m_AdvOptions[Name].ProcSpec != eOnlySpec) // eOnlySpec shows only process specific entries, no global once
				AddOptionEntry(Name, "", Values[0]);
		}
	}

	LoadOptionListTmpl();
}

void COptionsWindow::LoadOptionListTmpl(bool bUpdate)
{
	if (ui.chkShowOptionsTmpl->isChecked())
	{
		foreach(const QString& Template, m_pBox->GetTemplates())
		{
			foreach(const QString& Name, m_AdvOptions.keys()) {
				foreach(const QString & Value, m_pBox->GetTextListTmpl(Name, Template)) {
					QStringList Values = Value.split(",");
					if (Values.count() >= 2) 
						AddOptionEntry(Name, Values[0], Values[1], Template);
					else // all programs
						AddOptionEntry(Name, "", Values[0], Template);
				}
			}
		}
	}
	else if (bUpdate)
	{
		for (int i = 0; i < ui.treeOptions->topLevelItemCount(); )
		{
			QTreeWidgetItem* pItem = ui.treeOptions->topLevelItem(i);
			QString Name = pItem->data(0, Qt::UserRole).toString();
			if (Name.isEmpty()) {
				delete pItem;
				continue; // entry from template
			}
			i++;
		}
	}
}

void COptionsWindow::SaveOptionList()
{
	CloseOptionEdit(true);

	if (!ui.treeOptions) return;

	QMap<QString, QList<QString>> OptionMap;

	// cache unlisted set eOnlySpec global presets
	foreach(const QString& Name, m_AdvOptions.keys()) {
		foreach(const QString & Value, m_pBox->GetTextList(Name, m_Template)) {
			QStringList Values = Value.split(",");
			if (Values.count() < 2 && m_AdvOptions[Name].ProcSpec == eOnlySpec)
				OptionMap[Name].append(Values[0]);
		}
	}

	for (int i = 0; i < ui.treeOptions->topLevelItemCount(); i++)
	{
		QTreeWidgetItem* pItem = ui.treeOptions->topLevelItem(i);
		QString Name = pItem->data(0, Qt::UserRole).toString();
		if (Name.isEmpty())
			continue; // entry from template
		QString Program = pItem->data(1, Qt::UserRole).toString();
		QString Value = pItem->data(2, Qt::UserRole).toString();
		if (!Program.isEmpty())
			Value.prepend(Program + ",");

		OptionMap[Name].append(Value);
	}

	foreach(const QString & Key, m_AdvOptions.keys()) {
		WriteTextList(Key, OptionMap[Key]);
	}
}

void COptionsWindow::AddOptionEntry(const QString& Name, QString Program, const QString& Value, const QString& Template)
{
	QTreeWidgetItem* pItem = new QTreeWidgetItem();

	pItem->setText(0, Name + (Template.isEmpty() ? "" : " (" + Template + ")"));
	pItem->setData(0, Qt::UserRole, !Template.isEmpty() ? "" : Name);

	pItem->setData(1, Qt::UserRole, Program);
	bool bAll = Program.isEmpty();
	if (bAll)
		Program = tr("All Programs");
	bool Not = Program.left(1) == "!";
	if (Not)
		Program.remove(0, 1);
	//if (Program.left(1) == "<")
	//	Program = tr("Group: %1").arg(Program.mid(1, Program.length() - 2));
	//else if(!bAll)
	//	m_Programs.insert(Program);
	pItem->setText(1, (Not ? "NOT " : "") + Program);
	
	pItem->setText(2, Value);
	pItem->setData(2, Qt::UserRole, Value);

	//if(Template.isEmpty())
	//	pItem->setCheckState(0, disabled ? Qt::Unchecked : Qt::Checked);
	ui.treeOptions->addTopLevelItem(pItem);
}

void COptionsWindow::OnAddOption()
{ 
	CComboInputDialog progDialog(this);
	progDialog.setText(tr("Add special option:"));
	progDialog.setEditable(true);

	foreach(const QString & Name, m_AdvOptions.keys())
		progDialog.addItem(Name, Name, m_AdvOptions[Name].Description);

	progDialog.setValue("EnableMiniDump");

	if (!progDialog.exec())
		return;

	QString Name = progDialog.value(); 

	AddOptionEntry(Name, "", "");
}

void COptionsWindow::OnDelOption()
{
	DeleteAccessEntry(ui.treeOptions->currentItem());
	m_AdvancedChanged = true;
	OnOptChanged();
}

void COptionsWindow::OnOptionItemDoubleClicked(QTreeWidgetItem* pItem, int Column)
{
	//if (Column == 0)
	//	return;

	QString Name = pItem->data(0, Qt::UserRole).toString();
	if (Name.isEmpty()) {
		QMessageBox::warning(this, "SandboxiePlus", tr("Template values can not be edited."));
		return;
	}

	QString Program = pItem->data(1, Qt::UserRole).toString();

	if (m_AdvOptions[Name].ProcSpec != eNoSpec)
	{
		QWidget* pProgram = new QWidget();
		pProgram->setAutoFillBackground(true);
		QHBoxLayout* pLayout = new QHBoxLayout();
		pLayout->setContentsMargins(0,0,0,0);
		pLayout->setSpacing(0);
		pProgram->setLayout(pLayout);
		QToolButton* pNot = new QToolButton(pProgram);
		pNot->setText("!");
		pNot->setCheckable(true);
		if (Program.left(1) == "!") {
			pNot->setChecked(true);
			Program.remove(0, 1);
		}
		pLayout->addWidget(pNot);
		QComboBox* pCombo = new QComboBox(pProgram);
		if (m_AdvOptions[Name].ProcSpec != eOnlySpec)
			pCombo->addItem(tr("All Programs"), "");

		//foreach(const QString Group, GetCurrentGroups()){
		//	QString GroupName = Group.mid(1, Group.length() - 2);
		//	pCombo->addItem(tr("Group: %1").arg(GroupName), Group);
		//}

		foreach(const QString & Name, m_Programs)
			pCombo->addItem(Name, Name);


		pCombo->setEditable(true);
		int Index = pCombo->findData(Program);
		pCombo->setCurrentIndex(Index);
		if (Index == -1)
			pCombo->setCurrentText(Program);
		pLayout->addWidget(pCombo);

		ui.treeOptions->setItemWidget(pItem, 1, pProgram);
	}

	QComboBox* pValue = new QComboBox();
	pValue->setEditable(true);
	foreach(const QString& Value, m_AdvOptions[Name].Values)
		pValue->addItem(Value);
	int pos = pValue->findData(pItem->data(2, Qt::UserRole));
	pValue->setCurrentIndex(pos);
	if (pos == -1)
		pValue->setCurrentText(pItem->text(2));
	ui.treeOptions->setItemWidget(pItem, 2, pValue);
}

void COptionsWindow::OnOptionChanged(QTreeWidgetItem* pItem, int Column)
{
	if (Column != 0)
		return;

	m_AdvancedChanged = true;
	OnOptChanged();
}
	
void COptionsWindow::CloseOptionEdit(bool bSave)
{
	if (!ui.treeOptions) return;

	for (int i = 0; i < ui.treeOptions->topLevelItemCount(); i++)
	{
		QTreeWidgetItem* pItem = ui.treeOptions->topLevelItem(i);
		CloseOptionEdit(pItem, bSave);
	}
}

void COptionsWindow::CloseOptionEdit(QTreeWidgetItem* pItem, bool bSave)
{
	QComboBox* pValue = (QComboBox*)ui.treeOptions->itemWidget(pItem, 2);
	if (!pValue)
		return;

	if (bSave)
	{
		QWidget* pProgram = ui.treeOptions->itemWidget(pItem, 1);
		if (pProgram) 
		{
			QHBoxLayout* pLayout = (QHBoxLayout*)pProgram->layout();
			QToolButton* pNot = (QToolButton*)pLayout->itemAt(0)->widget();
			QComboBox* pCombo = (QComboBox*)pLayout->itemAt(1)->widget();

			QString Program = pCombo->currentText();
			int Index = pCombo->findText(Program);
			if (Index != -1)
				Program = pCombo->itemData(Index, Qt::UserRole).toString();
			//if (!Program.isEmpty() && Program.left(1) != "<")
			//	m_Programs.insert(Program);

			pItem->setText(1, (pNot->isChecked() ? "NOT " : "") + pCombo->currentText());
			pItem->setData(1, Qt::UserRole, (pNot->isChecked() ? "!" : "") + Program);
		}
		pItem->setText(2, pValue->currentText());
		pItem->setData(2, Qt::UserRole, pValue->currentText());

		m_AdvancedChanged = true;
		OnOptChanged();
	}

	ui.treeOptions->setItemWidget(pItem, 1, NULL);
	ui.treeOptions->setItemWidget(pItem, 2, NULL);
}
//

// triggers
void COptionsWindow::AddTriggerItem(const QString& Value, ETriggerAction Type, const QString& Template)
{
	QTreeWidgetItem* pItem = new QTreeWidgetItem();
	pItem->setData(0, Qt::UserRole, Template.isEmpty() ? Type : -1);
	switch (Type)
	{
		case eOnStartCmd:
			pItem->setText(0, tr("On Start"));
			pItem->setText(1, tr("Run Command"));
			break;
		case eOnStartSvc:
			pItem->setText(0, tr("On Start"));
			pItem->setText(1, tr("Start Service"));
			break;
		case eAutoExec:
			pItem->setText(0, tr("On Init"));
			pItem->setText(1, tr("Run Command"));
			break;
		case eRecoveryCheck:
			pItem->setText(0, tr("On File Recovery"));
			pItem->setText(1, tr("Run Command"));
			break;
		case eDeleteCmd:
			pItem->setText(0, tr("On Delete Content"));
			pItem->setText(1, tr("Run Command"));
			break;
		case eTerminateCmd:
			pItem->setText(0, tr("On Terminate"));
			pItem->setText(1, tr("Run Command"));
	}
	pItem->setText(2, Value);
	pItem->setFlags(pItem->flags() | Qt::ItemIsEditable);
	ui.treeTriggers->addTopLevelItem(pItem);
}

void COptionsWindow::OnAddAutoRun()
{
	QString Value = QInputDialog::getText(this, "Sandboxie-Plus", tr("Please enter the command line to be executed"), QLineEdit::Normal);
	if (Value.isEmpty())
		return;

	AddTriggerItem(Value, eOnStartCmd);
	m_AdvancedChanged = true;
	OnOptChanged();
}

void COptionsWindow::OnAddAutoSvc()
{
	QString Value = QInputDialog::getText(this, "Sandboxie-Plus", tr("Please enter a service identifier"), QLineEdit::Normal);
	if (Value.isEmpty())
		return;

	AddTriggerItem(Value, eOnStartSvc);
	m_AdvancedChanged = true;
	OnOptChanged();
}

void COptionsWindow::OnAddAutoExec()
{
	QString Value = QInputDialog::getText(this, "Sandboxie-Plus", tr("Please enter the command line to be executed"), QLineEdit::Normal);
	if (Value.isEmpty())
		return;

	AddTriggerItem(Value, eAutoExec);
	m_AdvancedChanged = true;
	OnOptChanged();
}

void COptionsWindow::OnAddDeleteCmd()
{
	QString Value = QInputDialog::getText(this, "Sandboxie-Plus", tr("Please enter the command line to be executed"), QLineEdit::Normal);
	if (Value.isEmpty())
		return;

	AddTriggerItem(Value, eDeleteCmd);
	m_AdvancedChanged = true;
	OnOptChanged();
}

void COptionsWindow::OnAddTerminateCmd()
{
	QString Value = QInputDialog::getText(this, "Sandboxie-Plus", tr("Please enter the command line to be executed"), QLineEdit::Normal);
	if (Value.isEmpty())
		return;

	AddTriggerItem(Value, eTerminateCmd);
	m_AdvancedChanged = true;
	OnOptChanged();
}

void COptionsWindow::OnAddRecoveryCheck()
{
	QString Value = QInputDialog::getText(this, "Sandboxie-Plus", tr("Please enter the command line to be executed"), QLineEdit::Normal);
	if (Value.isEmpty())
		return;

	AddTriggerItem(Value, eRecoveryCheck);
	m_AdvancedChanged = true;
	OnOptChanged();
}

void COptionsWindow::OnDelAuto()
{
	DeleteAccessEntry(ui.treeTriggers->currentItem());
	m_AdvancedChanged = true;
	OnOptChanged();
}
//

void COptionsWindow::OnAddProcess()
{
	QString Process = SelectProgram();
	if (Process.isEmpty())
		return;

	AddHiddenProcEntry(Process);

	m_AdvancedChanged = true;
	OnOptChanged();
}

void COptionsWindow::OnDelProcess()
{
	DeleteAccessEntry(ui.treeHideProc->currentItem());
	m_AdvancedChanged = true;
	OnOptChanged();
}

void COptionsWindow::OnHostProcessAllow()
{
	QString Process = QInputDialog::getText(this, "Sandboxie-Plus", tr("Please enter a program file name to allow access to this sandbox"));
	if (Process.isEmpty())
		return;

	AddHostProcEntry(Process, false);

	m_AdvancedChanged = true;
	OnOptChanged();
}

void COptionsWindow::OnHostProcessDeny()
{
	QString Process = QInputDialog::getText(this, "Sandboxie-Plus", tr("Please enter a program file name to deny access to this sandbox"));
	if (Process.isEmpty())
		return;

	AddHostProcEntry(Process, true);

	m_AdvancedChanged = true;
	OnOptChanged();
}

void COptionsWindow::OnDelHostProcess()
{
	DeleteAccessEntry(ui.treeHostProc->currentItem());
	m_AdvancedChanged = true;
	OnOptChanged();
}

void COptionsWindow::ShowHiddenProcTmpl(bool bUpdate)
{
	if (ui.chkShowHiddenProcTmpl->isChecked())
	{
		foreach(const QString& Template, m_pBox->GetTemplates())
		{
			foreach(const QString& Value, m_pBox->GetTextListTmpl("HideHostProcess", Template))
				AddHiddenProcEntry(Value, Template);
		}
	}
	else if (bUpdate)
	{
		for (int i = 0; i < ui.treeHideProc->topLevelItemCount(); )
		{
			QTreeWidgetItem* pItem = ui.treeHideProc->topLevelItem(i);
			int Type = pItem->data(0, Qt::UserRole).toInt();
			if (Type == -1) {
				delete pItem;
				continue; // entry from template
			}
			i++;
		}
	}
}

void COptionsWindow::ShowHostProcTmpl(bool bUpdate)
{
	if (ui.chkShowHostProcTmpl->isChecked())
	{
		foreach(const QString& Template, m_pBox->GetTemplates())
		{
			foreach(const QString & Value, m_pBox->GetTextListTmpl("DenyHostAccess", Template)) {
				StrPair NameVal = Split2(Value, ",");
				AddHostProcEntry(NameVal.first, NameVal.second.left(1).toLower() == "y", Template);
			}
		}
	}
	else if (bUpdate)
	{
		for (int i = 0; i < ui.treeHostProc->topLevelItemCount(); )
		{
			QTreeWidgetItem* pItem = ui.treeHostProc->topLevelItem(i);
			int Type = pItem->data(0, Qt::UserRole).toInt();
			if (Type == -1) {
				delete pItem;
				continue; // entry from template
			}
			i++;
		}
	}
}

void COptionsWindow::AddHiddenProcEntry(const QString& Name, const QString& Template)
{
	QTreeWidgetItem* pItem = new QTreeWidgetItem();
	pItem->setText(0, Name + (Template.isEmpty() ? "" : " (" + Template + ")"));
	pItem->setData(0, Qt::UserRole, Template.isEmpty() ? 0 : -1);
	ui.treeHideProc->addTopLevelItem(pItem);
}

void COptionsWindow::AddHostProcEntry(const QString& Name, bool Deny, const QString& Template)
{
	QTreeWidgetItem* pItem = new QTreeWidgetItem();
	pItem->setText(0, Name + (Template.isEmpty() ? "" : " (" + Template + ")"));
	pItem->setData(0, Qt::UserRole, Template.isEmpty() ? 0 : -1);
	pItem->setText(1, Deny ? tr("Deny") : tr("Allow"));
	pItem->setData(1, Qt::UserRole, Deny);
	ui.treeHostProc->addTopLevelItem(pItem);
}


#include <wtypes.h>
#include <objsel.h>

void COptionsWindow::OnAddUser()
{
	QStringList Users;

	IDsObjectPicker *pObjectPicker = NULL;
	HRESULT hr = CoCreateInstance(CLSID_DsObjectPicker, NULL, CLSCTX_INPROC_SERVER, IID_IDsObjectPicker, (void **)&pObjectPicker);
	if (FAILED(hr))
		return;

	DSOP_SCOPE_INIT_INFO ScopeInit;
	memset(&ScopeInit, 0, sizeof(DSOP_SCOPE_INIT_INFO));
	ScopeInit.cbSize = sizeof(DSOP_SCOPE_INIT_INFO);
	ScopeInit.flType = DSOP_SCOPE_TYPE_TARGET_COMPUTER | DSOP_SCOPE_TYPE_UPLEVEL_JOINED_DOMAIN | DSOP_SCOPE_TYPE_DOWNLEVEL_JOINED_DOMAIN;
	ScopeInit.flScope = DSOP_SCOPE_FLAG_STARTING_SCOPE | DSOP_SCOPE_FLAG_DEFAULT_FILTER_USERS | DSOP_SCOPE_FLAG_DEFAULT_FILTER_GROUPS;
	ScopeInit.FilterFlags.Uplevel.flBothModes = DSOP_FILTER_USERS | DSOP_FILTER_WELL_KNOWN_PRINCIPALS | DSOP_FILTER_BUILTIN_GROUPS
		| DSOP_FILTER_UNIVERSAL_GROUPS_SE | DSOP_FILTER_GLOBAL_GROUPS_SE | DSOP_FILTER_DOMAIN_LOCAL_GROUPS_SE;
	ScopeInit.FilterFlags.flDownlevel = DSOP_DOWNLEVEL_FILTER_USERS | DSOP_DOWNLEVEL_FILTER_LOCAL_GROUPS | DSOP_DOWNLEVEL_FILTER_GLOBAL_GROUPS;

	DSOP_INIT_INFO InitInfo;
	memset(&InitInfo, 0, sizeof(InitInfo));
	InitInfo.cbSize = sizeof(InitInfo);
	InitInfo.pwzTargetComputer = NULL;
	InitInfo.cDsScopeInfos = 1;
	InitInfo.aDsScopeInfos = &ScopeInit;
	InitInfo.flOptions = DSOP_FLAG_MULTISELECT;

	hr = pObjectPicker->Initialize(&InitInfo);

	if (SUCCEEDED(hr))
	{
		IDataObject *pDataObject = NULL;
		hr = pObjectPicker->InvokeDialog((HWND)this->winId(), &pDataObject);
		if (SUCCEEDED(hr) && pDataObject)
		{
			FORMATETC formatEtc;
			formatEtc.cfFormat = (CLIPFORMAT)RegisterClipboardFormat(CFSTR_DSOP_DS_SELECTION_LIST);
			formatEtc.ptd = NULL;
			formatEtc.dwAspect = DVASPECT_CONTENT;
			formatEtc.lindex = -1;
			formatEtc.tymed = TYMED_HGLOBAL;

			STGMEDIUM stgMedium;
			hr = pDataObject->GetData(&formatEtc, &stgMedium);
			if (SUCCEEDED(hr))
			{
				PDS_SELECTION_LIST pResults = (PDS_SELECTION_LIST)GlobalLock(stgMedium.hGlobal);
				if (pResults)
				{
					for (ULONG i = 0; i < pResults->cItems; i++)
						Users.append(QString::fromWCharArray(pResults->aDsSelection[i].pwzName));
					GlobalUnlock(stgMedium.hGlobal);
				}
			}
			pDataObject->Release();
		}
	}
	pObjectPicker->Release();


	if (Users.isEmpty())
		return;

	ui.lstUsers->addItems(Users);

	m_AdvancedChanged = true;
	OnOptChanged();
}

void COptionsWindow::OnDelUser()
{
	foreach(QListWidgetItem* pItem, ui.lstUsers->selectedItems())
		delete pItem;

	m_AdvancedChanged = true;
	OnOptChanged();
}

void COptionsWindow::CreateDebug()
{
	QStringList DebugOptions = theConf->ListKeys("DebugOptions");
	if(DebugOptions.isEmpty())
		ui.tabsAdvanced->removeTab(ui.tabsAdvanced->count() - 1);
	else
	{
		int RowCount = 0;
		foreach(const QString& DebugOption, DebugOptions)
		{
			QStringList ValueDescr = theConf->GetString("DebugOptions/" + DebugOption).split("|");

			QString Description = ValueDescr.size() >= 3 ? ValueDescr[2] : ValueDescr[0];
			int Column = 0; // use - to add up to 10 indents
			for (; Description[0] == '-' && Column < 10; Column++) Description.remove(0, 1);

			SDbgOpt DbgOption = { ValueDescr[0], ValueDescr.size() >= 2 ? ValueDescr[1] : "y" , false};

			QString Info = DbgOption.Name + "=" + DbgOption.Value;
			QCheckBox* pCheck = new QCheckBox(tr("%1 (%2)").arg(Description).arg(Info));
			if (ValueDescr.size() >= 2 && ValueDescr[1] == "x")
				pCheck->setDisabled(true);
			//pCheck->setToolTip(Info);
			ui.dbgLayout->addWidget(pCheck, RowCount++, Column, 1, 10-Column);

			connect(pCheck, SIGNAL(clicked(bool)), this, SLOT(OnDebugChanged()));
			m_DebugOptions.insert(pCheck, DbgOption);
		}

		for(int i=0; i < 10; i++)
			ui.dbgLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding), RowCount, i);
		ui.dbgLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum), RowCount, 10);
	}
}

void COptionsWindow::OnDebugChanged()
{
	QCheckBox* pCheck = qobject_cast<QCheckBox*>(sender());
	m_DebugOptions[pCheck].Changed = true;
	OnOptChanged();
}

void COptionsWindow::LoadDebug()
{
	foreach(QCheckBox* pCheck, m_DebugOptions.keys()) 
	{
		SDbgOpt& DbgOption = m_DebugOptions[pCheck];
		DbgOption.Changed = false;
		ReadAdvancedCheck(DbgOption.Name, pCheck, DbgOption.Value);
	}
}

void COptionsWindow::SaveDebug()
{
	foreach(QCheckBox * pCheck, m_DebugOptions.keys())
	{
		SDbgOpt& DbgOption = m_DebugOptions[pCheck];
		if (!DbgOption.Changed)
			continue;
		WriteAdvancedCheck(pCheck, DbgOption.Name, DbgOption.Value);
		DbgOption.Changed = false;
	}
}
