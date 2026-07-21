#pragma once
#include <QDialog>
#include <QLineEdit>

class AddSongDialog : public QDialog {
    Q_OBJECT
public:
    explicit AddSongDialog(QWidget* parent = nullptr);
    QString name() const { return nameEdit->text(); }
    int year() const { return yearEdit->text().toInt(); }
    QString genre() const { return genreEdit->text(); }
    QString path() const { return pathEdit->text(); }
private:
    QLineEdit *nameEdit, *yearEdit, *genreEdit, *pathEdit;
};
