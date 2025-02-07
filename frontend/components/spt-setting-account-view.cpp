//
// Created by Scrooge McDuck on 7/2/2025 AD.
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
//	if (PLSLoginUserInfo::getInstance()->getAuthType() == LOGIN_USERINFO_EMAIL) {
//		ui->email->setText(PLSLoginUserInfo::getInstance()->getEmail());
//	} else {
//		QString snsIconPath = pls_prism_user_thumbnail_path();
//		if (QFileInfo::exists(snsIconPath)) {
//			filePath = snsIconPath;
//		}
//		ui->email->setVisible(false);
//		ui->pushButton_change_pwd->setVisible(false);
//		ui->horizontalLayout_2->addStretch(1);
//
//		if ("whale" == PLSLoginUserInfo::getInstance()->getAuthType().toLower()) {
//			ui->userIconLabel->setPlatformPixmap(QString(":/resource/images/sns-profile/img-%1-profile.png").arg(PLSLoginUserInfo::getInstance()->getAuthType().toLower()),
//							     QSize(34 * 4, 34 * 4));
//		} else {
//			ui->userIconLabel->setPlatformPixmap(QString(":/resource/images/sns-profile/img-%1-profile.svg").arg(PLSLoginUserInfo::getInstance()->getAuthType().toLower()),
//							     QSize(34 * 4, 34 * 4));
//		}
//	}
	ui->userIconLabel->setPixmap(filePath, QSize(110, 110));
}

void SPTSettingAccountView::on_pushButton_logout_clicked()
{
	qDebug() << __FUNCTION__;
}
