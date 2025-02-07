//
// Created by Scrooge McDuck on 7/2/2025 AD.
//

#pragma once

#include <QWidget>

namespace Ui {
class SPTSettingAccountView;
}

class SPTSettingAccountView: public QWidget {
	Q_OBJECT

public:
	explicit SPTSettingAccountView(QWidget *parent = nullptr);
	~SPTSettingAccountView() override;
	void initUi();
	void setEnable(bool enable);
	
private slots:
	void on_pushButton_logout_clicked();

private:
	Ui::SPTSettingAccountView *ui;
};
