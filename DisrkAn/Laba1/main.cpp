#include <iostream>
#include <algorithm>
#include <cassert>

struct tPhoneNumber
{
    int country;
    int region;
    int main;
};

struct dict
{
    tPhoneNumber key;
    unsigned long long value;
};

template <typename T>
class vector {
    public:
    using value_type = T;
    using iterator = value_type*;
    using const_iterator = const value_type*;

    vector():
        already_used_(0), storage_size_(0), storage_(nullptr)
    {
    }

    vector(int size, const value_type& default_value = value_type()):
        vector()
    {
        assert(size >= 0);

        if (size == 0)
            return;

        already_used_ = size;
        storage_size_ = size;
        storage_ = new value_type[size];

        std::fill(storage_, storage_ + already_used_, default_value);
    }

    int size() const
    {
        return already_used_;
    }

    bool empty() const
    {
        return size() == 0;
    }

    iterator begin() const
    {
        return storage_;
    }

    iterator end() const
    {
        if (storage_)
            return storage_ + already_used_;

        return nullptr;
    }

    friend void swap(vector& lhs, vector& rhs)
    {
        using std::swap;

        swap(lhs.already_used_, rhs.already_used_);
        swap(lhs.storage_size_, rhs.storage_size_);
        swap(lhs.storage_, rhs.storage_);
    }

    vector& operator=(vector other)
    {
        swap(*this, other);
        return *this;
    }

    vector(const vector& other):
        vector()
    {
        vector next(other.storage_size_);
        next.already_used_ = other.already_used_;

        if (other.storage_ )
            std::copy(other.storage_, other.storage_ + other.storage_size_,
                      next.storage_);

        swap(*this, next);
    }

    ~vector()
    {
        delete[] storage_;

        storage_size_ = 0;
        already_used_ = 0;
        storage_ = nullptr;
    }

    void push_back(const value_type& value)
    {
        if (already_used_ < storage_size_) {
            storage_[already_used_] = value;
            ++already_used_;
            return;
        }

        int next_size = 1;
        if (storage_size_)
            next_size = storage_size_ * 2;

        vector next(next_size);
        next.already_used_ = already_used_;

        if (storage_ )
            std::copy(storage_, storage_ + storage_size_, next.storage_);

        next.push_back(value);
        swap(*this, next);
    }

    value_type pop_front()
    {
        value_type a = storage_[0];
        for(int i = 1; i < size(); i++)
            storage_[i-1] = storage_[i];
        --already_used_;
        return a;
    }

    const value_type& at(int index) const
    {
        if (index < 0 || index > already_used_)
            throw std::out_of_range("You are doing this wrong!");

        return storage_[index];
    }

    value_type& at(int index)
    {
        const value_type& elem = const_cast<const vector*>(this)->at(index);
        return const_cast<value_type&>(elem);
    }

    const value_type& operator[](int index) const
    {
        return at(index);
    }

    value_type& operator[](int index)
    {
        return at(index);
    }

    private:
    int already_used_;
    int storage_size_;
    value_type* storage_;
};

int main()
{
    vector<dict> main;
    char first, second, third;
    dict buf;
    while(std::cin >> first >> buf.key.country >> second >> buf.key.region >> third >> buf.key.main >> buf.value){
        main.push_back(buf);        
    }
    vector<dict> a0, a1, a2, a3, a4, a5, a6, a7, a8, a9;
    for(int j = 1; j < 8; j++){
        for(int i = 0; i < main.size(); i++){
            switch(main[i].key.main % (10*j))
            {
                case 0:
                    a0.push_back(main[i]);
                    break;
                case 1:
                    a1.push_back(main[i]);
                    break;
                case 2:
                    a2.push_back(main[i]);
                    break;
                case 3:
                    a3.push_back(main[i]);
                    break;
                case 4:
                    a4.push_back(main[i]);
                    break;
                case 5:
                    a5.push_back(main[i]);
                    break;
                case 6:
                    a6.push_back(main[i]);
                    break;
                case 7:
                    a7.push_back(main[i]);
                    break;
                case 8:
                    a8.push_back(main[i]);
                    break;
                case 9:
                    a9.push_back(main[i]);
                    break;     
            }
        }
        for(int i = 0; i < main.size(); i++) {
            if(!a0.empty()) main[i] = a0.pop_front();
            else if(a1.empty()) main[i] = a1.pop_front();
            else if(a2.empty()) main[i] = a2.pop_front();
            else if(a3.empty()) main[i] = a3.pop_front();
            else if(a4.empty()) main[i] = a4.pop_front();
            else if(a5.empty()) main[i] = a5.pop_front();
            else if(a6.empty()) main[i] = a6.pop_front();
            else if(a7.empty()) main[i] = a7.pop_front();
            else if(a8.empty()) main[i] = a8.pop_front();
            else if(a9.empty()) main[i] = a9.pop_front();
        }
    }

    for(int i = 0; i < main.size(); i++)
    {
        std::cout << main[i].key.country << " " << main[i].key.region << " " << main[i].key.main;
    }
    return 0;
}