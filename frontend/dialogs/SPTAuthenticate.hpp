//
// Created by Scrooge McDuck on 8/2/2025 AD.
//

#pragma once

#include "ui_SPTAuthenticate.h"
#include "auth/OAuthManager.hpp"
#include <QWidget>
#include <QMainWindow>
#include <QNetworkAccessManager>

class SPTAuthenticate: public QWidget {
    Q_OBJECT

public:
    explicit SPTAuthenticate(QWidget *parent = nullptr);
    std::unique_ptr<Ui::SPTAuthenticate> ui;
   void setMainWindow(QMainWindow* mainWindow) { this->mpMainWindow = mainWindow; }
   
protected:
   void initUi();
   
private:
   OAuthManager mAuthManager;
   QMainWindow *mpMainWindow;
};
