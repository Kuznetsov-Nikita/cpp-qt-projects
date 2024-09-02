#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow: public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_startgame_clicked();
    void on_exitgame_clicked();
    void on_attack_button_clicked();
    void on_defend_zone_currentIndexChanged(int index);
    void on_attack_zone_currentIndexChanged(int index);

private:
    Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H
