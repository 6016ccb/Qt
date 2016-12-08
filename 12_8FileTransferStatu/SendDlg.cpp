#include <QTimerEvent>
#include "SendDlg.h"
#include "AfGbk.h"

SendDlg::SendDlg(const QString& filepath, QWidget *parent /*= Q_NULLPTR*/)
{
		ui.setupUi(this);
		//���������߳�
		m_task = new SendTask(NULL);
		m_task->CreateTask(AfGbk::FromUnicode(filepath).c_str());
		m_timerid = startTimer(50);
}



SendDlg::~SendDlg()
{
}

void SendDlg::timerEvent(QTimerEvent* event)
{
	if (event->timerId() == m_timerid)
	{
		//��ȡ�����̵߳ĵ�ǰ״̬
		int status = m_task->GetStatus();
		int progress = m_task->GetProgress();

		ui.progressBar->setValue(progress);
		if (status == 1)
		{
			//��β����
			killTimer(m_timerid);	//�رն�ʱ��
			this->accept();				//�رնԻ���
			m_task->Destroy();
			delete m_task;
		}

	}
}
