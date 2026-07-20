#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "AuthService.h"
#include <QString>
#include <QVBoxLayout>
class LoginWindow:public QWidget
{
    Q_OBJECT
    QLineEdit* usernameedit;
    QLineEdit* passwordedit;
    QPushButton* loginbtn;
    QPushButton* gotosignupbtn;
    QLabel* errorlabel;
    AuthService& authservice;
public:
    LoginWindow(AuthService& service,QWidget* parent=nullptr): QWidget(parent),authservice(service){
        usernameedit = new QLineEdit(this);
        passwordedit = new QLineEdit(this);
        passwordedit->setEchoMode(QLineEdit::Password);
        loginbtn = new QPushButton("Login", this);
        gotosignupbtn = new QPushButton("Sign Up", this);
        errorlabel = new QLabel(this);

        auto* layout = new QVBoxLayout(this);
        layout->addWidget(new QLabel("Username:"));
        layout->addWidget(usernameedit);
        layout->addWidget(new QLabel("Password:"));
        layout->addWidget(passwordedit);
        layout->addWidget(loginbtn);
        layout->addWidget(gotosignupbtn);
        layout->addWidget(errorlabel);

        connect(loginbtn, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);
        connect(gotosignupbtn, &QPushButton::clicked, this, &LoginWindow::switchToSignUp);

    };
signals:
    void loginSuccess(Account acc);
    void switchToSignUp();
private slots:
    void onLoginClicked(){
        try{
            string user=usernameedit->text().toStdString();
            string pass=passwordedit->text().toStdString();
            Account acc = authservice.login(user,pass);
            emit loginSuccess(acc);
        } catch (exception& e){
            errorlabel->setText(QString::fromStdString(e.what()));
        }
    }
};

#endif // LOGINWINDOW_H
