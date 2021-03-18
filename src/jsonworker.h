#ifndef JSONWORKER_H
#define JSONWORKER_H

#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>

#include <optional>

class JsonWorker : public QObject
{
    Q_OBJECT
public:
    explicit JsonWorker(QObject *parent = nullptr);

    std::optional<QJsonDocument> readJson(const QString &path);
    bool saveJson(const QJsonObject &obj);

private:
    QString current_path;
};

#endif // JSONWORKER_H
