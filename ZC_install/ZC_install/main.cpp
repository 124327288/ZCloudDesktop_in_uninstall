#include "common.h"
#include "zc_install.h"
#include "zcSingleApplication.h"
#include "mainwidget.h"
#include <QtWidgets/QApplication>
#ifdef WINDOWS
#include <QtPlugin> 
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin);
#pragma   comment(linker,   "/subsystem:\"windows\"   /entry:\"mainCRTStartup\""   ) 
#endif

int main(int argc, char *argv[])
{
	SingleApplication a(argc, argv);
	if (a.isRunning())
	{
		QMessageBox msgBox(QMessageBox::Question, QString(QStringLiteral("����")), QStringLiteral("��װ�����Ѿ�������!"), QMessageBox::NoButton);
		msgBox.addButton(QStringLiteral("ȷ��"), QMessageBox::AcceptRole);
		msgBox.exec();
		return 0;
	}
#ifdef WINDOWS
	QTranslator translator;
	translator.load(":/qm/qt_zh_CN");
	a.installTranslator(&translator);
#endif

	MainWidget w;
	w.show();
	return a.exec();
}
