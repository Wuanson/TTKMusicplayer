#include "musicsongdownloadthread.h"

MusicSongDownloadThread::MusicSongDownloadThread(const QString &url, const QString &save,
                                                       QObject *parent)
    : MusicDownLoadThreadAbstract(url, save, parent)
{

}

void MusicSongDownloadThread::startToDownload()
{
    if( !m_file->exists() || m_file->size() < 4 )
    {
        if( m_file->open(QIODevice::WriteOnly) )
        {
            m_manager = new QNetworkAccessManager(this);
            startRequest(m_url);
        }
        else
        {
            qDebug() <<"The Music or pic file create failed";
            emit musicDownLoadFinished("The Music or pic file create failed");
            deleteAll();
        }
    }
}

void MusicSongDownloadThread::startRequest(const QUrl& url)
{
    m_reply = m_manager->get( QNetworkRequest(url));
    connect(m_reply, SIGNAL(finished()), this, SLOT(downLoadFinished()));
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)),
                this, SLOT(replyError(QNetworkReply::NetworkError)) );
    connect(m_reply, SIGNAL(readyRead()),this, SLOT(downLoadReadyRead()));
}

void MusicSongDownloadThread::downLoadFinished()
{
    if(!m_file) return;

    m_file->flush();
    m_file->close();
    QVariant redirectionTarget = m_reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if(m_reply->error())
    {
        m_file->remove();
    }
    else if(!redirectionTarget.isNull())
    {
//       QUrl newUrl = reply->url().resolved(redirectionTarget.toUrl());
        m_reply->deleteLater();
        m_file->open(QIODevice::WriteOnly);
        m_file->resize(0);
        startRequest(m_reply->url().resolved(redirectionTarget.toUrl()));
        return;
    }
    else
    {
        emit musicDownLoadFinished("Music");
        qDebug()<<"Music or pic download has finished!";
        deleteAll();
    }
}

void MusicSongDownloadThread::downLoadReadyRead()
{
    if(m_file)
      m_file->write(m_reply->readAll());
}
