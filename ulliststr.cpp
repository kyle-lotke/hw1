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

std::string* ULListStr::getValAtLoc(size_t loc) const {
    if (head_ == nullptr){
      return nullptr; // checks head is null
    }

    if (loc >= size_) { // checks if loc is within possbile range
      return nullptr;
    }

    Item* curr = head_; // copy node to iterate

    while (curr != nullptr){ // loop through list
      size_t items = curr->last - curr->first; //# elements in node

      if (loc < items){ // if loc is valid
        return &curr->val[curr->first + loc]; // return curr idx
      }
      loc -= items; // if not in there, move on to look at remaining
      curr = curr->next; //set curr to next node for iteration
    }
    return nullptr; //if returns above don't get triggered its out of range and returns null
  }


  std::string const & ULListStr::front() const {
    return head_->val[head_->first]; 
  }


  std::string const & ULListStr::back() const {
    return tail_->val[tail_->last-1]; 
  }


  void ULListStr::pop_front() {
    if (head_ == nullptr){ // if list empty, return nothing
      return; 
    }

    head_->first++; // changes first instead of shifting content ***
    size_--; //size shrinks to reflect shift

    if (head_->first == head_->last){ // means the list is empty
      Item* temp = head_; // store head
      head_ = head_->next; 

      if (head_ != nullptr){ //checks if next node exists
        head_->prev = nullptr; //new head node
      }
      else {
        tail_ = nullptr; // makes sure tail doesn't point to deleted node
      }

      delete temp; // deallocate temp 
    }
  }





void ULListStr::pop_back() {

    if (tail_ == nullptr){ // if empty return nothing
      return;
    }

    tail_->last = tail_->last-1; // changes first instead of shifting content
    size_--; //size shrinks to reflect shift

    if (tail_->last == tail_->first){ // checks if all vals have been removed
      Item* temp = tail_; // stores temp
      tail_ = tail_->prev; //check prev

      if (tail_ != nullptr){ // if the node exits, set the next to null, removing the node from both directions
        tail_->next = nullptr;
      }

      else {
        head_ = nullptr; // if tail is null then remove the head bc its size 1
      }
      delete temp; // deallocate temp node
    }
    
  }


void ULListStr::push_front(const std::string& val) {

    if (head_ == nullptr || head_->first ==0){ // if head is occipied or the entire list is empty make a new node    
      Item *input = new Item(); // input is the name of the new node being added
      input->next = head_; // set next node to previous head node 

      if (head_ != nullptr){ // if head exists
        head_->prev = input; // link the previous head node to input, needs to be linked in both directions
      }
      else {
        tail_ = input; // first node is head and tail because it wraps around
      }
      head_= input; // input becomes head as well because it wraps
      head_->first = ARRSIZE - 1; 
      head_->last = ARRSIZE;
      head_->val[head_->first] = val; // adds new val
    }
    else {
      head_->first--; // update first idx
      head_->val[head_->first] = val; // adds new val
    }
    size_++; // increment size
  }


void ULListStr::push_back(const std::string& val) {

    if (tail_ == nullptr || tail_->last == ARRSIZE) { // if tail is occipied or the entire list is full make a new node    
      Item *input = new Item(); // input is the name of the new node being added
      
      if (tail_ != nullptr){ // if tail exists
        tail_->next = input; // prev tail's next is the new node 
        input->prev = tail_; // links the input to the prev tail because it has to go both ways
      }
      else // if tail is null
      {
        head_ = input; // list must be empty so head is the input
      }
      tail_ = input; // move tail pointer to new tail's (input's) loc
      tail_->val[0] = val; // makes sure value is stored at first loc in new node
      tail_->first = 0; // set first idx
      tail_->last = 1; // set last idx
    } 
    else{ // if tail is not full
      tail_->val[tail_->last] = val; // set val at new node in new array
      tail_->last++; // increment last
    }
    size_++; // increment size
  }








