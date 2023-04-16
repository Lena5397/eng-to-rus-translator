#ifndef DYNAMICBUTTON_H
#define DYNAMICBUTTON_H

#include <QPushButton>

class DynamicButton : public QPushButton
{
    Q_OBJECT
public:
    explicit DynamicButton(QWidget *parent = nullptr);
    ~DynamicButton();

    QString getText();
    void setStoredText(QString t);



   public slots:

   private:
    QString text;


};

#endif // DYNAMICBUTTON_H
