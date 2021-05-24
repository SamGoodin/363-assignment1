// $Id: Array.cpp 820 2011-01-17 15:30:41Z hillj $

// Honor Pledge:
//
// I pledge that I have neither given nor receieved any help
// on this assignment.

#include "Array.h"
#include <stdexcept>

Array::Array (void)
// COMMENT Initialize all member variables in the base member initialization section
// of the constructor on its own line. Otherwise, it is hard to know what initialization
// has an error since it will not have its own unique line number.
: data_(new char [0]),
  cur_size_ (0),
  max_size_ (0)
{
	//Moved member variable initialization and placed them on separate lines
}

Array::Array (size_t length)
// COMMENT Initialize all member variables in the base member initialization section
// of the constructor on its own line. Otherwise, it is hard to know what initialization
// has an error since it will not have its own unique line number.
: data_(new char [length]),
  max_size_(length),
  cur_size_(0)
{
	//Moved member variable initialization and placed them on separate lines
}

Array::Array (size_t length, char fill)
// COMMENT Initialize all member variables in the base member initialization section
// of the constructor on its own line. Otherwise, it is hard to know what initialization
// has an error since it will not have its own unique line number.
: data_(new char [length]),
  max_size_(length),
  cur_size_(length)
{
	//Moved member variable initialization and placed them on separate lines
	for (int i = 0; i < length; i++) {
		data_[i] = fill;
	}
}


Array::Array (const Array & array)
// COMMENT Initialize all member variables in the base member initialization section
// of the constructor on its own line. Otherwise, it is hard to know what initialization
// has an error since it will not have its own unique line number.
: data_(new char [cur_size_]),
  cur_size_(array.cur_size_),
  max_size_(array.max_size_)
{
	//Moved member variable initialization and placed them on separate lines
	//Copy data from given array to this array
    for (int i = 0; i < cur_size_; i++) {
        data_[i] = array.data_[i];
    }
}

Array::~Array (void)
{
	delete [] data_;

  // COMMENT There is no need to reset the data_ variable since this object is no
  // longer useable after the desturctor returns.
	//Removed data_ = nullptr;
}

const Array & Array::operator = (const Array & rhs)
{
  // COMMENT Check for self assignment first.

  // COMMENT The assignment operator needs to create a deep copy of the source
  // array. Right now, you are not making a deep copy into this object.
	//Added deep copy
	this->cur_size_ = rhs.size();
	this->max_size_ = rhs.max_size();
	this->data_ = new char [max_size_];
	for (int i = 0; i < cur_size_; i++) {
		data_[i] = rhs.get(i);
	}

  // COMMENT This method should return *this for call chaining.
    //Changed return
	return *this;
}

char & Array::operator [] (size_t index)
{
	//Added check for index < 0
	if (index >= max_size_ || index < 0) {
		throw std::out_of_range ("out_of_range error: Index out of range for array");
	}
	else {
		return data_[index];
	}
}

const char & Array::operator [] (size_t index) const
{
	//Added check for index < 0
	if (index >= max_size_ || index < 0) {
	    throw std::out_of_range ("out_of_range error: Index out of range for array");
	}
	else {
		return data_[index];
	}
}

char Array::get (size_t index) const
{
  // COMMENT You are to throw out of range exception if the index is invalid.
	//Added throw and check for index < 0
	if (index >= max_size_ || index < 0) {
		throw std::out_of_range ("out_of_range error: Index out of range for array");
	}
	else {
		return data_[index];
	}
}

void Array::set (size_t index, char value)
{
  // COMMENT You are to throw out of range exception if the index is invalid.
	//Added throw and check for index < 0
	if (index >= max_size_ || index < 0) {
		throw std::out_of_range ("out_of_range error: Index out of range for array");
	}
	else {
		//Altered if to alter cur_size_ properly
		//(!(data_[value])) --> (index >= cur_size_)
		if (index >= cur_size_) {
			// Only modify cur_size_ if index is >= to cur_size_
			cur_size_++;
		}
		data_[index] = value;
	}
}

