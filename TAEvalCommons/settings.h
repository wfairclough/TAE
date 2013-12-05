#ifndef SETTINGS_H
#define SETTINGS_H


#if defined(Q_OS_DARWIN)
    #define CLIENT_SETTINGS_FILE_NAME "taeval.plist"
    #define SERVER_SETTINGS_FILE_NAME "taeval-server.plist"
#elif defined(Q_OS_UNIX)
    #define CLIENT_SETTINGS_FILE_NAME "taeval.cfg"
    #define SERVER_SETTINGS_FILE_NAME "taeval-server.cfg"
#else
#error "We don't support that version yet..."
#endif


#define CONNECTION_HOST "connection/host"
#define CONNECTION_PORT "connection/port"
#define DATABASE_PATH "database/path"
#define DATABASE_NAME "database/name"

#endif // SETTINGS_H
