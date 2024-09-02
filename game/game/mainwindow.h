#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow: public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private slots:
    void on_begin_button_clicked();
    void on_end_button_clicked();
    void on_make_atack_clicked();
    void on_def_zone_currentIndexChanged(int index);
    void on_attack_zone_currentIndexChanged(int index);

private:
    Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H
