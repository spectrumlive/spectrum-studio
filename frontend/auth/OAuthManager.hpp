#pragma once

#include <QtCore>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QDesktopServices>
#include <QTcpServer>
#include <QTcpSocket>

namespace OAuthProvider
{
   Q_NAMESPACE
   
   enum Provider
   {
      GOOGLE,
      APPLE
   };
   Q_ENUM_NS(Provider);
}

template <typename QEnum>
QString QtEnumToQString(const QEnum value)
{
   return QString(QMetaEnum::fromType<QEnum>().valueToKey((int)value)); // or c++23 version .valueToKey(std::to_underlying(value))
}

class OAuthManager : public QObject {
	Q_OBJECT
   
 public:
	explicit OAuthManager(QObject *parent = nullptr);
   void startLogin(QString strProvider);

signals:
   void loginSuccess(const QString &accessToken);
	void loginFailed(const QString &error);

private slots:
   void handleNewConnection();
	void fetchUserInfo();

private:
	QNetworkAccessManager networkManager;
	QTcpServer server;
	QString accessToken;
	const QString SUPABASE_URL = "https://supadev.dome.cloud";
	const QString SUPABASE_CLIENT_ID = "your-client-id";
	const QString REDIRECT_URI = "http://localhost:3000";  // Local server to capture token
};

