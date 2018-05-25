#ifndef OBJECT_H
#define OBJECT_H

namespace yixi
{


class Object
{
public:
    void* operator new(unsigned long size) throw();
    void operator delete (void* p);
    void* operator new[] (unsigned long size) throw();
    void operator delete[] (void* p);
    bool operator == (const Object& obj);
    bool operator != (const Object& obj);
    virtual ~Object()=0;
};

    void* Object::operator new(unsigned long size) throw()
    {
        return malloc(size);
    }

    void Object::operator delete (void* p)
    {
        free(p);
    }

    void* Object::operator new[] (unsigned long size) throw()
    {
        return malloc(size);
    }

    void Object::operator delete[] (void* p)
    {
        free(p);
    }

    bool Object::operator == (const Object& obj)
    {
        return (this == &obj);
    }
    bool Object::operator != (const Object& obj)
    {
        return (this != &obj);
    }

    Object::~Object()
    {

    }

}



#endif // OBJECT_H
