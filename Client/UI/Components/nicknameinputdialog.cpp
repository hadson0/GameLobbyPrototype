#include "nicknameinputdialog.h"

NicknameInputDialog::NicknameInputDialog(QWidget *parent)
    : QDialog{parent}, nickname("") {
    // Window proprieties
    this->setFixedSize(400, 175);
    this->setStyleSheet("QDialog {"
                            "color: qlineargradient(spread:pad, x1:0 y1:1, x2:1 y2:0,"
                            "stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"
                            "background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 #7d20bd, stop:1 #8165f0);"
                        "}" );
    this->setWindowTitle("Nickname");

    // Box Layout
    vbox = new QVBoxLayout;
    vbox->setGeometry(this->geometry());

    // Text input
    input = new CustomLineEdit(this);
    input->setPlaceholderText("Nickname");
    int inputWidth = this->width() - 10, inputHeight = this->height() * 0.08;
    int inputX = 10, inputY = 10;
    input->setGeometry(inputX, inputY, inputWidth, inputHeight);
    vbox->addWidget(input);

    // Accepts only Alphanumeric and underscore. Max of 12 chars
    QRegularExpression validNickname("^[a-zA-Z0-9_]*$");
    QValidator *validator= new QRegularExpressionValidator(validNickname, this);
    input->setValidator(validator);
    input->setMaxLength(12);

    // ButtonBox
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    buttonBox->setStyleSheet("* {"
                               "background-color: white; "
                               "border-radius: 15px; "
                               "border: 0px;"
                               "font-weight: bold;"
                               "color: #110C5A;"
                           "}");
    vbox->addWidget(buttonBox);
    this->setLayout(vbox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &NicknameInputDialog::onOkClicked);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &NicknameInputDialog::onCloseClicked);
}

QString NicknameInputDialog::getText() { return nickname; }

QString NicknameInputDialog::getNickname(QWidget *parent) {
    NicknameInputDialog nicknameDialog(parent);
    QString text;

    if (nicknameDialog.exec() == QDialog::Accepted) {
        text = nicknameDialog.getText();
    }

    return nicknameDialog.getText();
}

void NicknameInputDialog::onOkClicked() {
    nickname = input->text();
    this->close();
}

void NicknameInputDialog::onCloseClicked() { this->close(); }

