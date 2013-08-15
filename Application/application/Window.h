#ifndef WINDOW_H
#define WINDOW_H

#include <QMdiSubWindow>
#include <QVBoxLayout>
#include <QSize>

class Window : public QMdiSubWindow
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);
    virtual ~Window();


protected:

    static const int DEFAULT_WINDOW_WIDTH  = 400;
    static const int DEFAULT_WINDOW_HEIGHT = 300;

signals:
    
public slots:
    

};

#endif // WINDOW_H
