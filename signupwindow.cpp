#include "signupwindow.h"
#include <string>
#include <QString>
#include <QVBoxLayout>

using namespace std;

SignUpWindow::SignUpWindow(AuthService& service,QWidget* parent):QWidget(parent), authservice(service)
{
    fullnameedit = new QLineEdit(this);
    usernameedit = new QLineEdit(this);
    passwordedit = new QLineEdit(this);
    passwordedit->setEchoMode(QLineEdit::Password);
    bioedit      = new QLineEdit(this);
    rolebox      = new QComboBox(this);
    rolebox->addItems({"Artist", "Listener"});
    signupbtn    = new QPushButton("Sign Up", this);
    errorLabel   = new QLabel(this);

    auto* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Full Name:")); layout->addWidget(fullnameedit);
    layout->addWidget(new QLabel("Username:")); layout->addWidget(usernameedit);
    layout->addWidget(new QLabel("Password:")); layout->addWidget(passwordedit);
    layout->addWidget(new QLabel("Bio:"));      layout->addWidget(bioedit);
    layout->addWidget(new QLabel("Role:"));     layout->addWidget(rolebox);
    layout->addWidget(signupbtn);

    backbtn = new QPushButton("Back to Login", this);
    layout->addWidget(backbtn);

    layout->addWidget(errorLabel);

    connect(signupbtn, &QPushButton::clicked, this, &SignUpWindow::onSignUpClicked);

    connect(backbtn, &QPushButton::clicked, this, &SignUpWindow::switchToLogin);

}

void SignUpWindow::onSignUpClicked(){
    try {
        string name = fullnameedit->text().toStdString();
        string user = usernameedit->text().toStdString();
        string pass = passwordedit->text().toStdString();
        Role role = rolebox->currentText() == "Artist" ? Role::Artist : Role::Listener;
        string bio = bioedit->text().toStdString();

        Account newaccount(0, name, user, bio, role, pass);
        int newaccid = authservice.signUp(newaccount);

        emit signUpSuccess(newaccount);
    } catch (const exception& e) {
        errorLabel->setText(QString::fromStdString(e.what()));
    }
}
