#include "Window.h"

Window::Window(QWidget *parent) :
    QMdiSubWindow(parent)
{
    this->setAttribute(Qt::WA_DeleteOnClose,true);
}

Window::~Window()
{

}
