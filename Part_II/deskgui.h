#ifndef DESKGUI_H
#define DESKGUI_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include "knightmovecalculator.h"
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
    void calculOut(QByteArray out);
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void on_pushButton_start_clicked();

    void on_pushButton_stop_clicked();

    void addHodForTimeout();


signals:
    void startCalcul(uint8_t pos1, uint8_t pos2);
    void stopCalcul();
    void exit();
private:
    bool isCorrectCoordinate(QString pos);
    void setState(const uint8_t& st);
    void cleanDesk();
    QBrush ic[4];
    uint8_t step;
    QMessageBox qmb;
    Ui::DeskGUI *ui;
    QTimer timer;
    uint8_t cur_hod;
    uint8_t state;
    QImage img[4];
};

#endif // DESKGUI_H