void Array::resize (size_t new_size)
{
	// COMMENT The resize method should only increase the size of the allocation if
	  // the new size is larger than the current memory allocation for the array. If resized,
	  // you need to preserve the old data. Otherwise, you can just update cur_size_ to
	  // reflect the new size.
	if (new_size > max_size_) {
	  // COMMENT You have a memory leak because you are not deleting the old data.
		//Added deletes
		if (cur_size_ != 0) {
			//Only need to copy data if cur_size_ is > 0
			char * arr = new char [new_size];
			for (int i = 0; i < cur_size_; i++) {
				char c = data_[i];
				arr[i] = c;
			}
			delete [] data_;
			data_ = arr;
			max_size_ = new_size;
		}
		else {
			delete [] data_;
			data_ = new char [new_size];
			max_size_ = new_size;
		}
	}
	else {
		max_size_ = new_size;
	}
}

int Array::find (char ch) const
{
    char letter;
    for (int i = 0; i < max_size_; i++) {
        letter = data_[i];
        if (letter == ch) {
            return i;
        }
    }
    return -1;
}

int Array::find (char ch, size_t start) const
{
	if (start >= cur_size_) {
	    throw std::out_of_range ("out_of_range error: Index out of range for array");
	}
	else {
		char letter;
		for (int i = start; i < cur_size_; i++){
			letter = data_[i];
			if (letter == ch){
				return i;
			}
		}
		return -1;
	}
}

bool Array::operator == (const Array & rhs) const
{
  // COMMENT Check for self comparison first.
	//Added self comparison
	if (this == &rhs) {
		return true;
	}
	else{
		if (max_size_ == rhs.max_size_ && cur_size_ == rhs.cur_size_) {
			char rhsChar, thisChar;
			for (int i = 0; i < max_size_; i++) {
				rhsChar = rhs.data_[i];
				thisChar = data_[i];
				if (rhsChar != thisChar) {
					return false;
				}
			}
			return true;    // reaches this only if max_size_, cur_size_, & each element is equal
		}
		else {
			return false;
		}
	}
}

bool Array::operator != (const Array & rhs) const
{
  // COMMENT You can define operator != in terms of operator ==.
	//Defined in terms of == instead of !=, added self comparison
	if (this == &rhs) {
		return false;
	}
	else{
		if (max_size_ == rhs.max_size_ && cur_size_ == rhs.cur_size_) {
			char rhsChar, thisChar;
			for (int i = 0; i < max_size_; i++) {
				rhsChar = rhs.data_[i];
				thisChar = data_[i];
				if (rhsChar != thisChar) {
					return true;
				}
			}
			return false;    // reaches this only if max_size_, cur_size_, & each element is equal
		}
		else {
			return true;
		}
	}
}

void Array::fill (char ch)
{
	cur_size_ = max_size_;

  // COMMENT You are filling to the incorrect size.
	//Changed max_size to cur_size_ so it fills to cur instead of max
	for (int i = 0; i < cur_size_; i++) {
		data_[i] = ch;
	}

  // COMMENT You should not be changing the size of the array.
	//I'm confused about this comment, as if you fill to max_size_ and cur_size_
	//is 0, then the cur_size_ must be changed here. However, I did move
	//cur_size_ = max_size_ to before the actual filling
}

void Array::shrink (void)
{
  // COMMENT You should use the cur_size_ and max_size_ to determine if you
  // must shrink the array allocation.
	//Added check for if max > cur, and removed the double copy along with
	//resetting the max_size_ manually (done when data_ = arr is called)
	if (max_size_ > cur_size_) {
		char * arr = new char [cur_size_];
		for (int i = 0; i < cur_size_; i++) {
			char c = data_[i];
			arr[i] = c;
		}
		delete [] data_;
		data_ = arr;
		max_size_ = cur_size_;
	}

  // COMMENT There is no need to do a double copy for the data to shrink
  // the array. Just create a new arary, copy over the data, and then swap
  // the pointers.
}

void Array::reverse (void)
{
  // COMMENT There is no need to create a copy of the array to reverse its contents
	//Rewrote reverse method without creating a copy
	char placeholder;
	int length = cur_size_ / 2; //works with even or odd cur_size_
	for (int i = 0; i < length; i++) {
		placeholder = data_[i];
		data_[i] = data_[cur_size_ - (1+i)];
		data_[cur_size_ - (1 + i)] = placeholder;
	}
}

Array Array::slice (size_t begin) const
{
    Array a1;
    int counter = 0;
    for (int i = begin; i < cur_size_; i++) {
        char c = data_[i];
        a1.set(counter, c);
        counter++;
    }
    return a1;
}

Array Array::slice (size_t begin, size_t end) const
{
	Array a1;
    int counter = 0;
    for (int i = begin; i < end; i++) {
        char c = data_[i];
        a1.set(counter, c);
        counter++;
    }
    return a1;
}
