
//
//  Created by Phuongpham on 6/6/17.
//  Copyright © 2017 Phuongpham. All rights reserved.
//

#ifndef Login_h
#define Login_h

class Login{
private:
    string PassWord;
public:
    Login()
    {
        PassWord = "Jennifer";
    }
    bool compare_password(string _password)
    {
        if (_password == this->PassWord)
            return true;
        else{
            return false;
        }
    }
    
    void PasswordChange(string _CPass)
    {
        this -> PassWord = _CPass;
    }
    
};


#endif /* Login_h */
