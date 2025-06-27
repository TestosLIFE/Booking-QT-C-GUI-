#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QIntValidator>
#include <QFile>
#include <QTextStream>
#include <QMenu>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget *fereastra = new QWidget;
    fereastra->resize(800, 800);
    fereastra->setWindowTitle("Booking");

    QPushButton *login = new QPushButton("Login", fereastra);
    QPushButton *inapoi = new QPushButton("Back", fereastra);
    QPushButton *inregistrare = new QPushButton("Register", fereastra);
    QLineEdit *username = new QLineEdit(fereastra);
    username->setPlaceholderText("Username");
    QLineEdit *password = new QLineEdit(fereastra);
    password->setPlaceholderText("Password");
    QLabel *hello = new QLabel("Welcome!", fereastra);

    login->setGeometry(300, 450, 60, 40);
    inapoi->setGeometry(390, 450, 60, 40);
    inregistrare->setGeometry(370, 450, 60, 40);
    username->setGeometry(280, 350, 200, 25);
    password->setGeometry(280, 390, 200, 25);
    hello->setGeometry(350, 100, 200, 25);
    inapoi->hide();

    QLineEdit *code = nullptr;
    QLineEdit *name = nullptr;

    QPushButton *mangalia = nullptr;
    QPushButton *constanta = nullptr;
    QLabel *where = nullptr;
    QWidget *fereastra2 = nullptr;

    auto resetToLogin = [&]() {
        if (code) {
            code->hide();
            delete code;
            code = nullptr;
        }
        if (name) {
            name->hide();
            delete name;
            name = nullptr;
        }
        login->show();
        inapoi->hide();
        inregistrare->setText("Register");
        inregistrare->setGeometry(370, 450, 60, 40);
    };

    QObject::connect(inregistrare, &QPushButton::clicked, [&]() {
        if (!code) {
            code = new QLineEdit(fereastra);
            code->setPlaceholderText("Postal code");
            code->setGeometry(280, 300, 200, 25);
            code->setValidator(new QIntValidator(0, 999999, code));
            code->show();

            name = new QLineEdit(fereastra);
            name->setPlaceholderText("Full name");
            name->setGeometry(280, 250, 200, 25);
            name->show();

            login->hide();
            inapoi->show();
            inregistrare->setGeometry(320, 450, 60, 40);
            inregistrare->setText("Confirm");

            QObject::connect(inapoi, &QPushButton::clicked, resetToLogin);
        } else {
            if (username->text().isEmpty() || password->text().isEmpty() ||
                code->text().isEmpty() || name->text().isEmpty()) {
                QMessageBox::critical(fereastra, "Error", "Please complete all fields!");
                return;
            }

            if (code->text().length() != 6) {
                QMessageBox::critical(fereastra, "Error", "Postal code must be 6 digits!");
                return;
            }

            QFile file("clients.txt");
            if (file.open(QIODevice::Append | QIODevice::Text)) {
                QTextStream out(&file);
                out << "Username: " << username->text() << "\n";
                out << "Password: " << password->text() << "\n";
                out << "Code: " << code->text() << "\n";
                out << "Name: " << name->text() << "\n";
                out << "----------------\n";
                file.close();

                QMessageBox::information(fereastra, "Success", "Account created and saved!");
                resetToLogin();
            } else {
                QMessageBox::critical(fereastra, "Error", "Failed to save account!");
            }
        }
    });

    QObject::connect(login, &QPushButton::clicked, [&]() {
        if (username->text().isEmpty() || password->text().isEmpty()) {
            QMessageBox::critical(fereastra, "Error", "Please enter your data");
            return;
        }

        QFile file("clients.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::critical(fereastra, "Error", "No accounts found!");
            return;
        }

        QTextStream in(&file);
        QString currentUsername, currentPassword;
        bool found = false;

        while (!in.atEnd()) {
            QString line = in.readLine();
            if (line.startsWith("Username: ")) {
                currentUsername = line.mid(10).trimmed();
            } else if (line.startsWith("Password: ")) {
                currentPassword = line.mid(10).trimmed();
                if (currentUsername == username->text() && currentPassword == password->text()) {
                    found = true;
                    break;
                }
            }
        }
        file.close();

        if (!found) {
            QMessageBox::critical(fereastra, "Error", "Invalid username or password!");
            return;
        }

        inregistrare->hide();
        login->hide();
        username->hide();
        password->hide();
        hello->hide();

        if (!where) {
            where = new QLabel("Where do you want?", fereastra);
            where->setGeometry(340, 100, 200, 25);

            mangalia = new QPushButton("Mangalia", fereastra);
            constanta = new QPushButton("Navodari", fereastra);
            mangalia->setGeometry(280, 300, 200, 25);
            constanta->setGeometry(280, 350, 200, 25);

            QMenu *menu = new QMenu(fereastra);
            QAction *opt1 = new QAction("Saturn", menu);
            QAction *opt2 = new QAction("Venus", menu);
            menu->addAction(opt1);
            menu->addAction(opt2);
            mangalia->setMenu(menu);

            fereastra2 = new QWidget();
            fereastra2->resize(800, 800);
            fereastra2->setWindowTitle("Hotels");
            QObject::connect(constanta, &QPushButton::clicked, [&](){
                QMessageBox::information(fereastra2,"Demo", "Demo version");
            });

            QObject::connect(opt1, &QAction::triggered, [=]() {
                fereastra2->show();
                fereastra->hide();
                QPushButton *cleo = new QPushButton("Hotel Cleopatra(****)", fereastra2);
                QPushButton *narcis = new QPushButton("Hotel Narcis(***)", fereastra2);
                QPushButton *balada = new QPushButton("Hotel Balada(***)", fereastra2);
                QLabel *descriere = new QLabel("About Hotel", fereastra2);
                QLabel *cleo1 = new QLabel("The Cleopatra Saturn Hotel in Saturn resort is one of the most famous hotels on the Romanian seaside, located in the Narcis area, so named because of\n the beautiful natural landscapes. This hotel is part of the Cleopatra complex and offers accommodation in a pleasant environment. ", fereastra2);
                QLabel *fac = new QLabel("Comfortable rooms (some with sea view)\n Restaurant with Romanian and international specialties\n Bars and terraces\n Pools and relaxation areas\n Beach access (sometimes for a fee)\nPets allowed (under certain conditions)", fereastra2);
                QLabel *fac1 = new QLabel("Facilites: ", fereastra2);
                QLineEdit *nopti = new QLineEdit(fereastra2);
                QLineEdit *camera = new QLineEdit(fereastra2);
                QLineEdit *pat = new QLineEdit(fereastra2);
                QLineEdit *email = new QLineEdit(fereastra2);
                QPushButton *confirm2 = new QPushButton("Confirm", fereastra2);

                fac1->setGeometry(0, 125, 100, 100);
                fac->setGeometry(0, 130, 400, 300);
                descriere->setGeometry(0, 50, 100, 50);
                cleo1->setGeometry(0, 100, 1000, 40);
                cleo->setGeometry(10, 100, 200, 20);
                narcis->setGeometry(10, 150, 200, 20);
                balada->setGeometry(10, 200, 200, 20);

                cleo->show();
                narcis->show();
                balada->show();

                QMenu *menu1 = new QMenu(fereastra2);
                QMenu *menu2 = new QMenu(fereastra2);
                QMenu *menu3 = new QMenu(fereastra2);
                QAction *luni = new QAction(menu2);
                menu2->addAction(luni);
                QLabel *Reserve1 = new QLabel("Please select the date when you want", fereastra2);
                QPushButton *zile = new QPushButton("Data", fereastra2);
                QPushButton *luni1 = new QPushButton("Month", fereastra2);
                QStringList luni2 = {"April", "May", "June", "July", "August", "September"};
                QPushButton *ani1 = new QPushButton("Year", fereastra2);
                ani1->setGeometry(470, 300, 100, 25);
                ani1->setMenu(menu3);
                QPushButton *confirma1 = new QPushButton("Next", fereastra2);
                confirma1->setGeometry(460, 650, 60, 30);
                QPushButton *inapoi1 = new QPushButton("Back", fereastra2);
                QPushButton *Reserve = new QPushButton("Reserve", fereastra2);


                QObject::connect(cleo, &QPushButton::clicked, [=]() {
                    fereastra2->setWindowTitle("Cleopatra Hotel");
                    narcis->hide();
                    balada->hide();
                    cleo->hide();
                    cleo1->show();
                    fac->show();
                    descriere->show();
                    fac1->show();


                    inapoi1->setGeometry(350, 650, 60, 30);
                    Reserve->setGeometry(420, 650, 60, 30);
                    inapoi1->show();
                    Reserve->show();

                    QObject::connect(Reserve, &QPushButton::clicked, [=]() {
                        Reserve->hide();
                        confirma1->show();
                        cleo1->hide();
                        descriere->hide();
                        fac->hide();
                        fac1->hide();
                        Reserve1->setGeometry(300, 250, 200, 25);
                        Reserve1->show();
                        ani1->show();

                        zile->setGeometry(270, 300, 100, 25);
                        zile->setMenu(menu1);
                        zile->show();
                        luni1->setGeometry(370, 300, 100, 25);
                        luni1->show();

                        for(int i = 1; i <= 31; i++) {
                            QAction *zi = new QAction(QString::number(i), menu1);
                            menu1->addAction(zi);
                            QObject::connect(zi, &QAction::triggered, [=]() {
                                zile->setText("Day: " + QString::number(i));
                                zile->show();
                            });
                        }

                        for (const QString &luna2 : luni2) {
                            QAction *act = new QAction(luna2, menu2);
                            menu2->addAction(act);
                            QObject::connect(act, &QAction::triggered, [=]() {
                                luni1->setText("Month: " + luna2);
                            });
                        }

                        luni1->setMenu(menu2);
                        luni1->show();

                        for (int i = 2025; i <= 2026; i++) {
                            QAction *ani = new QAction(QString::number(i), menu3);
                            menu3->addAction(ani);
                            QObject::connect(ani, &QAction::triggered, [=]() {
                                ani1->setText("Year: " + QString::number(i));
                            });
                        }

                        QObject::connect(confirma1, &QPushButton::clicked, [=]() {
                            QString lunaText = luni1->text().split(": ").last();
                            int anul = ani1->text().split(": ").last().toInt();
                            int ziua2 = zile->text().split(": ").last().toInt();

                            if ((lunaText == "April" && anul == 2025 && ziua2 == 31) ||
                                (lunaText == "April" && anul == 2026 && ziua2 == 31) ||
                                (lunaText == "June" && anul == 2025 && ziua2 == 31) ||
                                (lunaText == "June" && anul == 2026 && ziua2 == 31) ||
                                (lunaText == "September" && anul == 2025 && ziua2 == 31) ||
                                (lunaText == "September" && anul == 2026 && ziua2 == 31)) {
                                QMessageBox::critical(fereastra2, "Error", "The month has only 30 days!");
                            } else {
                                inapoi1->setGeometry(380, 650, 60, 30);
                                confirma1->hide();
                                nopti->setPlaceholderText("How many nights?");
                                camera->setPlaceholderText("How many rooms?");
                                pat->setPlaceholderText("Double/Triple beds?");
                                email->setPlaceholderText("Email: ");
                                nopti->setGeometry(300, 300, 200, 25);
                                camera->setGeometry(300, 350, 200, 25);
                                pat->setGeometry(300, 400, 200, 25);
                                email->setGeometry(300, 450, 200, 25);
                                confirm2->setGeometry(200, 550, 500, 40);
                                confirm2->show();
                                pat->show();
                                nopti->show();
                                camera->show();
                                zile->hide();
                                luni1->hide();
                                ani1->hide();
                                email->show();

                                QObject::connect(confirm2, &QPushButton::clicked, [=]() {
                                    descriere->hide();
                                    cleo1->hide();
                                    fac->hide();
                                    fac1->hide();
                                    luni1->hide();
                                    zile->hide();
                                    Reserve1->hide();
                                    ani1->hide();
                                    confirma1->hide();

                                    if(nopti->text().isEmpty() || camera->text().isEmpty() || email->text().isEmpty() || pat->text().isEmpty()) {
                                        QMessageBox::critical(fereastra2, "Error", "Please fill the boxes");
                                    } else {
                                        QMessageBox::information(fereastra2, "Successful", "Your reservation at Cleopatra Hotel has been made successfully.");
                                        fereastra2->hide();
                                        fereastra->show();
                                        pat->hide();
                                        camera->hide();
                                        nopti->hide();
                                        email->hide();
                                        confirm2->hide();
                                        inapoi1->hide();
                                    }
                                });
                            }
                        });
                    });

                    QObject::connect(inapoi1, &QPushButton::clicked, [=]() {
                        fereastra2->hide();
                        Reserve->hide();
                        inapoi1->hide();
                        descriere->hide();
                        cleo1->hide();
                        fac->hide();
                        fac1->hide();
                        luni1->hide();
                        zile->hide();
                        Reserve1->hide();
                        ani1->hide();
                        confirma1->hide();
                        pat->hide();
                        nopti->hide();
                        camera->hide();
                        email->hide();
                        confirm2->hide();
                        fereastra->show();
                    });
                });


                QObject::connect(balada, &QPushButton::clicked, [=]() {
                    fereastra2->setWindowTitle("Balada Hotel");
                    cleo->hide();
                    narcis->hide();
                    balada->hide();

                    cleo1->setText("Hotel Balada (***) is located in the heart of Saturn resort, offering a relaxing experience.\n"
                                   "With modern rooms and excellent facilities, it's perfect for memorable vacations.");

                    fac->setText("Air-conditioned rooms with balcony\nLocal cuisine restaurant\nPool bar\n"
                                 "Outdoor swimming pool\nPrivate parking\nFree beach access");

                    cleo1->show();
                    fac->show();
                    descriere->show();
                    fac1->show();


                    inapoi1->setGeometry(350, 650, 60, 30);
                    Reserve->setGeometry(420, 650, 60, 30);
                    inapoi1->show();
                    Reserve->show();

                    QObject::connect(Reserve, &QPushButton::clicked, [=]() {
                        Reserve->hide();
                        confirma1->show();
                        cleo1->hide();
                        descriere->hide();
                        fac->hide();
                        fac1->hide();
                        Reserve1->setGeometry(300, 250, 200, 25);
                        Reserve1->show();
                        ani1->show();

                        zile->setGeometry(270, 300, 100, 25);
                        zile->setMenu(menu1);
                        zile->show();
                        luni1->setGeometry(370, 300, 100, 25);
                        luni1->show();

                        for(int i = 1; i <= 31; i++) {
                            QAction *zi = new QAction(QString::number(i), menu1);
                            menu1->addAction(zi);
                            QObject::connect(zi, &QAction::triggered, [=]() {
                                zile->setText("Day: " + QString::number(i));
                                zile->show();
                            });
                        }

                        for (const QString &luna2 : luni2) {
                            QAction *act = new QAction(luna2, menu2);
                            menu2->addAction(act);
                            QObject::connect(act, &QAction::triggered, [=]() {
                                luni1->setText("Month: " + luna2);
                            });
                        }

                        luni1->setMenu(menu2);
                        luni1->show();

                        for (int i = 2025; i <= 2026; i++) {
                            QAction *ani = new QAction(QString::number(i), menu3);
                            menu3->addAction(ani);
                            QObject::connect(ani, &QAction::triggered, [=]() {
                                ani1->setText("Year: " + QString::number(i));
                            });
                        }

                        QObject::connect(confirma1, &QPushButton::clicked, [=]() {
                            QString lunaText = luni1->text().split(": ").last();
                            int anul = ani1->text().split(": ").last().toInt();
                            int ziua2 = zile->text().split(": ").last().toInt();
                            if(lunaText.isEmpty()|| anul >31 && anul<=1|| ziua2<=1 && ziua2>=31 ) {
                                QMessageBox::critical(fereastra2, "Error", "Please selecte the period"); }
                            if ((lunaText == "April" && anul == 2025 && ziua2 == 31) ||
                                (lunaText == "April" && anul == 2026 && ziua2 == 31) ||
                                (lunaText == "June" && anul == 2025 && ziua2 == 31) ||
                                (lunaText == "June" && anul == 2026 && ziua2 == 31) ||
                                (lunaText == "September" && anul == 2025 && ziua2 == 31) ||
                                (lunaText == "September" && anul == 2026 && ziua2 == 31)) {
                                QMessageBox::critical(fereastra2, "Error", "The month has only 30 days!");
                            }
                            else {
                                inapoi1->setGeometry(380, 650, 60, 30);
                                confirma1->hide();
                                nopti->setPlaceholderText("How many nights?");
                                camera->setPlaceholderText("How many rooms?");
                                pat->setPlaceholderText("Double/Triple beds?");
                                email->setPlaceholderText("Email: ");
                                nopti->setGeometry(300, 300, 200, 25);
                                camera->setGeometry(300, 350, 200, 25);
                                pat->setGeometry(300, 400, 200, 25);
                                email->setGeometry(300, 450, 200, 25);
                                confirm2->setGeometry(200, 550, 500, 40);
                                confirm2->show();
                                pat->show();
                                nopti->show();
                                camera->show();
                                zile->hide();
                                luni1->hide();
                                ani1->hide();
                                email->show();

                                QObject::connect(confirm2, &QPushButton::clicked, [=]() {

                                    descriere->hide();
                                    cleo1->hide();
                                    fac->hide();
                                    fac1->hide();
                                    luni1->hide();
                                    zile->hide();
                                    Reserve1->hide();
                                    ani1->hide();
                                    confirma1->hide();

                                    if(nopti->text().isEmpty() || camera->text().isEmpty() || email->text().isEmpty() || pat->text().isEmpty()) {
                                        QMessageBox::critical(fereastra2, "Error", "Please fill the boxes");
                                    } else {
                                        QMessageBox::information(fereastra2, "Successful", "Your reservation at Balada Hotel has been made successfully.");
                                        fereastra2->hide();
                                        fereastra->show();
                                        pat->hide();
                                        camera->hide();
                                        nopti->hide();
                                        email->hide();
                                        confirm2->hide();
                                        inapoi1->hide();
                                    }
                                });
                            }
                        });
                    });

                    QObject::connect(inapoi1, &QPushButton::clicked, [=]() {

                        fereastra2->hide();
                        Reserve->hide();
                        inapoi1->hide();
                        descriere->hide();
                        cleo1->hide();
                        fac->hide();
                        fac1->hide();
                        luni1->hide();
                        zile->hide();
                        Reserve1->hide();
                        ani1->hide();
                        confirma1->hide();
                        pat->hide();
                        nopti->hide();
                        camera->hide();
                        email->hide();
                        confirm2->hide();
                        fereastra->show();
                    });
                });


                QObject::connect(narcis, &QPushButton::clicked, [=]() {
                    fereastra2->setWindowTitle("Narcis Hotel");
                    cleo->hide();
                    balada->hide();
                    narcis->hide();

                    cleo1->setText("Hotel Narcis (***) offers an intimate atmosphere and quality services.\n"
                                   "Located just 200m from the beach, it's ideal for families and romantic vacations.");

                    fac->setText("24/7 reception\nFree WiFi throughout the hotel\nRestaurant with terrace\n"
                                 "Children's pool\nSoundproof rooms\nRoom service");
                    cleo1->show();
                    fac->show();
                    descriere->show();
                    fac1->show();


                    inapoi1->setGeometry(350, 650, 60, 30);
                    Reserve->setGeometry(420, 650, 60, 30);
                    inapoi1->show();
                    Reserve->show();

                    QObject::connect(Reserve, &QPushButton::clicked, [=]() {
                        Reserve->hide();
                        confirma1->show();
                        cleo1->hide();
                        descriere->hide();
                        fac->hide();
                        fac1->hide();
                        Reserve1->setGeometry(300, 250, 200, 25);
                        Reserve1->show();
                        ani1->show();

                        zile->setGeometry(270, 300, 100, 25);
                        zile->setMenu(menu1);
                        zile->show();
                        luni1->setGeometry(370, 300, 100, 25);
                        luni1->show();

                        for(int i = 1; i <= 31; i++) {
                            QAction *zi = new QAction(QString::number(i), menu1);
                            menu1->addAction(zi);
                            QObject::connect(zi, &QAction::triggered, [=]() {
                                zile->setText("Day: " + QString::number(i));
                                zile->show();
                            });
                        }

                        for (const QString &luna2 : luni2) {
                            QAction *act = new QAction(luna2, menu2);
                            menu2->addAction(act);
                            QObject::connect(act, &QAction::triggered, [=]() {
                                luni1->setText("Month: " + luna2);
                            });
                        }

                        luni1->setMenu(menu2);
                        luni1->show();

                        for (int i = 2025; i <= 2026; i++) {
                            QAction *ani = new QAction(QString::number(i), menu3);
                            menu3->addAction(ani);
                            QObject::connect(ani, &QAction::triggered, [=]() {
                                ani1->setText("Year: " + QString::number(i));
                            });
                        }

                        QObject::connect(confirma1, &QPushButton::clicked, [=]() {
                            QString lunaText = luni1->text().split(": ").last();
                            int anul = ani1->text().split(": ").last().toInt();
                            int ziua2 = zile->text().split(": ").last().toInt();

                            if ((lunaText == "April" && anul == 2025 && ziua2 == 31) ||
                                (lunaText == "April" && anul == 2026 && ziua2 == 31) ||
                                (lunaText == "June" && anul == 2025 && ziua2 == 31)  ||
                                (lunaText == "June" && anul == 2026 && ziua2 == 31) ||
                                (lunaText == "September" && anul == 2025 && ziua2 == 31) ||
                                (lunaText == "September" && anul == 2026 && ziua2 == 31)) {
                                QMessageBox::critical(fereastra2, "Error", "The month has only 30 days!");
                            } else {
                                inapoi1->setGeometry(380, 650, 60, 30);
                                confirma1->hide();
                                nopti->setPlaceholderText("How many nights?");
                                camera->setPlaceholderText("How many rooms?");
                                pat->setPlaceholderText("Double/Triple beds?");
                                email->setPlaceholderText("Email: ");
                                nopti->setGeometry(300, 300, 200, 25);
                                camera->setGeometry(300, 350, 200, 25);
                                pat->setGeometry(300, 400, 200, 25);
                                email->setGeometry(300, 450, 200, 25);
                                confirm2->setGeometry(200, 550, 500, 40);
                                confirm2->show();
                                pat->show();
                                nopti->show();
                                camera->show();
                                zile->hide();
                                luni1->hide();
                                ani1->hide();
                                email->show();

                                QObject::connect(confirm2, &QPushButton::clicked, [=]() {
                                    descriere->hide();
                                    cleo1->hide();
                                    fac->hide();
                                    fac1->hide();
                                    luni1->hide();
                                    zile->hide();
                                    Reserve1->hide();
                                    ani1->hide();
                                    confirma1->hide();

                                    if(nopti->text().isEmpty() || camera->text().isEmpty() || email->text().isEmpty() || pat->text().isEmpty()) {
                                        QMessageBox::critical(fereastra2, "Error", "Please fill the boxes");
                                    } else {
                                        QMessageBox::information(fereastra2, "Successful", "Your reservation at Narcis Hotel has been made successfully.");
                                        fereastra2->hide();
                                        fereastra->show();
                                        pat->hide();
                                        camera->hide();
                                        nopti->hide();
                                        email->hide();
                                        confirm2->hide();
                                        inapoi1->hide();
                                    }
                                });
                            }
                        });
                    });

                    QObject::connect(inapoi1, &QPushButton::clicked, [=]() {
                        fereastra2->hide();
                        Reserve->hide();
                        inapoi1->hide();
                        descriere->hide();
                        cleo1->hide();
                        fac->hide();
                        fac1->hide();
                        luni1->hide();
                        zile->hide();
                        Reserve1->hide();
                        ani1->hide();
                        confirma1->hide();
                        pat->hide();
                        nopti->hide();
                        camera->hide();
                        email->hide();
                        confirm2->hide();
                        fereastra->show();
                    });
                });
            });
            QObject::connect(opt2,&QAction::triggered,[&](){
                QMessageBox::information(fereastra2, ":D" ,"Just a demo version :3");

            });

        }

        where->show();
        mangalia->show();
        constanta->show();
    });

    fereastra->show();
    return app.exec();
}
