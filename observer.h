#ifndef _OBSERVER_H_
#define _OBSERVER_H_


template <typename InfoTypee> class Subject;
class Grid;

template <typename InfoType> class Observer {
 public:
  virtual void notify(Subject<InfoType> &whoFrom) = 0; // pass the Subject that called the notify method
  virtual void clear() {}
  virtual void clearNext() {}
  virtual void update(int, int, int) {}
  virtual ~Observer() = default;
};
#endif
