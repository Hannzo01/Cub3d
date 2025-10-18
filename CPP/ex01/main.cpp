#include <iostream>
#include <stdio.h>
#include <string>
#include <cctype>


class Contact
{
	std::string first_name;
	std::string last_name;
	std::string nickname;
	std::string phone_number;
	std::string darkest_secret;
	public:
	void	set_field(std::string first, std::string last, std::string nickname, std::string num, std::string secret)
	{
		first_name = first;
		last_name = last;
		this->nickname = nickname;
		phone_number = num;
		darkest_secret = secret;
	}
};

class PhoneBook
{
	int index_contact = 0;
	Contact contacts[8];
	public :
	void add_contact(Contact created_contact)
	{
		contacts[index_contact] = created_contact;
		index_contact++;
		if (index_contact == 8)
			index_contact = 0;
	}
};

int	is_digit(std::string str)
{
	int i = 0;
	if (str.length() != 10)
		return 0;
	while (i < str.length())
	{
		if (!isdigit(str[i]))
			return 0;
		i++;
	}
	return 1;
}

int main()
{
	PhoneBook phonebook;

	while (1)
	{
		std::cout << "Enter Command: - ";
		std::string cmd, first, last, nickname, num, secret;
		std::getline(std::cin, cmd);
		if (cmd == "ADD")
		{
			Contact contact;
			std::cout << "Enter first name: -";
			std::getline(std::cin, first);

			std::cout << "Enter last name: -";
			std::getline(std::cin, last);
		
			std::cout << "Enter nickname: -";
			std::getline(std::cin, nickname);

			std::cout << "Enter phone number: -";
			std::getline(std::cin, num);

			std::cout << "Enter darkest secret: -";
			std::getline(std::cin, secret);

			if (first.empty() || last.empty() || nickname.empty() || num.empty() || secret.empty() || !is_digit(num))
				std::cout << "Invalid" << std::endl ;
			else
			{
				contact.set_field(first, last, nickname, num, secret);
				phonebook.add_contact(contact);
			}

		}
		else if (cmd == "SEARCH") //getter
			std::cout << "SEARCH is typed" << std::endl;
		else if (cmd == "EXIT")
			break ;
	}
}

