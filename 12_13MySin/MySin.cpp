#include <QPaintEvent>
#include <QPainter.h>
#include <cmath>
#include "MySin.h"
#include "AfGbk.h"

MySin::MySin(QWidget *parent)
	: QFrame(parent)
	,m_grain(1)
	,m_period(100)
	,m_radius(200)
{
// 	m_ui = new Test11_8a_12_13();
// 	string StrPeriod = AfGbk::FromUnicode(m_ui->GetPeriod());
// 	string StrGrain = AfGbk::FromUnicode(m_ui->GetGrain());
// 	string StrRadius = AfGbk::FromUnicode(m_ui->GetRadius());
// 	m_period = atoi(StrPeriod.c_str());
// 	m_radius = atoi(StrRadius.c_str());
// 	m_grain = atoi(StrGrain.c_str());

}

MySin::~MySin()
{

}


void MySin::paintEvent(QPaintEvent* event)
{
	if (m_grain == 0)
	{
		return;
	}

	QPainter painter(this);
	int width = this->width();
	int height = this->height();
	QRect rect(0, 0, width, height);

	//����������ɫ��
	painter.setBrush(QColor(0, 0, 0));
	painter.drawRect(rect);

	//����������ɫ ����ɫ��
	painter.setPen(QPen(QColor(255, 255, 255)));

	//���м��׼��
	QPoint o = origin();
	painter.drawLine(QPoint(0, o.y()), QPoint(width, o.y()));
	painter.drawLine(QPoint(o.x(), 0), QPoint(o.x(), height));

	
	painter.setPen(QPen(QColor(0, 255, 0)));



	//�������ߣ�������ԭ�㣬��������չ
	QPoint p1(0, 0);
	for (int x = 0; x < width / 2; x += m_grain)
	{
		double angle = (double)x / m_period * 2 * 3.1415926;
		double y = m_radius * sin(angle);
		QPoint p2(x, y);
		//��
		painter.drawLine(fromCoord(p1), fromCoord(p2));
		//��
		QPoint base(0, 0);
		painter.drawLine(fromCoord(base - p1), fromCoord(base - p2));
		p1 = p2;
	}

}

void MySin::Adjust(int period, int grain, int radius)
{
	m_period = period;
	m_grain = grain;
	m_radius = radius;
	update();
}

QPoint MySin::origin()
{
	QRect r = this->rect();
	return r.center();
}

//��GUI���ڵĵ㣨x,y��ת��������ϵͳ��ĵ�
QPoint MySin::toCoord(QPoint p)
{
	//Բ��
	QPoint o = this->origin();
	QPoint result = p - o;
	result.setY(0 - result.y());	//Y���귴ת
	return result;
}

//������ϵ�ڵĵ�(x,y)ת����GUI����
QPoint MySin::fromCoord(QPoint p)
{
	//Բ��
	QPoint o = this->origin();
	p.setY(0 - p.y());
	return p + o;
}


