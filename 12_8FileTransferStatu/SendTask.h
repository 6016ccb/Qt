#pragma once

#include <QThread>

class SendTask : public QThread
{
	Q_OBJECT

public:
	SendTask(QObject *parent);
	~SendTask();
public:
	int CreateTask(const char* filename);
	int Destroy();
	

	int GetProgress();
	int GetStatus();
private:
	void run();

private:
	char m_filepath[128];
	int m_filesize;		//�ļ������ֽ���
	int m_bytesread;	//��ȡ��������ֽ���
	int m_status;		//����״̬
};
