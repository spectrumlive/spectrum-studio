//
// Created by Scrooge McDuck on 8/2/2025 AD.
//

#include "SPTAuthenticate.hpp"
#include "auth/OAuthManager.hpp"
#include <QWidget>
#include <QDesktopServices>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

SPTAuthenticate::SPTAuthenticate(QWidget *parent) : QWidget(parent), ui(new Ui::SPTAuthenticate)
{
   ui->setupUi(this);
   initUi();
   
   QObject::connect(&mAuthManager, &OAuthManager::loginSuccess, [this](const QString &token) {
      qDebug() << "Login successful! Token:" << token;
      this->mpMainWindow->show();
      this->close();
   });
   
   QObject::connect(&mAuthManager, &OAuthManager::loginFailed, [](const QString &error) {
      qDebug() << "Login failed:" << error;
   });
}

void SPTAuthenticate::initUi()
{
   this->setFixedSize(size());
//   ui->btnGoogleMail->setDisabled(true);
   ui->btnAppleID->setDisabled(true);
   connect(ui->btnGoogleMail, &QPushButton::clicked, this, [this](){
      this->mAuthManager.startLogin(QtEnumToQString<OAuthProvider::Provider>(OAuthProvider::GOOGLE));
   });
   connect(ui->btnAppleID, &QPushButton::clicked, this, [this]() {
      this->mAuthManager.startLogin(QtEnumToQString<OAuthProvider::Provider>(OAuthProvider::APPLE));
   });
   connect(ui->btnSkipAuthen, &QPushButton::clicked, this, [this]() {
      this->hide();
      this->mpMainWindow->show();
   });
}
