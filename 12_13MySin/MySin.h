#pragma once

#include <QFrame>
#include <QPoint>

class MySin : public QFrame
{
	Q_OBJECT

public:
	MySin(QWidget *parent);
	~MySin();

	void Adjust(int period, int grain, int radius);

	//����ԭ��
	QPoint origin();
	//��GUI���ڵĵ㣨x,y��ת��������ϵͳ��ĵ�
	QPoint toCoord(QPoint p);
	//������ϵ�ڵĵ�(x,y)ת����GUI����
	QPoint fromCoord(QPoint p);

private:
	virtual void paintEvent(QPaintEvent* event);

private:
	int m_period;	//����
	int m_grain;		//����
	int m_radius;	//����
	//Test11_8a_12_13* m_ui;
};
