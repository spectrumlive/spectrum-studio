#include "OAuthManager.hpp"
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

OAuthManager::OAuthManager(QObject *parent) : QObject(parent) {
   connect(&server, &QTcpServer::newConnection, this, &OAuthManager::handleNewConnection);
   if (!server.listen(QHostAddress::LocalHost, 3000)) {
      emit loginFailed("Failed to start local server.");
      return;
   }
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
