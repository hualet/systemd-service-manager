#include "types.h"

QDBusArgument& operator<<(QDBusArgument &argument, const UnitFile &uf)
{
    argument.beginStructure();
    argument << uf.path << uf.state;
    argument.endStructure();
    return argument;
}

const QDBusArgument& operator>>(const QDBusArgument &argument, UnitFile &uf)
{
    argument.beginStructure();
    argument >> uf.path >> uf.state;
    argument.endStructure();
    return argument;
}
