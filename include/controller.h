#ifndef QT_WEB_SEARCH_CONTROLLER_H
#define QT_WEB_SEARCH_CONTROLLER_H

#include <QObject>

class QQuickView;

class Controller : public QObject {
Q_OBJECT

public:
    explicit Controller(QObject *parent = 0);

    ~Controller();

    void setupUI();

private:
    QQuickView *m_pUIContext;
};

#endif //QT_WEB_SEARCH_CONTROLLER_H
