template <typename T>
typename remove_reference<T>::type&& move(T&& arg)
{
  return static_cast<typename remove_reference<T>::type&&>(arg);
}

To allow perfect forwarding, C++11 standard provides special rules for reference collapsing, which are as follows:

Object &  &  = Object &
Object &  && = Object &
Object && &  = Object &
Object && && = Object &&


