#ifndef GEMINI_Cache_INCLUDE
#define GEMINI_Cache_INCLUDE
#include "../../public/Common.h"

namespace gemini
{

class Cache
{
    class PlaceHolder
    {
      public:
        PlaceHolder() {}
        virtual ~PlaceHolder() {}
        virtual const std::type_info &type() const = 0;
    };
    template <typename T>
    class Holder : public PlaceHolder
    {
      public:
        static Int index;
        Holder() {}
        virtual ~Holder() {}
        virtual const std::type_info &type() const { return typeid(T); }

      private:
        friend class Session;
        T _value;
    };

  public:
    template <class T>
    T &get()
    {
        if (0 == Holder<T>::index)
        {
            const std::type_info &typeinfo = typeid(T);
            Int i = 0;
            const Int len = (Int)_holders.size();
            for (; i < len; ++i)
            {
                if (_holders[i]->type() == typeinfo)
                    break;
            }
            if (i == len)
            {
                _holders.push_back(new Holder<T>());
            }
            Holder<T>::index = i;
        }

        return ((Holder<T> *)_holders[Holder<T>::index])->_value;
    }

  private:
    std::vector<PlaceHolder *> _holders;
};
template <class T>
Int Cache::Holder<T>::index = 0;

} // namespace gemini
#endif // !GEMINI_Cache_INCLUDE