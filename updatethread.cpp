#include "updatethread.h"

UpdateThread::UpdateThread(QObject *parent) :
    QThread(parent), currentReply_(0)
{
  networkProxy_.setHostName("10.0.0.172");
  networkProxy_.setPort(3150);
  manager_.setProxy(networkProxy_);

  connect(&manager_, SIGNAL(finished(QNetworkReply*)),
      this, SLOT(finished(QNetworkReply*)));

  qDebug() << objectName() << "::constructor";
}

UpdateThread::~UpdateThread()
{
  qDebug() << objectName() << "::~destructor";
}

void UpdateThread::run()
{
  qDebug() << objectName() << "::run()";
  return;
}

/*! \brief ���������� �������� ������ � ������� �������� **********************/
void UpdateThread::getUrl(const QUrl &url)
{
  urlsQueue_.enqueue(url);
  qDebug() << "urlsQueue_ <<" << url << "count=" << urlsQueue_.count();
  getQueuedUrl();
}

/*! \brief ��������� ������� �������� *****************************************/
void UpdateThread::getQueuedUrl()
{
  if (!currentUrl_.isEmpty()) return;

  if (!urlsQueue_.isEmpty()) {
    currentUrl_ = urlsQueue_.dequeue();
    qDebug() << "urlsQueue_ >>" << currentUrl_ << "count=" << urlsQueue_.count();
    get(currentUrl_);
  } else {
    qDebug() << "urlsQueue_ -- count=" << urlsQueue_.count();
    emit getUrlDone(1);
  }
}

/*! \brief ��������� �������� ������� � ������������� �������� ****************/
void UpdateThread::get(const QUrl &url)
{
  qDebug() << objectName() << "::get:" << url;
  QNetworkRequest request(url);
  if (currentReply_) {
      currentReply_->disconnect(this);
      currentReply_->deleteLater();
  }
  currentReply_ = manager_.get(request);
  connect(currentReply_, SIGNAL(readyRead()), this, SLOT(readyRead()));
  connect(currentReply_, SIGNAL(metaDataChanged()), this, SLOT(metaDataChanged()));
  connect(currentReply_, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));

//  start(QThread::LowPriority);
}

/*! \brief ������ ������ �������� �� ����
 *
 *   We read all the available data, and pass it to the XML
 *   stream reader. Then we call the XML parsing function.
 ******************************************************************************/
void UpdateThread::readyRead()
{
  int statusCode = currentReply_->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
  if (statusCode >= 200 && statusCode < 300) {
    QByteArray data = currentReply_->readAll();
    emit readedXml(data, currentUrl_);
  }
}

/*! \brief ��������� ������� ��������� ���������� ��������-������� ************/
void UpdateThread::metaDataChanged()
{
  QUrl redirectionTarget = currentReply_->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
  if (redirectionTarget.isValid()) {
    qDebug() << objectName() << "get redirect...";
    get(redirectionTarget);
  }
}

/*! \brief ��������� ������ html-������� **************************************/
void UpdateThread::error(QNetworkReply::NetworkError)
{
  qDebug() << objectName() << "::error retrieving RSS feed";
  currentReply_->disconnect(this);
  currentReply_->deleteLater();
  currentReply_ = 0;
  emit getUrlDone(-1);
  currentUrl_.clear();
  getQueuedUrl();
}

/*! \brief ���������� ��������� �������� �������

    The default behavior is to keep the text edit read only.

    If an error has occurred, the user interface is made available
    to the user for further input, allowing a new fetch to be
    started.

    If the HTTP get request has finished, we make the
    user interface available to the user for further input.
 ******************************************************************************/
void UpdateThread::finished(QNetworkReply *reply)
{
  Q_UNUSED(reply);
  qDebug() << objectName() << "::finished";
  emit getUrlDone(0);
  currentUrl_.clear();
  getQueuedUrl();
}

void UpdateThread::setProxyType(QNetworkProxy::ProxyType type)
{
  networkProxy_.setType(type);
  QNetworkProxy::setApplicationProxy(networkProxy_);
}