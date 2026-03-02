#include <memory>
#include <nana/gui.hpp>                 
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/group.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/msgbox.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/paint/detail/ptdefs.hpp>
#include <wx/wx.h>

#define WIDTH 500
#define HEIGHT 350

class LoginWindow {

private:

    std::shared_ptr<nana::form> fm = 
        std::make_shared<nana::form>(
            nana::API::make_center(WIDTH, HEIGHT));

    std::unique_ptr<nana::textbox> inputFirstname(std::shared_ptr<nana::form> fm) {
        
        auto firstname = 
            std::make_unique<nana::textbox>(*fm, nana::rectangle(10, 10, 100, 30));

        firstname -> tip_string("Firstname");
        firstname -> move(150, 150);
        firstname -> size({200, 25});

        return firstname;
    }    

    std::unique_ptr<nana::textbox> inputLastname(std::shared_ptr<nana::form> fm) {
        
        auto lastname = 
            std::make_unique<nana::textbox>(*fm, nana::rectangle(10, 10, 100, 30));

        lastname -> tip_string("Lastname");
        lastname -> move(150, 175);
        lastname -> size({200, 25});

        return lastname;
    }    

    std::unique_ptr<nana::textbox> inputPassword(std::shared_ptr<nana::form> fm) {
        
        auto password = 
            std::make_unique<nana::textbox>(*fm, nana::rectangle(10, 10, 100, 30));

        password -> tip_string("Password");
        password -> move(150,210);
        password -> size({200, 25});

        return password;
    }    
public:

    void runWindow() {

        fm->caption("Welcome to Quicksearch");

        auto fn = inputFirstname(fm);
        auto ln = inputLastname(fm);
        auto ps = inputPassword(fm);
        fm -> show();
        nana::exec();
    }
};



int main() {

    LoginWindow login;
    login.runWindow();
    return 0;
}