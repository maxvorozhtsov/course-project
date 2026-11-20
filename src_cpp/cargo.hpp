#pragma once

#include <string>
#include <string_view>

namespace courier
{

    class Cargo
    {
    private:
        static constexpr auto DEFAULT_DESC = "Стандартная посылка";
        static constexpr double DEFAULT_WEIGHT = 1.0;
        static constexpr double DEFAULT_VALUE = 100.0;

        std::string m_description{ DEFAULT_DESC };
        double m_weight{ DEFAULT_WEIGHT };
        double m_declaredValue{ DEFAULT_VALUE };
        bool m_isFragile{ false };
        bool m_isInTransit{ false };

    public:
        Cargo();
        Cargo(std::string_view description, double weight, double declaredValue, bool isFragile);
        ~Cargo();

        bool UpdateDeclaredValue(double newValue);
        void MarkAsInTransit();
        void PrintInfo() const;

        [[nodiscard]] double GetWeight() const
        {
            return m_weight;
        }

        [[nodiscard]] double GetDeclaredValue() const
        {
            return m_declaredValue;
        }

        [[nodiscard]] bool GetIsFragile() const
        {
            return m_isFragile;
        }

        [[nodiscard]] std::string_view GetDescription() const
        {
            return m_description;
        }
    };

} // namespace courier
