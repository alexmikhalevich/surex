#include <qt5/QtGui/QOpenGLFunctions>
#include <qt5/QtGui/QWindow>
#include <qt5/QtCore/QEvent>
#include <qt5/QtGui/QPainter>
#include <qt5/QtCore/QCoreApplication>
#include <qt5/QtGui/QSurfaceFormat>
#include <qt5/QtCore/QScopedPointer>
#include "csettings.h"
#include "cmainengine.h"

class CMainWindow : public QWindow, protected QOpenGLFunctions {
    Q_OBJECT
private:
    QSharedPointer<CMainEngine> m_engine;
    QSharedPointer<QOpenGLContext> m_context;
    bool m_update_pending;
protected:
    bool event(QEvent* event);
    void exposeEvent(QExposeEvent* event);
public:
    explicit CMainWindow(QWindow* parent = 0);
    ~CMainWindow();
    virtual void render(QPainter* painter);
    virtual void render();
    virtual void initialize();
public slots:
    void renderLater();
    void renderNow();
};
