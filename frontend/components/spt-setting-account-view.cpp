//
// Created by Nanusorn Photpipat on 7/2/2025 AD.
//

#include "spt-setting-account-view.hpp"
#include "ui_SPTSettingAccountView.h"
#include <QDebug>

SPTSettingAccountView::SPTSettingAccountView(QWidget *parent) : QWidget(parent),
	ui(new Ui::SPTSettingAccountView)
{
	ui->setupUi(this);
	initUi();
}

SPTSettingAccountView::~SPTSettingAccountView()
{
}

void SPTSettingAccountView::initUi()
{
	QString filePath = ":/settings/images/settings/profile.svg";
	ui->userIconLabel->setPixmap(filePath, QSize(110, 110));
}

void SPTSettingAccountView::on_pushButton_logout_clicked()
{
	qDebug() << __FUNCTION__;
}
