#include "order.hpp"

#include <iostream>

namespace courier
{

    Order::Order()
    {
        std::cout << "[Конструктор Order] Создан пустой заказ №0\n";
    }

    Order::Order(IdType id, std::string_view address, std::string_view cargoDesc, double weight, double value, bool fragile)
        : m_orderId{ id }
        , m_deliveryAddress{ address }
        , m_cargo{ cargoDesc, weight, value, fragile }
    {
        std::cout << "[Конструктор Order] Оформлен заказ №" << m_orderId << " по адресу: " << m_deliveryAddress << "\n";
    }

    Order::~Order()
    {
        std::cout << "[Деструктор Order] Заказ №" << m_orderId << " удаляется из системы.\n";
    }

    bool Order::AssignCourier(Courier* courier)
    {
        if (courier == nullptr)
        {
            std::cout << "[Отказ Order] Передан пустой указатель на курьера.\n";
            return false;
        }

        if (m_status != Status::eAccepted)
        {
            std::cout << "[Отказ Order] Заказ №" << m_orderId << " нельзя назначить, его текущий статус: " << GetStatusStr() << "\n";
            return false;
        }

        if (!courier->TryAddLoad(m_cargo.GetWeight()))
        {
            std::cout << "[Order] Назначение заказа №" << m_orderId << " курьеру " << courier->GetName() << " отклонено.\n";
            return false;
        }

        m_courier = courier;
        m_status = Status::eAssigned;
        std::cout << "[Order] Заказ №" << m_orderId << " успешно назначен курьеру " << m_courier->GetName() << ".\n";
        return true;
    }

    bool Order::StartDelivery()
    {
        if (m_status != Status::eAssigned || m_courier == nullptr)
        {
            std::cout << "[Отказ Order] Нельзя начать доставку заказа №" << m_orderId << ": не назначен курьер.\n";
            return false;
        }

        m_status = Status::eInTransit;
        m_cargo.MarkAsInTransit();
        std::cout << "[Order] Заказ №" << m_orderId << " передан курьеру и теперь В ПУТИ.\n";
        return true;
    }

    bool Order::CompleteDelivery(bool recipientConfirmed)
    {
        if (m_status != Status::eInTransit)
        {
            std::cout << "[Отказ Order] Нельзя завершить заказ №" << m_orderId << ", так как он не в пути.\n";
            return false;
        }

        if (!recipientConfirmed)
        {
            std::cout << "[Отказ Order] Нельзя закрыть заказ №" << m_orderId << " без подтверждения получения от адресата!\n";
            return false;
        }

        m_status = Status::eDelivered;
        if (m_courier != nullptr)
        {
            m_courier->RemoveLoad(m_cargo.GetWeight());
        }

        std::cout << "[Order] Заказ №" << m_orderId << " успешно ДОСТАВЛЕН по адресу: " << m_deliveryAddress << "\n";
        return true;
    }

    bool Order::TryRaiseCargoValue(double newValue)
    {
        return m_cargo.UpdateDeclaredValue(newValue);
    }

    void Order::PrintOrderDetails() const
    {
        std::cout << "=== Заказ №" << m_orderId << " [" << GetStatusStr() << "] ===\n"
            << "  Адрес: " << m_deliveryAddress << "\n"
            << "  Курьер: " << (m_courier != nullptr ? m_courier->GetName() : "Не назначен") << "\n";
        m_cargo.PrintInfo();
    }

    std::string_view Order::GetStatusStr() const
    {
        switch (m_status)
        {
        case Status::eAccepted:
            return "Принят";
        case Status::eAssigned:
            return "Назначен";
        case Status::eInTransit:
            return "В пути";
        case Status::eDelivered:
            return "Доставлен";
        default:
            return "Неизвестно";
        }
    }

} // namespace courier
