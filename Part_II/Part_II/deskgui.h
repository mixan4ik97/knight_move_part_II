#ifndef DESKGUI_H
#define DESKGUI_H

#include <QMainWindow>
#include <QMessageBox>
namespace Ui {
class DeskGUI;
}

class DeskGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit DeskGUI(QWidget *parent = 0);
    ~DeskGUI();
public slots:
    void finish(QVector<uint8_t> out);

private slots:
    void on_pushButton_start_clicked();

    void on_pushButton_stop_clicked();
signals:
    void startCalcul(uint8_t pos1, uint8_t pos2);
    void stopCalcul();

private:
    bool isCorrectCoordinate(QString pos);
    uint8_t step;
    Ui::DeskGUI *ui;
};

#endif // DESKGUI_H
