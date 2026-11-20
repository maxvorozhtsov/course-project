#include "courier.hpp"

#include <iostream>

namespace courier
{

    Courier::Courier()
    {
        std::cout << "[Конструктор Courier] Создан курьер по умолчанию: " << m_name << "\n";
    }

    Courier::Courier(std::string_view name, VehicleType vehicleType, double maxCapacity)
        : m_name{ name }
        , m_vehicleType{ vehicleType }
    {
        if (maxCapacity <= 0.0)
        {
            std::cout << "[Ошибка Courier] Грузоподъёмность должна быть > 0. Установлено 10 кг.\n";
            m_maxCapacity = DEFAULT_CAPACITY;
        }
        else
        {
            m_maxCapacity = maxCapacity;
        }

        std::cout << "[Конструктор Courier] Нанят курьер: " << m_name << " (" << GetVehicleTypeStr()
            << ", макс. " << m_maxCapacity << " кг)\n";
    }

    Courier::~Courier()
    {
        std::cout << "[Деструктор Courier] Удалён объект курьера: " << m_name << "\n";
    }

    bool Courier::OpenShift()
    {
        if (m_isShiftOpen)
        {
            std::cout << "[Отказ Courier] У курьера " << m_name << " уже открыта активная смена!\n";
            return false;
        }

        m_isShiftOpen = true;
        std::cout << "[Courier] Курьер " << m_name << " открыл рабочую смену.\n";
        return true;
    }

    void Courier::CloseShift()
    {
        if (m_currentLoad > 0.0)
        {
            std::cout << "[Отказ Courier] Нельзя закрыть смену: у курьера " << m_name
                << " ещё есть груз на руках (" << m_currentLoad << " кг)!\n";
            return;
        }

        m_isShiftOpen = false;
        std::cout << "[Courier] Курьер " << m_name << " закрыл рабочую смену.\n";
    }

    bool Courier::TryAddLoad(double weight)
    {
        if (!m_isShiftOpen)
        {
            std::cout << "[Отказ Courier] Курьер " << m_name << " не на смене!\n";
            return false;
        }

        if (m_currentLoad + weight > m_maxCapacity)
        {
            std::cout << "[Отказ Courier] Перегруз! Курьер " << m_name << " (" << GetVehicleTypeStr()
                << ") может взять ещё только " << GetAvailableCapacity() << " кг, а груз весит " << weight << " кг.\n";
            return false;
        }

        m_currentLoad += weight;
        std::cout << "[Courier] Курьер " << m_name << " принял груз (" << weight << " кг). Текущая загрузка: "
            << m_currentLoad << "/" << m_maxCapacity << " кг.\n";
        return true;
    }

    void Courier::RemoveLoad(double weight)
    {
        m_currentLoad -= weight;
        if (m_currentLoad < 0.0)
        {
            m_currentLoad = 0.0;
        }
    }

    void Courier::PrintStatus() const
    {
        std::cout << "Курьер: " << m_name << " | Транспорт: " << GetVehicleTypeStr()
            << " | Смена: " << (m_isShiftOpen ? "Открыта" : "Закрыта")
            << " | Загрузка: " << m_currentLoad << "/" << m_maxCapacity << " кг\n";
    }

    std::string_view Courier::GetVehicleTypeStr() const
    {
        switch (m_vehicleType)
        {
        case VehicleType::eFoot:
            return "Пеший";
        case VehicleType::eBicycle:
            return "Велосипед";
        case VehicleType::eMotorcycle:
            return "Мотоцикл";
        case VehicleType::eCar:
            return "Автомобиль";
        default:
            return "Неизвестно";
        }
    }

} // namespace courier
