#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "common.h" 

#include <QCoreApplication>
#include <QWidget>
#include <QDesktopWidget>
#include <QStackedLayout>
#include <QMainWindow>
#include <QPalette>
#include <QBrush>
#include <QPixmap>
#include <QPainter>
#include <QMessageBox>
#include <QTranslator>
#include <QScrollArea>
#include <QScrollBar>
#include <QPainterPath>
#include <QScrollBar>
#include <QFileDialog>
#include <QLineEdit>
#include <QProcess>
#include "zc_install.h"
#include "myclicklabel.h"

#ifdef WINDOWS
#include <iostream>
#include "resource.h"
#include "unzip.h"
#include <tchar.h>
#include <ShObjIdl.h>
#include <ShlObj.h>
#endif
#ifdef LINUX
#include "3rdparty/quazip/include/JlCompress.h"
#include "./3rdparty/quazip/include/quazip.h"
#include <QDir>
#include "./3rdparty/quazip/include/quazipfile.h"
#include <QSettings>
#include <QFileInfo>
#endif

// #include <JlCompress.h>  //���ĸ�����quazip��ѹ
// #include <quazip.h>
// #include <QDir>
// #include <quazipfile.h>


class MainWidget : public QDialog
{
	Q_OBJECT

public:
	MainWidget(QWidget *parent=0);
	~MainWidget();

	void showWidget(QWidget *);
	
protected:
	void createSetPathWidget();
	void createCopyWidget();
	void createFinishCopyWidget();
	void createLicenceWidget();
	void createUpdateWidget();

	bool eventFilter(QObject *, QEvent *);
protected slots:
	void doShowNextWidgetSlot();
	void doShowProtocolContentSlot();
	void doSwitchAgreeButtonSlot();
	void doExtendSetPathWidgetSlot();
	void doCloseMainWidgetSlot();
	void doSelectUserDefPathSlot();
	void doFinishExprButtonSlot();

	void doCopyTimerUnpress();
protected:
	ZC_install *m_setPathWidget;   //���ý���
	QWidget    *m_setPathParentWid;//�Զ�������ý���ĸ���
	QWidget    *m_setPathUserDefWid;//�Զ���·������
	ZC_install *m_copyWidget;//��ѹ����
	ZC_install *m_finishCopyWidget;//��ѹ��ɽ���
	ZC_install *m_updateWidget; //���½���
	bool       m_isFinish;   //�Ƿ�װ��������

	QStackedLayout *m_mainStackedLayout;//......................���ý���     **
	PushButton     *m_setPathInstallButton;  //������װ��ť
	MyClickLabel   *m_protocolLabel;  //���û����Э�顱��ť
	QLabel         *m_agreeLebel;  //��ͬ�⡱
	CheckButton    *m_agreeButton; //��ͬ�⡱ѡ���
	QLabel         *m_userDefLabel;     //���Զ��塱
	CheckButton    *m_userDefButton;  //���Զ��塱��ť
	QVBoxLayout    *m_setPathLayout;  //װ��������wid      **
	PushButton     *m_userSelectPath; //�û�ѡ��·����ť
	QLineEdit      *m_userDefPath;   //��ʾ��װ·��
	QString        m_installPath; //���ʹ�õİ�װ·��   **

	ZC_install     *m_licenceWidget;  //...............���Э�����
	QLabel         *m_licenceLabel;
	PushButton     *m_licenceButton;
	QScrollArea    *m_licenceScroll;

	QLabel         *m_percentLabel;//.....................��ѹ����
	QTimer         *m_copyTimer;
	QPainter       *m_copyPainter;
#ifdef WINDOWS
	IShellLink	   *m_psl;
	IShellLink	   *m_pslUnintall;
#endif

	PushButton     *m_finishExprButton;//..................��ѹ���

	PushButton     *m_updateButton;//..................���н�����������°�ť

	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	QPoint     m_movePoint;
	bool       m_mousePress;
private:
#ifdef WINDOWS
	void setLinkPath();
	BOOL CreateLnk(IShellLink * psl, UINT uiType, QString strLnkName, BOOL bCreateDir);
	void CreateRegedit(TCHAR *pversions, TCHAR *pPath);
	BOOL CreateLinkAndRegedit(int updateOrInstall);  //ʵ����ʱ����û����
	void QStringToTCHER(TCHAR** ppchar, const QString &str);
#endif
	int isInstallClient();
#ifdef LINUX
	bool createConfigureini(); //��¼��װλ�úͰ汾
	bool createDesktopLink(); //�����ݷ�ʽ
#endif
	void mainWidgetDoDelete(int whichWidget);

};

#endif // MAINWIDGET_H
