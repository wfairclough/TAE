#ifndef TAWINDOW_H
#define TAWINDOW_H

#include <QMainWindow>

namespace Ui {
class TaWindow;
}

class TaWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit TaWindow(QWidget *parent = 0);
    ~TaWindow();
    
private:
    Ui::TaWindow *ui;
};

#endif // TAWINDOW_H
