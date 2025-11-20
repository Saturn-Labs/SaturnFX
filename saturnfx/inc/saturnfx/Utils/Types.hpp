#pragma once
#include <map>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <unordered_map>
#include <vector>
#include <string>
#include <utility>
#include <concepts>
#include <functional>

template <typename T>
using Ref = std::shared_ptr<T>;
template <typename T, typename... Args>
requires std::constructible_from<T, Args...>
Ref<T> makeRef(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

template <typename T>
using Weak = std::weak_ptr<T>;

template <typename T>
using Unique = std::unique_ptr<T>;
template <typename T, typename... Args>
requires std::constructible_from<T, Args...>
Unique<T> makeUnique(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

using i8 = char;
using i16 = short;
using i32 = int;
using i64 = long long;
using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;
using f32 = float;
using f64 = double;
using usize = std::size_t;
using CString = const char*;
using WString = std::wstring;
using String = std::string;
template <typename T>
using Vector = std::vector<T>;
template <typename TKey, typename TValue>
using Map = std::map<TKey, TValue>;
template <typename TKey, typename TValue>
using Pair = std::pair<TKey, TValue>;
template <typename TKey, typename TValue>
using UnorderedMap = std::unordered_map<TKey, TValue>;
using Mutex = std::mutex;
using SharedMutex = std::shared_mutex;
template <typename T = std::mutex>
using LockGuard = std::lock_guard<T>;
template <typename T>
using UniqueLock = std::unique_lock<T>;
template <typename T>
using SharedLock = std::shared_lock<T>;
template <typename T>
using Atomic = std::atomic<T>;
template <typename T>
using Function = std::function<T>;
template <typename T>
using ReferenceWrapper = std::reference_wrapper<T>;