#ifndef JSONEDITORMODEL_H
#define JSONEDITORMODEL_H

#include <QObject>
#include <QList>
#include <QUrl>
#include <QAbstractListModel>

#include "jsonworker.h"

class JsonEditorModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString _message READ message WRITE setMessage NOTIFY messageChanged)

public:
    explicit JsonEditorModel(QObject *parent = nullptr);

    Q_INVOKABLE void openJson(const QUrl &path);
    Q_INVOKABLE void saveJson();

    QString message() const;
    void setMessage(const QString &message);

public:// QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QHash<int, QByteArray> roleNames() const override;

signals:
    void messageChanged();

private:
    void pushData(const QString &key, const QVariant &value, int type);

private:
    JsonWorker *json_worker_{};
    QString message_;

    enum ModelRoles
    {
        KEY = Qt::UserRole + 1,
        VALUE,
        TYPE
    };

    struct Entity
    {
        QString key;
        QVariant value;
        int type;
    };

    QList<Entity> data_;
};

#endif // JSONEDITORMODEL_H
