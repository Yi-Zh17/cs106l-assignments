#include "user.h"

/**
 * Creates a new User with the given name and no friends.
 */
User::User(const std::string& name)
  : _name(name)
  , _friends(nullptr)
  , _size(0)
  , _capacity(0)
{
}

/**
 * Adds a friend to this User's list of friends.
 * @param name The name of the friend to add.
 */
void
User::add_friend(const std::string& name)
{
  if (_size == _capacity) {
    _capacity = 2 * _capacity + 1;
    std::string* newFriends = new std::string[_capacity];
    for (size_t i = 0; i < _size; ++i) {
      newFriends[i] = _friends[i];
    }
    delete[] _friends;
    _friends = newFriends;
  }

  _friends[_size++] = name;
}

/**
 * Returns the name of this User.
 */
std::string
User::get_name() const
{
  return _name;
}

/**
 * Returns the number of friends this User has.
 */
size_t
User::size() const
{
  return _size;
}

/**
 * Sets the friend at the given index to the given name.
 * @param index The index of the friend to set.
 * @param name The name to set the friend to.
 */
void User::set_friend(size_t index, const std::string& name)
{
  _friends[index] = name;
}

/** 
 * STUDENT TODO:
 * The definitions for your custom operators and special member functions will go here!
 */
// Overload << operator
std::ostream& operator<<(std::ostream& out, User& user) {
  out << "User(name=" << user._name << ", friends=[";
  std::string* ptr = user._friends;
  for (int i = 0; i < user._size; ++i) {
    out << user._friends[i];
    if (i != user._size - 1) {
      out << ", ";
    }
  }
  out << "])";
  return out;
}

// SMFs
User::~User(){
  delete[] _friends;
}

User::User(const User& user) : _name(user._name), _capacity(user._capacity), _size(user._size) {
  _friends = new std::string[_capacity];
  for (int i = 0; i < _size; ++i) {
    _friends[i] = user._friends[i];
  }
} 

User& User::operator=(const User &user)
{
  this->_name = user._name;
  this->_capacity = user._capacity;
  this->_size = user._size;
  delete[] this->_friends;
  this->_friends = new std::string[this->_capacity];
  for (int i = 0; i < this->_size; ++i) {
    this->_friends[i] = user._friends[i];
  }
  return *this;
}

// Overload +=
User& User::operator+=(User& rhs) {
  this->add_friend(rhs.get_name());
  rhs.add_friend(this->get_name());
  return *this;
}

// Overload <
bool User::operator<(const User& rhs) const {
  std::string l_name = this->get_name();
  std::string r_name = rhs.get_name();
  return (l_name[0] < r_name[0]) ? true : false;
}
