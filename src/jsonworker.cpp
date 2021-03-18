#include "jsonworker.h"

JsonWorker::JsonWorker(QObject *parent)
    : QObject{parent}
{

}

std::optional<QJsonDocument> JsonWorker::readJson(const QString &path)
{
    current_path = path;

    QFile in(path);
    in.open(QIODevice::ReadOnly);
    auto bytes = in.readAll();
    in.close();

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(bytes, &error);

    if (error.error == QJsonParseError::NoError)
    {
        return doc;
    }
    else
    {
        qCritical() << "Json parse error, reason: " << error.errorString();
        return std::nullopt;
    }
}

bool JsonWorker::saveJson(const QJsonObject &obj)
{
    QFile out(current_path);
    if(out.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QJsonArray array;
        array.push_back(obj);
        out.write(QJsonDocument(array).toJson(QJsonDocument::JsonFormat::Indented));
        out.waitForBytesWritten(1000);
        out.close();
        return true;
    }
    return false;
}
