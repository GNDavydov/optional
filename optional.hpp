// Copyright 2021 GNDavydov

#ifndef INCLUDE_OPTIONAL_HPP_
#define INCLUDE_OPTIONAL_HPP_

#include <type_traits>
#include <memory>


namespace optional {
    template<class T>
    class optional {
    private:
        using Storage = std::aligned_storage_t<sizeof(T), alignof(T)>;
        Storage storage_;
        bool valid_;

    public:
        constexpr optional() noexcept: storage_(), valid_(false) {}

        explicit constexpr optional(const T &obj) : storage_(), valid_(false) {
            new(&storage_) T(obj);
            valid_ = true;
        }

        explicit constexpr optional(T &&obj) noexcept: storage_(), valid_(false) {
            new(&storage_) T(std::move(obj));
            valid_ = true;
        }

        explicit constexpr optional(std::nullopt_t) noexcept: storage_(), valid_(false) {}

        constexpr optional(const optional &copy) : storage_(), valid_(copy.valid_) {
            if (copy.valid_) new(&storage_) T(*copy);
        }

        constexpr optional(optional &&move) noexcept: storage_(), valid_(move.valid_) {
            if (move.valid_) {
                new(&storage_) T(std::move(*move));
                move.valid_ = false;
            }
        }

        optional &operator=(const optional &copy) {
            if (this == &copy) return *this;

            if (valid_) {
                if (copy.valid_) **this = *copy;
                else (**this).~T();
            } else {
                if (copy.valid_) new(&storage_) T(*copy);
            }

            valid_ = copy.valid_;
            return *this;
        }

        optional &operator=(optional &&move) noexcept {
            if (this == &move) return *this;

            if (valid_) {
                if (move.valid_) **this = std::move(*move);
                else (**this).~T();
            } else {
                if (move.valid_) new(&storage_) T(std::move(*move));
            }

            valid_ = move.valid_;
            move.valid_ = false;
            return *this;
        }

        optional &operator=(const T &obj) {
            if (valid_) **this = obj;
            else new(&storage_) T(obj);

            valid_ = true;
            return *this;
        }

        optional &operator=(T &&obj) noexcept {
            if (valid_) **this = std::move(obj);
            else new(&storage_) T(std::move(obj));

            valid_ = true;
            return *this;
        }

        T &operator*() {
            return *static_cast<T *>(static_cast<void *>(&storage_));
        }

        T *operator->() {
            return static_cast<T *>(static_cast<void *>(&storage_));
        }

        const T &operator*() const {
            return *static_cast<const T *>(static_cast<const void *>(&storage_));
        }

        const T *operator->() const {
            return static_cast<const T *>(static_cast<const void *>(&storage_));
        }

        explicit operator bool() const {
            return valid_;
        }

        T &value() {
            if (!valid_) throw std::runtime_error("bad optional access");

            return **this;
        }

        const T &value() const {
            if (!valid_) throw std::runtime_error("bad optional access");

            return **this;
        }

        template<class U>
        T value_or(U &&default_value) {
            return bool(*this) ? **this : static_cast<T>(std::forward<U>(default_value));
        }

        ~optional() noexcept {
            if (valid_) (**this).~T();
        }
    };
}


#endif //INCLUDE_OPTIONAL_HPP_
