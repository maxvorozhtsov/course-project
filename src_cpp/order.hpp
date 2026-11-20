#pragma once

#include "cargo.hpp"
#include "courier.hpp"

#include <cstdint>
#include <string>
#include <string_view>

namespace courier
{

    class Order
    {
    public:
        using IdType = std::uint32_t;

        enum class Status
        {
            eAccepted,
            eAssigned,
            eInTransit,
            eDelivered
        };

    private:
        static constexpr auto DEFAULT_ADDRESS = "Не указан";

        IdType m_orderId{ 0 };
        std::string m_deliveryAddress{ DEFAULT_ADDRESS };
        Status m_status{ Status::eAccepted };
        Cargo m_cargo{};
        Courier* m_courier{ nullptr };

    public:
        Order();
        Order(IdType id, std::string_view address, std::string_view cargoDesc, double weight, double value, bool fragile);
        ~Order();

        bool AssignCourier(Courier* courier);
        bool StartDelivery();
        bool CompleteDelivery(bool recipientConfirmed);
        bool TryRaiseCargoValue(double newValue);
        void PrintOrderDetails() const;

        [[nodiscard]] IdType GetOrderId() const
        {
            return m_orderId;
        }

        [[nodiscard]] std::string_view GetStatusStr() const;
    };

} // namespace courier
