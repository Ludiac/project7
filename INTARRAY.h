//m_length это величина сколько в IntArray элементов а m_size - сколько он занимает места на heap памяти.
//m_size всегда равен 2^n и не может быть меньше 2.
//IntArray может быть скопирован или перемещен

#ifndef INTARRAY_H
#define INTARRAY_H

#include <memory>
#include <math.h>

class IntArray
{
private:
    int m_size{2};
    int m_length{};
    std::unique_ptr<int[]> m_data = nullptr;

    int check(int length_to_check, int current_length){
        int a = power_of_two(length_to_check)+1;
        int b = power_of_two(current_length);
        int c = a - b;
        return c;
    }

    void biggen(int magnitude){
        int iop = power_of_two(m_size)-1;
        std::unique_ptr<int[]> data = std::make_unique<int[]>(std::pow(2, iop+magnitude));
        if(m_data != nullptr)
            for(int i = 0; i < m_length; ++i) {
                data[i] = this->m_data[i];
            }
        m_size = std::pow(2, iop+magnitude);
        m_data.swap(data);
    }

    void smallen(int magnitude){
        m_size = std::pow(2, power_of_two(m_size) + magnitude - 1);
        std::unique_ptr<int[]> data = std::make_unique<int[]>(m_size);
        for(int i = 0; i < m_size; ++i) {
            data[i] = this->m_data[i];
        }
        m_data.swap(data);
    }

    int power_of_two(int n) {
            int b = 1073741824;
            for(int i = 0; i < 32; ++i) {
                if((n&b) != 0) {
                    return 31 - i;
                }
                b >>= 1;
            }
            return 0;
    }

public:
    IntArray() = default;

    IntArray(int length):
        m_length{length}
    {
        if (length < 0) throw "invalid length";

        m_size = std::pow(2, power_of_two(length));

        if (length > 0) m_data = std::make_unique<int[]>(m_size);
    }

    ~IntArray()
    {
    }

    void erase()
    {
        m_data.reset();
        m_size = 2;
        m_length = 0;
    }

    int& operator[](int index)
    {
        if (index < 0 || index > m_length) throw "invalid index";
        return m_data[index];
    }

    void resize(int newLength)
    {
        if (newLength < 0) throw "invalid length";

        if (newLength == m_size)
        {
            m_length = m_size;
            return;
        }

        if (newLength == 0)
        {
            erase();
            return;
        }

        if (newLength < m_length)
        {
            int a = check(newLength, m_size);
            if (a < 0) smallen(a);
            m_length = newLength;
            return;
        }

        if (newLength < m_size && newLength > m_length)
        {
            m_length = newLength;
            return;
        }

        int a = check(newLength, m_size);
        if (a > 0) biggen(a);
        m_length = newLength;
    }

    void insertBefore(int value, int index)
    {
        if (index < 0 || index > m_length) throw "invalid index";

        if (check(m_length, m_size) > 0) biggen(1);

        for (int i = m_size-1; i > index; --i){
            m_data[i] = m_data[i-1];
        }
        m_data[index] = value;

        ++m_length;
    }

    void remove(int index)
    {
        if (index < 0 || index > m_length) throw "invalid index";

        if (m_length == 1)
        {
            erase();
            return;
        }

        if (m_length <= 0) throw "invalid operation";

        if (check(m_length-1, m_size/2) < 0) smallen(1);

        for (int i = index; i < m_length-1; ++i){
            m_data[i] = m_data[i+1];
        }

        --m_length;
    }

    void insertAtEnd(int value) { insertBefore(value, m_length); }

    int getLength() const noexcept { return m_length; }
    int getSize()   const noexcept { return m_size; }

    IntArray(IntArray const& w) :
        m_size {w.m_size},
        m_length {w.m_length}
    {
        if (w.m_data) m_data = std::make_unique<int[]>(w.m_size);
        for (auto i = 0; i < w.m_length; ++i) {
            m_data[i] = w.m_data[i];
        }
    };

    IntArray& operator=(const IntArray& wr) {
        IntArray tmp(wr);
        *this = std::move(tmp);

        return *this;
    };

    IntArray& operator=(IntArray&& wr) noexcept {
        if (this != &wr) {
            m_length = wr.m_length;
            m_size = wr.m_size;
            m_data.swap(wr.m_data);
            wr.erase();
        }

        return *this;
    };
};

#endif
