#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <type_traits>
#include <cassert>

template <typename Key, typename Value, typename F>
void update(std::map<Key, Value>& m, F foo) {
    for (auto& pair : m) {
        pair.second = foo(pair.first);
    }
}
template <typename Key, typename Value>
auto fetch(std::map<Key, Value>& m, Key& k){
    auto it = m.find(k);
    if (it == m.end())
        throw std::out_of_range("Key not found in map");
    return it->second;
}

template <typename... Args>
constexpr auto average(Args&&... args) {
    static_assert((std::is_arithmetic_v<std::decay_t<Args>> && ...), 
                  "average() only accepts arithmetic types (int, float, double, etc.)");
    const auto sum = (std::forward<Args>(args) + ...);

    const auto count = sizeof...(Args);

    if (count == 0) {
        std::cerr << "Warning: average() called with 0 arguments!" << std::endl;
        return decltype(sum){0};
    }
    
    return static_cast<double>(sum) / count;
}

template <typename T>
size_t  my_hash(const T& x){
    return std::hash<T>{}(x);
}

int main() {
    std::map<std::string, long long int> m{
        {"a", 1}, {"b", 2}, {"c", 3}
    };
    
    update(m, [](const std::string& key) { 
        return static_cast<long long int>(std::hash<std::string>{}(key));
    });
    
    for (auto&& [key, value] : m) {
        std::cout << key << ":" << value << std::endl;
    }
    std::string str = "b";
    auto x = fetch(m, str);
    std::cout << str << " : " << x << std::endl;

    std::string key = "a";
    m[key] = my_hash(key);
    auto val = fetch(m, key);
    auto hash_val = my_hash(val);
    auto hash_hash_val = my_hash(hash_val);
    auto hash_hash_hash_val = my_hash(hash_hash_val);
    assert((val = hash_hash_val) && (hash_val == hash_hash_hash_val));
        std::cout << "val = hash_hash_val" << " and " << "hash_val == hash_hash_hash_val" << std::endl;
    std::cout << average(1, 2, 3, 4, 5, 100.0) << std::endl;
    std::cout << average(2, 3, 4, 5, 6, 200.0) << std::endl;
    std::cout << "OK" << std::endl;
    return 0;
}
