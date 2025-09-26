#include <iostream>
#include <string>
using namespace std;

class Vector
{
public:

    // владеющий режим
    Vector()
    {
        this->data = nullptr;
        this->data = 0;
        this->flag_memory = 1;
    }

    Vector(size_t size)
    {
        this->size = size;
        this->flag_memory = 1;

        if (size > 0)
        {
            this->data = new double[size]{}; // заполнение нулями
        }
        else
        {
            data = nullptr;
        }
    }

    Vector(size_t size, double value)
    {
        this->size = size;
        this->flag_memory = 1;

        if (size > 0)
        {
            data = new double[size];
            for (int i = 0; i < size; i++)
            {
                data[i] = value;
            }
        }
        else
        {
            data = nullptr;
        }
    }
    // невладеющий режим
    Vector(double* external_data, size_t size)
    {
        this->data = external_data;
        this->size = size;
        this->flag_memory = 0;
    }

    /* конструктор копирования, который
    сохраняет режим владения */
    Vector(const Vector &other)
    {
        this->size = other.size;
        this->flag_memory = other.flag_memory;

        if (other.flag_memory)
        {
            if (other.size > 0)
            {
                this->data = new double[other.size];
                for (size_t i = 0; i < other.size; i++)
                {
                    this->data[i] = other.data[i];
                }
            }
            else
            {
                this->data = nullptr;
            }
        }
        else
        {
            this->data = other.data;
        }
    }

    // деструктор. срабатывает только, когда режим 
    ~Vector()
    {
        if (data != nullptr && flag_memory)
        {
            delete[] this->data;

        }
    }

    size_t Size()
    {
        return this->size;
    }

    bool OwnsMemory()
    {
        return this->flag_memory;
    }

    void SetElement(size_t index, double value)
    {
        if (size <= index)
        {
            cout << "Index out of range" << endl;
        }
        this->data[index] = value;
    }

    double GetElement(size_t index)
    {
        if (size <= index)
        {
            cout << "Index out of range" << endl;
        }
        return data[index];
    }

    double Dot(const Vector& other)
    {
        double dot = 0.0;
        if (this->size != other.size)
        {
            cout << "Sizes are difference!" << endl;
        }
        for (size_t i = 0; i < this->size; i++)
        {
            dot += this->data[i] * other.data[i];
        }
        return dot;
    }

    void Link(double* external_ptr, size_t new_size)
    {
        if (flag_memory && data != nullptr)
        {
            delete[] data;
        }
        data = external_ptr;
        size = new_size;
        flag_memory = 0;
    }

    void Unlink()
    {
        if (!flag_memory)
        {
            if (size > 0)
            {
                double* new_data = new double[size];
                for (size_t i = 0; i < size; i++)
                {
                    new_data[i] = data[i];
                }
                data = new_data;
                flag_memory = 1;
            }
            else
            {
                data = nullptr;
                flag_memory = 1;
            }
        }
    }
    void PrintVector()
    {
        cout << "[";
        for (size_t i = 0; i < size; i++)
        {
            cout << data[i];
            if (i < size - 1)
            {
                cout << ", ";
            }
        }
        cout << "] (flag_memory: " << flag_memory << ")" << endl;
    }

private:
    double* data;
    size_t size;
    bool flag_memory;
    // size_t Size;
};


int main()
{
    Vector vector;
}