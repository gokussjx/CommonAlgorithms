#include <iostream>
#include <algorithm>

class Node {
  friend class DLinkedList;
private:
  Node *pPrev_;
  Node *pNext_;
  int data_;

public:
  Node(): pPrev_(nullptr), pNext_(nullptr) { }
  Node(int d): data_(d), pPrev_(nullptr), pNext_(nullptr) { }
  Node(int d, Node *p, Node *n): data_(d), pPrev_(p), pNext_(n) { }

  // Getters
  const int getData() {
    return data_;
  }

  const Node* getPreviousNode() {
    return pPrev_;
  }

  const Node* getNextNode() {
    return pNext_;
  }
};

class DLinkedList {
private:
  Node *pHead_;
  Node *pTail_;

public:
  DLinkedList();
  DLinkedList(int d);
  DLinkedList(Node *n);
  DLinkedList(const DLinkedList &dLList);
  ~DLinkedList();

  DLinkedList& operator+=(const DLinkedList &dLList);
  const DLinkedList operator+(const DLinkedList &dLList) const;
  DLinkedList& operator=(const DLinkedList &dLList);

  void listDisplay();
  void reverseListDisplay();
  void append(int d);
  void append(Node *n);
  void append(const DLinkedList &dLList);
};

DLinkedList::DLinkedList(): pHead_(nullptr), pTail_(nullptr) { }

DLinkedList::DLinkedList(int d) {
  pHead_ = new Node(d, nullptr, nullptr);
  pTail_ = pHead_;
}

DLinkedList::DLinkedList(Node *n) {
  pHead_ = new Node(n->data_);
  pTail_ = pHead_;
}

DLinkedList::DLinkedList(const DLinkedList &dLList){

  Node *n1 = nullptr; // current
  Node *n2 = nullptr; // next

  if (dLList.pHead_ == nullptr) {
    pHead_ = nullptr;
  } else {
    pHead_ = new Node();
    pHead_->data_ = dLList.pHead_->data_;

    n1 = pHead_;
    n2 = dLList.pHead_->pNext_;
  }

  while (n2) {
    Node *prev = n1;
    n1->pNext_ = new Node();
    n1 = n1->pNext_;
    n1->pPrev_ = prev;
    n1->data_ = n2->data_;

    n2 = n2->pNext_;
  }

  pTail_ = n1;
  n1->pNext_ = nullptr;
}

DLinkedList& DLinkedList::operator=(const DLinkedList &dLList) {
  DLinkedList temp(dLList);
  std::swap(temp.pHead_, pHead_);
  std::swap(temp.pTail_, pTail_);
  return *this;
}

DLinkedList& DLinkedList::operator+=(const DLinkedList &dLList) {
  DLinkedList rhs(dLList);
  Node *n = nullptr;
  Node *r = nullptr;

  if ((*this).pHead_ == nullptr) {
    *this = rhs;
    return *this;
  }

  n = (*this).pTail_;
  r = rhs.pHead_;

  while (r) {
    Node *prev = n;
    n->pNext_ = new Node(); 
    n = n->pNext_;
    n->data_ = r->data_;
    n->pPrev_ = prev;
    r = r->pNext_;
  }
  
  n->pNext_ = nullptr;
  (*this).pTail_ = n;

  return *this;
}

const DLinkedList DLinkedList::operator+(const DLinkedList &dLList) const {
  DLinkedList temp = *this;
  
  temp += dLList;
  return temp;
}

DLinkedList::~DLinkedList() {
  while (Node *currentHead = pHead_) {
    pHead_ = currentHead->pNext_;
    delete currentHead;
  }
  pHead_ = nullptr;
  pTail_ = nullptr;
}

void DLinkedList::listDisplay() {
  if (pHead_ == nullptr) {
    std::cout << "List is empty!" << std::endl;
    return;
  }

  Node *it = pHead_;
  while (it != nullptr) {
    std::cout << it->data_ << std::endl;
    it = it->pNext_;
  }
  std::cout << std::endl;
}

void DLinkedList::reverseListDisplay() {
  if (pHead_ == nullptr) {
    std::cout << "List is empty!" << std::endl;
    return;
  }

  Node *it = pTail_;
  while (it != nullptr) {
    std::cout << it->data_ << std::endl;
    it = it->pPrev_;
  }
  std::cout << std::endl;
}

void DLinkedList::append(int d) {
  if (pHead_ == nullptr) {
    pHead_ = new Node(d, nullptr, nullptr);
    pTail_ = pHead_;
    return;
  }

  Node *n = new Node(d, pTail_, nullptr);
  pTail_->pNext_ = n;
  pTail_ = pTail_->pNext_;
}

void DLinkedList::append(Node *n) {
  if (pHead_ == nullptr) {
    pHead_ = n;
    pTail_ = pHead_;
    return;
  }

  pTail_->pNext_ = n;
  pTail_->pNext_->pPrev_ = pTail_;
  pTail_ = pTail_->pNext_;
}

void DLinkedList::append(const DLinkedList &dLList) {
  pTail_->pNext_ = dLList.pHead_;
  pTail_->pNext_->pPrev_ = pTail_;
  pTail_ = dLList.pTail_;
}

int main() {
  DLinkedList listA(10);
  listA.append(20);
  listA.append(30);

  DLinkedList listB = listA;
  // listB += listA;
  // listB.listDisplay();
  // listA.reverseListDisplay();
  // listB.reverseListDisplay();

  DLinkedList listC = listA + listB;
  DLinkedList listD;
  // listD = listC;
  listD += listC;

  listC.listDisplay();
  listC.reverseListDisplay();

  listD.listDisplay();
  listD.reverseListDisplay();
  return 0;
}