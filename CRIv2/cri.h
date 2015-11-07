#ifndef CRI_H
#define CRI_H

#include <QMainWindow>

namespace Ui {
class CRI;
}

class CRI : public QMainWindow
{
    Q_OBJECT

public:
    explicit CRI(QWidget *parent = 0);
    ~CRI();

private slots:
    void on_pushButton_clicked();

    void on_Exit_Button_clicked();

    void on_pushButton_2_clicked();

    void on_Calibrate_button_clicked();

private:
    Ui::CRI *ui;
};

#endif // CRI_H
