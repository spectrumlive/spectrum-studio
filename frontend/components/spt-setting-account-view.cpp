/******************************************************************************
 Copyright (C) 2025 by Nanusorn Photpipat (nanusorn@photpipat.com)
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 2 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************/

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
