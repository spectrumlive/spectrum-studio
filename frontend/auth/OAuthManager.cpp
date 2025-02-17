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

#include "OAuthManager.hpp"
#include "util/config-file.h"
#include <widgets/OBSBasic.hpp>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

#if !defined(_WIN32) && !defined(__APPLE__)
#include <obs-nix-platform.h>
#endif
#include <qt-wrappers.hpp>

OAuthManager::OAuthManager(QObject *parent) : QObject(parent) {
   connect(&server, &QTcpServer::newConnection, this, &OAuthManager::handleNewConnection);
}

void OAuthManager::startLogin(QString strProvider) {
   server.close();
   // Start local server to capture token
   if (!server.listen(QHostAddress::LocalHost, 3000)) {
     emit loginFailed("Failed to start local server.");
     return;
   }

   // Construct Supabase OAuth URL
   QUrl authUrl(QString("%1/auth/v1/authorize").arg(SUPABASE_URL));
   QUrlQuery query;
   query.addQueryItem("provider", strProvider.toLower());  // Change for other providers
   query.addQueryItem("redirect_to", REDIRECT_URI);
   authUrl.setQuery(query);
   
   qDebug() << authUrl.url() << authUrl.path() << authUrl.query();

   // Open the URL in the default browser
   QDesktopServices::openUrl(authUrl);
}

void OAuthManager::handleNewConnection() {
   QTcpSocket *socket = server.nextPendingConnection();
   if (!socket)
      return;

   socket->waitForReadyRead();
   QString request = socket->readAll();
   server.close();
   
   QRegularExpression tokenRegex("access_token=([^&\\s]+)");
   QRegularExpressionMatch match = tokenRegex.match(request);
   
   qDebug() << request;

   if (match.hasMatch()) {
      accessToken = match.captured(1);
      emit loginSuccess(accessToken);
      fetchUserInfo();
   } else {
      emit loginFailed("Token not found.");
   }

   // Send response to browser and close
   QByteArray response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"
                    "<html><body><h1>Login Successful</h1>You can close this window.</body></html>";
   socket->write(response);
   socket->flush();
   socket->waitForBytesWritten();
   socket->close();
   socket->deleteLater();
   
}

void OAuthManager::fetchUserInfo() {
    QNetworkRequest request(QUrl(QString("%1/auth/v1/user").arg(SUPABASE_URL)));
    request.setRawHeader("Authorization", "Bearer " + accessToken.toUtf8());

    QNetworkReply *reply = networkManager.get(request);
    connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "User Info:" << reply->readAll();
        } else {
            qDebug() << "Failed to fetch user info:" << reply->errorString();
        }
        reply->deleteLater();
    });
}

void OAuthManager::saveUserInfo(const QString &strToken, const QString &strDonationSlug,
                                const QString &strLiveSlug, const QString &strWallet) {
   QStringList listJwtParts = strToken.split(".");
   QByteArray input = QByteArray::fromBase64(listJwtParts.at(1).toUtf8());
   QJsonObject jObjData = QJsonDocument::fromJson(input).object();
   QJsonObject userMetaData = jObjData["user_metadata"].toObject();
   QJsonObject appMetaData = jObjData["app_metadata"].toObject();
   
   config_set_string(App()->GetUserConfig(), "UserInfo", "email", userMetaData["email"].toString().toStdString().c_str());
   config_set_string(App()->GetUserConfig(), "UserInfo", "full_name", userMetaData["full_name"].toString().toStdString().c_str());
   config_set_string(App()->GetUserConfig(), "UserInfo", "avatar_url", userMetaData["avatar_url"].toString().toStdString().c_str());
   config_set_string(App()->GetUserConfig(), "UserInfo", "provider", appMetaData["provider"].toString().toStdString().c_str());
   config_set_int(App()->GetUserConfig(), "UserInfo", "timeout", jObjData["exp"].toInt());
   config_set_string(App()->GetUserConfig(), "UserInfo", "token", strToken.toStdString().c_str());
   config_set_string(App()->GetUserConfig(), "UserInfo", "donation_slug", strDonationSlug.toStdString().c_str());
   config_set_string(App()->GetUserConfig(), "UserInfo", "live_slug", strLiveSlug.toStdString().c_str());
   config_set_string(App()->GetUserConfig(), "UserInfo", "wallet_address", strWallet.toStdString().c_str());
}

void OAuthManager::clearUserInfo() {
   
}
