#ifndef UNZIPTHREAD_H
#define UNZIPTHREAD_H

#include "common.h"
#include <QThread>



class UnzipThread : public QThread
{
	Q_OBJECT

public:
	UnzipThread(QObject *parent=0);
	~UnzipThread();

	volatile bool m_isRunning;
	void stopJob();
	void startJob();

signals:
	void unzipPercent(int percent);//����һ����ѹ�ٷֱȾͷ���һ���ź�
	void unzipComplete(); //��ѹ���ʱ�����ź�

private:
	void run();
};

#endif // UNZIPTHREAD_H
