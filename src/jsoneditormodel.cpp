#include "jsoneditormodel.h"

JsonEditorModel::JsonEditorModel(QObject *parent)
    : QAbstractListModel{parent}
{
    json_worker_ = new JsonWorker(this);
}

int JsonEditorModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }
    return data_.size();
}

QVariant JsonEditorModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant{};
    }

    const Entity &temp = data_[index.row()];

    switch (role)
    {
    case ModelRoles::KEY:
    {
        return temp.key;
    }
    case ModelRoles::VALUE:
    {
        return temp.value;
    }
    case ModelRoles::TYPE:
    {
        return temp.type;
    }
    default: return QVariant{};
    }
}

bool JsonEditorModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
    {
        return false;
    }

    switch (role)
    {
    case ModelRoles::KEY:
    {
        return false; // ключи не меняем
    }
    case ModelRoles::VALUE:
    {
        data_[index.row()].value = value;
        break;
    }
    case ModelRoles::TYPE:
    {
        return false;
    }
    default: return false;
    }

    emit dataChanged(index, index, QVector<int>() << role);
    return true;
}

Qt::ItemFlags JsonEditorModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return Qt::ItemIsEnabled;
    }
    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

QHash<int, QByteArray> JsonEditorModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(KEY,   "key");
    roles.insert(VALUE, "value");
    roles.insert(TYPE,  "type");
    return roles;
}

void JsonEditorModel::pushData(const QString &key, const QVariant &value, int type)
{
    beginInsertRows(QModelIndex{}, data_.size(), data_.size());
    data_.push_back({key, value, type});
    endInsertRows();
}

void JsonEditorModel::openJson(const QUrl &path)
{
    auto json = json_worker_->readJson(path.toLocalFile());

    if (json)
    {
        const QJsonDocument &doc = json.value();
        QJsonObject object;

        if (doc.isArray())
        {
            object = doc.array().first().toObject();
        }
        else if (doc.isObject())
        {
            object = doc.object();
        }

        beginResetModel();
        data_.clear();
        endResetModel();

        for (const auto &key : object.keys()) {
            QVariant value = object.value(key).toVariant();

            /*  В перечислении QJsonValue::Type (qt 5.15) нет целочисленного флага,
             * поэтому будем сами проверять, является ли число целым
             */
            if(value.toJsonValue().type() == QJsonValue::Type::Double) // для разрабора берем только double
            {
                if (value.toInt() == value.toDouble())
                {
                    /*В type будет id из QMetaType::Type*/
                    pushData(key, value, static_cast<quint64>(QVariant::Type::Int));
                    continue;
                }
            }
            pushData(key, value, value.type());
        }
        setMessage(QString("Выбранный файл: %1").arg(path.fileName()));
    }
    else
    {
        setMessage(QStringLiteral("Ошибка чтения json файла. Причина: Некорректный файл"));
    }
}

void JsonEditorModel::saveJson()
{
    auto get_type = [](Entity tuple)
    {
        switch (static_cast<QMetaType::Type>(tuple.type))
        {
        case QMetaType::Double:     return QJsonValue(tuple.value.toDouble());
        case QMetaType::Int:        return QJsonValue(tuple.value.toInt());
        case QMetaType::Bool:       return QJsonValue(tuple.value.toBool());
        case QMetaType::QString:    return QJsonValue(tuple.value.toString());
        default:                    return QJsonValue(tuple.value.toString());
        };
    };

    QJsonObject object;
    for (const auto &tuple : qAsConst(data_))
    {
        object.insert(tuple.key, get_type(tuple));
    }

    if(json_worker_->saveJson(object))
    {
        setMessage(QStringLiteral("Файл успешно сохранен"));
    }
    else
    {
        setMessage(QStringLiteral("Неудалось сохранить файл"));
    }
}

QString JsonEditorModel::message() const
{
    return message_;
}

void JsonEditorModel::setMessage(const QString &message)
{
    message_ = message;
    emit messageChanged();
}
