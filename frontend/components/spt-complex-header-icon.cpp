#include "spt-complex-header-icon.hpp"
#include "ui_SPTComplexHeaderIcon.h"

#include <qsvgrenderer.h>

SPTComplexHeaderIcon::SPTComplexHeaderIcon(QWidget *parent) : QLabel(parent),
	ui(new Ui::SPTComplexHeaderIcon)
{
	ui->setupUi(this);
	ui->PlatformLabel->hide();
}

SPTComplexHeaderIcon::~SPTComplexHeaderIcon()
{
}

void SPTComplexHeaderIcon::setPixmap(const QString &pix)
{
	QPixmap pixmap(pix);

	this->QLabel::setPixmap(pixmap);
}

void SPTComplexHeaderIcon::setPixmap(const QString &pix, const QSize &size)
{
	QPixmap pixmap(size * 4);
	if (pix.contains(".svg")) {
		//svg handler
		QSvgRenderer svgRenderer(pix);
		pixmap.fill(Qt::transparent);
		QPainter painter(&pixmap);
		svgRenderer.render(&painter);
	}

	pixmap = pixmap.scaled(size * 4, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	this->QLabel::setPixmap(pixmap.scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void SPTComplexHeaderIcon::setPlatformPixmap(const QString &pix, const QSize &size)
{
	QSvgRenderer svgRenderer(pix);
	QPixmap pixmap(size);
	pixmap.fill(Qt::transparent);
	QPainter painter(&pixmap);
	svgRenderer.render(&painter);
	setPlatformPixmap(pixmap);
}

void SPTComplexHeaderIcon::setPlatformPixmap(const QPixmap &pix)
{

	ui->PlatformLabel->setPixmap(pix);
	ui->PlatformLabel->show();
}

void SPTComplexHeaderIcon::changeEvent(QEvent *e)
{
	QLabel::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
		break;
	default:
		break;
	}
}
