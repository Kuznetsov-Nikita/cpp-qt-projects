#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<random>
#include<ctime>

class Fighter {
private:
    int health;

    std::pair<uint8_t, bool> head = {1, 0};
    std::pair<uint8_t, bool> body = {2, 0};
    std::pair<uint8_t, bool> legs = {3, 0};

    uint8_t current_attack_zone;

    void missed_Damage() {
        health -= 5;
    }

public:
    Fighter() {
        health = 100;
    }

    void setAttackZone(uint8_t attack_zone) {
        current_attack_zone = attack_zone;
    }

    uint8_t getAttackZone() {
        return current_attack_zone;
    }

    uint8_t getBlockZone() {
        if (head.second) {
            return head.first;
        }

        if (body.second) {
            return body.first;
        }

        if (legs.second) {
            return legs.first;
        }

        return 0;
    }

    void atacked_Damage() {
        health -= 10;
    }

    bool Attack(uint8_t zone_num, Fighter& enemy) {
        if (zone_num != enemy.getBlockZone()) {
            enemy.atacked_Damage();
            return true;
        } else {
            missed_Damage();
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
                legs.second = 1;
                break;
            default:
                break;
        }
        return;
    }

    void clearBlockZone() {
        head.second = 0;
        body.second = 0;
        legs.second = 0;
    }

    int getHealth() {
        return health;
    }

    void setHealth(int hp = 100) {
        health = hp;
    }
};

Fighter player, bot;

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->label->hide();
    ui->label_2->hide();
    ui->bot_health_2->hide();
    ui->player_health->hide();
    ui->attack_zone->hide();
    ui->def_zone->hide();
    ui->make_atack->hide();
    ui->end_button->hide();

    Fighter player, bot;
    ui->player_health->setNum(player.getHealth());
    ui->bot_health_2->setNum(bot.getHealth());
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_begin_button_clicked() {
    ui->label->show();
    ui->label_2->show();
    ui->bot_health_2->show();
    ui->player_health->show();
    ui->attack_zone->show();
    ui->def_zone->show();
    ui->make_atack->show();
    ui->bot_attack->show();
    ui->bot_defend->show();

    ui->begin_button->hide();
    ui->end_button->show();

    player.setHealth();
    bot.setHealth();
    ui->player_health->setNum(player.getHealth());
    ui->bot_health_2->setNum(bot.getHealth());
}

void MainWindow::on_end_button_clicked() {
    ui->label->hide();
    ui->label_2->hide();
    ui->bot_health_2->hide();
    ui->player_health->hide();
    ui->attack_zone->hide();
    ui->def_zone->hide();
    ui->make_atack->hide();
    ui->end_button->hide();
    ui->bot_attack->hide();
    ui->bot_defend->hide();

    ui->begin_button->show();
    ui->end_button->hide();

    player.setHealth();
    bot.setHealth();
}

void MainWindow::on_make_atack_clicked() {
    uint8_t zone;
    std::mt19937 generator(time(0));
    std::uniform_real_distribution<> rand_dia(0, 3);
    
    if (rand_dia(generator) < 1) {
        zone = 1;
        ui->bot_defend->setText("Голова");
    } else if (rand_dia(generator) < 2) {
        zone = 2;
        ui->bot_defend->setText("Туловище");
    } else {
        zone = 3;
        ui->bot_defend->setText("Ноги");
    }
    bot.setBlockZone(zone);

    if (player.Attack(player.getAttackZone(), bot)) {
        ui->bot_health_2->setNum(bot.getHealth());
    } else {
        ui->player_health->setNum(player.getHealth());
    }

    bot.clearBlockZone();
    
    if (rand_dia(generator) < 1) {
        zone = 1;
        ui->bot_attack->setText("Голова");
    } else if (rand_dia(generator) < 2) {
        zone = 2;
        ui->bot_attack->setText("Туловище");
    } else {
        zone = 3;
        ui->bot_attack->setText("Ноги");
    }

    if (bot.Attack(zone, bot)) {
        ui->player_health->setNum(bot.getHealth());
    } else {
        ui->bot_health_2->setNum(player.getHealth());
    }
}

void MainWindow::on_def_zone_currentIndexChanged(int index) {
    player.clearBlockZone();
    player.setBlockZone(index + 1);
}

void MainWindow::on_attack_zone_currentIndexChanged(int index) {
    player.setAttackZone(index + 1);
}
