#include "common.h"
#include "unstallthread.h"

UnstallThread::UnstallThread(QWidget *parent)
	: QThread(parent)
{
	m_unstallPath = QString("");
	isRunning = false;
}

UnstallThread::~UnstallThread()
{

}

void UnstallThread::startJob()
{
	isRunning = true;
	start();
}

void UnstallThread::stopJob()
{
	isRunning = false;
}

void UnstallThread::run()
{
	while (isRunning)
	{
		if (deleteDir(m_unstallPath))
		{
			isRunning = false;
			emit deleteall();
#ifdef DEBUG
			qDebug() << "isRunning ............." << isRunning;
#endif
		}
	}
}

bool UnstallThread::deleteDir(const QString &dirName)
{
	QDir directory(dirName);
	if (!directory.exists())
	{
		return true;
	}

	QString srcPath = QDir::toNativeSeparators(dirName);
	if (!srcPath.endsWith(QDir::separator()))
		srcPath += QDir::separator();

	QStringList fileNames = directory.entryList(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden);
	bool error = false;
	//int numitems = 0;
	static int number = 0;
	for (QStringList::size_type i = 0; i != fileNames.size(); ++i)
	{
		QString filePath = srcPath + fileNames.at(i);
		QFileInfo fileInfo(filePath);
		if (fileInfo.isFile() || fileInfo.isSymLink())
		{
			if (QString("uninst.exe") != fileNames.at(i))
			{
				QFile::setPermissions(filePath, QFile::WriteOwner);
				if (!QFile::remove(filePath))
				{
#ifdef DEBUG
					qDebug() << "remove file" << filePath << " faild!";
#endif
					//error = true;
					error = false;
				}
				//numitems = fileNames.size();
				number++;
				int percent = (double)number / (double)278 * 100.0;
				emit deletefile(percent);
#ifdef WINDOWS
				usleep(600);
#endif
#ifdef LINUX
				QThread::msleep(100); //��ʱ
				if (278 <= number) break;
#endif
			}
		}
		else if (fileInfo.isDir())
		{
			bool b;
			//b = removeDirWithContent(filePath);
			if (!deleteDir(filePath))
			{
				//error = true;
				error = false;
			}
		}
	}

	if (!directory.rmdir(QDir::toNativeSeparators(directory.path())))
	{
#ifdef DEBUG
		qDebug() << "remove dir" << directory.path() << " faild!";
#endif
		//error = true;
		error = false;
	}

	return !error;
}

void UnstallThread::setPath(const QString &unstallpath)
{
	m_unstallPath = unstallpath;
}

// bool UnstallThread::removeDirWithContent(const QString &dirName){
// 	static QVector<QString> dirNames;
// 	static QString funcErrMsg = "ɾ��[%1]ʧ��.";
// 	static QString funcInfFndMsg = "����[%1].";
// 	static QString funcInfDelMsg = "ɾ��[%1]�ɹ�.";
// 	QDir dir;
// 	QFileInfoList filst;
// 	QFileInfoList::iterator curFi;
// 
// 	//��ʼ��
// 	dirNames.clear();
// 	if (dir.exists()){
// 		dirNames << dirName;
// 	}
// 	else{
// 		return true;
// 	}
// 
// 	//���������ļ��У�������Щ�ļ����е��ļ�ɾ��
// 	for (int i = 0; i<dirNames.size(); ++i){
// 		dir.setPath(dirNames[i]);
// 		filst = dir.entryInfoList(QDir::Dirs | QDir::Files
// 			| QDir::Readable | QDir::Writable
// 			| QDir::Hidden | QDir::NoDotAndDotDot
// 			, QDir::Name);
// 		if (filst.size()>0){
// 			curFi = filst.begin();
// 			while (curFi != filst.end()){
// 				//�����ļ���,��������ļ����б�dirsβ��
// 				if (curFi->isDir()){
// 					dirNames.push_back(curFi->filePath());
// 				}
// 				else if (curFi->isFile()){
// 					//�����ļ�,��ɾ��֮
// 					if (!dir.remove(curFi->fileName())){
// 						return false;
// 					}
// 				}
// 				curFi++;
// 			}//end of while
// 		}
// 	}
// 
// 	//ɾ���ļ���
// 	for (int i = dirNames.size() - 1; i >= 0; --i){
// 		dir.setPath(dirNames[i]);
// 		if (!dir.rmdir(".")){
// 			return false;
// 		}
// 	}
// 
// 	return true;
// }


// TCHAR* namePath = NULL;
// TCHAR szTBuff[1024] = { 0 };
// 
// QStringToTCHER(&namePath, str);//qstringת����TCHAR
// _tcscpy(szTBuff, namePath);
// if (namePath)
// {
// 	delete[] namePath;
// 	namePath = NULL;
// }
// _tcscat_s(szTBuff, ze.name);
// 
// void MainWidget::QStringToTCHER(TCHAR** ppchar, const QString &str)
// {
// 	QByteArray byt = str.toUtf8();
// 	char *p = byt.data();
// 	char tmp[MAX_PATH] = { 0 };
// 	memmove(tmp, p, byt.length());
// 
// 
// 	DWORD dwNum = MultiByteToWideChar(CP_UTF8, 0, tmp, -1, NULL, 0);
// 	TCHAR *pwText;
// 	pwText = new TCHAR[dwNum];
// 	if (!pwText)
// 	{
// 		delete[]pwText;
// 	}
// 	MultiByteToWideChar(CP_UTF8, 0, tmp, -1, pwText, dwNum);
// 
// 	*ppchar = pwText;
// 
// }
