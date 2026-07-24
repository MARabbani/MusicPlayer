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
    QPushButton* backbtn;
    QLabel* errorLabel;
    AuthService& authservice;
public:
    SignUpWindow(AuthService& service,QWidget* parent=nullptr);
signals:
    void signUpSuccess(Account acc);
    void switchToLogin();
private slots:
    void onSignUpClicked();
};

#endif // SIGNUPWINDOW_H
