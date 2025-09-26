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
        this->size = 0;
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
            return 0;
        }
        return data[index];
    }

    double Dot(const Vector& other)
    {
        if (this->size != other.size)
        {
            cout << "Sizes are different!" << endl;
            return 0;
        }
        double dot = 0.0;
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
        if (size == 0)
        {
            cout << "[]" << endl;
        }
        else
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
        }

private:
    double* data;
    size_t size;
    bool flag_memory;
    // size_t Size;
};


int main()
{
    setlocale(LC_ALL, "ru");
    cout << "Демонстрация работы класса Vector и его конструкторов" << endl;

    cout << "\n---Конструктор по умолчанию, создающий пустой вектор---" << endl;
    Vector empty_v;
    empty_v.PrintVector();

    cout << "\n---Конструктор с параметром размера, создающий вектор заданного размера, инициализированный указанным значением---" << endl;
    Vector v_size(10);
    v_size.PrintVector();

    cout << "\n---Конструктор принимающий размер и значение, создающий вектор заданного размера, инициализирвоанный указанным значением---" << endl;
    Vector v_1(10, 5.1);
    v_1.PrintVector();

    cout << "\n---Конструктор, принимающий указатель на внешний массив и его размер---" << endl;
    double external_data[] = {1.1, 3.4, 5.6};
    Vector v_2(external_data, 3);
    cout << "\nvector изначальный: ";
    v_2.PrintVector();
    external_data[1] = 10;
    cout << "\nvector после изменения во внешнего массива: ";
    v_2.PrintVector();

    cout << "\n---Конструктор копирования, сохраняющий режим владения---" << endl;
    Vector v_3_owning = v_1;
    Vector v_3_non_owning = v_2;

    cout << "\nкопия владеющего вектора: ";
    v_3_owning.PrintVector();
    cout << "\nкопия невладеющего вектора: ";
    v_3_non_owning.PrintVector();

    cout << "\n---Скалярное произведение векторов---" << endl;
    Vector a(3, 3);
    Vector b(3, 2);
    double dot_res = a.Dot(b);
    cout << "a: ";
    a.PrintVector();
    cout << "b: ";
    b.PrintVector();
    cout << "результат скалярного перемножения: " << dot_res << endl;

    cout << "\n---Скалярное произведение векторов разных размеров---" << endl;
    Vector a_1(2, 3);
    Vector b_1(3, 2);
    double dot_res_1 = a_1.Dot(b_1);
    cout << "a_1: ";
    a_1.PrintVector();
    cout << "b_1: ";
    b_1.PrintVector();
    cout << "результат скалярного перемножения: " << dot_res_1 << endl;

    cout << "\n---Работа с элементами---" << endl;
    Vector v_4(4);
    v_4.SetElement(0, 10);
    v_4.SetElement(1, 20);
    v_4.SetElement(2, 30);
    v_4.SetElement(3, 19);
    cout << "v_4[2]: " << v_4.GetElement(2) << endl;

    cout << "\n---Выход за границы массива---" << endl;
    Vector v(3);
    v.SetElement(0, 1);
    v.SetElement(1, 2);
    v.SetElement(2, 3);
    cout << "v[3]: " << v.GetElement(3) << endl;

    // cout << "\n---2. Выход за границы массива---" << endl;
    // Vector u(3);
    // u.SetElement(0, 1);
    // u.SetElement(1, 2);
    // u.SetElement(2, 3);
    // u.SetElement(3, 4);
    // cout << "v[1]: " << u.GetElement(1) << endl;

    cout << "\n---Метод Link---" << endl;
    Vector v_5(2, 5.0);
    cout << "v_5 до Link: ";
    v_5.PrintVector();

    double new_external[] = {100.0, 200.0};
    v_5.Link(new_external, 2);
    cout << "v_5 после Link: ";
    v_5.PrintVector();
    
    cout << "\n---Метод Unlink---" << endl;
    double external[] = {7.7, 8.8};
    Vector v_6(external, 2);
    cout << "v_6 до Unlink: ";
    v_6.PrintVector();
    
    v_6.Unlink();
    cout << "v_6 после Unlink: ";
    v_6.PrintVector();
    
    external[0] = 99.9;
    cout << "v_6 после изменения external: ";
    v_6.PrintVector();

    return 0;
}