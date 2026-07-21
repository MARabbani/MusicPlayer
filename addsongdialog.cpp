#include "AddSongDialog.h"
#include <QFormLayout>
#include <QDialogButtonBox>

AddSongDialog::AddSongDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Add Song");
    auto* layout = new QFormLayout(this);
    nameEdit  = new QLineEdit(this);
    yearEdit  = new QLineEdit(this);
    genreEdit = new QLineEdit(this);
    pathEdit  = new QLineEdit(this);
    layout->addRow("Name:",  nameEdit);
    layout->addRow("Year:",  yearEdit);
    layout->addRow("Genre:", genreEdit);
    layout->addRow("Path:",  pathEdit);
    auto* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    layout->addRow(buttons);
    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
}
