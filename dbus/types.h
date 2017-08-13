#ifndef TYPES_H
#define TYPES_H

#include <QtDBus>

struct UnitFile {
    QString path;
    QString state;
};

typedef QList<UnitFile> UnitFileList;

Q_DECLARE_METATYPE(UnitFile)
Q_DECLARE_METATYPE(UnitFileList)

QDBusArgument &operator<<(QDBusArgument &argument, const UnitFile &uf);
const QDBusArgument &operator>>(const QDBusArgument &argument, UnitFile &uf);

#endif // TYPES_H
