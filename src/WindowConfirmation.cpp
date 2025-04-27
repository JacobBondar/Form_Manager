#include "WindowConfirmation.h"
#include "BookingForm.h"

//-----------------------------------------------------------------------------

WindowConfirmation::WindowConfirmation(const std::string& formTitle, 
                                       BookingForm* bookingForm, 
                                       std::vector<std::string> fieldValid) :
	m_confirmWindow(sf::VideoMode(500, 600), "Confirm " + formTitle), 
    m_bookingForm(bookingForm), 
    m_formTitle(formTitle),
    m_fieldError(fieldValid)
{}

//-----------------------------------------------------------------------------

void WindowConfirmation::openWindow()
{
    bool valid = true;

    for (auto& error : m_fieldError)
    {
        if (error != "") valid = false;
    }

    sf::RectangleShape approveButton(sf::Vector2f(120, 40));
    sf::RectangleShape cancelButton(sf::Vector2f(120, 40));

    setConfirmation(approveButton, cancelButton);

    waitForEvent(approveButton, cancelButton, valid);
}

//-----------------------------------------------------------------------------

void WindowConfirmation::waitForEvent(sf::RectangleShape approveButton, 
                                      sf::RectangleShape cancelButton, bool valid)
{
    while (m_confirmWindow.isOpen()) 
    {
        sf::Event event;
        while (m_confirmWindow.waitEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                m_confirmWindow.close();

            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

            if (event.type == sf::Event::MouseButtonPressed) 
            {
                checkPressed(approveButton, cancelButton, valid, mousePos);
            }
        } 
    }
}

//-----------------------------------------------------------------------------

void WindowConfirmation::checkPressed(sf::RectangleShape approveButton,
                                      sf::RectangleShape cancelButton, 
                                      bool valid, sf::Vector2f mousePos)
{
    if (approveButton.getGlobalBounds().contains(mousePos)) 
    {
        if (valid)
        {
            std::cout << m_formTitle << " Confirmed! Returning to main menu." 
                                        << std::endl;
            m_bookingForm->closeFormManager();
            m_confirmWindow.close(); // approve
        }
        m_confirmWindow.close();
    }
    if (cancelButton.getGlobalBounds().contains(mousePos)) 
    {
        m_confirmWindow.close(); // cancel
    }
}

//-----------------------------------------------------------------------------

void WindowConfirmation::setConfirmation(sf::RectangleShape& approveButton, 
                                         sf::RectangleShape& cancelButton)
{
    m_confirmWindow.clear(sf::Color(240, 240, 240));

    std::string bookingInfo, errorText;
    getStrings(bookingInfo, errorText);

    setRectangle(approveButton, sf::Vector2f{ 100 , 550 }, sf::Color(50, 150, 50));
    setRectangle(cancelButton, sf::Vector2f{ 280, 550 }, sf::Color(180, 0, 0));

    sf::Text title, approveText, cancelText, errors, details;

    setTexts(title, approveText, cancelText, errors, details, bookingInfo, errorText);
    drawConfirmation(details, errors, title, cancelButton, cancelText, 
                     approveButton, approveText);
}

//-----------------------------------------------------------------------------

void WindowConfirmation::setTexts(sf::Text& title, sf::Text& approveText, 
                                  sf::Text& cancelText, sf::Text& errors, 
                                  sf::Text& details, std::string bookingInfo, 
                                  std::string errorText) const
{
    title = setText(28, "Confirm " + m_formTitle, sf::Color::Black, sf::Vector2f{ 130, 20 });
    approveText = setText(18, "APPROVE", sf::Color::White, sf::Vector2f{ 118, 560 });
    cancelText = setText(18, "CANCEL", sf::Color::White, sf::Vector2f{ 305, 560 });
    errors = setText(18, errorText, sf::Color::Red, sf::Vector2f{ 50, 80 });
    details = setText(18, bookingInfo, sf::Color::Black, sf::Vector2f{ 50, 80 });
}

//-----------------------------------------------------------------------------

void WindowConfirmation::getStrings(std::string& bookingInfo, std::string& errorText) const
{
    for (int index = 0; index < m_bookingForm->getFieldsNum(); ++index)
    {
        bookingInfo += m_bookingForm->getField(index);

        if (m_fieldError[index] != "")
        {
            bookingInfo += "\n";
            errorText += m_fieldError[index];
        }
        else errorText += "\n";
    }
}

//-----------------------------------------------------------------------------

void WindowConfirmation::setRectangle(sf::RectangleShape& approveButton, 
                                      sf::Vector2f pos, sf::Color color) const
{
    approveButton.setPosition(pos);
    approveButton.setFillColor(color);
}

//-----------------------------------------------------------------------------

sf::Text WindowConfirmation::setText(int size, std::string txt, 
                                     sf::Color color, sf::Vector2f pos) const
{
    sf::Text temp = ResourceManager::instance().getTextFont();
    temp.setCharacterSize(size);
    temp.setString(txt);
    temp.setFillColor(color);
    temp.setPosition(pos);

    return temp;
}

//-----------------------------------------------------------------------------

void WindowConfirmation::drawConfirmation(sf::Text details, sf::Text errors, sf::Text title, 
                                          sf::RectangleShape cancelButton, sf::Text cancelText, 
                                          sf::RectangleShape approveButton, sf::Text approveText)
{
    m_confirmWindow.draw(details);
    m_confirmWindow.draw(errors);
    m_confirmWindow.draw(title);
    m_confirmWindow.draw(cancelButton);
    m_confirmWindow.draw(cancelText);
    m_confirmWindow.draw(approveButton);
    m_confirmWindow.draw(approveText);
    m_confirmWindow.display();
}