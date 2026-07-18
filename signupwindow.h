#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H
#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include "AuthService.h"


class SignUpWindow:public QWidget
{
    Q_OBJECT
    QLineEdit* fullnameedit;
    QLineEdit* usernameedit;
    QLineEdit* passwordedit;
    QLineEdit* bioedit;
    QComboBox* rolebox;
    QPushButton* signupbtn;
    QLabel* errorLabel;
    AuthService& authservice;
public:
    SignUpWindow(AuthService& service,QWidget* parent=nullptr);
signals:
    void signUpSuccess(Account acc);
    void switchToLogin();
private slots:
    void onSignUpClicked() {
        try {
            string name=fullnameedit->text().toStdString();
            string user=usernameedit->text().toStdString();
            string pass=passwordedit->text().toStdString();
            Role role=rolebox->currentText() == "Artist" ? Role::Artist : Role::Listener;
            string bio=bioedit->text().toStdString();
            Account newaccount(0,name,user,bio,role,pass);
            int newaccid=authservice.signUp(newaccount);
            emit signUpSuccess(newaccount);
        } catch (const exception& e) {
            errorLabel->setText(QString::fromStdString(e.what()));
        }
    }
};

#endif // SIGNUPWINDOW_H
