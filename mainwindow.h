#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once
#include <QMainWindow>
#include <QStackedWidget>
#include "LoginWindow.h"
#include "SignUpWindow.h"
#include "ArtistPanel.h"
#include "ListenerPanel.h"

class MainWindow:public QMainWindow {
    Q_OBJECT
    QStackedWidget* stack;
    ArtistService& artistservice;
    ListenerService& listenerservice;

public:
    MainWindow(AuthService& authservice,
               ArtistService& aservice,
               ListenerService& lservice):artistservice(aservice),listenerservice(lservice)
    {
        stack = new QStackedWidget(this);
        setCentralWidget(stack);

        auto* login=new LoginWindow(authservice);
        auto* signup= new SignUpWindow(authservice);


        connect(login, &LoginWindow::loginSuccess, this, [this,&authservice](Account acc) {
            if (acc.role == Role::Artist)
                stack->addWidget(new ArtistPanel(acc,artistservice));
            else{
                stack->addWidget(new ListenerPanel(acc, listenerservice));
            }
            stack->setCurrentIndex(stack->count() - 1);
        });
        connect(login, &LoginWindow::switchToSignUp, this, [this,signup]() {
            stack->setCurrentWidget(signup);
        });

        connect(signup, &SignUpWindow::switchToLogin, this, [this, login]() {
            stack->setCurrentWidget(login);
        });
        connect(login, &LoginWindow::loginSuccess,
                this, [this, &authservice](Account acc) {
                    if (acc.role == Role::Artist) {
                        auto* panel = new ArtistPanel(acc, artistservice);
                        stack->addWidget(panel);

                        connect(panel, &ArtistPanel::accountDeleted,
                                this, [this, panel]() {
                                    stack->setCurrentIndex(0);
                                    stack->removeWidget(panel);
                                    panel->deleteLater();
                                });
                    } else {
                        stack->addWidget(new ListenerPanel(acc, listenerservice));
                    }

                    stack->setCurrentIndex(stack->count() - 1);
                });

        stack->addWidget(login);
        stack->addWidget(signup);
        stack->setCurrentWidget(login);
    }
};
#endif // MAINWINDOW_H
