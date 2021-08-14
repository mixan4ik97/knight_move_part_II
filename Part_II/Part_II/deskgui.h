#ifndef DESKGUI_H
#define DESKGUI_H

#include <QMainWindow>

namespace Ui {
class DeskGUI;
}

class DeskGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit DeskGUI(QWidget *parent = 0);
    ~DeskGUI();

private slots:
    void on_pushButton_start_clicked();

    void on_pushButton_stop_clicked();

private:
    Ui::DeskGUI *ui;
};

#endif // DESKGUI_H
