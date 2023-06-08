#include "Window.h"

Window::Window(QWidget *parent) : QWidget(parent){
    this->setWindowTitle("DotaLSTM");
    this->setObjectName("MainWindow");
    this->setFixedSize(730, 800);

    inputField = new QLineEdit(this);
    inputField->setGeometry(10, 10, 600, 80);
    connect(inputField, &QLineEdit::textChanged, this, &Window::updatePrompt);
    inputField->setAlignment(Qt::AlignCenter);

    buttonGenerate = new QPushButton("Сгенерировать", this);
    buttonGenerate->setGeometry(10, 100, 600, 80);
    connect(buttonGenerate, &QPushButton::released, this, &Window::generate);

    outputText = new QLabel(this);
    outputText->setGeometry(10, 190, 600, 600);
    outputText->setAlignment(Qt::AlignCenter);

    noiseSlider = new QSlider(this);
    noiseSlider->setGeometry(620, 100, 100, 690);
    connect(noiseSlider, &QSlider::valueChanged, this, &Window::updateValue);

    noiseLabel = new QLabel("Шум", this);
    noiseLabel->setGeometry(620, 10, 100, 80);
    noiseLabel->setAlignment(Qt::AlignCenter);
    noiseLabel->setObjectName("NoiseLabel");
}


void Window::generate() {
    auto namesVector = model.generateNames(prompt.toStdWString(), noiseValue);
    int maxNames = 15;
    std::wstring namesText;
    std::vector<bool> chosen(namesVector.size(), 0);
    for (int i = 0; i < namesVector.size() and i < maxNames; i++){
        int randomInt = rand()%namesVector.size();
        while(chosen[randomInt]){
            randomInt = rand()%namesVector.size();
        }
        namesText += namesVector[randomInt] + L"\n";
    }
    QString qtString = QString::fromStdWString(namesText);
    outputText->setText(qtString);
}

void Window::updatePrompt(const QString &newPrompt) {
    prompt = newPrompt;
}

void Window::updateValue(int newValue) {
    noiseValue = std::log(newValue);
}
