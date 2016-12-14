#pragma once

#include <QFrame>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QEvent>

class MySlider : public QFrame
{
	Q_OBJECT

public:
	MySlider(QWidget *parent);
	~MySlider();

signals:
	void clicked(int progess);
	void tracking(int progress, QPoint pos);
	void focused(bool yes);

public:
	void setRange(int range);
	void setProgres(int progress);
	int range() const;
	int progress() const;

private:
	virtual QSize sizeHint() const;
	//���Ƹ���״̬
	virtual void enterEvent(QEvent* event);
	virtual void leaveEvent(QEvent *event);

	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void paintEvent(QPaintEvent* event);

private:
	int PosToProg(int position);
	int ProgToPos(int progress);

private:
	int m_range;
	int m_progress;
	int m_virtual_progress;		//���������
	bool m_focused;	//�Ƿ����
	bool m_pressed; //�Ƿ񱻰���
	QRect m_validRegion;
};
