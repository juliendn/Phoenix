
#ifndef CACHEIMAGE_H
#define CACHEIMAGE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSslError>
#include <QFile>
#include <QFileInfo>
#include <QUrl>
#include <QQuickItem>
#include <QImage>
#include <QDir>


class CachedImage : public QObject
{
    Q_OBJECT
    //Remote url
    Q_PROPERTY(QString imgsrc READ imgsrc WRITE setImgsrc NOTIFY imgsrcChanged)
    //Local url after downloading and saving the image
    Q_PROPERTY(QString localsrc READ localsrc NOTIFY localsrcChanged)
    //Subfolder where the image is stored in
    Q_PROPERTY(QString folder READ folder WRITE setFolder NOTIFY folderChanged)

    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(QString cacheDirectory READ cacheDirectory  WRITE setCacheDirectory  NOTIFY cacheDirectoryChanged)


    QNetworkAccessManager manager;

public:
    explicit CachedImage(QObject *parent = 0);
    void doDownload(const QUrl &url);
    QStringList saveFileName();
    bool saveToDisk(const QString &filename, QIODevice *data);
    void setImgsrc(const QString &imgsrc);

    QString imgsrc();
    QString localsrc();
    QString folder();
    QString fileName();
    QString suffix();
    QString cacheDirectory();

    void setFileName(const QString &fileName);
    void setFolder(const QString &folder);
    void setCacheDirectory(const QString &cacheDirectory);

    Q_INVOKABLE void start();

private:
    QString m_cache_directory;
    QString m_localUrl;
    QString m_src;
    QString m_folder;
    QString m_filename;
    QString m_suffix;


public slots:
    void downloadFinished(QNetworkReply *reply);
    void cacheImage();
    void returnCached(QUrl imgUrl);

signals:
    void imgsrcChanged();
    void localsrcChanged();
    void folderChanged();
    void fileNameChanged();
    void cacheLoaded(bool);
    void cacheDirectoryChanged();
};

#endif // CACHEIMAGE_H
