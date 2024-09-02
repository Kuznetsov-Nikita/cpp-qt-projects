#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <complex>
#include <sstream>
#include <iomanip>

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_solveButton_clicked() {
    std::complex<double> a, b, c, d;
    a = ui->avalue->value();
    b = ui->bvalue->value();
    c = ui->cvalue->value();
    d = b * b - 4.0 * a * c;
    
    std::ostringstream out;
    out << "Уравнение: ";
    
    if (a.real() != 0.0) {
        if (a * a == 1.0) {
            if (a.real() > 0.0) {
                out << "x^2";
            } else {
                out << "x^2";
            }
        } else {
            out << std::fixed << std::setprecision(2) << a.real() << "x^2";
        }
    }
    
    if (b.real() != 0.0) {
        if (b * b == 1.0) {
            if (b.real() > 0.0) {
                out << "+x";
            } else {
                out << "-x";
            }
        } else {
            if (b.real() > 0.0) {
                out << "+" << std::setprecision(2) << b.real() << "x";
            } else {
                out << std::setprecision(2) << b.real() << "x";
            }
        }
    }
    
    if (c.real() != 0.0) {
        if (c.real() > 0.0) {
            out << "+" << std::setprecision(2) << c.real();
        } else {
            out << std::setprecision(2) << c.real();
        }
    }
    
    out << "\n";
    out << "Дискриминант: " << d.real() << "\n";
    
    if(d.real() != 0.0) {
        out << "x1 = " << -(b.real() + sqrt(d).real()) / (2.0 * a.real());
        if (sqrt(d).imag() != 0.0) {
            if (-sqrt(d).imag() / (2.0 * a.real()) > 0.0) {
                out << "+" << -sqrt(d).imag() / (2.0 * a.real()) << "i";
            } else {
                out << -sqrt(d).imag() / (2.0 * a.real()) << "i";
            }
        }
        
        out << "\n";
        out << "x2 = " << (-b.real() + sqrt(d).real()) / (2.0 * a.real());
        
        if (sqrt(d).imag() != 0.0) {
            if (sqrt(d).imag() / (2.0 * a.real()) > 0.0) {
                out << "+" << sqrt(d).imag() / (2.0 * a.real()) << "i";
            } else {
                out << sqrt(d).imag() / (2.0 * a.real()) << "i";
            }
        }
        
        out << "\n";
    } else {
        d = -b.real() / (2.0 * a.real());
        out << "x = " << d.real();
    }
    
    out << '\n';
    ui->outputarea->setText(out.str().c_str());
}
