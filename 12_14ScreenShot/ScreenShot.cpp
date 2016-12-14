#include <QTimer>
#include <cassert>
#include <QApplication>
#include <QDialog>
#include <QPixmap>
#include <Qfiledialog>
#include <QDesktopWidget>
#include "ScreenShot.h"
//#include 

ScreenShot::ScreenShot(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	assert(
		connect(ui.actionCapture, SIGNAL(clicked()), this, SLOT(onCapture()))
		);
	assert(
		connect(ui.actionSave, SIGNAL(clicked()), this, SLOT(onSave()))
		);
}

int ScreenShot::onCapture()
{
	// ���������
	this->hide();

	// ���ر�������Ҫһ��ʱ�䣬����ʱһ��ʱ���ſ�ʼ��ͼ
	QTimer::singleShot(300, this, SLOT(onDelayedCapture()));

	return 0;
}

int ScreenShot::onDelayedCapture()
{
	QPixmap screen = QPixmap::grabWindow(QApplication::desktop()->winId());
	RegionSelector dlg(screen, this);
	if (QDialog::Accepted == dlg.exec())
	{
		QPixmap region = screen.copy(dlg.selectRegion);
		ui.frame->display(region);
	}
	this->showNormal();
	return 0;
}

int ScreenShot::onSave()
{	
	QPixmap picture = ui.frame->pixmap();
	
	//���浽Ŀ���ļ�
	QString filename = QFileDialog::getSaveFileName(this, "Save Picture", "", "Image File(*.jpg)");
	if (filename.length() > 0)
	{
		picture.save(filename);
	}

	return 0;
}
