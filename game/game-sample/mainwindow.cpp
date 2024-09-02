#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <random>
#include <ctime>

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->label->hide();
    ui->label_2->hide();
    ui->bot_health->hide();
    ui->player_health->hide();
    ui->attack_zone->hide();
    ui->defend_zone->hide();
    ui->attack_button->hide();
    ui->exitgame->hide();
    ui->label_3->hide();
    ui->label_6->hide();
    ui->bot_attack->hide();
    ui->bot_defend->hide();
}

class fighter {
private:
    int health;
    std::pair<uint8_t, bool> head = {1, 0};
    std::pair<uint8_t, bool> body = {2, 0};
    std::pair<uint8_t, bool> leg = {3, 0};
    uint8_t current_attack_zone;
    
    void missed_damage() {
        health -=5;
    }
    
public:
    fighter() {
        health = 100;
    }
    
    uint8_t getAttackZone() {
        return current_attack_zone;
    }
    
    void setAttackZone(uint8_t attack_zone) {
        current_attack_zone = attack_zone;
    }
    
    uint8_t getBlockZone() {
        if (head.second) {
            return head.first;
        }
        if (body.second) {
            return body.first;
        }
        if (leg.second) {
            return leg.first;
        }
        
        return 0;
    }
    
    void attacked_damage() {
        health -= 10;
    }
    
    bool attack(uint8_t zone_num, fighter& enemy) {
        if (zone_num != enemy.getBlockZone()) {
            enemy.attacked_damage();
            return true;
        } else {
            missed_damage();
            return false;
        }
    }
    
    void setBlockZone(uint8_t zun_num) {
        switch (zun_num) {
            case 1:
                head.second = 1;
                break;
            case 2:
                body.second = 1;
                break;
            case 3:
                leg.second = 1;
                break;
            default:
                break;
        }
        return;
    }
    
    void clear_block_zone() {
        head.second = 0;
        body.second = 0;
        leg.second = 0;
    }
    
    void setHealth(int hp = 100) {
        health = hp;
    }
    
    int getHealth() {
        return health;
    }
};

MainWindow::~MainWindow() {
    delete ui;
}

fighter player, bot;

void MainWindow::on_startgame_clicked() {
    ui->label->show();
    ui->label_2->show();
    ui->bot_health->show();
    ui->player_health->show();
    ui->attack_zone->show();
    ui->defend_zone->show();
    ui->attack_button->show();
    ui->label_3->show();
    ui->label_6->show();
    ui->bot_attack->show();
    ui->bot_defend->show();
    ui->startgame->hide();
    ui->exitgame->show();
    player.setHealth();
    bot.setHealth();
    ui->player_health->setNum(player.getHealth());
    ui->bot_health->setNum(bot.getHealth());
}

void MainWindow::on_exitgame_clicked() {
    ui->label->hide();
    ui->label_2->hide();
    ui->bot_health->hide();
    ui->player_health->hide();
    ui->attack_zone->hide();
    ui->defend_zone->hide();
    ui->attack_button->hide();
    ui->exitgame->hide();
    ui->label_3->hide();
    ui->label_6->hide();
    ui->bot_attack->hide();
    ui->bot_defend->hide();
    ui->startgame->show();
    player.setHealth();
    bot.setHealth();
}

void MainWindow::on_attack_button_clicked() {
    uint8_t zone;
    std::mt19937 generator(time(0));
    std::uniform_real_distribution<> rand_dia(0, 3);
    
    if (rand_dia(generator) < 1) {
        zone = 1;
        ui->bot_defend->setText("Голову");
    } else if (rand_dia(generator) < 2) {
        zone = 2;
        ui->bot_defend->setText("Туловище");
    } else {
        zone = 3;
        ui->bot_defend->setText("Ноги");
    }
    bot.setBlockZone(zone);

    if (player.attack(player.getAttackZone(),  bot)) {
        ui->bot_health->setNum(bot.getHealth());
    } else {
        ui->player_health->setNum(player.getHealth());
    }
    
    bot.clear_block_zone();
    
    if (rand_dia(generator) < 1) {
        zone = 1;
        ui->bot_attack->setText("В голову");
    } else if (rand_dia(generator) < 2) {
        zone = 2;
        ui->bot_attack->setText("В туловище");
    } else {
        zone = 3;
        ui->bot_attack->setText("По ногам");
    }
    
    if (bot.attack(zone, player)) {
        ui->player_health->setNum(player.getHealth());
    } else {
        ui->bot_health->setNum(bot.getHealth());
    }
}

void MainWindow::on_defend_zone_currentIndexChanged(int index) {
    player.clear_block_zone();
    player.setBlockZone(index + 1);
}

void MainWindow::on_attack_zone_currentIndexChanged(int index) {
    player.setAttackZone(index + 1);
}
