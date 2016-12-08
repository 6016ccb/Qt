#include <string.h>
#include <cassert>
#include <QDebug>
#include "SendTask.h"

SendTask::SendTask(QObject *parent)
	: QThread(parent)
{

}

SendTask::~SendTask()
{
}

int SendTask::CreateTask(const char* filename)
{
	strcpy(m_filepath, filename);
	m_filesize = 0;
	m_bytesread = 0;
	m_status = 0;

	start();	//�����߳�
	return 0;
}

int SendTask::Destroy()
{
	wait();
	return 0;
}

int SendTask::GetProgress()		//�̵߳Ľ���
{
	if (m_filesize <= 0)
	{
		return 0;
	}
	return m_bytesread * 100 / m_filesize;
}

int SendTask::GetStatus()
{
	return m_status;
}

void SendTask::run()
{
	FILE* fp = fopen(m_filepath, "rb");
	if (!fp)
	{
		m_status = -1;		//״̬������
		return;
	}
	//��ȡ�ļ���С
	fseek(fp, 0, SEEK_END);
	m_filesize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char buffer[1024];
	int part = 0;
	memset(buffer, '\0', sizeof(buffer) / sizeof(*buffer));

	while (1)
	{
		int n = fread(buffer, 1, sizeof(buffer), fp);
		if ( n <= 0 )	//��ȡ���s
		{
			break;
		}
		m_bytesread += n;
		part += n;
		//ÿ��һ��ʱ��sleepһ��
		if (part > 1024 * 32)
		{
			QThread::msleep(25);		//ģ�⣬����1024���ֽڣ���Ҫһ����
			part = 0;
		}
		//���ͣ�ʡ��
	}
	fclose(fp);
	m_status = 1;		//״̬�������
}
