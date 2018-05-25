#ifndef DUALLINKLIST_H
#define DUALLINKLIST_H

#include "../../List/List.h"
#include "../../Exception/Exception.h"
namespace yixi
{
template <typename T>
class DualLinkList :public List<T>
{
protected:
    struct Node : public Object
    {
        T value;
        Node* next;
        Node* pre;
    };

    mutable struct : public Object
    {
        char reserved[sizeof(T)];
        Node* next;
        Node* pre;

    }m_header;

    int m_length;
    Node* m_current;
    int m_step;
    virtual Node* create()
    {
        return new Node();
    }

    virtual void destroy(Node* pn)
    {
        delete pn;
    }


    Node* position(int i) const
    {

        Node* ret = reinterpret_cast<Node*>(&m_header);
        {
            for(int p =0;p<i;p++)
            {
                ret = ret->next;
            }
        }
        return ret;
    }


public:
    DualLinkList()
    {
        m_header.next = NULL;
        m_header.pre = NULL;
        m_length = 0;
        m_step = 1;
        m_current = NULL;
    }

    virtual bool insert(const T& e)
    {
        return insert(m_length,e);
    }

    virtual bool insert(int i,const T& e)
    {
        bool ret = (i>=0) && (i<=m_length);
        if(ret)
        {
            Node* node = create();
            if(node != NULL)
            {
                Node* current = position(i);
                Node* next = current->next;
                node->value = e;
                node->next = next;
                current->next = node;

                if(current != reinterpret_cast<Node*>(&m_header))
                {

                    node->pre = current;
                }
                else
                {
                    node->pre = NULL;
                }

                if(next != NULL)
                {
                    next->pre = node;
                }

                m_length ++ ;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"No Enough Memory to create new node");
            }
        }
        return ret;
    }

    virtual bool remove(int i)
    {
        bool ret = (i>=0) && (i<m_length);
        if(ret)
        {
            Node* current = position(i);
            Node* toDel = current->next;
            Node* next = toDel->next;

            if(m_current == toDel)
            {

                m_current = toDel->next;

            }

            current->next = next;

            if(next != NULL)
            {
                next->pre = current;
            }

            m_length--;
            this->destroy(toDel);

        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException,"Index Out Of Bounds DualLinkList");
        }
        return ret;
    }
    virtual bool set(int i,const T& e)
    {
        bool ret = (i>=0) && (i<m_length);
        if(ret)
        {
           position(i)->next->value = e;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException,"Index Out Of Bounds DualLinkList");
        }
        return ret;
    }

    virtual T get(int i) const
    {
        T ret;
        if(get(i,ret))
        {
            return ret;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException,"Index Out Of Bounds DualLinkList");
        }
    }

    virtual bool get(int i,T& e)const
    {
        bool ret = (i>=0) && (i<m_length);
        if(ret)
        {
            e = position(i)->next->value;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException,"Index Out Of Bounds DualLinkList");
        }
        return ret;
    }

    virtual int length() const
    {
        return m_length;
    }

    virtual void clear()
    {
        int size = this->length();
        for(int i = 0;i<size;i++)
        {
            remove(0);

        }

    }
    virtual int find(const T& e) const
    {
        int ret = -1;
        Node* current = reinterpret_cast<Node*>(&m_header);
        for(int i = 0 ; i<this->length();i++)
        {
            current = current->next;
            if(current->value == e)
            {
                ret = i;
                break;
            }
        }
        return ret;
    }

    virtual bool move(int i,int step = 1)
    {
        bool ret = (0 <= i) && (i<this->m_length) && (step > 0);

        if(ret)
        {
            m_current = position(i)->next;
            m_step = step;
        }

        return ret;
    }

    virtual bool end()  //
    {
        return (m_current == NULL);
    }

    virtual T current()
    {
        if( m_current != NULL)
        {
            return m_current->value;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException,"Index Out Of Bounds DualLinkList");
        }
    }
    virtual bool next()
    {
        int i = 0;
        while( (i < m_step) && !end())
        {
            i++;
            m_current = m_current->next;
        }

        return (i == m_step);
    }

    virtual bool pre()
    {
        int i = 0;
        while( (i < m_step) && !end())
        {
            i++;
            m_current = m_current->pre;
        }

        return (i == m_step);
    }


    ~DualLinkList()
    {
        clear();
    }

};
}

#endif // DUALLINKLIST_H
