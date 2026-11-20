#include "cargo.hpp"

#include <iostream>

namespace courier
{

    Cargo::Cargo()
    {
        std::cout << "[Конструктор Cargo] Создан груз по умолчанию: " << m_description << "\n";
    }

    Cargo::Cargo(std::string_view description, double weight, double declaredValue, bool isFragile)
        : m_description{ description }
        , m_isFragile{ isFragile }
    {
        if (weight <= 0.0)
        {
            std::cout << "[Ошибка Cargo] Вес должен быть больше 0! Установлено значение 1.0 кг.\n";
            m_weight = DEFAULT_WEIGHT;
        }
        else
        {
            m_weight = weight;
        }

        if (declaredValue < 0.0)
        {
            std::cout << "[Ошибка Cargo] Ценность не может быть отрицательной! Установлено 0.\n";
            m_declaredValue = 0.0;
        }
        else
        {
            m_declaredValue = declaredValue;
        }

        std::cout << "[Конструктор Cargo] Создан груз: \"" << m_description << "\" (" << m_weight << " кг)\n";
    }

    Cargo::~Cargo()
    {
        std::cout << "[Деструктор Cargo] Уничтожен груз: \"" << m_description << "\"\n";
    }

    bool Cargo::UpdateDeclaredValue(double newValue)
    {
        if (m_isInTransit && newValue > m_declaredValue)
        {
            std::cout << "[Отказ Cargo] Нельзя повысить объявленную ценность груза \"" << m_description
                << "\", так как он уже в пути!\n";
            return false;
        }

        if (newValue < 0.0)
        {
            std::cout << "[Отказ Cargo] Ценность не может быть отрицательной.\n";
            return false;
        }

        m_declaredValue = newValue;
        std::cout << "[Cargo] Новая объявленная ценность груза \"" << m_description << "\": " << m_declaredValue << " руб.\n";
        return true;
    }

    void Cargo::MarkAsInTransit()
    {
        m_isInTransit = true;
    }

    void Cargo::PrintInfo() const
    {
        std::cout << "  Груз: " << m_description
            << " | Вес: " << m_weight << " кг"
            << " | Ценность: " << m_declaredValue << " руб."
            << " | Хрупкий: " << (m_isFragile ? "Да" : "Нет") << "\n";
    }

} // namespace courier
