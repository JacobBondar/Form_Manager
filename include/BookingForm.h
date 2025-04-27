#ifndef BOOKINGFORM_H
#define BOOKINGFORM_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <array>
#include "ResourceManager.h"
#include "Field.h"
#include "WindowConfirmation.h"
#include "Button.h"
#include "ButtonFinish.h"

#include "ValidName.h"
#include "ValidID.h"
#include "ValidLocation.h"
#include "ValidEmail.h"
#include "ValidDate.h"
#include "ValidType.h"
#include "ValidStationComapare.h"

const int START_Y = 60;
const int FIRST_DATE_DEFAULT = 5;
const int SECOND_DATE_DEFAULT = 6;

class DialogueManager;

class BookingForm
{
public:
    BookingForm(DialogueManager* manager);
    virtual ~BookingForm() = 0 {};
    
    virtual void render(sf::RenderWindow& window) const;
    virtual int getAmount() const { return 0; };
    virtual std::string getTypeName() const { return std::string(); };
    virtual std::string getCompareField() const { return ""; };
    virtual std::vector<std::string> getNames() const { return std::vector<std::string>(); };
    virtual std::string getValidateName() const { return ""; };
    virtual std::string getFormType() const { return std::string(); };

    void createButtons(int& yOffset, float addX = 115, 
                       sf::Vector2f sizeRec = { 90 , 30 });
	void drawLabels(sf::RenderWindow& window) const;
    void closeFormManager() const;
    void createFinishButtons(int& yOffset);
    void handleInput(sf::Event event);
    int getFieldsNum() { return m_inputBoxes.size(); };
    sf::Text setDefaultText(std::string str, int size, sf::Color color, 
                            sf::Vector2f pos) const;
    std::string getField(int index) const;
    std::string setDefaultDate() const;
    std::vector<std::string> getVectorTypes() const;

    template<typename T>
    void checkClick(T& arr, int cell, int cellField);
    template<typename T>
    void check_dup(T& arr, bool last);

protected:
    std::vector<std::string> m_fieldLabels;
	std::vector<std::unique_ptr<FieldBase>> m_inputBoxes;
    std::vector<std::unique_ptr<Button>> m_inputButtons;
    sf::Clock m_cursorTimer;
    std::size_t m_activeField = 0;

    // Values so that the event window will run, which we didnt improved:
    std::vector<std::string> userInput;
    //end

private:
    DialogueManager* m_formManager;
    std::vector<std::unique_ptr<ButtonFinish>> m_finishButtons;

    virtual int getSize() const { return 0; };
    virtual std::string getString(int index) const { return ""; }
    virtual bool checkSelected(int index) const { return false; }
	virtual void drawRectangles(int yOffset, sf::RenderWindow& window) const;
    virtual void doClicked(int index) {};
    virtual void checkClickMouse(sf::Vector2f mousePos);

    bool isValidInfo() const;
    bool checkUserClick(sf::Vector2f mousePos);
    void openConfirmationWindow();
    void drawButtons(sf::RenderWindow& window) const;
    void drawFinishButtons(sf::RenderWindow& window) const;
    void drawTitle(sf::RenderWindow& window) const;
    void checkUserSpecial(sf::Event event);
    void drawLabelsAndInputFields(sf::RenderWindow& window, int& yOffset,
                                  bool cursorVisible) const;
    void updateFieldString(std::string text, bool active,
                           int index, int value) const;
    sf::RectangleShape setDefaultRectangle(sf::Vector2f size, sf::Vector2f pos,
        sf::Color fillColor, float outlineThickness,
        sf::Color outlineColor) const;

    template<typename T>
    bool checkNoneChose(T& arr, bool last);
    template<typename T>
    void checkAllChosen(T& arr, bool& allActive);
    template<typename T>
    void chooseLast(T& arr);
};

//-----------------------------------------------------------------------------

template<typename T>
void BookingForm::checkClick(T& arr, int cell, int cellField)
{
    arr[cell].second = !arr[cell].second;

    check_dup(arr, cell == arr.size() - 1);

    m_inputBoxes[cellField]->setString("");
    for (int index = 0; index < arr.size(); ++index)
    {
        updateFieldString(arr[index].first, arr[index].second, index, cellField);
    }
}

//-----------------------------------------------------------------------------

template<typename T>
void BookingForm::check_dup(T& arr, bool last)
{
    if (checkNoneChose(arr, last)) return;

    bool allActive = true;
    checkAllChosen(arr, allActive);

    if (allActive) chooseLast(arr);
}

//-----------------------------------------------------------------------------

template<typename T>
bool BookingForm::checkNoneChose(T& arr, bool last)
{
    if (last)
    {
        for (int i = 0; i < arr.size() - 1; i++)
        {
            arr[i].second = false;
        }
        return true;
    }
    return false;
}

//-----------------------------------------------------------------------------

template<typename T>
void BookingForm::checkAllChosen(T& arr, bool& allActive)
{
    for (int i = 0; i < arr.size() - 1; i++)
    {
        if (!arr[i].second) allActive = false;
        else arr[arr.size() - 1].second = false;
    }
}

//-----------------------------------------------------------------------------

template<typename T>
void BookingForm::chooseLast(T& arr)
{
    int i;
    for (i = 0; i < arr.size() - 1; i++)
    {
        arr[i].second = false;
    }
    arr[i].second = true;
}

#endif // BOOKINGFORM_H