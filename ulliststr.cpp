#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE
/**
   * Adds a new value to the back of the list
   *   - MUST RUN in O(1)
   */
  void ULListStr::push_back(const std::string& val) {
    if (this->tail_ == NULL) {
      Item* newItem = new Item();
      newItem->first = 0;
      newItem->last = 1;
      newItem->val[newItem->first] = val;
      this->head_ = newItem;
      this->tail_ = newItem;
      this->tail_->next = NULL;
    }
    else if (this->tail_->last == ARRSIZE) {
      Item* newTail = new Item();
      newTail->first = 0;
      newTail->last = 1;
      newTail->val[newTail->first] = val;
      newTail->prev = this->tail_;
      this->tail_->next = newTail;
      this->tail_ = newTail;
    }
    else {
      this->tail_->val[(this->tail_)->last] = val;
      this->tail_->last++;
    }
    this->size_++;
  }

/**
   * Removes a value from the back of the list
   *   - MUST RUN in O(1)
   */
  void ULListStr::pop_back() {
    if (this->tail_ == NULL) {
      return;
    }
    (this->tail_)->last--;
    this->size_--;

    //last node is empty, needs to be deleted
    if ((this->tail_)->first == (this->tail_)->last) {
      Item* temp = this->tail_;
      this->tail_ = this->tail_->prev;
      if (this->tail_ == NULL) {
        this->head_ = NULL;
      }
      else {
        this->tail_->next = NULL;
      }
      delete temp;
    }

    if (size_ == 0) {
        head_ = tail_ = NULL;
    }
  }

/**
   * Adds a new value to the front of the list.
   * If there is room before the 'first' value in
   * the head node add it there, otherwise, 
   * allocate a new head node.
   *   - MUST RUN in O(1)
   */
  void ULListStr::push_front(const std::string& val) {
    if (this->head_ == NULL) {
      Item* newHead = new Item();
      newHead->first = ARRSIZE-1;
      newHead->val[newHead->first] = val;
      newHead->last = ARRSIZE;
      newHead->next = NULL;  
      newHead->prev = NULL;
      this->head_ = newHead;
      this->tail_ = newHead;
    }
    else if (this->head_->first > 0) {
      this->head_->first--;
      this->head_->val[this->head_->first] = val;
    }
    else { //need to create new head 
      Item* newHead = new Item();
      newHead->first = ARRSIZE-1;
      newHead->val[newHead->first] = val;
      newHead->last = ARRSIZE;
      newHead->prev = NULL;
      newHead->next = this->head_;
      this->head_->prev = newHead;
      this->head_ = newHead;
    }
    this->size_++;
  }

/**
   * Removes a value from the front of the list
   *   - MUST RUN in O(1)
   */
void ULListStr::pop_front() {
  if (this->head_ == NULL) {
    return;
  }

  (this->head_->first)++;//walk through mechanics of this for loop I think I need to decrement last instead of increment first
  this->size_--; 

  if (this->head_->first == this->head_->last) {
    Item* temp = head_;
    this->head_ = this->head_->next;
    if (this->head_==NULL) {
      this->tail_ == NULL;
    }
    else {
      this->head_->prev = NULL;
    }
    delete temp;
  }

  if (size_ == 0) {
        head_ = tail_ = NULL;
    }
}

/**
   * Returns a const reference to the back element
   *   - MUST RUN in O(1)
   */
std::string const & ULListStr::back() const {
  return *(getValAtLoc(this->size_ - 1));
}

/**
   * Returns a const reference to the front element
   *   - MUST RUN in O(1)
   */
std::string const & ULListStr::front() const {
  return *(getValAtLoc(0));
}


/** 
   * Returns a pointer to the item at index, loc,
   *  if loc is valid and NULL otherwise
   *   - MUST RUN in O(n) 
   */
std::string* ULListStr::getValAtLoc(size_t loc) const {
  if (head_ == NULL) {
    return NULL;
  }
  Item* currItem = head_;
  size_t currentIndex = 0;
  while (currItem != NULL) {
    size_t itemSize = currItem->last - currItem->first;
    if (loc >= currentIndex && loc < currentIndex + itemSize) {
      return &(currItem->val[currItem->first + (loc-currentIndex)]);
    }
    currentIndex = currentIndex + itemSize;
    currItem=currItem->next;
  }

  return NULL;
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
