#ifndef UNINST_H
#define UNINST_H

#include "common.h"
#include "zc_unstall.h"
#include "unstallthread.h"
#include <QtWidgets/QDialog>
#include <QIcon>
#include <QMouseEvent>
#include <QStackedLayout>
#include <QTimer>
#include <QLabel>
#include <QDir>
#include <QProcess>
#include <iostream>

#ifdef WINDOWS
#include "resource.h"
#include <windows.h>
#include <Shlobj.h>
#include <strsafe.h>
#endif
#ifdef LINUX
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <QTextCodec>
#endif

#include <QDebug>
#include <iostream>

class MainWidget : public QDialog
{
	Q_OBJECT

public:
	MainWidget(QWidget *parent = 0);
	~MainWidget();

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	QPoint     m_movePoint;
	bool       m_mousePress;

	void createStartUnstWidget();
	void createOnUnstWidget();
	void createFinishWidget();

	void eventForStartUnstBt(); //................ ��ʼж�ذ�ť�¼�����
	void eventForFinishUnshBt();//.....................���ɾ����Ҫ�ļ�֮����ɾ�����˳������¼�����
	
#ifdef WINDOWS
	bool clearLink();
	bool clearRegeidt();
	bool RegDelnodeRecurse(HKEY hKeyRoot, LPTSTR lpSubKey);
	bool RegDelnode(HKEY hKeyRoot, LPTSTR lpSubKey);
#endif
#ifdef LINUX
	bool clearConfiginiAndUserfile();
#endif

	bool eventFilter(QObject *, QEvent *);

private slots:
	void doCloseMainWidgetSlot();
	void setOnUnstallPecent(int percent);  //�ı�������İٷֱ�
	void setOnUnstallFinish();

private:
	QStackedLayout *m_mainStackedLayout; //........����ת��
	bool           m_isFinish;

	ZC_unstall     *m_startUnstWidget;
	ZC_unstall     *m_onUnstWidget;
	ZC_unstall     *m_finishUnstWidget;

	PushButton     *m_startUnstBt; //��ʼж�ذ�ť

	QTimer         *m_onUnstTimer;   //ɾ���ļ���ʱ�� , û���ö�ʱ��, ��m_onUnstThread �̴߳�����
	QLabel         *m_percentLabel;
	UnstallThread  *m_onUnstThread;

	PushButton     *m_finishUnstBt;//���ж�ذ�ť
};

#endif // UNINST_H
