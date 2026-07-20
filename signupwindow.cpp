#include "signupwindow.h"
#include <string>
#include <QString>

using namespace std;

SignUpWindow::SignUpWindow(AuthService& service,QWidget* parent)
    : QWidget(parent), authservice(service)
{}

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
