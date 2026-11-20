#pragma once

#include <string>
#include <string_view>

namespace courier
{

    class Courier
    {
    public:
        enum class VehicleType
        {
            eFoot,
            eBicycle,
            eMotorcycle,
            eCar
        };

    private:
        static constexpr auto DEFAULT_NAME = "Неизвестный курьер";
        static constexpr double DEFAULT_CAPACITY = 10.0;

        std::string m_name{ DEFAULT_NAME };
        VehicleType m_vehicleType{ VehicleType::eFoot };
        double m_maxCapacity{ DEFAULT_CAPACITY };
        double m_currentLoad{ 0.0 };
        bool m_isShiftOpen{ false };

    public:
        Courier();
        Courier(std::string_view name, VehicleType vehicleType, double maxCapacity);
        ~Courier();

        bool OpenShift();
        void CloseShift();
        bool TryAddLoad(double weight);
        void RemoveLoad(double weight);
        void PrintStatus() const;

        [[nodiscard]] std::string_view GetName() const
        {
            return m_name;
        }

        [[nodiscard]] double GetAvailableCapacity() const
        {
            return m_maxCapacity - m_currentLoad;
        }

        [[nodiscard]] bool GetIsShiftOpen() const
        {
            return m_isShiftOpen;
        }

        [[nodiscard]] std::string_view GetVehicleTypeStr() const;
    };

} // namespace courier
